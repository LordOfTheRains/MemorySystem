/*
 * Project 5: address.c
 *
 * This program demonstrates:
 * (1) how to derive page number and offset from a logical address
 * (2) how to create a physical address using frame number and offset
 *
 * Compile: gcc address.c -o address
 * Run: ./address
 * Xiao Qin.
 */



#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "include/address.h"


laddress_t l_addr_table[MAX_L_ADDR];

int load_logical_from_file(char *fname){
  FILE * fp;
  char * line = NULL;
  int i = 0;
  int j = 0;// index used to traverse the laddr table back for debug
  size_t len = 0;
  ssize_t read;

  fp = fopen(fname,"r");
  if (fp == NULL)
      exit(EXIT_FAILURE);
  while ((read = getline(&line, &len, fp)) != -1) {
    l_addr_table[i] = atoi(line);
    //printf("l_addr_table : %d \n", l_addr_table[i]);
    printf("from logical addr table: %d \n", l_addr_table[i]);
    i++;
      //printf("Retrieved line of length %zu :\n", read);
  }

  for (j = 0; j < sizeof(l_addr_table); j++ ) {
      printf("logical address [%d] = %d\n", j, l_addr_table[j] );
   }

  fclose(fp);
  if (line)
      free(line);
  //exit(EXIT_SUCCESS);
  return 0;
}


int translate_to_physical_addr(tlb_t *tlb ){
  laddress_t logical_address;
  page_t     page_num;
  offset_t   offset;
  frame_t    frame_num;
  paddress_t physical_address;
  for (int i = 0; i < MAX_L_ADDR; i++ ){
    logical_address = l_addr_table[i];
    printf("translating %d to physical address\n", logical_address);
    int err =  translate_logical_addr(&tlb, logical_address,
                                         &page_num,
                                         &offset,
                                         &frame_num,
                                         &physical_address);
    if(err == 0){
      printf("logical address: %d, page number: %d, offset: %d frame number: %d \nphysical address: %d\n",
              logical_address,
              page_num,
              offset,
              frame_num,
              physical_address);
      printf("------------------------------------------\n");
    }

  }
  return 0;
}

//
int translate_logical_addr( tlb_t *tlb,
                            laddress_t l_address,
                            page_t *p_num,
                            offset_t *o_set,
                            frame_t *f_num,
                            paddress_t *p_addr)
{
    laddress_t logical_address;
    page_t     page_num;

    offset_t   offset;
    frame_t    frame_num;
    paddress_t physical_address;


    //logical_address = 16916;
    logical_address = l_address;

    page_num = logical_address >> OFFSET_BITS;
    offset = logical_address & OFFSET_MASK;
    //printf("logical address: %d, page number: %d, offset: %d\n", logical_address, page_num, offset);

#ifdef DEBUG
    printf("logical address: %s\n", itob(logical_address));
    printf("logical address: %s\n", itob16(logical_address));
    printf("page number: %s\n", itob8(page_num));
    printf("offset: %s\n", itob8(offset));
    printf("Unit Testing: Now create physical address ...\n");
#endif
    frame_num = page_num;
    physical_address = frame_num << OFFSET_BITS | offset;


#ifdef DEBUG
    printf("frame number:%d, offset: %d, physical address: %d\n", frame_num, offset, physical_address);
#endif

    *p_num = page_num;

    *o_set = offset;
    *f_num = frame_num;
    *p_addr = physical_address;

    return 0;
}

/*
 * convert machine number to human-readable binary string.
 * Returns: pointer to static string overwritten with each call.
 * Reference:
 * https://bytes.com/topic/c/answers/621985-print-binary-representation
 * */
char *itob(int x)
{
    static char buff[sizeof(int) * CHAR_BIT + 1];
    int i;
    int j = sizeof(int) * CHAR_BIT - 1;

    buff[j] = 0;
    for(i=0;i<sizeof(int) * CHAR_BIT; i++) {
        if(x & (1 << i))
            buff[j] = '1';
        else
            buff[j] = '0';
        j--;
    }
    return buff;
}

/*
 * Xiao Qin:
 * This is a mofified version of the above itob()
 * Only print 16 bits
 */
char *itob16(int x)
{
    static char buff[17];
    int i;
    int j = 15;

    buff[j] = 0;
    for(i=0;i<16; i++) {
        if(x & (1 << i))
            buff[j] = '1';
        else
            buff[j] = '0';
        j--;
    }
    return buff;
}

/*
 * Xiao Qin:
 * This is a mofified version of the above itob()
 * Only print 8 bits
 */
char *itob8(int x)
{
    static char buff[9];
    int i;
    int j = 7;

    buff[j] = 0;
    for(i=0;i<8; i++) {
        if(x & (1 << i))
            buff[j] = '1';
        else
            buff[j] = '0';
        j--;
    }
    return buff;
}



void a_hello()
{
    printf("Hello from address\n");
}

int mem_reader( int seek_p, int num_byte, physical_mem_t *p_mem){}
    const char backingstore[] = BACKING_STORE;

    FILE *file;
    int i;
    int seek_position;
    fpos_t pos;
    int num_bytes_read;
    byte one_byte;
    printf("accessing the backing store.....");
    /* argc should be 3 for correct execution */
    // if ( argc != 3 ) {
    //     /* We print argv[0] assuming it is the program name */
    //     printf( "usage: %s, <seek position>, <number of bytes to read>\n", argv[0]);
    //     return 0;
    // }

    /*
     * Convert strings into seek_position and num_bytes_read
     * We assume argv[1] is seek_position and argv[2] is num_bytes_read
     */
    seek_position = seek_p;
    num_bytes_read =num_byte;

#ifdef DEBUG
    printf("seek_position =%d, num_bytes_read =%d\n", seek_position, num_bytes_read);
#endif

    file = fopen(backingstore, "r" );

    /* fopen returns 0, the NULL pointer, on failure */
    if ( file == 0 ) {
         printf( "Could not open file: %s.\n", backingstore);
    }
    else {
        /* SEEK_SET: reference position is the beginning of file */
        fseek(file, seek_position, SEEK_SET);
        fgetpos(file, &pos);
        //printf("Reading from position: %d.\n",pos);

        /* Read and print data from backingstore */

        for (i = 0; i < num_bytes_read; i++) {
           fread(&one_byte, 1, 1, file);
           /* printf prints one byte as hex */
           printf("0x%x, %d", one_byte, one_byte);
           int frame =   p_mem->next__frame_ptr;
            p_mem->memory[frame+i] = one_byte;
           /*
            * Note: If one_byte's data type is int,
            * then we have to use a bit mask: one_byte&0xFF
            */
        }
        printf("\n");

        fclose( file );
    }
}
