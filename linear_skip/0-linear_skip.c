#include "search.h"

/**
 * linear_skip - searches for a value in a sorted skip list of integers
 * @list: pointer to the head of the skip list to search in
 * @value: value to search for
 *
 * Return: pointer to the first node where value is located, or NULL if not found
 */
skiplist_t *linear_skip(skiplist_t *list, int value)
{
	skiplist_t *express_node, *prev_express, *current;

	if (list == NULL)
		return (NULL);

	express_node = list;
	prev_express = NULL;

	/* Traverse the express lane to find the range */
	while (express_node != NULL)
	{
		printf("Value checked at index [%lu] = [%d]\n",
		       express_node->index, express_node->n);

		if (express_node->n >= value)
			break;

		prev_express = express_node;
		express_node = express_node->express;
	}

	/* Determine the search range */
	if (prev_express == NULL)
	{
		/* Value should be between start and first express node */
		if (express_node != NULL)
		{
			printf("Value found between indexes [%lu] and [%lu]\n",
			       list->index, express_node->index);
		}
		current = list;
	}
	else if (express_node == NULL)
	{
		/* Value should be between last express node and end */
		/* Find the last node */
		skiplist_t *last_node = prev_express;
		while (last_node->next != NULL)
			last_node = last_node->next;

		printf("Value found between indexes [%lu] and [%lu]\n",
		       prev_express->index, last_node->index);
		current = prev_express;
	}
	else
	{
		/* Value should be between prev_express and current express_node */
		printf("Value found between indexes [%lu] and [%lu]\n",
		       prev_express->index, express_node->index);
		current = prev_express;
	}

	/* Linear search in the determined range */
	while (current != NULL)
	{
		printf("Value checked at index [%lu] = [%d]\n",
		       current->index, current->n);

		if (current->n == value)
			return (current);

		if (current->n > value)
			break;

		/* Stop if we've gone beyond the express node boundary */
		if (express_node != NULL && current->index >= express_node->index)
			break;

		current = current->next;
	}

	return (NULL);
}
