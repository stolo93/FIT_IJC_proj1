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

   
    char format[3];
    unsigned color = 0;
    
    //reading file header
    if (fscanf(ppm_file, "%3s %u %u %u ", format, &(picture -> xsize), &(picture -> ysize), &color) != 4)
    {
        warning_msg("Header not formated correctly.\n");
        goto error_handling2;
    }

    //checking file header atributes 
    if (color != 255 && strncmp(format, "P6\0", 3) != 0)
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
