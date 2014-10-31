buddy_allocator
===============

buddy system memory allocator from Linux kernel

## System Storage

![buddy_system](https://raw.github.com/godspeed1989/buddy_allocator/master/buddy_system.png)
![buddy_system1](https://raw.github.com/godspeed1989/buddy_allocator/master/buddy_system1.png)

������С������ڽӵ��ڴ�鱻������顣

���������鶼�ǿ��еģ��Ὣ��ϲ���һ��������ڴ�飬��Ϊ��һ�����ĳ���ڴ��Ļ�顣

page��Ϊ���ࣺ
+ ����Buddyϵͳ��PG_buddy�������䣩
	page->order��¼order��page������free_areaҲ��ʾ����order�������ںϲ�ʱ�ļ��
+ ������Buddyϵͳ���ѷ��䣩
	��ҳ��page->order��¼order
	���ҳ���׸���PG_head��page��¼order�����ࣨPG_tail��ָ����ҳ�������ͷ�ʱ�Ľ����

===============

## Buddy Allocator

![buddy_alloc](https://raw.github.com/godspeed1989/buddy_allocator/master/buddy_alloc.png)

ÿ�ΰ�һ������ڴ��԰��з֣�һֱ�е���Ҫ�Ĵ�С��

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

����������һ����Ҫ�ͷŵ�ҳ������orderΪ0��page_idxΪ10��

���ȼ������Ļ�� 10^(1<<0) = 11��Ȼ�����ϲ������ʼҳƫ��Ϊ10&~(1<<0) = 10��

���ھ͵õ���һ��orderΪ1�Ŀ飬��ʼҳƫ��Ϊ10�����Ļ��Ϊ10^(1<<1)=8���ϲ������ʼҳƫ��Ϊ10&~(1<<1)=8��

����Ƶ���ȥ��

===============

## dump_print_dot()

��Buddyϵͳ״̬��ӡ��GraphViz��.dot�ļ��С�

![dump_print](https://raw.github.com/godspeed1989/buddy_allocator/master/dump.png)

===============

## Compilers

VS2008
GCC
