#include "menger.h"

/**
 * is_menger_point - determines if a point should be filled in Menger sponge
 * @x: x coordinate
 * @y: y coordinate
 * @level: current level of recursion
 *
 * Return: 1 if point should be filled, 0 otherwise
 */
int is_menger_point(int x, int y, int level)
{
	/* Base case: level 0 is always filled */
	if (level == 0)
		return (1);

	/* Calculate the size of the current level */
	int size = (int)pow(3, level - 1);

	/* Determine which of the 9 sections this point is in */
	int section_x = x / size;
	int section_y = y / size;

	/* If it's in the center section (1,1), it's empty */
	if (section_x == 1 && section_y == 1)
		return (0);

	/* Recursively check the point within its section */
	return (is_menger_point(x % size, y % size, level - 1));
}

/**
 * menger - draws a 2D Menger Sponge
 * @level: level of the Menger Sponge to draw
 *
 * Description: Draws a 2D Menger sponge of the specified level.
 * If level is lower than 0, the function does nothing.
 */
void menger(int level)
{
	int size, x, y;

	/* Do nothing if level is negative */
	if (level < 0)
		return;

	/* Calculate the size of the sponge */
	size = (int)pow(3, level);

	/* Draw the sponge row by row */
	for (y = 0; y < size; y++)
	{
		for (x = 0; x < size; x++)
		{
			if (is_menger_point(x, y, level))
				printf("#");
			else
				printf(" ");
		}
		printf("\n");
	}
}
