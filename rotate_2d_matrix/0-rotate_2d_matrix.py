#!/usr/bin/python3
"""Rotate 2D Matrix in-place by 90 degrees clockwise."""

from typing import List


def rotate_2d_matrix(matrix):
    """
    Rotates an n x n 2D matrix 90 degrees clockwise in place.

    Args:
        matrix (list of list of int): The matrix to rotate.
    """
    n = len(matrix)

    # Transpose the matrix (flip over the diagonal)
    for i in range(n):
        for j in range(i + 1, n):
            matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]

    # Reverse each row
    for row in matrix:
        row.reverse()
