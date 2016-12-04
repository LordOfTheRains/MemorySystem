#include <stdio.h>
#include <assert.h>
#include "include/tlb.h"


void tlb_hello()
{
    printf("Hello from tlb\n");
}


int tlb_replacement(tlb_entry_t new_entry, tlb_t *tlb, policy_t policy){
    if (tlb->next_tlb_ptr < TLB_SIZE) {
        tlb->tlb_entry[tlb->next_tlb_ptr] = new_entry;
    } else {
        switch(policy) {
            case POLICY_LRU:
                break;
            case POLICY_FIFO:
                break;
        }
    }
}

int tlb_replacement_LRU(page_t p_num, frame_t f_num, tlb_t *tlb){
    int oldest_used = 0;
    int oldest_ptr = 0;
    bool found = false;
    
    int i;
    for (i = 0; i < tlb->next_tlb_ptr; i++)  {
        assert(tlb->tlb_entry[i].valid);

        if(tlb->tlb_entry[i].page_num == p_num){
            assert(tlb->tlb_entry[i].frame_num == f_num);
            found = true;
            tlb->tlb_entry[i].used = 0;
        } else {
            tlb->tlb_entry[i].used++;
            if (tlb->tlb_entry[i].used > oldest_used) {
                oldest_used = tlb->tlb_entry[i].used;
                oldest_ptr = i;
            }
        }
    }

    if (found == false) {
        tlb_entry_t muh_entry;

        muh_entry.page_num = p_num;
        muh_entry.frame_num = f_num;
        muh_entry.valid = true;
        muh_entry.age = 0;
        muh_entry.used = 0;
        if(tlb->tlb_entry[tlb->next_tlb_ptr].valid == false) {
            assert(tlb->next_tlb_ptr >= 0 && tlb->next_tlb_ptr < TLB_SIZE);
            tlb->tlb_entry[tlb->next_tlb_ptr] = muh_entry;

            tlb->next_tlb_ptr++;
        } else {
             tlb->tlb_entry[oldest_ptr] = muh_entry;
        }
    }    

}

int tlb_replacement_FIFO(page_t p_num, frame_t f_num, tlb_t *tlb){
    int oldest_age = 0;
    int oldest_ptr = 0;
    bool found = false;
    
    int i;
    for (i = 0; i < tlb->next_tlb_ptr; i++)  {
        assert(tlb->tlb_entry[i].valid);

        if(tlb->tlb_entry[i].page_num == p_num){
            assert(tlb->tlb_entry[i].frame_num == f_num);
            found = true;
            tlb->tlb_entry[i].age++;
        } else {
            tlb->tlb_entry[i].age++;
            if (tlb->tlb_entry[i].age > oldest_age) {
                oldest_age = tlb->tlb_entry[i].age;
                oldest_ptr = i;
            }
        }
    }
    
    if (found == false) {
        tlb_entry_t muh_entry;

        muh_entry.page_num = p_num;
        muh_entry.frame_num = f_num;
        muh_entry.valid = true;
        muh_entry.age = 0;
        muh_entry.used = 0;

        if(tlb->tlb_entry[tlb->next_tlb_ptr].valid == false) {
            assert(tlb->next_tlb_ptr >= 0 && tlb->next_tlb_ptr < TLB_SIZE);
            tlb->tlb_entry[tlb->next_tlb_ptr] = muh_entry;


            tlb->next_tlb_ptr++;
        } else {
            tlb->tlb_entry[oldest_ptr] = muh_entry;

        }
    }    
}

int tlb_search(page_t p_num, frame_t f_num, tlb_t *tlb, bool *isHit){
    
    int i;
    for(i = 0; i < tlb->next_tlb_ptr; i++) {
        assert(tlb->tlb_entry[i].valid);
        if (tlb->tlb_entry[i].page_num == p_num) {
            assert(tlb->tlb_entry[i].frame_num == f_num);
            isHit = true;
            return 0;
        }
    }
    isHit = false;
    return 0;
}

int tlb_init(tlb_t *tlb){
    //Am i missing something or is this it?
    tlb->next_tlb_ptr = 0;
}
