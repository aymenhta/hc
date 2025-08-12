#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


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
