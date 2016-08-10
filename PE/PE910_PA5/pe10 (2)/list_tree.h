#ifndef _LIST_TREE_H_
#define _LIST_TREE_H_
#include <stdint.h>
#define ASCII_COUNT 256

typedef struct _tnode{
  int value;
  struct _tnode*left;
  struct _tnode*right;
}tnode;

typedef struct _lnode{
  struct _lnode*next;
  tnode *tree;
}lnode;

void push(lnode*head,lnode*node);
lnode* pop(lnode*head);
int stack_size(lnode*head);
tnode *tree_construct(int key,tnode*left,tnode*right);
void tree_destruct(tnode*node);
int is_leaf_node(tnode*node);
lnode *node_construct(tnode*tree);
void node_destruct(lnode*node);
void stack_flush(lnode*head);
void post_order_print(tnode*node,FILE*outfptr,int*array,int index);
tnode *Build_huffman_tree(FILE *infptr);
int Huffman_decoding(tnode*huffman,FILE*infptr,FILE*outfptr);
int Decode_a_char(tnode*tree,FILE*infptr);
#endif 
