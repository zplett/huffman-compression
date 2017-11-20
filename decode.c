/* Zac Plett and Ezra Goss
 *
 * This file contains the implementations of our decoding functionality
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "list.c"
#include "decode.h"

/** Recursive pre-order tree traversal */
void pre_order( Tree_Node *root_node )
{

  // Base Case: If this node is a leaf.
  if( root_node -> type == LEAF )
    {
      return;
    }
  // Recursive case: Preorder traversals call for root, left, right. 
  else
    {
      if( root_node -> left != NULL )
	{
	  pre_order( root_node -> left );
	}
      if( root_node -> right != NULL )
	{
	  pre_order( root_node -> right );
	}
      return;
    }

}

/** Function used to open and read the input file */
FILE* open_file( int argc, char *argv[] )
{

  // Input file
  FILE *file;
  // If the user doesn't input a file name when running the executable the program exits
  // as there is nothing to be decoeded.
  if( argc == 1 )
    {
      fprintf( stderr, "File name not entered while running program\n" );
      exit( -1 );
    }
  // Opens the file to be read
  file = fopen( argv[ 1 ], "r" );
  return file;
  
}

/** Returns a 1 bit shifted to the left CHAR_BIT - 1 times */
char shift_bit()
{

  // Creates a character with the value 1 and then shifts it to the left
  // CHAR_BIT - 1 times.
  unsigned char byte = 1;
  return byte << ( CHAR_BIT - 1 );
  
}

/** Returns the next byte in the file, acts as a wrapper function for read_bit */
char read_byte( FILE *file )
{

  // byte is used to construct the next byte in the file
  unsigned char byte = 0 << ( CHAR_BIT - 1 );
  // ref is used to keep track of where in the byte to insert ( or not insert ) a 1
  // into the byte
  unsigned char ref = shift_bit();
  // Iterates CHAR_BIT times and sets the values in each position of the byte based on
  // what read bit returns at each index
  for( int i = 0; i < CHAR_BIT; ++i )
    {
      // If the current position has a 1 in the byte, or the byte with the reference to give
      // the byte a 1 in that position
      if( read_bit( file ) == 1 )
	  byte = byte | ref;
      // Shift the reference to the left ( next position )
      ref = ref >> 1;
    }
  return byte;
}

/** Ands a byte and reference and returns 1 if the and value is != 0 and 0 otherwise */ 
int read_bit( FILE *file )
{

  // Static reference bit
  static int ref = 0;
  // Static byte
  static unsigned char byte = 0;
  // Static counter
  static int count = 0;
  // Sets reference bit 
  if( count == 0 )
    {
      ref = fgetc( file );
      //printf( "%c\n", ref );
      byte = shift_bit();
    }
    ++count;
  // Flag for which value should be returned
  int return_val = 0;
  // Evaluates the bitwise and operation and sets the return flag value appropriately 
  if( ( byte & ref ) != 0 )
      return_val = 1;
  // Shifts the byte to the right by one
  byte = byte >> 1;
  // If count == CHAR_BIT - 1 that means we will have read in an entire bit so the static
  // values get reset
  if( count == CHAR_BIT )
      count = 0;
  return return_val;
  
}

/** Tree construction wrapper function, calls the recursive construct depending on the  
 *  initial ( root ) node's type ( internal or leaf ).
 */
Tree_Node* construct_tree( FILE *file )
{

  // Node to be returned, will be the root of the reconstructed tree
  Tree_Node *root_node;
  // If the first bit in the file is a 0, then the root node is an internal node, so an internal
  // node is constructed and then input into the recursive tree building function.
  if( read_bit( file ) == 0 )
    {
      Tree_Node *node = init_tree_node();
      root_node = recursive_construct( node, file );
      free( node );
    }
  // If the first bit wasn't a 0, that means it was a 1 which indicates the root node is a leaf, so
  // a leaf node is constructed and then input into the recursive tree building function.
  else
    {
      Tree_Node *leaf = init_tree_leaf();
      root_node = recursive_construct( leaf, file );
      free( leaf );
    }
  // The root node is then returned
  return root_node;
  
}

/** Recursive tree construction */
Tree_Node* recursive_construct( Tree_Node *node, FILE *file )
{

  // Sets the current node to the input node
  Tree_Node *current = node;
  // Base case: if the next bit is a 1, this is a leaf node so the value of this current 
  // node is set to the next byte. 
  if( read_bit( file ) == 1 )
      current -> value = read_byte( file );
  // Recursive case: Preorder calls for node, left, right so the value of the current internal
  // node is set to 0 and then the function is called recursively on the left and right
  // children of the current node. 
  else
    {
      current -> value = 0;
      recursive_construct( current -> left, file );
      recursive_construct( current -> right, file );
    }
  // The current node is then returned
  return current;
  
}

/** Main Function */
int main( int argc, char *argv[] )
{

  // Input file
  FILE *file = open_file( argc, argv );
  
  // Closes the file and returns 0 as the program ran successfully
  return 0;
  
}

