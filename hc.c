#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

void panic(const char* err)
{
  if (err != NULL)
  {
    perror(err);
  }
  exit(EXIT_FAILURE);
}


bool check_file_exists(const char* file_path)
{
  if (file_path == NULL)
  {
    return false;
  }
  
  if (access(file_path, F_OK) == 0)
  {
    return true;
  }
  
  return false;
} 


void handle_file(const char* file_path)
{
  // check if file exists
  if (!check_file_exists(file_path))
  {
    panic("file doesn't exist!!");
  }
  
  // open file
  FILE *f;
  f = fopen(file_path, "rb");
  if (f == NULL)
  {
    panic("couldn't open file");
  }

  // print content to stdout
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
  
  // close file
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

void print_usage()
{
  printf("Concatenate FILE(s) to standard output.\n\n");
  printf("USAGE: hc [OPTION]... [FILE]...\n");
  printf("With no FILE, or when FILE is -, read standard input.\n\n");
  printf("Options:\n");
  printf("\t-h, --help: print the application usage\n");
  printf("Examples:\n");
  printf("\thc f - g  Output f's contents, then standard input, then g's contents.\n");
  printf("\thc        Copy standard input to standard output.\n");
  exit(EXIT_SUCCESS);
}

// TODO: add support for pattern matching
int main(int argc, char **argv)
{
  if (argc == 1)
  {
    handle_stdin();
  }
  
  if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0))
  {
      print_usage();
  }

  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-") == 0)
    {
      handle_stdin();
      continue;
    }
    handle_file(argv[i]); 
  }

  return EXIT_SUCCESS;
}
