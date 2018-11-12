#pragma once
#include "pars.h"
#include "threading.h" 



int thread_list_creator(Threads_to_run_s *head, char *file_path);
void thread_list_creator_helper(Threads_to_run_s *node, char *program, char *args_for_thread, char *output_path);
void thread_list_creator_helper_command(Threads_to_run_s *node, char *command_line, char *output_path);
void print_output(Threads_to_run_s *node, char *file_path);