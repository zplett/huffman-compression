/* Zac Plett and Ezra Goss
 *
 * This file contains the implementations of our list and tree structures
 *
 */

/** Included libraries */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int ascii_list[ 256 ] = { 0 };

/** Checks the frequency of a given character */
int check_freq( char value )
{
  // As long as the value isn't EOF, the frequency is returned
  if( value != EOF )
    return ascii_list[ (int) value ];
  // Otherwise 1 is returned
  else if( value == EOF )
    return 1;
  fprintf( stderr, "Index does not exist: no frequency available\n" );
  exit( -1 );
}

/** Struct for each node of the tree */
struct tree_node_s
{
  
  // Leaf or internal
  node_type type;
  // Value of the node
  char value;
  // Value of the frequency
  int freq;
  // Is this the eof value?
  bool is_eof;
  // Left and right children
  struct tree_node_s *left;
  struct tree_node_s *right;
  // Previous and next node fields
  struct tree_node_s *prev;
  struct tree_node_s *next;
  
};

/** Struct for the linked list */
struct linked_list_s
{

  // Sentinel nodes
  Tree_Node *head, *tail;
  
};

/** Struct for the iterator of the linked list */
struct iterator_s
{
  
  // Index of the node pointed to
  int index;
  // Node pointed to
  Tree_Node *node;
  
};

/** Function that gets the node at a given index and returns and iterator */
Iterator* get( Linked_List *list, int freq )
{

  // Handle only valid lists
  if( list -> head == NULL )
    {
      fprintf( stderr, "Can't create iterator for incomplete list. Missing head node.\n");
      return NULL;
    }
  if( list -> tail == NULL )
    {
      fprintf( stderr, "Can't create iterator for incomplete list. Missing tail node.\n");
      return NULL;
    }
  // Iterator pointing to the head of the list
  Iterator *iter = init_iter( list );

  // If index is out of range, iterator to tail is returned
  while( iter -> node -> next != NULL )
    {
      if( iter -> node -> freq >= freq )
        {
          return iter;
        }
      ( iter -> index ) += 1;
      iter -> node = iter -> node -> next;
    }

  return iter;
  
}

/** Function that gets the node at a given index and returns and iterator */
Iterator* get_at( Linked_List *list, int index )
{

  // Handle only valid lists
  if( list -> head == NULL )
    {
      fprintf( stderr, "Can't create iterator for incomplete list. Missing head node.\n");
      return NULL;
    }
  if( list -> tail == NULL )
    {
      fprintf( stderr, "Can't create iterator for incomplete list. Missing tail node.\n");
      return NULL;
    }
  // Iterator pointing to the head of the list
  Iterator *iter = init_iter( list );

  // If index is out of range, iterator to tail is returned
  while( iter -> node -> next != NULL )
    {
      if( iter -> index == index )
        {
          return iter;
        }
      ( iter -> index ) += 1;
      iter -> node = iter -> node -> next;
    }

  return iter;
  
}


/** Initializes a tree leaf node */
Tree_Node* init_tree_leaf()
{

  // Allocates memory for the tree node
  Tree_Node *tree_node = malloc( sizeof( *tree_node ) );
  // Initializes the value fields of a tree node
  if( tree_node != NULL )
    {
      tree_node -> type = LEAF;
      tree_node -> value = -2;
      tree_node -> freq = 0;
      tree_node -> is_eof = FALSE;
      tree_node -> left = NULL;
      tree_node -> right = NULL;
      tree_node -> prev = NULL;
      tree_node -> next = NULL;
    }
  return tree_node;
  
}

/** Initializes an internal tree node */
Tree_Node* init_tree_node()
{

  // Allocates memory for the tree node
  Tree_Node *tree_node = malloc( sizeof( *tree_node ) );
  // Initializes the value fields of a tree node
  if( tree_node != NULL )
    {
      tree_node -> type = INTERNAL;
      tree_node -> value = -2;
      tree_node -> freq = 0;
      tree_node -> is_eof = FALSE;
      tree_node -> left = NULL;
      tree_node -> right = NULL;
      tree_node -> prev = NULL;
      tree_node -> next = NULL;
    }
  return tree_node;

}

