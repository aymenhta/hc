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
  exit(1);
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


void print_usage()
{
  printf("print the content of some file\n\n");
  printf("USAGE:\n");
  printf("\tcat [OPTION]\n");
  printf("OPTIONS\n");
  printf("\t-h, --help: print the application usage\n");
  printf("\tf: the file's path\n");
  exit(0);
}

// TODO: add support for piping
// TODO: add support for pattern matching
int main(int argc, char **argv)
{
  if (argc == 1) print_usage();
  if (argc == 2)
  {
    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
    {
      print_usage();
    }
  }
  // loop through files and display their content to stdout
  for (int i = 1; i < argc; i++)
  {
    printf("----------------------------------------------------------------\n");
    printf("Handling file: %s\n", argv[i]);
    printf("----------------------------------------------------------------\n");
    handle_file(argv[i]); 
  }
  return 0;
}
