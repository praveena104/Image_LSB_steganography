#include<stdio.h>
#include "decode.h"
#include "types.h"
#include "common.h"
#include <string.h>
#include <stdlib.h>
/* Function Definitions */
//function to read and validate args

Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)
{
//Check for stego.bmp file
if(strstr(argv[2], ".bmp") != NULL && strcmp(strstr(argv[2],"."),".bmp")==0)
{
        decInfo->stego_image_fname=argv[2];
}
else
{
        return e_failure;
}

//Check for extension file
if(argv[3]!=NULL)
{
        decInfo->secret_fname=argv[3];
        //strcpy(decInfo->extn_secret_file,strchr(argv[3],'.'));
}
else
{
        decInfo->secret_fname="decode_data.txt";
}
return e_success;
}

//Function definition for Decoding Magic string
Status decode_magic_string(const char *magic_string,DecodeInfo *decInfo)
{
    decode_data_from_image((char *)magic_string,strlen(magic_string),decInfo->fptr_stego_image,decInfo->fptr_secret);
    return e_success;
}
//Function definition for decode_data_from_image
Status decode_data_from_image(char *data, int size, FILE *fptr_stego_image, FILE *fptr_secret)
{
   char buffer[8];
   for(int i=0;i<size;i++)
   {
          fread(buffer,8,1,fptr_stego_image);
          
           decode_byte_from_lsb(data[i],buffer);
           fwrite(data,1,size,fptr_secret);
   }
   
   return e_success;
}
//Function definition for decode_byte_from_lsb
Status decode_byte_from_lsb(char data, char *image_buffer)
{
for(int i=0;i<8;i++)
{
    data |= ((image_buffer[i] & 0x01) << (7 - i));
    //ch=(buffer[i] & 0x01) | ch;
}
return e_success;
}
//Function definition for decode_size_from_lsb
Status decode_size_from_lsb(int size, char *image_buffer)
{
        //char ch,buffer[32];
  
for(int i=0;i<32;i++)
{
    size |= ((image_buffer[i] & 0x01) << (31 - i));
       // ch=(buffer[i] & 0x01) | ch;
}
return e_success;
}

//Funtion definition for decode_secret_file_extn_size
Status decode_secret_file_extn_size(int size, DecodeInfo *decInfo) {
    char buffer[32];
   fread(buffer, 32, 1, decInfo->fptr_stego_image);    
decode_size_from_lsb(size, buffer);
    return e_success;
}

//Funtion definition for decode_secret_file_extn
Status decode_secret_file_extn(char *file_extn, DecodeInfo *decInfo) 
{
    decode_data_from_image(file_extn, strlen(file_extn), decInfo->fptr_stego_image, decInfo->fptr_secret);
    return e_success;
}

//Funtion definition for decode_secret_file_size
Status decode_secret_file_size(int file_size, DecodeInfo *decInfo) 
{
    char buffer[32];
    fread(buffer, 32, 1, decInfo->fptr_stego_image);           
     decode_size_from_lsb(file_size, buffer);
    return e_success;
}

//Funtion definition for decode_secret_file_data
Status decode_secret_file_data(DecodeInfo *decInfo)
{
        char *buffer=malloc(decInfo->size_secret_file);
        if (buffer == NULL) 
        {
    // Handle allocation failure
          return e_failure;
        }
       fread(buffer, decInfo->size_secret_file, 1, decInfo->fptr_stego_image);
       
    decode_data_from_image(buffer,decInfo->size_secret_file,decInfo->fptr_stego_image,decInfo->fptr_secret);
    free(buffer);
        return e_success;
}


//Function call for decoding
Status do_decoding(DecodeInfo *decInfo)
{
        //Start decoding
        if(Open_files(decInfo)==e_success)
    {
                printf("Open file is successful\n");
        //Decode Magic String
         if(decode_magic_string(MAGIC_STRING,decInfo)==e_success)
         {
             printf("Decoded Magic String successfully\n");
             
                 //decode secret file data   
                 if(decode_secret_file_data(decInfo)==e_success)
                    {
                             printf("Decoded Secret file data successfully\n");
                     
                    return e_success;
                    }
                else
                {
                                  printf("Decoding secret file data failed\n");
                                  return e_failure;
                }
         
         }
         else
         {
         
             printf("Decoding Magic String failed\n");
             return e_failure;
         }
      }
    else
    {
                printf("Open file is unsuccessful\n");
        return e_failure;
    }
    fclose(decInfo->fptr_secret);
    fclose(decInfo->fptr_stego_image);
return e_success;
}   

/*
 * Get File pointers for i/p and o/p files
 * Inputs: Stego Image file, Secret file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status Open_files(DecodeInfo *decInfo)
{
    decInfo->fptr_stego_image = fopen(decInfo->stego_image_fname, "rb");
    // Do Error handling
    if (decInfo->fptr_stego_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->stego_image_fname);
        return e_failure;
    }
    // Secret file
    decInfo->fptr_secret = fopen("decode_data.txt", "w");
    // Do Error handling
    if (decInfo->fptr_secret == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->secret_fname);

        return e_failure;
    }

    //Skip the BMP header(54 bytes)
fseek(decInfo->fptr_stego_image,54,SEEK_SET);

    // no failure return success
    return e_success;
}

























































































