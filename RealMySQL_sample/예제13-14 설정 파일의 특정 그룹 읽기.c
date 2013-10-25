// --------------------------------------------------------------------------
// load mysql configuration file
// gcc load_config2.c -o load_config2 `mysql_config --cflags --libs`
// --------------------------------------------------------------------------

#include <my_global.h>
#include <my_sys.h>
#include <mysql.h>

static const char* config_groups[] = { "custom_group", "client",  NULL };

int main(int argc, char *argv[]){
  MY_INIT (argv[0]);
  load_defaults("my", config_groups, &argc, &argv);

  int param_idx=0;
  for (param_idx = 0; param_idx < argc; param_idx++){
    printf ("    parameter %d: %s\n", param_idx, argv[param_idx]);
  }
}
