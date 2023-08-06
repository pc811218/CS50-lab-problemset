#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);
// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(header.chunkID, sizeof(uint8_t), 4, input);
    fread(&header.chunkSize, sizeof(uint32_t), 1, input);
    fread(header.format, sizeof(uint8_t), 4, input);
    fread(header.subchunk1ID, sizeof(uint8_t), 4, input);
    fread(&header.subchunk1Size, sizeof(uint32_t), 1, input);
    fread(&header.audioFormat, sizeof(uint16_t), 1, input);
    fread(&header.numChannels, sizeof(uint16_t), 1, input);
    fread(&header.sampleRate, sizeof(uint32_t), 1, input);
    fread(&header.byteRate, sizeof(uint32_t), 1, input);
    fread(&header.blockAlign, sizeof(uint16_t), 1, input);
    fread(&header.bitsPerSample, sizeof(uint16_t), 1, input);
    fread(header.subchunk2ID, sizeof(uint8_t), 4, input);
    fread(&header.subchunk2Size, sizeof(uint32_t), 1, input);

    // printf("header.chunkID: %x \n",header.chunkID[0]);
    // printf("header.chunkID: %x \n",header.chunkID[1]);
    // printf("header.chunkID: %x \n",header.chunkID[2]);
    // printf("header.chunkID: %x \n",header.chunkID[3]);
    // printf("header.chunkSize: %x \n",header.chunkSize);
    // printf("header.format: %x \n",header.format[0]);
    // printf("header.format: %x \n",header.format[1]);
    // printf("header.format: %x \n",header.format[2]);
    // printf("header.format: %x \n",header.format[3]);
    // printf("header.subchunk2Size: %x \n",header.subchunk2Size);
    // printf("header.numChannels: %x \n",header.numChannels);
    // printf("header.bitsPerSample (10): %i \n",header.bitsPerSample);
    // printf("header.bitsPerSample (sizeof): %lu \n",sizeof(header.bitsPerSample));

    // Use check_format to ensure WAV format
    // TODO #4
    if(!check_format(header)) {
        printf("Not a WAV file.\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(header.chunkID, sizeof(uint8_t), 4, output);
    fwrite(&header.chunkSize, sizeof(uint32_t), 1, output);
    fwrite(header.format, sizeof(uint8_t), 4, output);
    fwrite(header.subchunk1ID, sizeof(uint8_t), 4, output);
    fwrite(&header.subchunk1Size, sizeof(uint32_t), 1, output);
    fwrite(&header.audioFormat, sizeof(uint16_t), 1, output);
    fwrite(&header.numChannels, sizeof(uint16_t), 1, output);
    fwrite(&header.sampleRate, sizeof(uint32_t), 1, output);
    fwrite(&header.byteRate, sizeof(uint32_t), 1, output);
    fwrite(&header.blockAlign, sizeof(uint16_t), 1, output);
    fwrite(&header.bitsPerSample, sizeof(uint16_t), 1, output);
    fwrite(header.subchunk2ID, sizeof(uint8_t), 4, output);
    fwrite(&header.subchunk2Size, sizeof(uint32_t), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);

    //initial input cursor to last sample
    fseek(input, 0L, SEEK_END);
    long file_size = ftell(input);

    printf("ftell : %ld \n",file_size);
    printf("subchunk2Size : %u \n",header.subchunk2Size);
    fseek(input, block_size * -1, SEEK_CUR);

    // Write reversed audio to file
    // TODO #8

    //store 4 bytes for 1 sample * 2 Channels
    uint32_t buffer;

    while (ftell(input) >= HEADER_SIZE) {

        fread(&buffer, sizeof(buffer), 1, input);
        fwrite(&buffer, sizeof(buffer), 1, output);

        //back 2 block because fread will foward 1 block
        fseek(input, block_size * 2 * -1, SEEK_CUR);
    }



    fclose(input);
    fclose(output);

}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == 0x57 && header.format[1] == 0x41 && header.format[2] == 0x56 && header.format[3] == 0x45) {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7

    return sizeof(header.bitsPerSample) * header.numChannels;
}