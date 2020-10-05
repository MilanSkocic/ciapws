/**
 *@file main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iapws.h"
#include "main.h"

static char help[] = "usage: iapws [option] [<gas>] [<temperature>]\n"
        "\t IAPWS Computation of solubility in water.\n"
        "\t Supported gases in water: He, Ne, Ar, Kr, Xe, H2, N2, O2, CO, CO2, H2S, CH4, C2H6, SF6.\n"
        "\t Supported gases in heavywater: He, Ne, Ar, Kr, Xe, D2, CH4\n"
        "Arguments:\n"
        "    gas\t\t gas for the computation [default: O2]\n"
        "    temperature\t temperature in degree Celsius for the computation [default 25.0]\n"
        "Options:\n"
        "    -p, --print\t print coefficients\n"
        "    -h, --help\t help\n\n";

/**
 * \brief Start program.
 *
 * Usage: iapws GAS TEMPERATURE [SOLVENT] [PRINT]
 *
 * IAPWS Computation of solubility in H2O and in D2O.
 *
 * Supported gases in water: He, Ne, Ar, Kr, Xe, H2, N2, O2, CO, CO2, H2S, CH4, C2H6, SF6.\n
 *
 * \return EXIT_SUCCESS.
 */
int main(int argc, char **argv)
{
    //initialization
    int i=0, ix=0, j=0, run = 1;
    int stringlen = 32;
    char default_gas[] = "O2";
    char default_temp[] = "25.0";

    // options
    int n_options = 5;
    char **option_keys = (char **) calloc(n_options, sizeof(char *));
    for (i=0; i<n_options; i++)
    {
        option_keys[i] = (char *) calloc(1, (stringlen+1)*sizeof(char));
    }
    enum{D, P, PRINT, H, HELP};
    strcpy(option_keys[D], "-d");
    strcpy(option_keys[P], "-p");
    strcpy(option_keys[PRINT], "--print");
    strcpy(option_keys[H], "-h");
    strcpy(option_keys[HELP], "--help");
    int *option_values = (int *) calloc(n_options, sizeof(int));


    // positional arguments
    int nargs = 2;
    char **args = (char **) calloc(nargs, sizeof(char *));
    for (i=0; i<n_options; i++)
    {
        args[i] = (char *) calloc(1, (stringlen+1)*sizeof(char));
    }
    enum{GAS, TEMP};
    strcpy(args[GAS], default_gas);
    strcpy(args[TEMP], default_temp);

    for (i=0; i<argc; i++)
    {
        if (i)
        {
            ix = find(argv[i], option_keys, n_options);
            if (ix>=0)
            {
                option_values[ix] = 1;
            }
            else
            {
                if (j<nargs)
                {
                    strcpy(args[j], argv[i]);
                    j = j + 1;
                }
            }
        }
    }

    if (argc == 1)
    {
        printf("%s", help);
    }

    if (option_values[H]|option_values[HELP])
    {
    option_values[H] = 1;
    option_values[HELP] = 1;
    printf("%s", help);
    run = 0;
    }
    if (option_values[P]|option_values[PRINT])
    {
    option_values[P] = 1;
    option_values[PRINT] = 1;
    run = 1;
    }

    if (run)
    {
        solubility(args[GAS], strtod(args[TEMP], NULL), option_values[D], option_values[P]);
    }

    // Clean up pointers
    free(option_values);

    for (i=0; i<n_options; i++)
    {
        free(option_keys[i]);
    }
    free(option_keys);

    for (i=0; i<nargs; i++)
    {
        free(args[i]);
    }
    free(args);

    return 0;
}