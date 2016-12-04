#include <stdio.h>

#include "include/system.h"
#include "include/page.h"
#include "include/tlb.h"
#include "include/address.h"
#include "include/backingstore_reader.h"

char *fname = "testinput.txt";
char *outname = "vm_sim_output.txt";

int main( int argc, char *argv[] )
{
  if( argc == 2 ) {
      printf(" %s\n", argv[1]);
      fname = argv[1];
   }


  printf("Hello, World! from %s\n", argv[1]);
	p_hello();
	tlb_hello();
	a_hello();
  //initialize physical mmemory;

	//Get dat replacement policy
	policy_t usr_policy = -1;
	int tlb_hits = 0;
	while (usr_policy != POLICY_FIFO && usr_policy != POLICY_LRU) {
		printf("Choose TLB replacement policy [%d: FIFO, %d: LRU] ", POLICY_FIFO, POLICY_LRU);
		scanf("%d", &usr_policy);
		if (usr_policy != POLICY_FIFO && usr_policy != POLICY_LRU) {
			printf("Not valid policy.\n");
		}
	}
	switch (usr_policy){
		case POLICY_LRU:
			printf("Using LRU policy.\n");
			break;
		case POLICY_FIFO:
			printf("Using FIFO policy.\n");
			break;
	}

	tlb_t sys_tlb;
	tlb_init(&sys_tlb);

// address.h tests
  int read_file = load_logical_from_file(fname);
  int err = translate_to_physical_addr();
  printf("Bye, World!\n");
	return 0;
}
