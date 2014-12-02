#ifndef __BUDDY_H__
#define __BUDDY_H__

#include "list.h"
#include <stdio.h>  //printf
#include <string.h> //memset
#include <assert.h> //assert

/*
 * 标记Page所处的状态
 * */
enum pageflags{
    PG_head,    //不在buddy系统内，首个页
    PG_tail,    //不在buddy系统内，首页之外的页面
    PG_buddy,   //在buddy系统内
};

#define BUDDY_PAGE_SHIFT    (12UL)
#define BUDDY_PAGE_SIZE     (1UL << BUDDY_PAGE_SHIFT)
#define BUDDY_MAX_ORDER     (9UL)

struct page
{
    // spin_lock        lock;
    struct list_head    lru;
    unsigned long       flags;
    union {
        unsigned long   order;
        struct page     *first_page;
    };
};

struct free_area
{
    struct list_head    free_list;
    unsigned long       nr_free;
};

struct mem_zone
{
    // spin_lock        lock;
    unsigned long       page_num;
    unsigned long       page_size;
    struct page        *first_page;
    unsigned long       start_addr;
    unsigned long       end_addr;
    struct free_area    free_area[BUDDY_MAX_ORDER];
};

void         buddy_system_init(struct mem_zone *zone,
                               struct page *start_page,
                               unsigned long start_addr,
                               unsigned long page_num);
struct page *buddy_get_pages(struct mem_zone *zone,
                             unsigned long order);
void         buddy_free_pages(struct mem_zone *zone,
                              struct page *page);
unsigned long buddy_num_free_page(struct mem_zone *zone);

/*
 * 页分为两类：一类是单页（zero page）,
 * 一类是组合页（compound page），
 * 组合页的第一个是head，其余为tail。
 * */
static void __SetPageHead(struct page *page)
{
    page->flags |= (1UL<<PG_head);
}

static void __SetPageTail(struct page *page)
{
    page->flags |= (1UL<<PG_tail);
}

static void __SetPageBuddy(struct page *page)
{
    page->flags |= (1UL<<PG_buddy);
}
/**/
static void __ClearPageHead(struct page *page)
{
    page->flags &= ~(1UL<<PG_head);
}

static void __ClearPageTail(struct page *page)
{
    page->flags &= ~(1UL<<PG_tail);
}

static void __ClearPageBuddy(struct page *page)
{
    page->flags &= ~(1UL<<PG_buddy);
}
/**/
static int PageHead(struct page *page)
{
    return (page->flags & (1UL<<PG_head));
}

static int PageTail(struct page *page)
{
    return (page->flags & (1UL<<PG_tail));
}

static int PageBuddy(struct page *page)
{
    return (page->flags & (1UL<<PG_buddy));
}

/*
 * 设置页的order和PG_buddy标志
 * */
static void set_page_order_buddy(struct page *page, unsigned long order)
{
    page->order = order;
    __SetPageBuddy(page);
}

static void rmv_page_order_buddy(struct page *page)
{
    page->order = 0;
    __ClearPageBuddy(page);
}

/*
 * 查找buddy页
 * */
static unsigned long
__find_buddy_index(unsigned long page_idx, unsigned int order)
{
    return (page_idx ^ (1 << order));
}

static unsigned long
__find_combined_index(unsigned long page_idx, unsigned int order)
{
    return (page_idx & ~(1 << order));
}

/*
 * Linux内核将组合页的order记录在第二个页面的prev指针里
 * 本系统将组合页的order记录在首个页面的page->order域里
 * */
static unsigned long compound_order(struct page *page)
{
    if (!PageHead(page))
        return 0; //单页
    //return (unsigned long)page[1].lru.prev;
    return page->order;
}

static void set_compound_order(struct page *page, unsigned long order)
{
    //page[1].lru.prev = (void *)order;
    page->order = order;
}

static void BUDDY_BUG(const char *f, int line)
{
    printf("BUDDY_BUG in %s, %d.\n", f, line);
    assert(0);
}

// print buddy system status
void dump_print(struct mem_zone *zone);
void dump_print_dot(struct mem_zone *zone);

#endif
