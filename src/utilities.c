/**
 * @file utilities.c
 * @author M. Skocic
 * @brief Functions for assiting computation
 * @date 2021/04/27
 *
 * Provides functions for assisting the main computations.
 */

#include "utilities.h"

 /**
 * @brief Round with n decimals
 * @param x Value to be rounded
 * @param p Number of significant digits
 * @return Rounded x
 */
double roundn(double x, int p){

    double fac, logx, n;
    logx = floor(log10(fabs(x)));

    n = logx + 1 - p;

    fac = pow(10, n);


    return round(x / fac) * fac;

}

/**
 * @brief Find the index of an item in a list of strings.
 * @param item Item to be found in list.
 * @param list List of strings.
 * @param size Size of the list.
 * @return index >0 if item was found or -1 if not found.
 */
int find(char *item, char **list, int size)
{
    int i;
    int index=-1;
    for (i=0;i<size;i++)
    {

        if (strcmp(list[i], item)==0)
        {
            index = i;
            break;

        }

    }
    return index;
}
