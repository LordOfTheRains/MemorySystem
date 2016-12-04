
#include <stdio.h>
#include "include/system.h"
#include "include/page.h"
#include "include/backingstore_reader.h"

#include "include/tlb.h"


int next_frame_in_backing = 0;
int next_frame;




int page_table_init(page_table_t *page_table)
{
	int i;
	for (i = 0; i < PAGE_TABLE_SIZE; i++)
	{
		page_table->page_entry[i].valid = false;
	}
	return 0;
}

void search_page_table(page_table_t *page_table, page_t page_num, bool *is_page_fault, frame_t *frame_num)
{
  //check poage number out ofbound and page not loaded
  if(page_num >= PAGE_TABLE_SIZE || !page_table->page_entry[page_num].valid){
      *is_page_fault = true;
  }
  *frame_num = page_table->page_entry[page_num].frame_num;
}


void load_from_backing_store(){
  // byte block[FRAME_SIZE];
  // example_reader(frame,FRAME_SIZE,);
  // next_frame_in_backing += FRAME_SIZE;

}


int page_fault_handler(page_t page_num,	frame_t *frame_num, physical_mem_t *physical_memory,
			page_table_t *page_table, policy_t tlb_replacement_policy)
{

	// Load a frame from the backing store
	// Also gives the frame number of the newly loaded page
	load_from_backing_store(page_num, BACKING_STORE, physical_memory,
			frame_num);

	// Add a page entry to the page table
	page_table->page_entry[page_num].page_num = page_num;
	page_table->page_entry[page_num].frame_num = *frame_num;
	page_table->page_entry[page_num].valid = true;

	// Add the newly made page into the TLB
	//tlb_replacement(page_num, *frame_num,tlb_replacement_policy);

	return 0;
}








void p_hello()
{
    printf("Hello from pages\n");
}
