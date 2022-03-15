/**
 * @file ppm.c
 * @author Samuel Stolarik (xstola03@stud.fit.vutbr.cz), FIT
 * 
 * @brief IJC-DU1, part B
 * implementation of functions defined in ppm.h header file
 * Used compiler: gcc (GCC) 11.2.0
 * 
 * @date 2022-03-03
 */



#include "ppm.h"
#include "error.h"

#define _HEADER_MAX 50 //maximum lenght of the header after deleting consequent white spaces
#define _HEADER_WORDS 4 //expected number of word in the header

//---prototypes of the auxiliary functions used in this module---
static bool get_p6_header(FILE * file, unsigned * xsize, unsigned * ysize);
static bool check_p6_header(char * header, unsigned * x, unsigned * y);


struct ppm * ppm_read(const char * filename)
{
    FILE * ppm_file = fopen(filename, "r");
    if (ppm_file == NULL)
    {
        warning_msg("File was not open successfully.\n");
        return NULL;
    }

    ppm_t * picture = malloc(sizeof(ppm_t));
    if (picture == NULL)
    {
        warning_msg("Ran out of space while allocating for ppm struct.\n");
        goto error_handling1;
    }

    if (get_p6_header(ppm_file, &(picture -> xsize), &(picture -> ysize)) == false)
    {
        warning_msg("Header not formated correctly.\n");
        goto error_handling2;
    }

    const unsigned pic_size = RGB_PARTS * (picture -> xsize) * (picture -> ysize); 
    picture = realloc (picture, sizeof(ppm_t) + pic_size);

    int c;
    unsigned read_bytes = 0;
    while((c = getc(ppm_file)) != EOF)
    {
        picture -> data[read_bytes++] = c;
    }

    fclose(ppm_file);
    return picture;

    error_handling2:
    free(picture);

    error_handling1:
    fclose(ppm_file);
    
    return NULL;
}

void ppm_free(struct ppm *p)
{
    free(p);
}



//------auxiliary functions only for this module-----

/**
 * @brief Get the file header in P6 format without comments
 * and store picture size in "xsize" and "ysize"
 * 
 * @param file 
 * @param xsize 
 * @param ysize 
 * @return true 
 * @return false 
 */
static bool get_p6_header(FILE * file, unsigned * xsize, unsigned * ysize)
{
    char header[_HEADER_MAX] = {0};
    int c, word_count = 0, read_chars = 0;
    bool in_word = false;
    char delim = ' ';

    //reads only the "_HEADER_WORDS" first words from the file and separates them with "delim"
    while((c = getc(file)) != EOF)
    {
        switch (in_word)
        {
        //in word already
        case true:
            if (!isspace(c))
            {
                header[read_chars++] = c;
                break;
            }

            if (isspace(c))
            {
                if (word_count == _HEADER_WORDS)
                {
                    //deal with all remaining white spaces after reading all information from header;
                    int s;
                    while (isspace(s = getc(file)))
                    ;
                    ungetc(s, file);
                    goto finished_reading_header;
                }
                header[read_chars++] = delim;
                in_word = false;
            }
            
            break;
        //not in word
        case false:
            if (!isspace(c))
            {
                in_word = true;
                word_count++;

                if (word_count > _HEADER_WORDS)
                {
                    goto finished_reading_header;
                    break;
                }
                header[read_chars++] = c;
            }
            break;
        }
    }
    
    finished_reading_header:
    if (word_count != _HEADER_WORDS)
    {
        return false;
    }
    //check if header is formated correctly and if x and y sizes are correct
    if (check_p6_header(header, xsize, ysize)){
        return true;
    }
    
    //the function will get here only in case of incorrect header format
    fclose(file);
    error_exit("Incorect format.\n");
}

/**
 * @brief check correctness of the P6 file header with color 255 given in argument "header"
 * and store picture sizes from header into "x" and "z"
 * 
 * @param header 
 * @param x 
 * @param y 
 * @return true 
 * @return false 
 */
static bool check_p6_header(char * header, unsigned * x, unsigned * y)
{
    const char * format = "P6";
    if (strncmp(format, strtok(header, " "), 2) != 0)
    {
        // warning_msg("File not starting with format \"P6\".\n");
        return false;
    }
    unsigned long tmp_x = strtoul(strtok(NULL, " "),NULL, 10);
    unsigned long tmp_y = strtoul(strtok(NULL, " "), NULL, 10);

    //first checking if picture size in the header can be fit into unsigned int
    if (tmp_x > UINT_MAX || tmp_y > UINT_MAX)
    {
        // warning_msg("Picture dimensions are more than limit. Max size: %d x %d.\n", X_MAX, Y_MAX);
        return false;        
    }

    *x = (unsigned int)tmp_x;
    *y = (unsigned int)tmp_y;

    if (*x > X_MAX || *y > Y_MAX)
    {
        // warning_msg("Picture dimensions are more than limit. Max size: %d x %d.\n", X_MAX, Y_MAX);
        return false;
    }
    const char * color = "255";
    if (strncmp(color, strtok(NULL, " "), 3) != 0)
    {
        // warning_msg("Color value in the header not supported. Only supports: %d.\n", _PPM_COLOR);
        return false;
    }
    
    return true;
}