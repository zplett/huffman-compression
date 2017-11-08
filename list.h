/* Header file for list implementations
 *
 */

#ifndef TYPEDEF_LISTS
#define TYPEDEF_LISTS
typedef struct list_node_s List_Node;
typedef struct tree_node_s Tree_Node;
typedef struct iterator_s Iterator;
#endif

#ifndef NODE_TYPE
#define NODE_TYPE
typedef enum node_type { INTERNAL, LEAF } node_type;
#endif
