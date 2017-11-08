/* Zac Plett and Ezra Goss
 *
 * This file contains the implementations of our list and tree structures
 * for this lab
 */

#include <stdio.h>
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
  struct list_node_s *head, *tail;
  
}


int main()
{

  return 0;
  
}