/** Initialize a list */
Linked_List* init_list( )
{

  // Allocates memory for the list
  Linked_List *list = malloc( sizeof( *list ) );
  // Initializes the sentinel nodes
  if( list != NULL )
    {
      list -> head = init_tree_leaf();
      list -> tail = init_tree_leaf();
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

  // Makes sure that the list has a head node
  if( list -> head == NULL )
    return NULL;
  // Make new iterator point to list head
  Iterator *iter_ptr = malloc( sizeof( *iter_ptr ) );
  if( iter_ptr != NULL )
    {
      iter_ptr -> index = 0;
      iter_ptr -> node = list -> head -> next;
    }
  // Return new iterator
  return iter_ptr;
  
}

/** Function that assigns the iterator to the given index */
void insert( Linked_List *list, char value )
{

  // Make a new node
  Tree_Node *node = init_tree_leaf();
  // The value of the tree node in the list node is set to parameter value
  node -> value = value;
  node -> freq = check_freq( value );
  // Grab iterator to the node we want to insert in front of
  Iterator *target_iter = init_iter( list );
  // If list is empty
  if( list -> head -> next == list -> tail )
    target_iter -> node = list -> tail; 
  // If list is not empty
  else
    {
      free( target_iter );
      target_iter = get( list, check_freq( value ) );
    }
  // Link the new node in place
  if( target_iter -> node != NULL )
    {
      if( target_iter -> node -> prev != NULL )
	{
	  Tree_Node *temp = target_iter -> node -> prev;
	  node -> prev = temp;
	  temp -> next = node;
	}
      target_iter -> node -> prev = node;
      node -> next = target_iter -> node;
    }
  // Reassign the iterator to the new node
  target_iter -> node = node;
  // Frees re assigned iterator
  free( target_iter );
  
}


/** Function that assigns the iterator to the given index */
void insert_at( Linked_List *list, int index,  char value )
{

  // Make a new node
  Tree_Node *node = init_tree_leaf();
  // The value of the tree node in the list node is set to parameter value
  node -> value = value;
  // Grab iterator to the node we want to insert in front of
  Iterator *target_iter = init_iter( list );
  // If list is empty
  if( list -> head -> next == list -> tail )
    target_iter -> node = list -> tail; 
  // If list is not empty
  else
    {
      free( target_iter );
      target_iter = get_at( list, index );
    }
  // Link the new node in place
  if( target_iter -> node != NULL )
    {
      if( target_iter -> node -> prev != NULL )
	{
	  Tree_Node *temp = target_iter -> node -> prev;
	  node -> prev = temp;
	  temp -> next = node;
	}
      target_iter -> node -> prev = node;
      node -> next = target_iter -> node;
    }
  // Reassign the iterator to the new node
  target_iter -> node = node;
  // Frees re assigned iterator
  free( target_iter );
  
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
      if( iter -> node -> value == value )
        return iter;
      // Update the iterator 
      iter -> index += 1;
      iter -> node = iter -> node -> next;
    }
  // If the while loop finished without finding the value, return NULL
  return NULL;
  
}

/** Remove a node from the linked list */
Iterator* remove_node( Iterator *iter )
{

  // Handles empty lists or lists without the input index 
  if( iter == NULL )
    {
      fprintf( stderr, "Invalid input, iterator not found.\n" );
      return NULL;
    }
  // Provided list and value fields are valid
  else
    {
      // Sets node's previous and next fields to point to each other
      iter -> node -> prev -> next = iter -> node -> next;
      iter -> node -> next -> prev = iter -> node -> prev;
    }
  // If the remove was succesful, the iterator is returned
  return iter;
  
}

/** Insert a premade node */
void insert_ready_node( Linked_List *list, Iterator *iter )
{
  
  // Get the surrounding nodes
  Iterator *target = get( list, iter -> node -> freq );
  Tree_Node *target_prev = target -> node -> prev;
  // Link in the list
  iter -> node -> next = target -> node;
  iter -> node -> prev = target_prev;
  target_prev -> next = iter -> node;
  target -> node -> prev = iter -> node;
  iter -> index = target -> index;
  target -> index += 1;
  // Frees iterator to node
  free( target );
  
}

