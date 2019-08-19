# include "params.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Params::Params(int argc, char *argv[]) {
    Params();
    int i = 0;
    if ((i = ArgPos((char *) "-size", argc, argv)) > 0)
        layer1_size = atoi(argv[i + 1]);
    if ((i = ArgPos((char *) "-train", argc, argv)) > 0)
        strcpy(mTrainFile, argv[i + 1]);
    if ((i = ArgPos((char *) "-save-vocab", argc, argv)) > 0)
        strcpy(save_vocab_file, argv[i + 1]);
    if ((i = ArgPos((char *) "-read-vocab", argc, argv)) > 0)
        strcpy(read_vocab_file, argv[i + 1]);
    if ((i = ArgPos((char *) "-debug", argc, argv)) > 0)
        debug_mode = atoi(argv[i + 1]);
    if ((i = ArgPos((char *) "-binary", argc, argv)) > 0)
        binary = atoi(argv[i + 1]);
    if ((i = ArgPos((char *) "-cbow", argc, argv)) > 0)
        cbow = atoi(argv[i + 1]);

    if (cbow)
        alpha = 0.05;

    if ((i = ArgPos((char *) "-alpha", argc, argv)) > 0)
        alpha = atof(argv[i + 1]);
    if ((i = ArgPos((char *) "-output", argc, argv)) > 0)
        strcpy(output_file, argv[i + 1]);
    if ((i = ArgPos((char *) "-window", argc, argv)) > 0)
        window = atoi(argv[i + 1]);
    if ((i = ArgPos((char *) "-sample", argc, argv)) > 0)
        sample = atof(argv[i + 1]);
    if ((i = ArgPos((char *) "-hs", argc, argv)) > 0)
        hs = atoi(argv[i + 1]);
    if ((i = ArgPos((char *) "-negative", argc, argv)) > 0)
        negative = atoi(argv[i + 1]);
    if ((i = ArgPos((char *) "-threads", argc, argv)) > 0)
        num_threads = atoi(argv[i + 1]);
    if ((i = ArgPos((char *) "-iter", argc, argv)) > 0)
        iter = atoi(argv[i + 1]);
    if ((i = ArgPos((char *) "-min-count", argc, argv)) > 0)
        min_count = atoi(argv[i + 1]);
    if ((i = ArgPos((char *) "-classes", argc, argv)) > 0)
        classes = atoi(argv[i + 1]);


    mInstance = this;

}

int Params::ArgPos(char *str, int argc, char **argv) {

    int a = 0;
    for (a = 1; a < argc; a++)
        if (!strcmp(str, argv[a])) {
            if (a == argc - 1) {
                printf("Argument missing for %s\n", str);
                exit(1);
            }
            return a;
        }
    return -1;
}