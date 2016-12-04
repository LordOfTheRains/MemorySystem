

#define DEBUG

#define BACKING_STORE "BACKING_STORE"

#define PAGE_SIZE = 256
//max number of page table size;
#define PAGE_TABLE_SIZE 256
//max number of entry in tlb
#define TLB_SIZE 16

// frame size
#define FRAME_SIZE 256

//physical memeory size
#define PHYSICAL_MEM_SIZE 65536


//should be 256 when done
#define MAX_L_ADDR 12 //max number of logical address loaded from file

//For picking policy
typedef int policy_t;
#define POLICY_FIFO 1
#define POLICY_LRU 2

/*gotta have muh bools */
typedef int bool;
#define true 1
#define false 0

/* There is no byte data type in C */
typedef unsigned char byte;

/* new data type of pages, frames, and offset */



typedef unsigned int page_t;
typedef unsigned int frame_t;
typedef unsigned int offset_t;
typedef unsigned int laddress_t;
typedef unsigned int paddress_t;

typedef unsigned int age_t;
typedef unsigned int used_t;
