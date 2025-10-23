#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //check the command line argument
    if(argc != 2)
    {
        printf("Usage: ./recover the name of the image file\n");
        return 1;
    }

    //open file
    FILE *input = fopen(argv[1],"r");
    if(input == NULL)
    {
        printf("Couldn't open the file\n");
        return 1;
    }

    //create memory for fread
    unsigned char block[512];
    #define BLOCK_SIZE 512

    int filecount = 0;
    char filename[8];
    FILE *pfile = NULL;

    //check if fread finished reading the data
    while(fread(block, sizeof(block), 1, input) != 0)
    {
        //check if it is a new file
        if(block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            if(pfile != NULL)
            {
                fclose(pfile);
            }

            sprintf(filename, "%03i.jpg", filecount);
            pfile = fopen(filename, "w");

            filecount++;
        }

        //write the data 
        if(pfile != NULL)
        {
            fwrite(block, sizeof(block), 1, pfile);
        }
    }

    if (pfile != NULL)
    {
        fclose(pfile);
    }

    fclose(input);
}
