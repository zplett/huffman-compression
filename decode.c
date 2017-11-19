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
  char byte = 1;
  return byte << ( CHAR_BIT - 1 );
  
}

/** Ands a byte and reference and returns 1 if the and value is != 0 and 0 otherwise */ 
int read_bit( char byte, char ref )
{

  // Evaluates the bitwise and operation and returns the appropriate value accordingly
  if( ( byte & ref ) != 0 )
    return 1;
  return 0;
  
}

/** Tree construction from encoded file */
Tree_Node* construct_tree( FILE *file )
{

  /*
  // Reads in input while fgetc can be called on the file
  while( int c = fgetc( file ) )
    {
      // Sets a new marker byte for each iteration
      char marker = shift_bit();
      // Performs bitwise evaluations and then shifts the marker to the right by 1
      // each iteration until it is 0.
      while( marker != 0 )
	{
	  // The result of using the bitwise and operation on the last character from the file
	  // and the marker byte.
	  char result = ( c & marker );
	  // If the result is 0, then the position of the 1 in the marker byte is a 0 in the
	  // file's character. 
	  if( result == 0 )
	    {
	      // INTERNAL NODE
	      
	      
	    }
	  // Otherwise, the position of the 1 in the marker byte is also a 1 in the file's
	  // character as result is a non zero value. 
	  else
	    {

	    }
	  marker = marker >> 1;
	}
    } */
  
}

/** Main Function */
int main( int argc, char *argv[] )
{

  // Input file
  FILE *file = open_file( argc, argv );
  
  fclose( file );
  return 0;
  
}

