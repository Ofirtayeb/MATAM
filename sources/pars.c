#include "pars.h"

int count_line_space(p_ret_str) {
	int whitespace = 0;
	char *temp = p_ret_str;
	char ch;
	for (int i = 0; i < strlen(p_ret_str); i++) {
		ch = temp[i];
		if (ch == ' ')
			++whitespace;
	}
	return whitespace;
}


char pars_line(char **Line, char **program, char **args_for_thread, char **output_path) {

	char *word = NULL;
	char delim[] = " "; //need to check if i change to space and ,
	char *safty_token = NULL;

	char *P_last_space = NULL;

	if (1 == count_line_space(*Line)) {
		word = strtok_s(*Line, delim, &safty_token); // get program name
		*program = word; // copy the program path to *program
		*args_for_thread = NULL;
		*output_path = strtok_s(safty_token, "\n", &safty_token);//puts \0 insted of \n (need to check) 
		printf("first string: %s \n second string: %s \n third string : %s \n", *program, *args_for_thread, *output_path);


	}
	else {
		word = strtok_s(*Line, delim, &safty_token); // get program name
			*program = word;  // copy the program path to *program
		P_last_space = strrchr(safty_token, ' ');
		*P_last_space = '\0';
		*args_for_thread = safty_token;
		P_last_space += 1;//gets the output file path safty token poits to it
 		*output_path = strtok_s(P_last_space, "\n", &P_last_space);//puts \0 insted of \n
		printf("first string: %s \n second string: %s \n third string : %s \n", *program, *args_for_thread, *output_path);
	}

}

void create_command_line(char **Line, char **command_line, char **output_path) {
	char *P_last_space = NULL;
	P_last_space = strrchr(*Line, ' ');
	*P_last_space = '\0';
	P_last_space += 1;
	*output_path = strtok_s(P_last_space, "\n", &P_last_space);//puts \0 insted of \n
	*command_line = *Line;
}

int line_counter(FILE *file_pointer) {
	int lines = 0;
	char ch;
	while (!feof(file_pointer))
	{
		ch = fgetc(file_pointer);
		if (ch == '\n')
		{
			lines++;
		}
	}
}



char* backslash_adder(char *exe_path) {
	char *temp_string = NULL;
	char c;
	char *pTemp = exe_path;
	temp_string = (char *)malloc((strlen(exe_path)  + char_count_in_str(exe_path,'\\')) * sizeof(char) + 5);
	strcpy_s(temp_string, 3 , "\"");
	printf("temp : %d\n", strlen(temp_string) + 1);
	printf("path : %d\n", strlen(exe_path) + 1);
	strcat_s(temp_string, strlen(exe_path) + strlen(temp_string) +2, exe_path);


	for (int i = 1; i < strlen(temp_string) + 1; i++) {//start with 2 because i dont want to check the "\//
		c = *(temp_string+i);//
		if ('\\' == c) {
			memmove(temp_string + i + 1, temp_string + i, strlen(temp_string) - i + 1);
			//temp_string[i] = '\\';
		}
	}
	strcat_s(temp_string, strlen(exe_path) + strlen(temp_string) + 2 , "\"");

	return temp_string;
}

int char_count_in_str(char *pString, char c) {
	char* pTemp = pString;
	int count = 0;
	while (pTemp != NULL)
	{
		pTemp = strchr(pTemp, c);
		if (pTemp) {
			pTemp++;
			count++;
		}
	}
}



