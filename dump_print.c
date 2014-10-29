#include "buddy.h"

void dump_print(struct mem_zone *zone)
{
    unsigned long i;
    printf("order(npage) nr_free\n");
    for(i = 0; i < BUDDY_MAX_ORDER; i++)
    {
        printf("  %ld(%ld)   %ld\n", i, 1UL<<i, zone->free_area[i].nr_free);
    }
}
