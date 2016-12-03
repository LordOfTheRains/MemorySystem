#include <stdio.h>
#include "include/page.h"
#include "include/tlb.h"
#include "include/address.h"


int main()
{
    printf("Hello, World!\n");
	p_hello();
	tlb_hello();
	a_hello();
	return 0;
}

