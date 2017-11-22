/* Zac Plett and Ezra Goss
 *
 * Header file for decoding
 *
 */

/** Function definitions */
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
char shift_bit( );
#endif

#ifndef READ_BIT
#define READ_BIT
int read_bit( FILE *file );
#endif

#ifndef READ_BYTE
#define READ_BYTE
char read_byte( FILE *file );
#endif

#ifndef RECURSIVE_CONSTRUCT
#define RECURSIVE_CONSTRUCT
Tree_Node* recursive_construct( Tree_Node *node, FILE *file );
#endif

#ifndef OPEN_OUTPUT
#define OPEN_OUTPUT
FILE* open_output( int argc, char *argv[] );
#endif

#ifndef NEXT_OUTPUT
#define NEXT_OUTPUT
Tree_Node* next_output( FILE *file, Tree_Node *node );
#endif

#ifndef OUTPUT_WRAPPER
#define OUTPUT_WRAPPER
void output_wrapper( FILE *file, FILE *output, Tree_Node *root );
#endif

#ifndef PLACE_EOF
#define PLACE_EOF
void place_eof( FILE *file, Tree_Node *root );
#endif
