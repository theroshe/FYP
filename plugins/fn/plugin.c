
#include "plugin.h"
#include "plugin-version.h"
#include "tree.h"
#include "tree-pretty-print.h"
#include "toplev.h"

#include <stdlib.h>


//Confirm that the plugin is open source.
//GCC exits without this
int plugin_is_GPL_compatible;

void event(void * gcc_data, void * user_data)
{
  tree funcType; //Node describing function type (return type, parameters, etc.)
  tree funcDecl;
  
  funcType = build_function_type_list(void_type_node, NULL_TREE);
  
  funcDecl = build_decl(BUILTINS_LOCATION, FUNCTION_DECL, get_identifier("aFunction"), funcType);
  
  DECL_EXTERNAL(funcDecl) = 0;
  TREE_PUBLIC(funcDecl) = 0;
  TREE_STATIC(funcDecl) = 0;
  //DECL_ARGUMENTS(funcDecl) = params;
  
  DECL_RESULT(funcDecl) = build_decl(BUILTINS_LOCATION, RESULT_DECL, NULL_TREE, integer_type_node);
  DECL_CONTEXT(DECL_RESULT(funcDecl)) = funcDecl;
  
  /* These functions attempt to add the function to the tree */
  rest_of_decl_compilation(funcDecl, 1, 0);
  announce_function(funcDecl);
  current_function_decl = funcDecl;
  make_decl_rtl(funcDecl);
  init_function_start(funcDecl);

  printf("**************\n");
  debug_tree(funcDecl);
  printf("**************\n\n");
}

//Called at plugin initialisation
int plugin_init(struct plugin_name_args *plugin_info, struct plugin_gcc_version *version)
{
  //Check GCC version
  if(!plugin_default_version_check (version, &gcc_version)) {
    printf("This plugin is meant for use with gcc %s\n", version->basever);
    return 1;
  }
  
  //params = NULL_TREE;   //Our new function has no parameters
  //paramTypes = tree_cons(NULL_TREE, void_type_node, NULL_TREE);
  
  
  register_callback("plugin", PLUGIN_PRE_GENERICIZE, event, NULL);
  printf("Plugin is running\n");
  
  return 0;
}
