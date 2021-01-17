#ifndef __LIBS_SKEW_HEAP_H__
#define __LIBS_SKEW_HEAP_H__

#include <stdio.h>

struct skew_heap_entry {
     struct skew_heap_entry *parent, *left, *right;
};

typedef struct skew_heap_entry skew_heap_entry_t;

typedef int(*compare_f)(void *a, void *b);

typedef void(*print_f)(void *a);

static inline void skew_heap_init(skew_heap_entry_t *a) __attribute__((always_inline));
static inline skew_heap_entry_t *skew_heap_merge(
     skew_heap_entry_t *a, skew_heap_entry_t *b,
     compare_f comp);
static inline skew_heap_entry_t *skew_heap_insert(
     skew_heap_entry_t *a, skew_heap_entry_t *b,
     compare_f comp) __attribute__((always_inline));
static inline skew_heap_entry_t *skew_heap_remove(
     skew_heap_entry_t *a, skew_heap_entry_t *b,
     compare_f comp) __attribute__((always_inline));

static inline void skew_heap_print(
        skew_heap_entry_t *a, print_f print) __attribute__((always_inline));


static inline void
skew_heap_init(skew_heap_entry_t *a)
{
     a->left = a->right = a->parent = NULL;
}

static inline skew_heap_entry_t *
skew_heap_merge(skew_heap_entry_t *a, skew_heap_entry_t *b,
                compare_f comp)
{
     if (a == NULL) return b;
     else if (b == NULL) return a;
     
     skew_heap_entry_t *l, *r;
     if (comp(a, b) == -1)
     {
          r = a->left;
          l = skew_heap_merge(a->right, b, comp);
          
          a->left = l;
          a->right = r;
          if (l) l->parent = a;

          return a;
     }
     else
     {
          r = b->left;
          l = skew_heap_merge(a, b->right, comp);
          
          b->left = l;
          b->right = r;
          if (l) l->parent = b;

          return b;
     }
}

static inline skew_heap_entry_t *
skew_heap_insert(skew_heap_entry_t *a, skew_heap_entry_t *b,
                 compare_f comp)
{
     skew_heap_init(b);
     return skew_heap_merge(a, b, comp);
}

static inline skew_heap_entry_t *
skew_heap_remove(skew_heap_entry_t *a, skew_heap_entry_t *b,
                 compare_f comp)
{
     skew_heap_entry_t *p   = b->parent;
     skew_heap_entry_t *rep = skew_heap_merge(b->left, b->right, comp);
     if (rep) rep->parent = p;
     
     if (p)
     {
          if (p->left == b)
               p->left = rep;
          else p->right = rep;
          return a;
     }
     else return rep;
}



static inline void skew_heap_echo(skew_heap_entry_t *a, print_f print){
    if(a){
        print(a);
    }else{
        return;
    }

    skew_heap_echo(a->left, print);
    skew_heap_echo(a->right, print);
}

static inline void skew_heap_print(skew_heap_entry_t *a, print_f print) {
    skew_heap_echo(a, print);
    cprintf("\n");
}

#endif    /* !__LIBS_SKEW_HEAP_H__ */
