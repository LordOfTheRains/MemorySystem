
#include <stdio.h>
#include "include/system.h"
#include "include/page.h"


page_t page_table[PAGE_TABLE_SIZE];


void page_table_init(){


}

void search_page_table(page_num,
    		              *is_page_fault,
 				              *frame_num)
{
  //check poage number out ofbound and page not loaded
  if(page_num >= PAGE_TABLE_SIZE||page_table[page_num] == NULL){
      is_page_fault = 1;
    }
  }
  frame_num = page_table[page_num];
}


void replace_page_table_entry(page_t new_page){

}










void p_hello()
{
    printf("Hello from pages\n");
}
