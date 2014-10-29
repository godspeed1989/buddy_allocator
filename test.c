#include "buddy.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mem_block {
    struct mem_zone     zone;
    struct page        *pages;
};

static struct mem_block global_mem_block;

static int mem_block_init(void)
{
    int pages_size;
    unsigned long start_addr;
#define _NPAGES 491
    // init global memory block
    pages_size = _NPAGES * sizeof(struct page);
    global_mem_block.pages = (struct page*)malloc(pages_size);
    if (!global_mem_block.pages)
        return -1;
    start_addr = (unsigned long)malloc(_NPAGES * BUDDY_PAGE_SIZE);
    if (!start_addr)
    {
        free(global_mem_block.pages);
        return -2;
    }
    // init buddy
    buddy_system_init(&global_mem_block.zone,
                       global_mem_block.pages,
                       start_addr,
                       _NPAGES);
    return 0;
}

static void mem_block_destroy(void)
{
    free((void*)global_mem_block.pages);
    free((void*)global_mem_block.zone.start_addr);
}

int main()
{
    struct page *p;
    struct mem_zone *zone;

    if (mem_block_init() < 0)
        return -1;
    zone = &global_mem_block.zone;
    dump_print(zone);
    printf("init done\n");

    p = buddy_get_pages(zone, 0);
    dump_print(zone);
    buddy_free_pages(zone, p);
    dump_print(zone);

    p = buddy_get_pages(zone, 1);
    dump_print(zone);
    buddy_free_pages(zone, p);
    dump_print(zone);

    mem_block_destroy();
    return 0;
}