/** Fuses two nodes to make a tree */
void fuse( Linked_List *list, Iterator *iter1, Iterator *iter2 )
{

  // Checks whether or not the iterators point to nodes
  if( ( iter1 -> node == NULL ) || ( iter2 -> node == NULL ) )
    {
      fprintf( stderr, "Iterator points to an invalid node.\n" );
      return;
    }
  // Verifies that the nodes iter1 and iter2 are pointing to have valid types because the next step
  // uses the type to access frequencies from the nodes
  if( ( iter1 -> node -> type !=  INTERNAL && iter1 -> node -> type != LEAF  ) || ( iter2 -> node -> type !=  INTERNAL && iter2 -> node -> type != LEAF ) ) 
    {
      fprintf( stderr, "Invalid node type.\n" );
      return;
      }
  // Create a root internal node with value being the sum of the frequencies of both parameter nodes
  Tree_Node *root = init_tree_node();
  Iterator *iter_root = malloc( sizeof( *iter_root ) );
  iter_root -> index = 0;
  iter_root -> node = root;
  // Internal nodes will have their frequencies stored as that node's value while leaf nodes
  // have their frequencies stored in the ascii_list. These conditional statements handle which method
  // to use when accessing the frequencies. 
  int left_sum = iter1 -> node -> freq;
  int right_sum = iter2 -> node -> freq;
  root -> freq = left_sum + right_sum;
  // Make the children be the two parameter nodes
  root -> left = iter1 -> node;
  root -> right = iter2 -> node;
  remove_node( iter1 );
  remove_node( iter2 );
  insert_ready_node( list, iter_root );
  free( iter_root );
  
}

/** Prints the elements of a list */
void print_list( Linked_List *list )
{

  // Creates an iterator over the list
  Iterator *iter = init_iter( list );
  // Checks to see if the list is empty and prints a message and then returns
  // if this is the case. 
  if( list -> head -> next == list -> tail )
    {
      printf( "Empty list, please insert elements!\n" );
      free( iter );
      return;
    }
  // Iterates while the current node isn't the tail and prints
  // the current nodes value
  while( iter -> node != list -> tail )
    {
      if( iter -> node -> type == INTERNAL )
        printf( "%d ", iter -> node -> freq );
      else
        printf( "%d ", iter -> node -> value );
      if( iter -> node -> next == list -> tail )
	break;
      iter -> node = iter -> node -> next;
    }
  printf( "\n" );
  // Frees the iterator
  free( iter );
  
}

/** Frees the memory allocated for a list */
void free_list( Linked_List *list )
{

  // Creates an iterator over the list and free each node while
  // the iterator's node has non null values
  Iterator *iter = init_iter( list );
  while( iter -> node != NULL )
    {
      // Free each node one by one
      Tree_Node *temp = iter -> node;
      iter -> node = iter -> node -> next;
      free( temp );
    }
  // Frees the list and the temporary iterator
  free( iter );
  
}

/** Build the huffman tree */
Tree_Node* build_huff_tree( Linked_List *list )
{

  // Initializes node
  Tree_Node *node;
  // Checks to see if the list has only one element, if it doesn then an iterator
  // pointing to that node is returned
  if( list -> head -> next -> next == list -> tail )
    return list -> head -> next;
  // Loop until there is only one root
  while( 1 )
    {
      Iterator *iter1 = get_at( list, 0 );
      Iterator *iter2 = get_at( list, 1 );
      // Checks to make sure the second iterator isn't pointing to the list's tail
      if( iter2 -> node != list -> tail )
        {
	  // Fuses the nodes from iter1 and iter2 and then frees both of the iterators
          fuse( list, iter1, iter2 );
          free( iter1 );
          free( iter2 );
        }
      // If iter2's node does point to the list's tail, the node to be returned is set to
      // iter1's node, iter1 and iter2 are freed and the loop breaks.
      else
        {
          node = iter1 -> node;
          free( iter1 );
          free( iter2 );
          break;
        }
    }
  
  return node;
  
} 

/** Recursive pre-order tree traversal for freeing the tree */
void free_tree( Tree_Node *root_node )
{

  // Recursive case: Preorder traversals call for root, left, right. We traverse the left then
  // right children if they exist. 
  if ( root_node -> type == INTERNAL )
    {
      if( root_node -> left != NULL )
          free_tree( root_node -> left );
      if( root_node -> right != NULL )
          free_tree( root_node -> right );
    }
  // Regardless of the node type, the node needs to be freed. 
  free( root_node );
  // The function returns after evaluating all conditionals.
  return;
  
}

