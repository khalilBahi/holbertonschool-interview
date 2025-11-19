#include "palindrome.h"

/**
 * is_palindrome - checks whether or not a given unsigned integer is a palindrome
 * @n: the number to be checked
 *
 * Return: 1 if n is a palindrome, 0 otherwise
 */
int is_palindrome(unsigned long n)
{
	unsigned long original = n;
	unsigned long reversed = 0;

	/* Handle single digit numbers (always palindromes) */
	if (n < 10)
		return (1);

	/* Reverse the number */
	while (n > 0)
	{
		reversed = reversed * 10 + n % 10;
		n /= 10;
	}

	/* Compare original with reversed */
	return (original == reversed ? 1 : 0);
}
