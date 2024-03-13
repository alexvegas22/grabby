#include <stdio.h>
#include <string.h>
#include "gui.h"

char * version = "v0.0.1";
char * name = "grabby";

void printHelp() {
  printf("Usage: %s [OPTIONS]\n",name);
  printf("Options:\n");
  printf("  -h, --help        Display this help message\n");
  printf("  -v, --version     Display the version\n");
  printf("  -o, --output      Set the output file\n");
  printf("Arguments:\n");
  printf("  gui               Open grabby's GUI\n");
}

int
main(int argc, char **argv)
{
  if (argc>1){
    if (strncmp(argv[1], "-v",2)==0 || strncmp(argv[1], "--version",9) == 0){
        printf("%s\n", version);
    }
    
    if (strncmp(argv[1], "-h", 2)==0 || strncmp(argv[1], "--help", 6) == 0){
      printHelp();
    }
    if (strncmp(argv[1], "gui", 3)==0){
      startGui();
    }
  }
  else{
    printf("%s: No arguments provided\n", name);
  }
    return 0;
}
