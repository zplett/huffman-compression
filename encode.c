#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include "list.c"


char *bit_strings[256];

void init_bit_strings()
{
  // Initialize the array with empty strings
  for( int i = 0; i < 256; ++i )
    {
      bit_strings[i] = 
      strcpy( bit_strings[i], "" );
    }
}

/** Shift a character 1 bit and output if it reaches the capacity of the byte */
void shift( int binary )
{
  // This is the output byte
  static char byte = 0;
  // Counter to checj against CHAR_BIT
  static int counter = 0;
  if( binary == 0 ){
    byte = byte << 1;
  }
  else if( binary == 1 )
    {
      byte = byte << 1;
      byte = byte | 1;
    }

  ++counter;
  
  if( counter == CHAR_BIT )
    {
      printf( "%c", byte );
      byte = 0;
      counter = 0;
    }

  if( binary == -1 )
    {
      // Make sure the padding is in the least position
      byte = byte << ( CHAR_BIT - ( counter - 1 ) );
      printf("%c", byte );
    }
}

/** Break character into bits and then shift output byte appropriately */
void breakdown_character( char ch )
{
  // Reference byte
  unsigned char byte = 1;
  // Put reference byte into proper position
  byte = byte << ( CHAR_BIT - 1 );

  for( int i = 0; i < CHAR_BIT; ++i )
  {
    if( ( byte & ch ) != 0 )
      shift( 1 );
    else
    shift( 0 );
    byte = byte >> 1;
  } 
  
}

/** Copy the current path through the tree to the bitstring array */
void set_bit_string( char value, char *bit_string )
{
  // Copy the current path into the bit_string array
  strcpy( bit_strings[ (int)value ], bit_string ); 
}

/** Recursive pre-order tree traversal */
void pre_order( Tree_Node *root_node, char *bit_string )
{
  // Base Case: If this node is a leaf, print its value to indicate so and return as there are 
  // no more levels of the tree to be traversed.
  if( root_node -> type == LEAF )
    {
      // Set the bit string to current path
      set_bit_string( root_node -> value, bit_string );
      // Print a 1 bit
      shift( 1 );
      // Print the character
      breakdown_character( root_node -> value );
      return;
    }
  // Recursive case: Preorder traversals call for root, left, right. We print a 0 indicating
  // a traversal to the left and a 1 indicating a traversal to the right. 
  else
    {
      shift( 0 );
      if( root_node -> left != NULL )
        {
          strcat( bit_string, "0" );
          pre_order( root_node -> left, bit_string );
        }
      if( root_node -> right != NULL )
        {
          strcat( bit_string, "1" );
          pre_order( root_node -> right, bit_string );
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
  insert( chars, 0, EOF );
  // Build the tree and get the root
  Tree_Node *root = build_huff_tree( chars );
  init_bit_strings();
  char *bit_string = malloc( sizeof( *bit_string ) + 1);
  strcpy( bit_string, "" );
  pre_order( root, bit_string );
  // Flush the padding
  shift( -1 );


  free_tree( root );
  free( chars -> head );
  free( chars -> tail );
  free( chars );
  free( bit_string );
  for( int i = 0; i < 256; ++i )
    free( bit_strings[i] );
  
}
