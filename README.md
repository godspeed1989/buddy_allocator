buddy_allocator
===============

buddy system memory allocator

## System Storage



![buddy_system](https://github.com/godspeed1989/buddy_allocator/master/buddy_system.png)
===============

## Buddy Allocator



![buddy_alloc](https://github.com/godspeed1989/buddy_allocator/master/buddy_alloc.png)
===============

## Buddy Free

```
static inline unsigned long
__find_buddy_index(unsigned long page_idx, unsigned int order)
{
    return (page_idx ^ (1 << order));
}
static inline unsigned long
__find_combined_index(unsigned long page_idx, unsigned int order)
{
    return (page_idx & ~(1 << order));
}
```

假设现在有一个将要释放的页，它的order为0，page_idx为10。

则先计算它的伙伴 10^(1<<0) = 11，然后计算合并后的起始页偏移为10&~(1<<0) = 10。

现在就得到了一个order为1的块，起始页偏移为10，它的伙伴为10^(1<<1)=8，合并后的起始页偏移为10&~(1<<1)=8。

如此推导下去。

![buddy_free](https://github.com/godspeed1989/buddy_allocator/master/buddy_free.png)
===============
