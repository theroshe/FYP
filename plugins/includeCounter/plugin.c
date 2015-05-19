
#include "plugin.h"
#include "plugin-version.h"
#include "tree.h"
#include "tree-pass.h"
#include "intl.h"
#include "print-tree.h"

#include "tree-pretty-print.h"

#include <stdlib.h>

int plugin_is_GPL_compatible;

int includeCount = 0;

void includeParse(void * gcc_data, void * user_data)
{
  *((int*) user_data) += 1; //Increment counter
  printf("Include %d: %s\n", *((int*) user_data), (char*) gcc_data);
}


//Called at plugin initialisation
int plugin_init(struct plugin_name_args *plugin_info, struct plugin_gcc_version *version)
{    
  //Check GCC version
  if(!plugin_default_version_check (version, &gcc_version)) {
    printf("This plugin is meant for use with gcc %s\n", version->basever);
    return 1;
  }
  
  register_callback("plugin", PLUGIN_INCLUDE_FILE, includeParse, &includeCount);
  
  return 0;
}
