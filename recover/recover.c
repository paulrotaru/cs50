#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>


typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    // check argv to take only one argument
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    //open the image disk
    char *files = argv[1];
    FILE *inptr = fopen(files, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", files);
        return 2;
    }


    //create the buffer
    BYTE buffer[512];
    //create the output file
    char outputjpeg[8] = "000.jpg";
    //create counter for jpeg found
    int count_jpg = 0;
    //boolean var to check if is already copy
    bool copy = false;
    //create the output file pointer
    FILE *outptr = fopen(outputjpeg, "w");
    //check 512 bites packages into the buffer
    while(fread(buffer, 512, 1, inptr) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count_jpg != 0)
            {
            fclose(outptr);
            sprintf(outputjpeg, "%03i.jpg", count_jpg);
            outptr = fopen(outputjpeg, "w");
            }
        count_jpg ++;
        copy = true;
        }
        if (copy)
        {
        fwrite(buffer, 512, 1, outptr);
        }
    }
    fclose(inptr);
    fclose(outptr);
    return 0;


}