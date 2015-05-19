
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

tree handleBitBand(tree_node ** node, tree name, tree args, int flags, bool * no_add_attrs)
{
    //"node" is the node which we applied our attribute to
    //Should be var_decl, since we are instantiating a struct variable

    //Check that the node we have is a var_decl of record_type
    if(TREE_CODE(*node) == VAR_DECL) {
        if(tree decl = TREE_TYPE(*node)) {    
            if(TREE_CODE(decl) == RECORD_TYPE) { 
	      debug_tree(*node);
            }
	    else {
	      printf("****Attribute must be applied to a struct!****\n");
	      //Generate a warning
	    }
	}
    }

    return NULL_TREE;
}


//Called at attribute registration
void attr_reg(void * gcc_data, void * user_data)
{
    //Set up struct with attr information
    //Defined on line 4917 of tree.h
    static struct attribute_spec bit_band = 
      {"bit_band", 0, 1, false, false, false, handleBitBand, false};
    
    register_attribute(&bit_band);
}

//Called at plugin initialisation
int plugin_init(struct plugin_name_args *plugin_info, struct plugin_gcc_version *version)
{
    //Check GCC version
    if(!plugin_default_version_check (version, &gcc_version)) {
        printf("This plugin is meant for use with gcc %s\n", version->basever);
        return 1;
    }

    //Attribute registration
    register_callback("plugin", PLUGIN_ATTRIBUTES, attr_reg, NULL); 

    return 0;
}
