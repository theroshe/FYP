
#include "plugin.h"
#include "plugin-version.h"
#include "tree.h"
//#include "tree-pass.h"
//#include "intl.h"
#include "print-tree.h"
#include "stringpool.h"

#include "tree-pretty-print.h"

#include <stdlib.h>

//Confirm that the plugin is open source.
//GCC exits without this
int plugin_is_GPL_compatible;


//Called at plugin initialisation
int plugin_init(struct plugin_name_args *plugin_info, struct plugin_gcc_version *version)
{
    //Check GCC version
    if(!plugin_default_version_check (version, &gcc_version)) {
        printf("This plugin is meant for use with gcc %s\n", version->basever);
        return 1;
    }

    tree params; //Function parameters
    tree paramTypes; //Type of the parameters
    tree funcType;
    tree funcDecl;

    //params = NULL_TREE;   //Our new function has no parameters
    //paramTypes = tree_cons(NULL_TREE, void_type_node, NULL_TREE);
    funcType = build_function_type_list(void_type_node, NULL_TREE);

    funcDecl = build_decl(BUILTINS_LOCATION, FUNCTION_DECL, get_identifier("test"), funcType);

    
    DECL_EXTERNAL(funcDecl) = 0;
    TREE_PUBLIC(funcDecl) = 0;
    TREE_STATIC(funcDecl) = 0;
    DECL_ARGUMENTS(funcDecl) = params;

    DECL_RESULT(funcDecl) = build_decl(BUILTINS_LOCATION, RESULT_DECL, NULL_TREE, integer_type_node);
    DECL_CONTEXT(DECL_RESULT(funcDecl)) = funcDecl;
    

    debug_tree(funcDecl);

    return 0;
}
