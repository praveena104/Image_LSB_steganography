#ifndef DECODE_H
#define DECODE_H

#include "types.h" // Contains user defined types

/*
 * Structure to store information required for
 * encoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
 */

#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4

typedef struct _DecodeInfo
{
    /* Source Image info */
    char *stego_image_fname;
    FILE *fptr_stego_image;
    char image_data[MAX_IMAGE_BUF_SIZE];

    /* Secret File Info */
    char *secret_fname;
    FILE *fptr_secret;
    char extn_secret_file[MAX_FILE_SUFFIX];
    char secret_data[MAX_SECRET_BUF_SIZE];
    int size_secret_file;


}DecodeInfo;

/* Decoding function prototypes */

/* Check operation type */
OperationType check_operation_type(char *argv[]);

/* Read and validate Decode args from argv */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

/* Perform the decoding */
Status do_decoding(DecodeInfo *decInfo);

/* Get File pointers for i/p and o/p files */
Status Open_files(DecodeInfo *decInfo);

/* Decode the magic string from the stego image */
Status decode_magic_string(const char *magic_string, DecodeInfo *decInfo);

/* Decode secret file extenstion size*/
Status decode_secret_file_extn_size(int size, DecodeInfo *decInfo);

/* Decode the secret file extension */
Status decode_secret_file_extn(char *file_extn, DecodeInfo *decInfo);

/* Decode the secret file size */
Status decode_secret_file_size(int file_size, DecodeInfo *decInfo);

/* Decode the secret file data */
Status decode_secret_file_data(DecodeInfo *decInfo);

/* Decode function, which does the real decoding */
Status decode_data_from_image(char *data, int size, FILE *fptr_stego_image, FILE *fptr_secret);

/* Decode a byte from LSB of image data array */
Status decode_byte_from_lsb(char data, char *image_buffer);

/* Decode a size from LSB of image data array */
Status decode_size_from_lsb(int size, char *image_buffer);


#endif
