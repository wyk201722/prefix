//#include "vector.h"
#include "map.h"
#include "Prefixspan.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* Globals */
void Usage();
void Version();
void ParseParameters (int argc, char **argv,struct Prefix* prefix);

//vector<string> filenames;
char      filenames[] = "data.txt";
bool           toggle_verbose       = false;
int            min_sup              = 1;    // minimum support for LCM
int            max_pat              = 0;    // maximum_itemset_size : default infinity;

int main(int argc, char* argv[])
{

  Version();
 
  
  struct Prefix prefix;
  ParseParameters(argc, argv, &prefix);
  
  struct Pairdata pairdata;  
  int lines;

  lines = read(&pairdata,&prefix);
  
  prefix.pattern = (int*)malloc(sizeof(int) * 20);
  for(int i = 0; i < 20; i++) {
	prefix.pattern[i] = -1;
  }
  project(&pairdata,&prefix,lines);


  struct Transaction tmp;
 
  //project(pairdata,prefix); 
  //Prefixspan prefixspan(min_sup, max_pat);
  //prefixspan.run(filenames[0]);
  return 0;

}

/*****************************************************************************
 * Version
 ****************************************************************************/
void Version(){
   printf("PrefixSpan version 1.00 - Sequential Pattern Miner\n");
    printf("Written by Yasuo Tabei\n\n");
}

/***************************************************************************
 * Usage
 ***************************************************************************/
void Usage(){

        printf("Usage: prefixspan [OPTION]... INFILE\n");
      	 printf("wwhere [OPTION]...  is a list of zero or more optional arguments\n");
       	 printf(" INFILE(s)    is the name of the input transaction database\n");
          printf("Additional arguments (at most one input file may be specified):\n");
        printf("       -min_sup [minimum support]\n");
        printf("       -max_pat [maximum pattern]\n");
       
  exit(0);
}

/*****************************************************************************
 * ParseParameters
 *****************************************************************************/
void ParseParameters (int argc, char* argv[],struct Prefix* prefix){
 
  if (argc == 1) Usage();
  for (int argno = 1; argno < argc; argno++){
   
    if (argv[argno][0] == '-'){
      if      (!strcmp (argv[argno], "-version")){
	Version();
      }
      else if (!strcmp (argv[argno], "-verbose")) {
	toggle_verbose = true;
      }
      else if (!strcmp (argv[argno], "-min_sup")) {
	if (argno == argc - 1)  printf("Must specify minimum support after -min_sup\n");
	prefix->min_sup = atoi(argv[++argno]);
      }
      else if (!strcmp (argv[argno], "-max_pat")) {
	if (argno == argc - 1)  printf("Must specify miximum itemset size after -max_size\n");
	prefix->max_pat = atoi(argv[++argno]);
      }
    }
    
  }

}

