#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    int data[22] = {3,4,5,2,3,1,4,1,2,5,1,1,3,2,1,1,1,2,3,3,2,2};
    fp = fopen("data.bin", "wb");
    for (int i=0; i<22; ++i)
        fwrite(&data[i], sizeof(int), 1, fp);
    return 0;
}

