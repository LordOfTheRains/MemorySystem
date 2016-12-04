
#include <stdio.h>
#include "include/page.h"


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



int page_fault_handler(page_t page_num,	frame_t *frame_num, physical_mem_t *physical_memory,
			page_table_t *page_table, policy_t tlb_replacement_policy)
{

	// Load a frame from the backing store
	// Also gives the frame number of the newly loaded page
	mem_reader(frame_num,FRAME_SIZE, &physical_memory);

	// Add a page entry to the page table
	page_table->page_entry[page_num].page_num = page_num;
	page_table->page_entry[page_num].frame_num = *frame_num;
	page_table->page_entry[page_num].valid = true;

	// Add the newly made page into the TLB
	tlb_replacement(page_num, *frame_num,tlb_replacement_policy);

	return 0;
}








void p_hello()
{
    printf("Hello from pages\n");
}



int mem_reader( int seek_p, int num_byte, physical_mem_t *p_mem){
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
           frame_t frame =   p_mem->next_frame_ptr;
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
