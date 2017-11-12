/* Header file for list implementations
 *
 */

#ifndef TYPEDEF_LISTS
#define TYPEDEF_LISTS
typedef struct tree_node_s Tree_Node;
typedef struct iterator_s Iterator;
typedef struct linked_list_s Linked_List;
#endif

#ifndef NODE_TYPE
#define NODE_TYPE
typedef enum node_type { INTERNAL, LEAF } node_type;
#endif

#ifndef GET
#define GET
Iterator* get( Linked_List *list, int index ); 
#endif

#ifndef TREE_LEAF_INIT
#define TREE_LEAF_INIT
Tree_Node* init_tree_leaf();
#endif

#ifndef TREE_NODE_INIT
#define TREE_NODE_INIT
Tree_Node* init_tree_node();
#endif

#ifndef LINKED_LIST_INIT
#define LINKED_LIST_INIT
Linked_List* init_list();
#endif

#ifndef ITER_INIT
#define ITER_INIT
Iterator* init_iter( Linked_List* );
#endif

#ifndef FIND
#define FIND
Iterator* find( Linked_List*, char);
#endif

#ifndef INSERT
#define INSERT
Iterator* insert( Linked_List *list, int index , char value );
#endif

#ifndef REMOVE
#define REMOVE
Iterator* remove_node( Iterator *iter );
#endif 
