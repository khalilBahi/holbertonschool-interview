#!/usr/bin/python3
"""
Module for calculating minimum operations to reach n H characters
"""


def minOperations(n):
    """
    Calculates the fewest operations to reach exactly n 'H' characters.

    Starting with one H, we can only Copy All and Paste.

    Args:
        n (int): Target number of H characters

    Returns:
        int: Minimum number of operations needed, or 0 if impossible

    The key insight: this is a prime factorization problem.
    For each prime factor p, we do 1 Copy All and (p-1) Pastes,
    which totals p operations. So the minimum operations is the
    sum of all prime factors of n.
    """
    if n <= 1:
        return 0

    operations = 0
    factor = 2

    # Find all prime factors and sum them
    while factor * factor <= n:
        while n % factor == 0:
            operations += factor
            n //= factor
        factor += 1

    # If n is still greater than 1, then it's a prime factor
    if n > 1:
        operations += n

    return operations
