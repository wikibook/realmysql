// --------------------------------------------------------------------------
// load mysql configuration file
// gcc load_config3.c -o load_config3 `mysql_config --cflags --libs`
// --------------------------------------------------------------------------

#include <my_global.h>
#include <my_sys.h>
#include <mysql.h>
#include <my_getopt.h>

const char* config_groups[] = { "client",  NULL };

char* host_name=NULL;
char* user_name=NULL;
char* user_password=NULL;
char* socket_file=NULL;
unsigned int port_no=0;
char* charset=NULL;
unsigned int flags=0;

struct my_option mysql_configs[] = {
  {"host", 'h', "MySQL server", (uchar **)&host_name, NULL, NULL, 
      GET_STR, REQUIRED_ARG, 0, 0, 0, 0, 0, 0},
  {"user", 'u', "User account", (uchar **)&user_name, NULL, NULL, 
      GET_STR, REQUIRED_ARG, 0, 0, 0, 0, 0, 0},
  {"password", 'p', "User password", (uchar **)&user_password, NULL, NULL, 
      GET_STR, OPT_ARG, 0, 0, 0, 0, 0, 0},
  {"socket", 'S', "Socket file", (uchar **)&socket_file, NULL, NULL, 
      GET_STR, REQUIRED_ARG, 0, 0, 0, 0, 0, 0},
  {"default-character-set", 'c', "Default character set", (uchar **)&charset, NULL, NULL, 
      GET_STR, OPT_ARG, 0, 0, 0, 0, 0, 0},
  {"port", 'P', "MySQL port", (uchar **)&port_no, NULL, NULL, 
      GET_UINT, REQUIRED_ARG, 0, 0, 0, 0, 0, 0},
  { NULL, 0, NULL, NULL, NULL, NULL, GET_NO_ARG, NO_ARG, 0, 0, 0, 0, 0, 0 }
};

my_bool aux_config_reader(int config_id, const struct my_option* config, char *arg){
  // 아무런 처리 없이 그냥 리턴
  return 0;
}

int main(int argc, char *argv[]){
  MY_INIT (argv[0]);
  load_defaults("my", config_groups, &argc, &argv);

  int config_error = handle_options(&argc, &argv, mysql_configs, aux_config_reader);
  if(config_error!=0){
    fprintf(stderr, "Can't load configuration file");
    return;
  }

  fprintf(stdout, "Refined configuration\n");
  fprintf(stdout, "    host : %s\n", host_name);
  fprintf(stdout, "    user: %s\n", user_name);
  fprintf(stdout, "    password: %s\n", user_password);
  fprintf(stdout, "    socket: %s\n", socket_file);
  fprintf(stdout, "    port: %d\n", port_no);
}
