buddy_allocator
===============

buddy system memory allocator

## System Storage

![buddy_system](https://raw.github.com/godspeed1989/buddy_allocator/master/buddy_system.png)
![buddy_system1](https://raw.github.com/godspeed1989/buddy_allocator/master/buddy_system1.png)

ϵͳ�еĿ����ڴ��������������ģ�ÿ���е������ڴ�鱻������顣

���ķ�������Ǳ˴˶����ģ������������鶼�ǿ��еģ���ô�ں˽��Ὣ��ϲ���һ��������ڴ�飬��Ϊ��һ�����ĳ���ڴ��Ļ�顣

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
