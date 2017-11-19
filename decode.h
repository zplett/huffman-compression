/* Zac Plett and Ezra Goss
 *
 * Header file for decoding
 *
 */

#ifndef PRE_ORDER
#define PRE_ORDER
void pre_order( Tree_Node *root_node );
#endif

#ifndef OPEN_FILE
#define OPEN_LIFE
FILE* open_file( int argc, char*argv[] );
#endif

#ifndef CONSTRUCT_TREE
#define CONSTRUCT_TREE
Tree_Node* construct_tree( FILE *file );
#endif

#ifndef SHIFT_BIT
#define SHIFT_BIT
char OBshift_bit( );
#endif

#ifndef READ_BIT
#define READ_BIT
int read_bit( char byte, char ref );
#endif
