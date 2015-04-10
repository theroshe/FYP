
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

static unsigned int includeCount = 0;
static unsigned int intCount = 0;

typedef struct pluginStats {
  int includeCount;
  int intCount;
};



//Node to which the atribute will be applied
//Name of the attribute
//TREE_LIST of the arguments (may be null)
//Flags
//Set no_add_attrs on error to prevent attribute application

/*tree_node**/
tree handleBitBand(tree_node ** node, tree name, tree args, int flags, bool * no_add_attrs)
{
    //node is the node which we applied our attribute to
    //Should be var_decl, since we are instantiating a struct variable

    //Check that the node we have is a var_decl of record_type (i.e is a struct declaration)
    if(TREE_CODE(*node) == VAR_DECL) {
        if(tree decl = TREE_TYPE(*node)) {    //Get type of declaration (need to check if non null)
            //printf("%s\n", get_tree_code_name(TREE_CODE(t)));
            if(TREE_CODE(decl) == RECORD_TYPE) { //If type is record...
                //printf("Record found!\n");
                //debug_tree(*node);
            }
            else {
                //printf("Not a record!\n");
                //Generate a warning
            }
        }
    }
    else {
        //printf("Not a variable declaration!\n");
        //Generate a warning
    }

    return NULL_TREE;

    //Tree codes are defined in tree.def

    //args is the list of arguments to the attribute

    //  debug_tree(*node);
    //debug_tree(TREE_CHAIN(*node));
    //debug_tree_chain (*node);

    //tree_node * current = *node;

    /*  fputs("\n\n", stderr);

    while(current)
    {
    print_node_brief(stderr, "", current, 0);
    current = TREE_CHAIN(current);
}

//print_node_brief(stderr, "", TREE_CHAIN(*node), 0);
fputs("\n\n", stderr);
*/

int hash;
struct bucket *b;
enum machine_mode mode;
enum tree_code_class tclass;
int len;
int i;
expanded_location xloc;
enum tree_code code;

//code = TREE_CODE(*node);
//tclass = TREE_CODE_CLASS(code);

//  print_node(
//	    dump_addr

/*

if(TREE_CODE(*node) == RECORD_TYPE)
{
/*      printf("RECORD_TYPE\n");
printf("%d\n", RECORD_OR_UNION_TYPE_P(*node));
printf("%d\n", TYPE_P(*node));
printf("%d\n", TREE_TYPE(*node));
printf("%d\n", TREE_ADDRESSABLE(*node));
printf("%d\n", TREE_STATIC(*node));
printf("%d\n", TREE_THIS_VOLATILE(*node));
printf("%d\n", TREE_READONLY(*node));
printf("%d\n", TYPE_NAME(*node));
printf("%d\n", TYPE_ADDR_SPACE(*node));

//type_bino
//type_attributes

//look at tree code documentation in tree.def
if(!TREE_USED(*node))
{
printf("Node unused!\n");
}

debug_tree(*node);

}

else if(TREE_CODE(*node) == TYPE_DECL)
{
printf("TYPE_DECL\n");

}
else
{
printf("Invalid type\n");
}

*/
}


//Called at end of plugin
void gcc_end(void * gcc_data, void * user_data)
{
    int *intCount = (int*) user_data;

    printf("Compilation finished.\n");
    printf("There were %d includes\n", *intCount);
}

void includeParse(void * gcc_data, void * user_data)
{
    printf("Include: %s\n", (char*) gcc_data);
    *((int*) user_data) += 1;
}

//User data = int intCount, which is incremented for each int decl
void declParse(void * gcc_data, void * user_data)
{
    //Gcc data is the decl node which has been parsed
    tree decl = (tree) gcc_data;

    if(DECL_IS_BUILTIN(decl)) {     //We don't want decls which are not from the source program
        printf("Builtin\n");
        return;
    }

    if(TREE_CODE(decl) == VAR_DECL) {                                   //If node is a variable declaration...
        if(TREE_CODE(TREE_TYPE(decl)) == INTEGER_TYPE) {                //...which declares an integer...
            printf("int %s: %s:%d\n", IDENTIFIER_POINTER(DECL_NAME(decl)), DECL_SOURCE_FILE(decl), DECL_SOURCE_LINE(decl));    //...print the declaration's identifier
            *((int*) user_data) += 1;                                   //Increment intCount
            tree test = DECL_ATTRIBUTES(decl);                          //Get list of decl attributes
            debug_tree(test);
        }
    }
}

//Called at attribute registration
void attr_reg(void * gcc_data, void * user_data)
{
    //printf("Attribute registration\n");

    //Set up struct with attr information
    //Defined on line 4917 of tree.h
    static struct attribute_spec bit_band = {"bit_band", 0, 1, false, false, false, handleBitBand, false};
    //Name, min argc, max argc, decl_required, type_required, function_type_required,
    //function handler, affects_type_identity
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



    //printf("%s\n%s\n%s\n%s\n", plugin_info->base_name, plugin_info->full_name,
    // plugin_info->version, plugin_info->help);

    //Register callback functions for GCC events
    //Events are defined in plugin.def
    //Final parameter is a pointer to user data

    register_callback("plugin", PLUGIN_ATTRIBUTES, attr_reg, NULL); //Attribute registration

    register_callback("plugin", PLUGIN_FINISH_DECL, declParse, &intCount); //After decl parsing
    register_callback("plugin", PLUGIN_FINISH, gcc_end, &includeCount); //End of plugin

    register_callback("plugin", PLUGIN_INCLUDE_FILE, includeParse, &includeCount);

    //printf("Plugin loaded successfully\n");
    return 0;
}
