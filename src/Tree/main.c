#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tree.h"

int main(int argc, char **argv) {
    d_t test = createTree();
    test = NULL;
    FILE *in = fopen(argv[1], "r");
    char x;

    test = charCounter(in, test, true);
    readTree(test);
    freeTree(test);




}