#include "system.h"
/*
 * Project 5: address.h
 * This is a header file of address.c
 * Xiao Qin.
 */
#ifndef ADDRESS_H
#define ADDRESS_H

/* offset is used to address the location within a page */
#define OFFSET_BITS 8
/*
 * In C language, there is no binary format in printf
 * You must implement the following functions to print binary format
/* mask is used to extract the offset from a logical address */ 
#define OFFSET_MASK 0xFF 

/* There is no byte data type in C */
// typedef unsigned char byte;

/* new data type of pages, frames, and offset */
// typedef unsigned int page_t;
// typedef unsigned int frame_t;
// typedef unsigned int offset_t;
// typedef unsigned int laddress_t;
// typedef unsigned int paddress_t;

/* 
 * In C language, there is no binary format in printf 
 * You must implement the following functions to print binary format 
>>>>>>> 2766e3defbb5ae90a4d41b3670a7afb32941f458
 * itob16() and itob8() are modified from itob() by Xiao Qin.
 */
char *itob(int x);
char *itob16(int x);
char *itob8(int x);



void a_hello();
int load_logical_from_file(char *fname, laddress_t *logic_addr_list[]);

//this translates all l addr
int translate_to_physical_addr();
//given example code
///only traslate one at a time
int translate_logical_addr(
                            laddress_t l_address,
                            page_t *p_num,
                            offset_t *offset,
                            frame_t *f_num,
                            paddress_t *p_addr);
//might not need this
int get_page_number();
int get_frame_number();

#endif
