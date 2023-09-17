#include <stdio.h>

#define ZARGS_IMPLEMENTATION
#include "src/zargs.h"

int main(int argc, char **argv){
    
    MZ_SRAND();

    char* prog_file_name = za_next_arg(&argc, &argv);

    za_parse_args(prog_file_name, &argc, &argv);

    return 0;
}