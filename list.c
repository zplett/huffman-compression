/* Zac Plett and Ezra Goss
 *
 * This file contains the implementations of our list and tree structures
 * for this lab
 */

#include <stdio.h>
#include "list.h"


/** Struct for each node of the tree.*/
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
  
  Tree_Node *value;
  struct list_node_s *prev;
  struct list_node_s *next;

};

/** Struct for the iterator of the linked list */
struct iterator_s
{
  
  // Index of the node pointed to
  int index;
  // Node pointed to
  List_Node *node;
  
};

/** Function that assigns the iterator to the given index */
/*
Iterator* insert( Linked_List list, int index )
{

}
*/

int main()
{

  
  
}
