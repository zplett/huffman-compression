/* Zac Plett and Ezra Goss
 *
 * This file contains the implementations of our list and tree structures
 * for this lab
 */

#include <stdio.h>

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
  Tree_Node *left;
  Tree_Node *right;
};

  
struct list_node_s
{
  Tree_Node *value;
  List_Node *prev;
  List_Node *next;
};

