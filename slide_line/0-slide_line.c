#include "slide_line.h"

/**
 * slide_left - slides and merges an array to the left
 * @line: pointer to array of integers
 * @size: size of the array
 *
 * Return: 1 on success, 0 on failure
 */
static int slide_left(int *line, size_t size)
{
	size_t i, j, write_pos = 0;

	if (size == 0)
		return (1);

	/* First pass: slide all non-zero elements to the left */
	for (i = 0; i < size; i++)
	{
		if (line[i] != 0)
		{
			if (write_pos != i)
			{
				line[write_pos] = line[i];
				line[i] = 0;
			}
			write_pos++;
		}
	}

	/* Second pass: merge identical adjacent elements */
	for (i = 0; i < write_pos && i < size - 1 && write_pos > 1; i++)
	{
		if (line[i] == line[i + 1] && line[i] != 0)
		{
			line[i] *= 2;
			/* Shift remaining elements left */
			for (j = i + 1; j < size - 1; j++)
				line[j] = line[j + 1];
			line[size - 1] = 0;
			write_pos--;
		}
	}

	return (1);
}

/**
 * slide_right - slides and merges an array to the right
 * @line: pointer to array of integers
 * @size: size of the array
 *
 * Return: 1 on success, 0 on failure
 */
static int slide_right(int *line, size_t size)
{
	size_t i, j;
	int write_pos;

	if (size == 0)
		return (1);

	write_pos = (int)size - 1;

	/* First pass: slide all non-zero elements to the right */
	for (i = size; i > 0; i--)
	{
		if (line[i - 1] != 0)
		{
			if (write_pos != (int)(i - 1))
			{
				line[write_pos] = line[i - 1];
				line[i - 1] = 0;
			}
			write_pos--;
		}
	}

	/* Second pass: merge identical adjacent elements from right */
	for (i = size - 1; i > 0; i--)
	{
		if (line[i] == line[i - 1] && line[i] != 0)
		{
			line[i] *= 2;
			/* Shift remaining elements right */
			for (j = i - 1; j > 0; j--)
				line[j] = line[j - 1];
			line[0] = 0;
		}
	}

	return (1);
}

/**
 * slide_line - slides and merges an array of integers
 * @line: pointer to array of integers
 * @size: size of the array
 * @direction: direction to slide (SLIDE_LEFT or SLIDE_RIGHT)
 *
 * Return: 1 upon success, 0 upon failure
 */
int slide_line(int *line, size_t size, int direction)
{
	if (line == NULL)
		return (0);

	if (direction == SLIDE_LEFT)
		return (slide_left(line, size));
	else if (direction == SLIDE_RIGHT)
		return (slide_right(line, size));
	else
		return (0);
}
