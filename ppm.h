/**
 * @file ppm.h
 * @author Samuel Stolarik (xstola03@stud.fit.vutbr.cz), FIT
 * 
 * @brief IJC-DU1, part B
 * header file defining data structures and functions for operating on .ppm files
 * 
 * @date 2022-03-03
 */

#ifndef _PPM_H
#define _PPM_H

#define X_MAX 8000
#define Y_MAX 8000
#define _PPM_COLOR 255

typedef struct ppm {
        unsigned xsize;
        unsigned ysize;
        char data[];    // RGB bajty, celkem 3*xsize*ysize
}ppm_t;

/**
 * @brief loads .ppm file
 * into dynamicaly allocated ppm struct which is then returned
 * 
 * if "filename" is of incorect file format error_warning is called and NULL is returned
 * @param filename 
 * @return struct ppm* 
 */
struct ppm * ppm_read(const char * filename);


/**
 * @brief frees memory allocated by ppm_read function
 * 
 * @param p 
 */
void ppm_free(struct ppm *p);

#endif //_PPM_H