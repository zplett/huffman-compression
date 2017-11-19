/* Zac Plett and Ezra Goss 
 *
 * This file contains the implementations of our encoding functionality
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.c"

char *bit_strings[ 256 ] = { "" };

/** Recursive pre-order tree traversal */
void pre_order( Tree_Node *root_node )
{
  
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


/** Main function */
int main()
{

  // Fill the ascii tree with frequencies
  for( int ch = getchar(); ch != EOF;  ch = getchar() )
    {
      // Increment the frequency for this character
      ++ascii_list[ ch ];
    }

  // The list of characters
  Linked_List *chars = init_list();
  
  // Insert into the list of characters
  for( int i = 0; i < 256; ++i )
    {
      // If there is any frequency, insert
      if( ascii_list[i] > 0 )
        insert( chars, 0, i );
    }

  // Build the tree and get the root
  Tree_Node *root = build_huff_tree( chars );
  pre_order( root );
  
}
