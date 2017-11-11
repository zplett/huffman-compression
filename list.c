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
  Iterator *iter = init_iter( list );

  if( iter -> node == NULL )
    printf("WHATTTTTTTTTTT\n");
  
  // If index is out of range, iterator to tail is returned
  while( iter -> node -> next != NULL )
    {
      if( iter -> index == index )
        return iter;
      ( iter -> index ) += 1;
      iter -> node = iter -> node -> next;
    }

  // If the while loop finished then it hit tail ( if index is 0 and the list is empty, it will always return tail )
  if( index == 0 )
    fprintf( stderr, "Get called on empty list. Iterator returns tail.\n");
  else if( index != 0 )
    fprintf( stderr, "Iterator index out of bounds. Iterator returns tail.\n");
  return iter;
  
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

/** Initializes the iterator of a list */
Iterator* init_iter( Linked_List *list )
{

  if( list -> head == NULL )
    return NULL;

  // Make new iterator point to list head
  Iterator *iter_ptr = malloc( sizeof( Iterator* ) );
  if( iter_ptr != NULL )
    {
      iter_ptr -> index = 0;
      iter_ptr -> node = list -> head -> next;
    }
  // Return new iterator
  return iter_ptr;
  
}

/** Function that assigns the iterator to the given index */
Iterator* insert( Linked_List *list, int index, char value )
{

  // Make a new node
  List_Node *node = init_list_node();
  // The value of the tree node in the list node is set to parameter value
  node->value->value = value;
  // Grab iterator to the node we want to insert in front of
  Iterator *target_iter = init_iter( list );
  // If list is empty
  if( list->head->next == list->tail )
    target_iter->node = list->tail; 
  // If list is not empty
  else  
    target_iter = get( list, index );
  // Link the new node in place
  if( target_iter -> node != NULL )
    {
    if( target_iter -> node -> prev != NULL )
      {
        List_Node *temp = target_iter->node->prev;
        node->prev = temp;
        temp->next = node;
      }
    target_iter->node->prev = node;
    node->next = target_iter->node;
    }
  // Reassign the iterator to the new node
  target_iter->node = node;
  target_iter->index = index;
  // Return re assigned iterator
  return target_iter;
  
}

/** Find the given value in the list or return a NULL iterator */
Iterator* find( Linked_List *list, char value )
{

  // Initialize new iterator to the head of the list
  Iterator *iter = init_iter( list );
  // Iterate through list until character value is found
  while( iter -> node -> next != NULL )
    {
      // If the values are the same, the iterator should be returned
      if( iter -> node -> value -> value == value )
        return iter;
      // Update the iterator 
      ++iter -> index;
      iter -> node = iter -> node -> next;
    }
  // If the while loop finished without finding the value, return NULL
  return NULL;
  
}

/** Insertion sort 
Iterator* insertion_sort( Linked_List *list )
{

}
*/

/** Main function */
int main()
{

  Linked_List *list = init_list();
  for( int i = 0; i < 10; ++i )
    insert( list, 0, i );

  Iterator *found = find( list, '3' - '0' );
  Iterator *iter = get( list, 3 );
  printf( "Get: %d, %d\n", iter -> node -> value -> value, iter -> index );
  if( found == NULL )
    printf("Not found\n");
  else 
  printf( "Found: %d, %d\n", found -> node -> value -> value, found -> index );
}
