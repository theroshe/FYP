
#include "plugin.h"
#include "plugin-version.h"
#include "tree.h"
#include "tree-pass.h"
#include "intl.h"
#include "print-tree.h"

#include "tree-pretty-print.h"

#include <stdlib.h>

//Confirm that the plugin is open source.
//GCC exits without this
int plugin_is_GPL_compatible;

static unsigned int intCount = 0;

//User data = int intCount, which is incremented for each int decl
void declParse(void * gcc_data, void * user_data)
{
    //Gcc data is the decl node which has been parsed
    tree decl = (tree) gcc_data;

    //We don't want decls which are not from the source program
    if(DECL_IS_BUILTIN(decl)) {     
        printf("Builtin\n");
        return;
    }

    //If node is an integer variable declaration...
    if(TREE_CODE(decl) == VAR_DECL) {                                   
        if(TREE_CODE(TREE_TYPE(decl)) == INTEGER_TYPE) {
	  //...print its name and location
	  printf("int %s: %s:%d\n", IDENTIFIER_POINTER(DECL_NAME(decl)), 
		   DECL_SOURCE_FILE(decl), DECL_SOURCE_LINE(decl));    
	    
	  *((int*) user_data) += 1; //Increment intCount
        }
    }
}


//Called at plugin initialisation
int plugin_init(struct plugin_name_args *plugin_info, 
		struct plugin_gcc_version *version)
{
    //Check GCC version
    if(!plugin_default_version_check (version, &gcc_version)) {
        printf("This plugin is meant for use with gcc %s\n", version->basever);
        return 1;
    }
    
    //Register for event which is called after decl parsing
    register_callback("plugin", PLUGIN_FINISH_DECL, declParse, &intCount); 

    return 0;
}
