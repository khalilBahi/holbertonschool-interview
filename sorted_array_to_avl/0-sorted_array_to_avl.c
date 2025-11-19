#include "binary_trees.h"

/**
 * create_node - creates a new AVL tree node
 * @parent: pointer to the parent node
 * @value: value to store in the new node
 *
 * Return: pointer to the new node, or NULL on failure
 */
avl_t *create_node(avl_t *parent, int value)
{
	avl_t *new_node;

	new_node = malloc(sizeof(avl_t));
	if (new_node == NULL)
		return (NULL);

	new_node->n = value;
	new_node->parent = parent;
	new_node->left = NULL;
	new_node->right = NULL;

	return (new_node);
}

/**
 * build_avl_recursive - recursively builds AVL tree from sorted array
 * @array: pointer to the first element of the array
 * @start: starting index of the current subarray
 * @end: ending index of the current subarray
 * @parent: pointer to the parent node
 *
 * Return: pointer to the root node of the created subtree, or NULL on failure
 */
avl_t *build_avl_recursive(int *array, int start, int end, avl_t *parent)
{
	avl_t *root;
	int mid;

	if (start > end)
		return (NULL);

	/* Find the middle element */
	mid = start + (end - start) / 2;

	/* Create root node with middle element */
	root = create_node(parent, array[mid]);
	if (root == NULL)
		return (NULL);

	/* Recursively build left and right subtrees */
	root->left = build_avl_recursive(array, start, mid - 1, root);
	root->right = build_avl_recursive(array, mid + 1, end, root);

	return (root);
}

/**
 * sorted_array_to_avl - builds an AVL tree from a sorted array
 * @array: pointer to the first element of the array to be converted
 * @size: number of elements in the array
 *
 * Return: pointer to the root node of the created AVL tree, or NULL on failure
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{
	if (array == NULL || size == 0)
		return (NULL);

	return (build_avl_recursive(array, 0, (int)size - 1, NULL));
}
