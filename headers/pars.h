#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LEN 100


int count_line_space(p_ret_str);//creating exe path, agrs and out path

void create_command_line(char **Line, char **command_line, char **output_path); //creating command line and out path 

int line_counter(FILE *file_pointer);

char* backslash_adder(char *exe_path);