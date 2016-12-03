#include <stdio.h>
#include "include/page.h"
#include "include/tlb.h"
#include "include/address.h"


char *fname = "testinput.txt";

int main()
{
    printf("Hello, World!\n");
	p_hello();
	tlb_hello();
	a_hello();

// address.h tests
  int read_file = load_logical_from_file(fname);
  translate_to_physical_addr();

	return 0;
}
