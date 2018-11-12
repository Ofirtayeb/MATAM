#include "linked_list.h"

int thread_list_creator(Threads_to_run_s *head,char *file_path) {
	char p_line[MAX_LINE_LEN] = { 0 };
	char *p_ret_str = NULL;
	char *program = NULL;//to malloc it like ilays mom
	char *args_for_thread = NULL;
	char *command_line = NULL;
	char *output_path = NULL;//strcpy? allocate?
	FILE *input_file_stream = NULL;
	Threads_to_run_s *curr;

	errno_t retval;
	retval = fopen_s(&input_file_stream, file_path, "r");

	if (0 != retval)
	{
		printf("Failed to open file.\n");
		return STATUS_CODE_FAILURE;
	}

	p_ret_str = fgets(p_line, MAX_LINE_LEN, input_file_stream);
	if (NULL == p_ret_str)
		return STATUS_CODE_FAILURE;
	create_command_line(&p_ret_str, &command_line, &output_path);
	thread_list_creator_helper_command(head, command_line, output_path);
	//pars_line(&p_ret_str, &program, &args_for_thread, &output_path);
	//thread_list_creator_helper(head, program, args_for_thread, output_path);

	head->next = NULL;
	curr = head;


	p_ret_str = fgets(p_line, MAX_LINE_LEN, input_file_stream);
	while (NULL != p_ret_str)
	{
		Threads_to_run_s *new_Threads_to_run_s;
		new_Threads_to_run_s = (Threads_to_run_s *)malloc(sizeof(Threads_to_run_s));

		//pars_line(&p_ret_str, &program, &args_for_thread, &output_path);
		//thread_list_creator_helper(new_Threads_to_run_s, program, args_for_thread, output_path);

		create_command_line(&p_ret_str, &command_line, &output_path);
		thread_list_creator_helper_command(new_Threads_to_run_s, command_line, output_path);

		new_Threads_to_run_s->next = NULL;
		curr->next = new_Threads_to_run_s;
		curr = new_Threads_to_run_s;
		p_ret_str = fgets(p_line, MAX_LINE_LEN, input_file_stream);
	}
	retval = fclose(input_file_stream);
	if (0 != retval)
		return STATUS_CODE_FAILURE;
	return STATUS_CODE_SUCCESS;
}

void thread_list_creator_helper(Threads_to_run_s *node, char *program, char *args_for_thread, char *output_path) {
	node->program = (char*)malloc(strlen(program) * sizeof(char) + 1);
	if (node->program == NULL) return STATUS_CODE_FAILURE;
	strcpy_s(node->program, strlen(program) + 1, program);

	if (NULL != args_for_thread) {
		node->args_for_thread = (char*)malloc(strlen(args_for_thread) * sizeof(char) + 1);
		if (node->args_for_thread == NULL) return STATUS_CODE_FAILURE;
		strcpy_s(node->args_for_thread, strlen(args_for_thread) + 1, args_for_thread);
	}

	node->output_path = (char*)malloc(strlen(output_path) * sizeof(char) + 1);
	if (node->output_path == NULL) return STATUS_CODE_FAILURE;
	strcpy_s(node->output_path, strlen(output_path) + 1, output_path);
}

void thread_list_creator_helper_command(Threads_to_run_s *node, char *command_line, char *output_path) {
	node->command_line = (char*)malloc(strlen(command_line) * sizeof(char) + 1);
	if (node->command_line == NULL) return STATUS_CODE_FAILURE;
	strcpy_s(node->command_line, strlen(command_line) + 1, command_line);

	node->output_path = (char*)malloc(strlen(output_path) * sizeof(char) + 1);
	if (node->output_path == NULL) return STATUS_CODE_FAILURE;
	strcpy_s(node->output_path, strlen(output_path) + 1, output_path);
}

void print_output(Threads_to_run_s *node, char *file_path) {
	errno_t retval;
	FILE *input_file_stream = NULL;
	Threads_to_run_s *temp = node;
	int test_number = 1;

	retval = fopen_s(&input_file_stream, file_path, "a+");
	if (0 != retval)
	{
		printf("Failed to open file.\n");
		return STATUS_CODE_FAILURE;
	}
	
	while (NULL != temp) {
		switch (temp->status)
		{
		case (0):	fprintf(input_file_stream, "test #%d : %s", test_number, temp->message);//succeded
		case (0x102): fprintf(input_file_stream, "test #%d : %s", test_number, temp->message);//timedout
		case (-69): fprintf(input_file_stream, "test #%d : %s", test_number, temp->message);//faild
		default: fprintf(input_file_stream, "test #%d : %s %d", test_number, temp->message,temp->status);//crashed
			break;
		}
		temp = temp->next;
	}

	retval = fclose(input_file_stream);
	if (0 != retval)
	{
		printf("Failed to close file.\n");
		return STATUS_CODE_FAILURE;
	}
}