#include "address.h"

void tlb_hello();

#define TLB_SIZE 16 


typedef struct {
    page_t page_num;
    frame_t frame_num;
    bool valid;
    age_t age;
} tlb_entry_t;

typedef struct {
    tlb_entry_t tlb_entry[TLB_SIZE];
    unsigned int next_tlb_ptr;
} tlb_t;

int tlb_replacement_LRU(page_t p_num, frame_t f_num, tlb_t *tlb);

int tlb_replacement(tlb_entry_t new_entry, tlb_t *tlb);

int tlb_init(tlb_t *tlb);

