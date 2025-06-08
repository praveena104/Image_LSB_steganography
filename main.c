#include <stdio.h>
#include "encode.h"
#include "decode.h"
#include "types.h"
#include <string.h>
int main(int argc,char *argv[])
{
        if(argc < 3)
    {
        printf("Enter valid number of arguments: ./a.out -e/d <input.bmp> [<output.bmp or secret.txt>]\n");
        return 0;
    }
    EncodeInfo encInfo;
    DecodeInfo decInfo;
    //Whether User wants to perform Encoding or Decoding
    if(check_operation_type(argv)==e_encode)
    {
        if (argc < 4)
        {
            printf("Encoding mode requires: ./a.out -e <input.bmp> <output.bmp>\n");
            return 0;
        }
	    printf("Selected encoding\n");
	    //Read and Validate encoding argument
	    if(read_and_validate_encode_args(argv,&encInfo)==e_success)
	    {
		    printf("Read and validate is success\n");
		    //start encoding
		    if(do_encoding(&encInfo)==e_success)
		    {
			    printf("Encoding is successful\n");
		    }
		    else
		    {
			    printf("Encoding failed\n");
		    }
	    }
	    else
	    {
		    printf("Read and validate failed\n");
		    printf("Please pass ./a.out -e beautiful.bmp stego.bmp\n");
		    return 1;
	    }
    }
    else if(check_operation_type(argv)==e_decode)
    {
         if (argc < 3)
        {
            printf("Decoding mode requires: ./a.out -d <input.bmp> [output.txt]\n");
            return 0;
        }
	    printf("Selected decoding\n");
	    //Read and Validate argument
            if(read_and_validate_decode_args(argv,&decInfo)==e_success)
            {
                    printf("Read and validate is success\n");
                    //start decoding
                    if(do_decoding(&decInfo)==e_success)
                    {
                            printf("Decoding is successful\n");
                    }
                    else
                    {
                            printf("Decoding failed\n");
                    }
            }
            else
            {
                    printf("Read and validate failed\n");
                    printf("Please pass ./a.out -d stego.bmp secret.txt\n");
                    return 1;
            }
    }
    else
    {
	    printf("Invalid Input\n");
    }

  
    return 0;
}
OperationType check_operation_type(char *argv[])
{
	if(strcmp(argv[1],"-e")==0)
        	return e_encode;
	if(strcmp(argv[1],"-d")==0)
		return e_decode;
        else
		return e_unsupported;
}	

