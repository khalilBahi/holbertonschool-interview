#include "binary_trees.h"

/**
 * heap_size - Measures the size of a binary tree
 * @tree: Pointer to the root node of the tree to measure the size
 *
 * Return: Size of the tree, or 0 if tree is NULL
 */
size_t heap_size(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);

	return (1 + heap_size(tree->left) + heap_size(tree->right));
}

/**
 * find_last_level_parent - Find parent for insertion using level order
 * @root: Root of the heap
 *
 * Return: Parent node where next insertion should happen
 */
heap_t *find_last_level_parent(heap_t *root)
{
	heap_t *queue[1024];
	int front = 0, rear = 0;
	heap_t *current;

	if (!root)
		return (NULL);

	queue[rear++] = root;

	while (front < rear)
	{
		current = queue[front++];

		if (!current->left || !current->right)
			return (current);

		queue[rear++] = current->left;
		queue[rear++] = current->right;
	}

	return (NULL);
}

/**
 * heapify_up - Maintains max heap property by bubbling up
 * @node: Pointer to the node to heapify up
 *
 * Return: Pointer to the final position of the node
 */
heap_t *heapify_up(heap_t *node)
{
	int temp;
	heap_t *original_node = node;

	while (node->parent && node->n > node->parent->n)
	{
		temp = node->n;
		node->n = node->parent->n;
		node->parent->n = temp;
		node = node->parent;
	}

	return (original_node);
}

/**
 * heap_insert - Inserts a value into a Max Binary Heap
 * @root: Double pointer to the root node of the Heap
 * @value: Value to store in the node to be inserted
 *
 * Return: Pointer to the inserted node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *new_node, *parent;

	if (root == NULL)
		return (NULL);

	if (*root == NULL)
	{
		*root = binary_tree_node(NULL, value);
		return (*root);
	}

	parent = find_last_level_parent(*root);
	new_node = binary_tree_node(parent, value);
	if (new_node == NULL)
		return (NULL);

	if (parent->left == NULL)
		parent->left = new_node;
	else
		parent->right = new_node;

	return (heapify_up(new_node));
}
