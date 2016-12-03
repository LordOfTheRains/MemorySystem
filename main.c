#include <stdio.h>

#include "include/system.h"
#include "include/page.h"
#include "include/tlb.h"
#include "include/address.h"


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

// address.h tests
  int read_file = load_logical_from_file(fname);
  int err = translate_to_physical_addr();

  printf("Bye, World!\n");
	return 0;
}
