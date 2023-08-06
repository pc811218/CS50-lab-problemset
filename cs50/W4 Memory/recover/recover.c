#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Number of bytes
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];

    // size_t header_ret = fread(&header, sizeof(uint8_t), BLOCK_SIZE, input);

    // printf("header_ret: %ld\n",header_ret);
    int file_count = 0;
    char filename[8];
    FILE *jpeg_file;

    bool isJPEGfound = false;

    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        //if find jpeg header
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {

            //close previous file
            if(isJPEGfound) {
                fclose(jpeg_file);
            }

            //JPEG found
            isJPEGfound = true;

            //open new file
            sprintf(filename,"%03i.jpg",file_count);
            jpeg_file = fopen(filename, "w");
            if (jpeg_file == NULL)
            {
                printf("Could not open file.\n");
                return 1;
            }
            file_count++;

            fwrite(buffer, 1, BLOCK_SIZE, jpeg_file);

        } else if (isJPEGfound) {
            fwrite(buffer, 1, BLOCK_SIZE, jpeg_file);
        }

    }

    // Close files
    fclose(raw_file);
    fclose(jpeg_file);
}
