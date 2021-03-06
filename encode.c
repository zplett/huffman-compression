/* Zac Plett and Ezra Goss 
 *
 * This file contains the implementations of our encoding functionality
 *
 */

/** Included libraries */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include "list.c"

/** Shift a character 1 bit and output if it reaches the capacity of the byte */
void shift( int binary, FILE *output  )
{
  
  // This is the output byte
  static char byte = 0;
  // Counter to check against CHAR_BIT
  static int counter = 0;
  // Make the appropriate shifts based on binary value
  if( binary == 0 ){
    byte = byte << 1;
  }
  else if( binary == 1 )
    {
      byte = byte << 1;
      byte = byte | 1;
    }
  ++counter;
  // If counter is CHAR_BIT then print the char and reset byte and counter
  if( counter == CHAR_BIT )
    {
      fprintf( output, "%c", byte );
      byte = 0;
      counter = 0;
    }
  // If binary == -1 account for padding
  if( binary == -1 )
    {
      // Make sure the padding is in the least position
      byte = byte << ( CHAR_BIT - ( counter - 1 ) );
      fprintf( output, "%c", byte );
    }
  
}

/** Break character into bits and then shift output byte appropriately */
void breakdown_character( char ch, FILE *output )
{

  // Reference byte
  unsigned char byte = 1;
  // Put reference byte into proper position
  byte = byte << ( CHAR_BIT - 1 );
  // Iterates to CHAR_BIT and does the proper shifts
  for( int i = 0; i < CHAR_BIT; ++i )
  {
    if( ( byte & ch ) != 0 )
      shift( 1, output );
    else
      shift( 0, output );
    byte = byte >> 1;
  } 
  
}

/** Recursive pre-order tree traversal */
void pre_order( Tree_Node *root_node, FILE *output  )
{
  
  // Base Case: If this node is a leaf, print its value to indicate so and return as there are 
  // no more levels of the tree to be traversed.
  if( root_node -> type == LEAF )
    {
      
      // Print a 1 bit
      shift( 1, output );
      // Print the character
      breakdown_character( root_node -> value, output );
      
      //printf("%c\n", root_node -> value  );
      return;
    }
  // Recursive case: Preorder traversals call for root, left, right. We print a 0 indicating
  // a traversal to the left and a 1 indicating a traversal to the right. 
  else
    {
      shift( 0, output );
      if( root_node -> left != NULL )
        {
          //printf("%d\n", 0  );
          pre_order( root_node -> left, output );
        }
      if( root_node -> right != NULL )
        {
          //printf("%d\n", 1 );
          pre_order( root_node -> right, output );
        }
      return;
    }
  
}

/** Recursive find tree traversal */
int find_helper( Linked_List *list, Tree_Node *root_node, char target, FILE *output  )
{
  
  // Base Case: If this node is a leaf, print its value to indicate so and return as there are 
  // no more levels of the tree to be traversed.
  if( root_node -> type == LEAF )
    {
      if( root_node -> value != target )
        {
          return 0;
        }
      else if( root_node -> value == target )
        {
          return 1;
        }
    }
  // Recursive case: Preorder traversals call for root, left, right. We print a 0 indicating
  // a traversal to the left and a 1 indicating a traversal to the right. 
  else
    {
      if( root_node -> left != NULL )
        {
          if( find_helper( list, root_node -> left, target, output ) == 1)
            {
              // Enter in 0 to the path
              insert_at( list, 0, 0 );
              return 1;
            }
        }
      if( root_node -> right != NULL )
        {
          if( find_helper( list, root_node -> right, target, output ) == 1 )
            {
              // Enter in 1 to the path
              insert_at( list, 0, 1 );
              return 1;
            }
        }
      return 0;
    }
  return 0;

}

