#include "sort.h"

/**
 * swap - swaps two integers in an array
 * @array: the array
 * @i: first index
 * @j: second index
 * @size: size of the array (for printing)
 */
void swap(int *array, size_t i, size_t j, size_t size)
{
	int temp;

	if (i != j)
	{
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
		print_array(array, size);
	}
}

/**
 * sift_down - maintains the max heap property by sifting down
 * @array: the array representing the heap
 * @start: the start index (root of the subtree)
 * @end: the end index (last element of the heap)
 * @size: size of the original array (for printing)
 */
void sift_down(int *array, size_t start, size_t end, size_t size)
{
	size_t root = start;
	size_t child, swap_idx;

	while (2 * root + 1 <= end)
	{
		child = 2 * root + 1; /* left child */
		swap_idx = root;

		/* Check if left child is greater than root */
		if (array[swap_idx] < array[child])
			swap_idx = child;

		/* Check if right child exists and is greater than current max */
		if (child + 1 <= end && array[swap_idx] < array[child + 1])
			swap_idx = child + 1;

		/* If root is already the largest, heap property is satisfied */
		if (swap_idx == root)
			return;

		/* Swap and continue sifting down */
		swap(array, root, swap_idx, size);
		root = swap_idx;
	}
}

/**
 * heapify - builds a max heap from an unsorted array
 * @array: the array to heapify
 * @size: size of the array
 */
void heapify(int *array, size_t size)
{
	int start;

	/* Start from the last parent node and sift down */
	start = (size - 2) / 2;
	while (start >= 0)
	{
		sift_down(array, start, size - 1, size);
		start--;
	}
}

/**
 * heap_sort - sorts an array of integers in ascending order using heap sort
 * @array: the array to sort
 * @size: size of the array
 */
void heap_sort(int *array, size_t size)
{
	size_t end;

	if (!array || size < 2)
		return;

	/* Build max heap */
	heapify(array, size);

	/* Extract elements from heap one by one */
	end = size - 1;
	while (end > 0)
	{
		/* Move current root to end */
		swap(array, 0, end, size);

		/* Reduce heap size and sift down the new root */
		end--;
		sift_down(array, 0, end, size);
	}
}
