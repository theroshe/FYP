
#include "plugin.h"
#include "plugin-version.h"
#include "tree.h"
#include "tree-pass.h"
#include "intl.h"
#include "print-tree.h"

#include "stringpool.h" //get_identifier

#include "tree-pretty-print.h"

#include <stdlib.h>

//Confirm that the plugin is open source.
//GCC exits without this
int plugin_is_GPL_compatible;

static unsigned int includeCount = 0;
static unsigned int intCount = 0;

void declParse(void * gcc_data, void * user_data)
{
    //Gcc data is the decl node which has been parsed
    tree decl = (tree) gcc_data;
    *((int*) user_data) += 1;
}

//Called at plugin initialisation
int plugin_init(struct plugin_name_args *plugin_info, struct plugin_gcc_version *version)
{
    //Check GCC version
    if(!plugin_default_version_check (version, &gcc_version)) {
        printf("This plugin is meant for use with gcc %s\n", version->basever);
        return 1;
    }

    register_callback("plugin", PLUGIN_FINISH_DECL, declParse, &intCount); //After decl parsing
        

    //Create new builtin function
    
    tree type = integer_type_node; //Get node describing standard signed int
    tree id = get_identifier("test"); //Create identifier node
    
    //Create func_decl node
    tree func = build_decl(BUILTINS_LOCATION, FUNCTION_DECL, id, type);
			   //create as builtin

    //tree result = build_decl(BUILTINS_LOCATION, RESULT_DECL, id, type);
    //DECL_RESULT(func) = result;

    debug_tree(func);

    return 0;
}
