#include <stdlib.h>
#include <stdio.h>

#include "list_tree.h"

int Decode_a_char(tnode*tree,FILE*infptr){
if(tree==NULL){
return-1;
}
if(is_leaf_node(tree)){
return tree->value;
}
//get a bit from infptr,how?
static int read_char=0;
static int pos = -1;

if (pos<0){
  read_char = fgetc(infptr);
  if(read_char == EOF){
     return -1;
  }
  pos =7;
}

int mask = 1<<pos;
pos-=1;
int token = mask & read_char;

if(token == 0){
return Decode_a_char(tree->left,infptr);
}else{
return Decode_a_char(tree->right,infptr);
}
}
int Huffman_decoding(tnode*huffman,FILE*infptr,FILE*outfptr)
{
int char_count;
if(fread(&char_count,sizeof(int),1,infptr)!=1){
return 0;
}
while(char_count){
  int decoded_char = Decode_a_char(huffman,infptr);
  if(decoded_char != -1){
    fputc(decoded_char,outfptr);
    char_count--;
  }
  else
  {
    break;
  }
}

if(char_count !=0)
{
  return 0;
}else{
return 1;
}
}


tnode *Build_huffman_tree(FILE *infptr)
{
  lnode stack;
  stack.next = NULL;
  stack.tree = (tnode *)0;

  int token;

  while(1){
    token = fgetc(infptr);
    if(token =='0'){
      //pop,pop,push
      if(stack_size(&stack)<=1){
        break;
      }
      lnode *right_node=pop(&stack);
      lnode *left_node=pop(&stack);

      tnode*right_tree=right_node->tree;
      tnode*left_tree=left_node->tree;

      tnode*tree_node=tree_construct(ASCII_COUNT,left_tree,right_tree);
      if(tree_node == NULL){
        node_destruct(left_node);
        node_destruct(right_node);
        token = -1;
        break;}
      right_node->tree = tree_node;
      right_node->next=NULL;
      push(&stack,right_node);
      free(left_node);
    }else if(token =='1'){
      token = fgetc(infptr);
      if(token ==EOF){
        fprintf(stderr,"Unexpected\n");
        break;
      }
      tnode*tree_node = tree_construct(token,NULL,NULL);
      if(tree_node == NULL){
        token = -1;
        break;
      }
      lnode *stack_node =node_construct(tree_node);

      if(stack_node == NULL){
        tree_destruct(tree_node);
        token =-1;
        break;
      }
      push(&stack,stack_node);
    }else{
      break;
    }
  }

  if((token =='0')&&(stack_size(&stack)==1)){

    lnode *node = pop(&stack);
    tnode *huffman = node->tree;
    free(node);
    return huffman;
  }
  stack_flush(&stack);
  return NULL;
}

tnode *tree_construct(int key,tnode*left,tnode*right)
 {
   tnode*node=(tnode*)malloc(sizeof(tnode));

   if(node==NULL){return NULL;}
   node ->value =key;
   node->left=left;
   node->right=right;
   return node;
 }

void tree_destruct(tnode*node)
 {
   if(node==NULL)
     {return;}
   tree_destruct(node->left);
   tree_destruct(node->right);
   free(node);
 }

int is_leaf_node(tnode*node)
{
  if(node!=NULL){
    if((node->left==NULL)&&(node->right==NULL))
      {return 1;}
    else
      {return 0;}
  }
  else
    {return 0;}
}

lnode *node_construct(tnode*tree)
{
  lnode*node=(lnode*)malloc(sizeof(lnode));
  if(node == NULL){
    return NULL;}
  node->tree = tree;
  node->next = NULL;
  return node;
}

void node_destruct(lnode*node)
 {
   if(node!=NULL){
     tree_destruct(node->tree);
     free(node);
   }
 }

void stack_flush(lnode*head)
 {
   lnode*curr=head->next;
   while(curr!=NULL)
     {
       lnode*temp=curr->next;
       node_destruct(curr);
       curr=temp;
     }
   head->next=NULL;
   head->tree=(tnode*)0;
 }

void push(lnode*head,lnode*node)
 {
   node->next=head->next;
   head->next=node;
   int size = (unsigned long)(head->tree)+1;
   head->tree=(tnode*)((unsigned long)size);
 }

lnode* pop(lnode*head)
{
  lnode*node=head->next;
  if(node!=NULL){
    head->next=node->next;
    node->next=NULL;
    int size =(unsigned long)(head->tree)-1;
    head->tree=(tnode*)((unsigned long)size);
  }
  return node;
}

int stack_size(lnode*head)
{
  int size=(unsigned long)(head->tree);
  return size;
}

