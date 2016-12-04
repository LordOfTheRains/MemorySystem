#include <stdio.h>

#include "include/system.h"
#include "include/page.h"
#include "include/tlb.h"
#include "include/address.h"
#include "include/backingstore_reader.h"

char *fname = "testinput.txt";

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
// address.h tests
  int read_file = load_logical_from_file(fname);
  int err = translate_to_physical_addr();
  printf("about to read from main mem\n");
  int main_mem = example_reader(1,20);
  printf("Bye, World!\n");
	return 0;
}
