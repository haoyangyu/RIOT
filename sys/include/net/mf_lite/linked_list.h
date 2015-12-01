/*
* Description: This file is for linked list data struct for linux
* Reference resources: Linux/include/linux/list.h
* By Linus Torvalds
* Author: Haoyang Yu <haoyang.yu@rutgers.edu>
*/
#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

typedef struct list_head{
    struct list_head *next, *prev;
}list_head_t;

typedef list_head_t* list_head_p;

#define LIST_HEAD_INIT(name) { \
&(name), &(name) \
}

#define LIST_HEAD(name){ \
list_head_t name = {&name, &name}; \
}

#define INIT_LIST_HEAD(ptr) do { \
(ptr)->next = ptr; \
(ptr)->prev = ptr; \
} while(0)

static __inline__ void __list_add(list_head_t *new, list_head_t *prev, list_head_t *next){
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

//insert a new entry after the specified head
static __inline__ void list_add(list_head_t *new, list_head_t *head){
    __list_add(new, head, head->next);
}

//insert a new entry at the tail
static __inline__ void list_add_tail(list_head_t *new, list_head_t *head){
    __list_add(new, head->prev, head);
}

static __inline__ void __list_del(list_head_t *prev, list_head_t *next){
    next->prev = prev;
    prev->next = next;
}

static __inline__ void list_del(list_head_t *head){
    __list_del(head->prev, head->next);
}

//list_empty: if empty return TRUE == 1, OTHERWISE return FALSE == 0
static __inline__ int list_empty(list_head_t *head){
    return head->next == head;
}

#define list_entry(ptr, type, member) \
((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); \
        pos = pos->next)

#endif
