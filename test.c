#include "buddy.h"
#include <time.h>
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
#define _NPAGES 1024
    // init global memory block
    // all pages area
    pages_size = _NPAGES * sizeof(struct page);
    global_mem_block.pages = (struct page*)malloc(pages_size);
    if (!global_mem_block.pages)
        return -1;
    // address area (optional)
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

void do_test()
{
#define    RUN_SECONDS    20
    time_t start;
    struct page *page;
    struct list_head page_list;
    unsigned long loop, order;
    struct mem_zone *zone = &global_mem_block.zone;

    loop = 0;
    start = time(NULL);
    srand((unsigned int)start);
    INIT_LIST_HEAD(&page_list);
    for (;;)
    {
        // run n seconds test
        if (loop % 1000 == 0 && time(NULL)-start >= RUN_SECONDS)
            break;
        loop++;
        if (rand () & 1)
        // allocate
        {
            order = (unsigned long)rand() % BUDDY_MAX_ORDER;
            page = buddy_get_pages(zone, order);
            if (page)
               list_add(&page->lru, &page_list);
        }
        else if (!list_empty(&page_list))
        // free
        {
            page = list_entry(page_list.next, struct page, lru);
            list_del(&page->lru);
            buddy_free_pages(zone, page);
        }
    }
    printf("do_test(): %ld loops in %ld s\n",
           loop, (unsigned long)(time(NULL)-start));
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

    // print to .dot file
    p = buddy_get_pages(zone, 2);
    printf("num free: %ld\n", buddy_num_free_page(zone));
    dump_print_dot(zone);
    if (p)
        buddy_free_pages(zone, p);

    // more comprehensive test
    do_test();

    mem_block_destroy();
    return 0;
}
