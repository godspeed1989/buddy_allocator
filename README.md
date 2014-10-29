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

����������һ����Ҫ�ͷŵ�ҳ������orderΪ0��page_idxΪ10��

���ȼ������Ļ�� 10^(1<<0) = 11��Ȼ�����ϲ������ʼҳƫ��Ϊ10&~(1<<0) = 10��

���ھ͵õ���һ��orderΪ1�Ŀ飬��ʼҳƫ��Ϊ10�����Ļ��Ϊ10^(1<<1)=8���ϲ������ʼҳƫ��Ϊ10&~(1<<1)=8��

����Ƶ���ȥ��

![buddy_free](https://github.com/godspeed1989/buddy_allocator/master/buddy_free.png)
===============
