#include "lists.h"

/**
 * check_cycle - checks if a singly linked list has a cycle in it
 * @list: pointer to the head of the list
 *
 * Return: 0 if there is no cycle, 1 if there is a cycle
 *
 * Algorithm: Floyd's Cycle Detection Algorithm (Tortoise and Hare)
 * - Use two pointers: slow (tortoise) moves 1 step, fast (hare) moves 2 steps
 * - If there's a cycle, the fast pointer will eventually meet the slow pointer
 * - If there's no cycle, the fast pointer will reach the end (NULL)
 */
int check_cycle(listint_t *list)
{
	listint_t *slow, *fast;

	/* Handle empty list or single node */
	if (list == NULL || list->next == NULL)
		return (0);

	/* Initialize both pointers to the head */
	slow = list;
	fast = list;

	/* Move pointers until fast reaches end or they meet */
	while (fast != NULL && fast->next != NULL)
	{
		slow = slow->next;        /* Move slow pointer 1 step */
		fast = fast->next->next;  /* Move fast pointer 2 steps */

		/* If pointers meet, there's a cycle */
		if (slow == fast)
			return (1);
	}

	/* Fast pointer reached end, no cycle */
	return (0);
}
