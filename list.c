/* Zac Plett and Ezra Goss
 *
 * This file contains the implementations of our list and tree structures
 * for this lab
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/** Struct for each node of the tree */
struct tree_node_s
{
  
  // Leaf or internal
  node_type type;
  // Value of the node
  char value;
  // Frequency of the node
  int frequency;
  // Left and right children
  struct tree_node_s *left;
  struct tree_node_s *right;

};

/** Struct for each node of the linked list */  
struct list_node_s
{

  // Tree node with the value
  Tree_Node *value;
  // This node's previous and next node fields
  struct list_node_s *prev;
  struct list_node_s *next;

};

/** Struct for the linked list */
struct linked_list_s
{

  // Sentinel nodes
  List_Node *head, *tail;
  
};

/** Struct for the iterator of the linked list */
struct iterator_s
{
  
  // Index of the node pointed to
  int index;
  // Node pointed to
  List_Node *node;
  
};

/** Function that gets the node at a given index and returns and iterator */
Iterator* get( Linked_List *list, int index )
{

  // Handle only valid lists
  if( list -> head == NULL )
    {
      fprintf( stderr, "Can't create iterator for incomplete list. Missing head node.");
      return NULL;
    }
  if( list -> tail == NULL )
    {
      fprintf( stderr, "Can't create iterator for incomplete list. Missing tail node.");
      return NULL;
    }
  // Iterator pointing to the head of the list
  Iterator iter = { 0, list -> head }, *iter_ptr = malloc( sizeof( Iterator ) );
  iter_ptr = &iter;

  // If index is out of range, iterator to tail is returned
  while( iter.node -> next != NULL )
    {
      if( iter.index == index )
        return iter_ptr;
      ++iter.index;
      iter.node = iter.node -> next;
    }

  fprintf( stderr, "Iterator index out of bounds. Iterator returns tail.");
  return iter_ptr;
  
}

/** Initializes a tree leaf node */
Tree_Node* init_tree_leaf()
{

  // Allocates memory for the tree node
  Tree_Node *tree_node = malloc( sizeof( Tree_Node ) );
  // Initializes the value fields of a tree node
  if( tree_node != NULL )
    {
      tree_node -> type = LEAF;
      tree_node -> value = -2;
      tree_node -> frequency = 0;
      tree_node -> left = NULL;
      tree_node -> right = NULL; 
    }

  return tree_node;
  
}

/** Initializes an internal tree node */
Tree_Node* init_tree_node()
{

  // Allocates memory for the tree node
  Tree_Node *tree_node = malloc( sizeof( Tree_Node ) );
  // Initializes the value fields of a tree node
  if( tree_node != NULL )
    {
      tree_node -> type = INTERNAL;
      tree_node -> value = -2;
      tree_node -> frequency = 0;
      tree_node -> left = NULL;
      tree_node -> right = NULL;
    }

  return tree_node;

}

/** Initialize the list node */
List_Node* init_list_node()
{

  // Allocates memory for the list node
  List_Node *node = malloc( sizeof( List_Node ) );
  // Initializes the node's value and defines the node's next
  // and previous fields as null
  if( node != NULL )
    {
      node -> value = init_tree_node();
      node -> next = NULL;
      node -> prev = NULL;
    }

  return node;
  
}

/** Initialize a list */
Linked_List* init_list( )
{

  // Allocates memory for the list
  Linked_List *list = malloc( sizeof( Linked_List ) );
  // Initializes the sentinel nodes
  if( list != NULL )
    {
      list -> head = init_list_node();
      list -> tail = init_list_node();
    }
  // Links sentinel nodes together
  if( list -> head != NULL )
    list -> head -> next = list -> tail;
  if( list -> tail != NULL )
    list -> tail -> prev = list -> head;

  return list;
  
}

/** Function that assigns the iterator to the given index */
Iterator* insert( Linked_List list, int index )
{
  return NULL;
}

/** Main function */
int main()
{

  Linked_List *list = init_list();
  List_Node *node = init_list_node();
  Tree_Node *tree_node = init_tree_leaf();
  tree_node -> value = 75;
  node -> value = tree_node;
  node -> prev = list -> head;
  node -> next = list -> tail;
  list -> head -> next = node;
  list -> tail -> prev = node;
  Iterator *iter = get( list, 1 );
  printf( "%d, %d\n", iter -> node -> value -> value, iter -> index );
  
}
