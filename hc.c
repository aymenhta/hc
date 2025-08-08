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
  if (file_path == NULL) return false;
  if (access(file_path, F_OK) == 0) return true;
  return false;
} 


void handle_file(const char* file_path)
{
  // check if file exists
  if (!check_file_exists(file_path)) panic("file doesn't exist!!");

  // open file
  FILE *f;
  f = fopen(file_path, "rb");
  if (f == NULL) panic("couldn't open file");

  // print content to stdout
  int c = fgetc(f);
  while (feof(f) == 0) {
    printf("%c", c);
    c = fgetc(f);
  }

  // close file
  fclose(f);
}

void handle_stdin()
{
  int c = fgetc(stdin);
  while(feof(stdin) == 0 && c != 0) {
    printf("%c", c);
    c = fgetc(stdin);
  }
}

void print_usage()
{
  printf("print the content of some file\n\n");
  printf("USAGE:\n");
  printf("\tcat [OPTION]\n");
  printf("OPTIONS\n");
  printf("\t-h, --help: print the application usage\n");
  printf("\tf: the file's path\n");
  exit(EXIT_SUCCESS);
}

// TODO: add support for pattern matching
int main(int argc, char **argv)
{
  if (argc == 1) handle_stdin();
  if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0))
  {
      print_usage();
  }

  // loop through files and display their content to stdout
  for (int i = 1; i < argc; i++)
  {
    handle_file(argv[i]); 
  }

  return EXIT_SUCCESS;
}
