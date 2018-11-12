#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <windows.h>

#define TIMEOUT_IN_MILLISECONDS 10000
#define MAX_MESSAGE_LEN 11
static const int STATUS_CODE_SUCCESS = 0;
static const int STATUS_CODE_FAILURE = -1;


typedef struct Threads_to_run_s{
	HANDLE thread_handle;
	DWORD thread_id;
	DWORD status; //maybe int
	char message[MAX_MESSAGE_LEN];
	char *program;
	char *command_line;
	char *args_for_thread;
	char *output_path;
	struct Threads_to_run_s *next;
}Threads_to_run_s;


DWORD WINAPI test_and_compare(LPVOID lpParam);
HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine, LPVOID **prog_to_test);
static BOOL CreateProcessSimple(LPTSTR p_command_line, PROCESS_INFORMATION *p_process_info);