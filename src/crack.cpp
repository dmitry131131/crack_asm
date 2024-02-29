#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "crack.h"

int cracker (const char* file_name)
{
    assert(file_name);

    FILE* input_file = fopen(file_name, "rb");
    if (!input_file)
    {
        printf("Open file error!\n");
        return 1;
    }

    if (fseek(input_file, 0, SEEK_END))
    {
        printf("Seek error!\n");
        return 1;
    }

    long int file_len = ftell(input_file);

    if (fseek(input_file, 0, SEEK_SET))
    {
        printf("Seek error!\n");
        return 1;
    }

    unsigned char* file_buffer = (unsigned char*) calloc((size_t) (file_len + 1), sizeof(int));

    if (!file_len)
    {
        printf("Calloc error!\n");
        return 1;
    }

    fread(file_buffer, sizeof(char), (size_t) file_len, input_file);

    const unsigned char new_file_segment[] =   {0x90, 0x90, 0x90, 0xba, 0xeb, 0x03, 0xe8, 0xbe, 0x02, 0xbf, 0xe0, 0x03, 0x90, 0x90, 0x90, 0x90,
                                                0x90, 0x90, 0xe8, 0x50, 0x02, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90};
    
    fclose(input_file);
    FILE* output_file = fopen(file_name, "wb");
    if (!output_file)
    {
        printf("Open file error!\n");
        return 1;
    }

    memcpy(file_buffer, new_file_segment, 32);

    file_buffer[746] = 0x11;

    fwrite(file_buffer, sizeof(char), (size_t) file_len, output_file);

    free(file_buffer);
    fclose(output_file);
    return 0;
}