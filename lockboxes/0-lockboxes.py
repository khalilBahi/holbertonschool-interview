#!/usr/bin/python3
"""
Module for solving the lockboxes problem
"""


def canUnlockAll(boxes):
    """
    Determines if all boxes can be opened.
    
    Args:
        boxes: List of lists where each inner list contains keys to other boxes
        
    Returns:
        True if all boxes can be opened, False otherwise
        
    The algorithm uses BFS to traverse through all reachable boxes:
    1. Start with box 0 (always unlocked)
    2. Use a queue to process boxes and a set to track opened boxes
    3. For each box, collect all keys and add unopened boxes to the queue
    4. Continue until no more boxes can be opened
    5. Check if all boxes have been opened
    """
    if not boxes or len(boxes) == 0:
        return True
    
    n = len(boxes)
    opened = set([0])  # Box 0 is always unlocked
    queue = [0]  # Start with box 0
    
    while queue:
        current_box = queue.pop(0)
        
        # Get all keys from current box
        for key in boxes[current_box]:
            # Check if key corresponds to a valid box and box is not opened yet
            if 0 <= key < n and key not in opened:
                opened.add(key)
                queue.append(key)
    
    # Check if all boxes have been opened
    return len(opened) == n
