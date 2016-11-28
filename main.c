#include <stdio.h>
#include "include/page.h"
#include "include/tlb.h"



int main()
{
    printf("Hello, World!\n");
	p_hello();
	tlb_hello();
	return 0;
}

