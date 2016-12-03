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


#define MAX_L_ADDR 20


#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "include/address.h"
#include "include/page.h"
#include "include/tlb.h"
//#define DEBUG


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

    l_addr_table[i] = (laddress_t)*line;
    printf("%d", l_addr_table[i]);
    i++;
      //printf("Retrieved line of length %zu :\n", read);
      printf("%d", line);
  }
  for (j = 0; j < MAX_L_ADDR; j++ ) {
      printf("Element[%d] = %s\n", j, l_addr_table[j] );
   }


  fclose(fp);
  if (line)
      free(line);
  exit(EXIT_SUCCESS);
  return 0;
}


int translate_to_physical_addr(){
  laddress_t logical_address;
  page_t     page_num;
  offset_t   offset;
  frame_t    frame_num;
  paddress_t physical_address;
  int i;
  for (i = 0; i < sizeof(l_addr_table); i++ ){
    logical_address = l_addr_table[i];
    int err =  translate_logical_addr(logical_address,
                                         &page_num,
                                         &offset,
                                         &frame_num,
                                         &physical_address);
    if(err == 0){
      printf("logical address: %d, page number: %d, offset: %d frame number: %d physical address: %d\n",
              logical_address,
              page_num,
              offset,
              frame_num,
              physical_address);
    }

  }




  return 0;
}

//
int translate_logical_addr(laddress_t l_address,
                            page_t *p_num,
                            offset_t *o_set,
                            frame_t *f_num,
                            paddress_t *p_addr) {
    laddress_t logical_address;
    page_t     page_num = *p_num;
    offset_t   offset = *o_set;
    frame_t    frame_num = *f_num;
    paddress_t physical_address = *p_addr;


    //logical_address = 16916;
    logical_address = l_address;

    page_num = logical_address >> OFFSET_BITS;
    offset = logical_address & OFFSET_MASK;
    printf("logical address: %d, page number: %d, offset: %d\n", logical_address, page_num, offset);

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
