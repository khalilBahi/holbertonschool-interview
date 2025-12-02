#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Assuming _putchar is provided in _putchar.c */
int _putchar(char c);

/**
 * error_exit - Prints "Error" and exits with status 98
 */
void error_exit(void)
{
	char *error = "Error\n";

	while (*error)
		_putchar(*error++);
	exit(98);
}

/**
 * is_digit_string - Checks if a string contains only digits
 * @str: String to check
 * Return: 1 if all characters are digits, 0 otherwise
 */
int is_digit_string(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

/**
 * multiply_digits - Multiplies two numbers represented as strings
 * @num1: First number
 * @num2: Second number
 * @len1: Length of num1
 * @len2: Length of num2
 * Return: Pointer to result array, or NULL on failure
 */
int *multiply_digits(char *num1, char *num2, size_t len1, size_t len2)
{
	int *result;
	size_t i, j;
	int carry, product;

	/* Allocate result array (max digits = len1 + len2) */
	result = calloc(len1 + len2, sizeof(int));
	if (!result)
		return (NULL);

	/* Multiply digits */
	for (i = 0; i < len1; i++)
	{
		carry = 0;
		for (j = 0; j < len2; j++)
		{
			product = (num1[len1 - 1 - i] - '0') * (num2[len2 - 1 - j] - '0') +
				result[i + j] + carry;
			result[i + j] = product % 10;
			carry = product / 10;
		}
		result[i + j] = carry;
	}

	return (result);
}

/**
 * print_result - Prints the result array, skipping leading zeros
 * @result: Array of digits
 * @len: Length of the result array
 */
void print_result(int *result, size_t len)
{
	size_t i = len;
	int started = 0;

	/* Find first non-zero digit */
	while (i > 0)
	{
		i--;
		if (result[i] != 0)
			started = 1;
		if (started)
			_putchar(result[i] + '0');
	}
	/* If result is 0, print a single 0 */
	if (!started)
		_putchar('0');
	_putchar('\n');
}

/**
 * main - Multiplies two positive numbers provided as arguments
 * @argc: Number of arguments
 * @argv: Array of argument strings
 * Return: 0 on success, 98 on error
 */
int main(int argc, char *argv[])
{
	char *num1, *num2;
	size_t len1, len2;
	int *result;

	/* Check for correct number of arguments */
	if (argc != 3)
		error_exit();

	num1 = argv[1];
	num2 = argv[2];

	/* Validate inputs are digit strings */
	if (!is_digit_string(num1) || !is_digit_string(num2))
		error_exit();

	len1 = strlen(num1);
	len2 = strlen(num2);

	/* Handle case where either number is "0" */
	if ((len1 == 1 && num1[0] == '0') || (len2 == 1 && num2[0] == '0'))
	{
		_putchar('0');
		_putchar('\n');
		return (0);
	}

	/* Perform multiplication */
	result = multiply_digits(num1, num2, len1, len2);
	if (!result)
		error_exit();

	/* Print result */
	print_result(result, len1 + len2);

	/* Free allocated memory */
	free(result);

	return (0);
}

