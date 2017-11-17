/* Zac Plett and Ezra Goss
 *
 * This file contains the implementations of our list and tree structures
 * for this lab
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int ascii_list[ 256 ] = { 0 };

/** Struct for each node of the tree */
struct tree_node_s
{
  
  // Leaf or internal
  node_type type;
  // Value of the node
  char value;
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
Iterator* get( Linked_List *list, int index )
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
        return iter;
      ( iter -> index ) += 1;
      iter -> node = iter -> node -> next;
    }

  // If the while loop finished then it hit tail ( if index is 0 and the list is empty, it will always return tail )
  if( index == 0 )
    {
      fprintf( stderr, "Get called on empty list. Iterator returns tail.\n");
      return iter;
    }
  else if( index != 0 )
    {
      fprintf( stderr, "Iterator index out of bounds. Iterator returns tail.\n");
      return iter;
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
void insert( Linked_List *list, int index, char value )
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
      target_iter = get( list, index );
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
  target_iter -> index = index;
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
void insert_ready_node( Linked_List *list, int index, Iterator *iter )
{
  
  // Get the surrounding nodes
  Iterator *target = get( list, index );
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

/** Insertion sort */
Iterator* insertion_sort( Linked_List *list )
{

  // Insertion sort starts by retrieving the second element in the list, if there's fewer than two
  // elements in the list then this call to get returns the tail and the program won't execute properly.
  // Therefore first check if the head's next next is the list tail ( indicating the list has one element ) and
  // return an new iterator pointing to the list. 
  if( ( list -> head -> next -> next == list -> tail ) || ( list -> head -> next == list -> tail ) )
    return init_iter( list );
  // Sets an iterator to point to the second element in the list ( index 1 )
  Iterator *iter = get( list, 1 );
  int index = 1;
  // Iterate through the list until we reach the tail
  while( iter -> node != list -> tail )
    {
      // At each iteration of the outer loop this sets an inner iterator to point to the outer iterator 
      Iterator *inner = iter;
      // While loop set to an infinite loop, break conditions are assessed at the start of each iteration.
      // This is done because one of the conditionals is based upon node frequencies. The method used for
      // accessing these frequencies differs based on node type so this logic is handled internally instead
      // of in the looping condition.
      while( 1 )
	{
	  // Temporary variables used for frequency comparison 
	  int freq, prev_freq;
	  // Nodes have two types: inner and leaf, these conditionals assess how to acces the frequency
	  // of the node based on what type of node each is. If a node is a leaf then access its frequency
	  // through its values place in the ascii list. If it's an internal node then its frequency
	  // is the value of the node. Otherwise, the node type is invalid and a stderr message is printed
	  // before returning the iterator. 
	  if( inner -> node -> type == LEAF )
	    freq = ascii_list[ (int) inner -> node -> value ];
	  else if( inner -> node -> type == INTERNAL )
	    freq = inner -> node -> value;
	  else
	    {
	      fprintf( stderr, "Invalid node type\n" );
	      return iter;
	    } 
	  if( inner -> node -> prev -> type == LEAF )
	    prev_freq = ascii_list[ (int) inner -> node -> prev -> value ];
	  else if( inner -> node -> prev -> type == INTERNAL )
	    prev_freq = inner -> node -> prev -> value;
	  else
	    {
	      fprintf( stderr, "Invalid node type\n" );
	      return iter;
	    }
	  // This is the while loop's actual conditional statement:
	  // While the inner iterator has previous nodes and the frequency of the previous node is greater
	  // than the frequency of the current node, swap these two nodes.
	  if( prev_freq <= freq || inner -> node -> prev == NULL )
	    break; 
	  // Sets temporary iterators to point to the inner node and the previous inner node
	  Iterator *iter1 = find( list, inner -> node -> value );
	  Iterator *iter2 = find( list, inner -> node -> prev -> value );
	  // Calls the swap helper function
	  swap( iter1, iter2 );
	  // Moves the inner node to its previous node
	  inner -> node = inner -> node -> prev;
	  // Frees memory allocated for temporary lists
	  free( iter1 );
	  free( iter2 );
	}
      // Sets the outer iterator to point to its next node.
      iter = get( list, ++index );
      // If the outer while loop will break on the next iteration, free the inner iterator.
      // This needs to be done inside the outer while loop as if the outer while loop never
      // executed then the inner iterator would never have been instantiated. 
      if( iter -> node  == list -> tail )
	{
	  free( inner );
	  break;
	}
    }
  return iter;
  
} 

/** Swaps the value and the children */
void swap( Iterator *iter1, Iterator *iter2 )
{

  // Make a temporary copy of iter1
  Tree_Node *temp = init_tree_leaf();
  temp -> value = iter1 -> node -> value;
  temp -> left = iter1 -> node -> left;
  temp -> right = iter1 -> node -> right;
  // Store the index of iter1
  int temporary_index = iter1 -> index;
  // Put iter2 values into iter1
  iter1 -> node -> value = iter2 -> node -> value;
  iter1 -> node -> left = iter2 -> node -> left;
  iter1 -> node -> right = iter2 -> node -> right;
  iter1 -> index = iter2 -> index;
  // Put temp (iter1) values into iter2
  iter2 -> node -> value = temp -> value;
  iter2 -> node -> left = temp -> left;
  iter2 -> node -> right = temp -> right;
  iter2 -> index = temporary_index;
  // Switch types (leaf vs internal)
  node_type temp_type = iter1 -> node -> type;
  iter1 -> node -> type = iter2 -> node -> type;
  iter2 -> node -> type = temp_type;
  // Free our temporary copy
  free( temp );
  // Swap the iterators
  temp = iter1 -> node;
  iter1 -> node = iter2 -> node;
  iter2 -> node = temp;

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
  // Store the integer ascii value of each node for indexing the frequency array
  int ascii_index1 = (int) iter1 -> node -> value;
  int ascii_index2 = (int) iter2 -> node -> value;
  // Create a root internal node with value being the sum of the frequencies of both parameter nodes
  Tree_Node *root = init_tree_node();
  Iterator *iter_root = malloc( sizeof( *iter_root ) );
  iter_root -> index = 0;
  iter_root -> node = root;
  // Internal nodes will have their frequencies stored as that node's value while leaf nodes
  // have their frequencies stored in the ascii_list. These conditional statements handle which method
  // to use when accessing the frequencies. 
  int left_sum = iter1 -> node -> type == INTERNAL ? iter1 -> node -> value : ascii_list[ ascii_index1 ];
  int right_sum = iter2 -> node -> type == INTERNAL ? iter2 -> node -> value : ascii_list[ ascii_index2 ];
  root -> value = left_sum + right_sum;
  // Make the children be the two parameter nodes
  root -> left = iter1 -> node;
  root -> right = iter2 -> node;
  remove_node( iter1 );
  remove_node( iter2 );
  insert_ready_node( list, 0, iter_root );
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
  free( list -> head );
  free( list );
  
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
      Iterator *iter1 = get( list, 0 );
      Iterator *iter2 = get( list, 1 );
      // Sort the list
      insertion_sort( list );
      // Fuse the two nodes
      if( iter2 -> node -> next != list -> tail )
        {
          // Instantiate iterators with first and second node
          iter1 = get( list, 0 );
          iter2 = get( list, 1 );
          print_list( list );
          fuse( list, iter1, iter2 );
	  free( iter1 );
	  free( iter2 );
	}
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



/** Recursive pre-order tree traversal */
void pre_order( Tree_Node *root_node )
{

  printf( "%d: ", root_node -> value );
      
  // Base Case: If this node is a leaf, print its value to indicate so and return as there are 
  // no more levels of the tree to be traversed.
  if( root_node -> type == LEAF )
    {
      printf("end leaf\n");
      return;
    }
  // Recursive case: Preorder traversals call for root, left, right. We print a 0 indicating
  // a traversal to the left and a 1 indicating a traversal to the right. 
  else
    {
      if( root_node -> left != NULL )
        {
          printf( "%d\n", 0 );
          pre_order( root_node -> left );
        }
      if( root_node -> right != NULL )
        {
          printf( "%d\n", 1 );
          pre_order( root_node -> right );
        }
      return;
    }
  
}


int main()
{

  Linked_List *list = init_list();
  insert( list, 0, 'c' );
  insert( list, 0, 'h' );
  insert( list, 0, 'e' );
  insert( list, 0, 's' );
  insert( list, 0, '\n');
  insert( list, 0, 0 );
  ascii_list[ (int) 'c' ] = 1;
  ascii_list[ (int) 'h' ] = 1;
  ascii_list[ (int) 'e' ] = 3;
  ascii_list[ (int) 's' ] = 1;
  ascii_list[ (int) '\n' ] = 1;
  ascii_list[ (int) 0 ] = 1;
  print_list( list );
  printf("\n");
  build_huff_tree( list );
  print_list( list );
  printf("\n");
  pre_order( list -> head -> next );
  free_list( list );
  //free( iter1 );
  //free( iter2 );
  
}
