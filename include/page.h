
#include "system.h"
#include "backingstore_reader.h"

typedef struct {
    page_t page_num;
    frame_t frame_num;
    bool valid;
} page_entry_t;

typedef struct {
    page_entry_t page_entry[PAGE_TABLE_SIZE];
} page_table_t;

void p_hello();


void search_page_table(page_table_t *page_table, page_t page_num,int *is_page_fault,frame_t *frame_num);
