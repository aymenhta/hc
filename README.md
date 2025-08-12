# HC: Cat clone

This is a simple implementation of the unix cat command written in C, it reads files and outputs their contents to the standard output.

## Features

- Concatenates and displays file contents.
- Supports multiple file inputs.
- Reads from standard input if no files are specified.

## Compilation

To compile the program, use the following command:

```bash
make build
```

## Usage

When running the program with the -h flag, it outputs a simple usage guide with some examples:

```bash
Concatenate FILE(s) to standard output.

USAGE: hc [OPTION]... [FILE]...
With no FILE, or when FILE is -, read standard input.

Options:
	-h, --help: print the application usage
Examples:
	hc f - g         Output f's contents, then standard input, then g's contents.
  hc file*.txt     Output the content of all the files that match the pattern `file*.txt`
	hc               Copy standard input to standard output.
```
