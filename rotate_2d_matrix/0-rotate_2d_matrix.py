#!/usr/bin/python3
"""Rotate 2D Matrix in-place by 90 degrees clockwise."""

from typing import List


def rotate_2d_matrix(matrix: List[List[int]]) -> None:
	"""Rotate an n x n 2D matrix 90 degrees clockwise in-place.

	Args:
		matrix: Square matrix represented as a list of lists.

	The function modifies the matrix in-place and does not return anything.
	"""
	n = len(matrix)
	if n == 0:
		return

	# Transpose the matrix in-place
	for i in range(n):
		for j in range(i + 1, n):
			matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]

	# Reverse each row to complete 90-degree clockwise rotation
	for i in range(n):
		matrix[i].reverse()
