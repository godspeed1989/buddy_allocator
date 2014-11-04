#include "buddy.h"
#include <stdio.h>
#include <assert.h>

void dump_print(struct mem_zone *zone)
{
    unsigned long i;
    printf("order(npage) nr_free\n");
    for (i = 0; i < BUDDY_MAX_ORDER; i++)
    {
        printf("  %ld(%ld)   %ld\n", i, 1UL<<i, zone->free_area[i].nr_free);
    }
}

#define PRINT_PAGES_INFO    1

void dump_print_dot(struct mem_zone *zone)
{
    long i, j, k;

    FILE *fout;
    fout = fopen("bdgraph.dot", "w");
    assert(fout);

    // graph header
    fprintf(fout, "digraph g {\n");
    fprintf(fout, "graph [rankdir=LR];\n");
    fprintf(fout, "edge [dir=both,arrowsize=.5];\n");
    fprintf(fout, "node [shape=record,height=.1];\n");
    fprintf(fout, "\n");

    // free_area
    fprintf(fout, "free_area [label = \"");
    for (i = 0; i < BUDDY_MAX_ORDER; i++)
    {
        fprintf(fout, "<%ld>2^%ld-%ld", i, i,
                zone->free_area[i].nr_free);
        if (i+1 != BUDDY_MAX_ORDER)
            fprintf(fout, "|");
    }
    fprintf(fout, "\"];\n\n");
#if PRINT_PAGES_INFO
    fprintf(fout, "pages [style=filled,color=gray,label = \"{");
    for (i = zone->page_num - 1, k = 0; i >=0 ; i--)
    {
        if (PageBuddy(&zone->first_page[i]))
        {
            if (k == 0) k = 1;
            else fprintf(fout, "|");
            fprintf(fout, "<%ld>%ld~%ld", i,
                    i+(1UL<<zone->first_page[i].order), i);
        }
    }
    fprintf(fout, "}\"];\n\n");
#endif
    // each list in free area
    for (i = 0; i < BUDDY_MAX_ORDER; i++)
    {
        struct list_head *pos;
        struct page *page;
        unsigned long page_idx;
        fprintf(fout, "// area %ld\n", i);
        j = 0;
        // each node in list
        list_for_each(pos, &zone->free_area[i].free_list)
        {
            page = list_entry(pos, struct page, lru);
            page_idx = page - zone->first_page;
            fprintf(fout, "node%ld_%ld [label = \"{%ld}\"];",
                    i, j, page_idx);
        #if PRINT_PAGES_INFO
            fprintf(fout, "node%ld_%ld -> pages:%ld;\n", i, j, page_idx);
        #else
            fprintf(fout, "\n");
        #endif
            j++;
        }
        // connect nodes
        for (k = 0; k < j; k++)
        {
            if (k == 0)
                fprintf(fout, "free_area:%ld -> node%ld_%ld;\n", i, i, k);
            else
                fprintf(fout, "node%ld_%ld -> node%ld_%ld;\n", i, k-1, i, k);
        }
        fprintf(fout, "\n");
    }

    // graph end
    fprintf(fout, "\n");
    fprintf(fout, "}\n");
    fclose(fout);
}
