#include "shell.h"

int number_len(int number);
char *_itoa(int number);
int create_error(char **args, int err);

/**
 * num_len - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int number_len(int number)
{
	unsigned int number1;
	int len = 1;

	if (number < 0)
	{
		len++;
		number1 = number * -1;
	}
	else
	{
		number1 = number;
	}
	while (number1 > 9)
	{
		len++;
		number1 /= 10;
	}

	return (len);
}

/**
 * _itoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *_itoa(int number)
{
	char *buffer;
	int len = number_len(number);
	unsigned int number1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (number < 0)
	{
		number1 = number * -1;
		buffer[0] = '-';
	}
	else
	{
		number1 = number;
	}

	len--;
	do {
		buffer[len] = (number1 % 10) + '0';
		number1 /= 10;
		len--;
	} while (number1 > 0);

	return (buffer);
}


/**
 * create_error - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int create_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = error_env(args);
		break;
	case 1:
		error = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error_2_syntax(args);
		else
			error = error_2_cd(args);
		break;
	case 126:
		error = error_126(args);
		break;
	case 127:
		error = error_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}
