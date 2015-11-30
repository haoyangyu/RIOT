/*
* Description: This file is for linked list data struct for linux
* Reference resources: Linux/include/linux/list.h
* By Linus Torvalds
* Author: Haoyang Yu <haoyang.yu@rutgers.edu>
*/
#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

struct list_head{
    struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) { \
&(name), &(name) \
}

#define LIST_HEAD(name){ \
struct list_head name = {&name, &name}; \
}

#define INIT_LIST_HEAD(ptr) do { \
(ptr)->next = ptr; \
(ptr)->prev = ptr; \
} while(0)

static __inline__ void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next){
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

//insert a new entry after the specified head
static __inline__ void list_add(struct list_head *new, struct list_head *head){
    __list_add(new, head, head->next);
}

//insert a new entry at the tail
static __inline__ void list_add_tail(struct list_head *new, struct list_head *head){
    __list_add(new, head->prev, head);
}

static __inline__ void __list_del(struct list_head *prev, struct list_head *next){
    next->prev = prev;
    prev->next = next;
}

static __inline__ void list_del(struct list_head *head){
    __list_del(head->prev, head->next);
}

static __inline__ int list_empty(struct list_head *head){
    return head->next = head;
}

#define list_entry(ptr, type, member) \
((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); \
        pos = pos->next)

#endif