/** Recursive find tree traversal */
int find_eof_helper( Linked_List *list, Tree_Node *root_node, FILE *output  )
{
  
  // Base Case: If this node is a leaf, print its value to indicate so and return as there are 
  // no more levels of the tree to be traversed.
  if( root_node -> type == LEAF )
    {
      if( root_node -> is_eof == FALSE )
        {
          return 0;
        }
      else if( root_node -> is_eof == TRUE )
        {
          return 1;
        }
    }
  // Recursive case: Preorder traversals call for root, left, right. We print a 0 indicating
  // a traversal to the left and a 1 indicating a traversal to the right. 
  else
    {
      if( root_node -> left != NULL )
        {
          if( find_eof_helper( list, root_node -> left, output ) == 1)
            {
              // Enter in 0 to the path
              insert_at( list, 0, 0 );
              return 1;
            }
        }
      if( root_node -> right != NULL )
        {
          if( find_eof_helper( list, root_node -> right, output ) == 1 )
            {
              // Enter in 1 to the path
              insert_at( list, 0, 1 );
              return 1;
            }
        }
      return 0;
    }
  return 0;

}

/** Find and print the path of EOF  */
void find_eof( Tree_Node *root_node, FILE *output )
{

  // Build the list
  Linked_List *list = init_list();     
  // Call the find helper recursive function
  find_eof_helper( list, root_node, output );
  // Print out path
  Iterator *iter = init_iter( list );
  while( iter -> node != list -> tail )
    {
      if( iter -> node -> value == 0 )
        shift( 0, output );
      else if( iter -> node -> value == 1 )
        shift( 1, output );

      iter -> node = iter -> node -> next;
    }
  // Free memory
  free_list( list );
  free( list -> head );
  free( list );
  free( iter );
  
}


/** Find and print the target value */
void find_path( Tree_Node *root_node, char target, FILE *output )
{

  // Build the list
  Linked_List *list = init_list();     
  // Call the find helper recursive function
  find_helper( list, root_node, target, output );
  // Print out path
  Iterator *iter = init_iter( list );
  while( iter -> node != list -> tail )
    {
      if( iter -> node -> value == 0 )
        shift( 0, output );
      else if( iter -> node -> value == 1 )
        shift( 1, output );

      iter -> node = iter -> node -> next;
    }
  // Free memory
  free_list( list );
  free( list -> head );
  free( list );
  free( iter );
  
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
  if( file == NULL )
    {
      fprintf( stderr, "File given is not valid\n" );
      exit( -1 );
    }
  return file;
  
}

/** Open output file */
FILE* open_output( int argc, char *argv[] )
{

  // Filename marker
  char *filename = NULL;
  // If there is a third argument, make the filename that argument
  if( argc > 1 )
    filename = argv[2];
  // File to be used for output stream
  FILE *file = NULL;
  // If filename isn't null, use open this file and use it for output
  if( filename != NULL )
    file = fopen( filename, "w" );
  // Otherwise, return the stdout output stream
  else
    return stdout;
  return file;
  
}

int main( int argc, char *argv[] )
{
  
  // Open the files for input and output 
  FILE *file = open_file( argc, argv );
  FILE *output = open_output( argc, argv );
  // Fill the ascii tree with frequencies
  for( int ch = fgetc( file ); ch != EOF;  ch = fgetc( file ) )
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
        insert( chars, i );
    }
  // Hard code EOF
  Tree_Node *eof = init_tree_leaf();
  eof -> value = -1;
  eof -> is_eof = TRUE;
  eof -> freq = 1;
  Iterator *eof_iter = malloc( sizeof( *eof_iter ) );
  eof_iter -> node = eof;
  // End of EOF hard code
  insert_ready_node( chars, eof_iter );
  // Build the tree and get the root
  Tree_Node *root = build_huff_tree( chars );
  pre_order( root, output );
  find_eof( root, output );
  fclose( file );
  file = open_file( argc, argv );
  // Finds path
  for( int c = fgetc( file ); c != EOF; c = fgetc( file ) )
    {
      find_path( root, c, output );
    }
  find_eof( root, output );
  // Flush the padding
  shift( -1, output );
  // Frees allocated memory
  free_tree( root );
  free( chars -> head );
  free( chars -> tail );
  free( chars );
  free( eof_iter );
  fclose( file );
  fclose( output );

}
