buddy_allocator
===============

buddy system memory allocator from Linux kernel

## System Storage

![buddy_system](https://raw.github.com/godspeed1989/buddy_allocator/master/buddy_system.png)
![buddy_system1](https://raw.github.com/godspeed1989/buddy_allocator/master/buddy_system1.png)

两个大小相等且邻接的内存块被称作伙伴。

如果两个伙伴都是空闲的，会将其合并成一个更大的内存块，作为下一层次上某个内存块的伙伴。

page分为两类：

+ 属于Buddy系统（PG_buddy，待分配）

	page->order记录order（page所属的free_area也表示了其order），用于合并时的检测

+ 不属于Buddy系统（已分配）

	单页：page->order记录order

	组合页：首个（PG_head）page记录order，其余（PG_tail）指向首页。order用于释放时的解组合

===============

## Buddy Allocator

![buddy_alloc](https://raw.github.com/godspeed1989/buddy_allocator/master/buddy_alloc.png)

每次把一个大的内存块对半切分，一直切到需要的大小。

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

![buddy_free](https://raw.github.com/godspeed1989/buddy_allocator/master/buddy_free.png)

假设现在有一个将要释放的页，它的order为0，page_idx为10。

则先计算它的伙伴 10^(1<<0) = 11，然后计算合并后的起始页偏移为10&~(1<<0) = 10。

现在就得到了一个order为1的块，起始页偏移为10，它的伙伴为10^(1<<1)=8，合并后的起始页偏移为10&~(1<<1)=8。

如此推导下去。

===============

## dump_print_dot()

将Buddy系统状态打印至GraphViz的.dot文件中。

![dump_print](https://raw.github.com/godspeed1989/buddy_allocator/master/dump.png)

===============

## Compilers

VS2008

GCC
