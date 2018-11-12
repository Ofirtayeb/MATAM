#include "main.h"



int main(int argc, char *argv[])
{
	Threads_to_run_s *head_Threads_to_run_s = NULL;
	Threads_to_run_s *temp_Threads_to_run_s = NULL;
	FILE *input_file_stream = NULL;
	char p_line[MAX_LINE_LEN] = { 0 };
	char *p_ret_str = NULL;
	char *program = NULL;//to malloc it like ilays mom
	char *args_for_thread = NULL;
	char *output_path=NULL;//strcpy? allocate?
	int num_of_lines = 0;
	int handle_index = 0;
	HANDLE *arr_of_thread_handles = NULL;
	DWORD dwMilliseconds = INFINITY;//maybe need to be in h file


	num_of_lines = line_counter(input_file_stream);//we might need number of lines in the file
	arr_of_thread_handles = (HANDLE *)malloc(sizeof(HANDLE)*num_of_lines);



	head_Threads_to_run_s = (Threads_to_run_s*)malloc(sizeof(Threads_to_run_s));
	thread_list_creator(head_Threads_to_run_s, argv[1]);
	temp_Threads_to_run_s = head_Threads_to_run_s;

	while (NULL != temp_Threads_to_run_s) {


		CreateThreadSimple(test_and_compare, &temp_Threads_to_run_s);

		arr_of_thread_handles[handle_index] = temp_Threads_to_run_s->thread_handle;
		handle_index++;
		temp_Threads_to_run_s = temp_Threads_to_run_s->next;
	}

	WaitForMultipleObjects(num_of_lines, arr_of_thread_handles,1,dwMilliseconds);
	print_output(head_Threads_to_run_s, argv[2]);

	//free all slaves like ilya's mom. she is my slave.
	//close handles
	return 0;
}