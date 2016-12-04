
#ifndef PAGE_H
#define PAGE_H

#include "system.h"


typedef struct {
    page_t page_num;
    frame_t frame_num;
    bool valid;
} page_entry_t;

typedef struct {
    page_entry_t page_entry[PAGE_TABLE_SIZE];
} page_table_t;

void p_hello();

int page_table_init(page_table_t *page_table);
int page_fault_handler(page_t page_num,	frame_t *frame_num, physical_mem_t *physical_memory,
			page_table_t *page_table, policy_t tlb_replacement_policy);
int mem_reader( int seek_p, int num_byte, physical_mem_t *p_mem);

void search_page_table(page_table_t *page_table, page_t page_num,int *is_page_fault,frame_t *frame_num);
#endif
