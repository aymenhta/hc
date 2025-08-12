#pragma once


#include "./utils.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>


void handle_file(const char* file_path)
{
  if (!check_file_exists(file_path))
  {
    panic("file doesn't exist!!");
  }
  
  FILE *f;
  f = fopen(file_path, "rb");
  if (f == NULL)
  {
    panic("couldn't open file");
  }

  int c = fgetc(f);
  while (feof(f) == 0)
  {
    printf("%c", c);
    c = fgetc(f);
  }

  if (ferror(f) != 0)
  {
    panic("error occured while reading file...");  
  }

  fflush(f);  
  fclose(f);
}


void handle_stdin()
{
  int c = fgetc(stdin);
  while(feof(stdin) == 0)
  {
    printf("%c", c);
    c = fgetc(stdin);
  }
}


void handle_file_paths(glob_t *globbuf)
{
  for (size_t i = 0; i < globbuf->gl_pathc; i++)
  {
      if (strcmp(globbuf->gl_pathv[i], "-") == 0)
      {
        handle_stdin();
        continue;
      }
      handle_file(globbuf->gl_pathv[i]); 
  }
}


void set_paths_with_pattern_matching(glob_t *globbuf, int argc, char **argv)
{
  if (globbuf == NULL)
  {
    panic("glob handler cannot be null");  
  }

  if (argc <= 1 || argv == NULL)
  {
    panic("cannot operate on an empty set of patterns");
  }
  
  int ret = 0;
  globbuf->gl_pathc = 0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-") == 0)
    {
      ret = glob("-", GLOB_NOSORT | GLOB_APPEND | GLOB_NOCHECK, NULL, globbuf);
    }
    else
    {
      ret = glob(argv[i], GLOB_NOSORT | GLOB_APPEND, NULL, globbuf);
    }
    if (ret != 0)
    {
      panic("error occurred while using glob for pattern");
    }
  }
}


void exec_hc(int argc, char **argv)
{  
  if (argc == 1)
  {
    handle_stdin();
  }
  
  if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0))
  {
      print_usage();
  }

  glob_t globbuf = {0};
  set_paths_with_pattern_matching(&globbuf, argc, argv);
  handle_file_paths(&globbuf);
  globfree(&globbuf);
}
