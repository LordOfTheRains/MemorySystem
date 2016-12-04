#include "address.h"
#include "system.h"

void tlb_hello();

#define TLB_SIZE 16
// #define TLB_SIZE 16

/*age_t is used for FIFO, used_t is used for LRU
The only real difference is age_t will never be incremented. */
// typedef unsigned int age_t;
// typedef unsigned int used_t;

typedef struct {
    page_t page_num;
    frame_t frame_num;
    bool valid;
    age_t age;
    used_t used;
} tlb_entry_t;

typedef struct {
    tlb_entry_t tlb_entry[TLB_SIZE];
    unsigned int next_tlb_ptr;
} tlb_t;

<<<<<<< HEAD

int update_tlb(page_t p_num, frame_t f_num, tlb_t *tlb, int policy);

int tlb_replacement(tlb_entry_t new_entry, tlb_t *tlb);
=======
int tlb_replacement(tlb_entry_t new_entry, tlb_t *tlb, policy_t policy);
>>>>>>> 4e607a65539113631abc20778d6e56b2ace1b12d

int tlb_replacement_LRU(page_t p_num, frame_t f_num, tlb_t *tlb);

int tlb_replacement_FIFO(page_t p_num, frame_t f_num, tlb_t *tlb);

int tlb_search(page_t p_num, frame_t f_num, tlb_t *tlb, bool *isHit);

int tlb_init(tlb_t *tlb);
