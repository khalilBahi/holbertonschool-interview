#!/usr/bin/python3
"""
UTF-8 Validation Module

This module contains a function to validate if a given data set
represents a valid UTF-8 encoding.
"""


def validUTF8(data):
    """
    Determines if a given data set represents a valid UTF-8 encoding.
    
    Args:
        data: List of integers representing bytes of data
        
    Returns:
        True if data is a valid UTF-8 encoding, else False
        
    UTF-8 encoding rules:
    - 1-byte chars: 0xxxxxxx (0-127)
    - 2-byte chars: 110xxxxx 10xxxxxx
    - 3-byte chars: 1110xxxx 10xxxxxx 10xxxxxx
    - 4-byte chars: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    """
    if not data:
        return True
    
    i = 0
    while i < len(data):
        # Get the 8 least significant bits
        byte = data[i] & 0xFF
        
        # Determine how many bytes this character should have
        num_bytes = 0
        
        if (byte >> 7) == 0:  # 0xxxxxxx
            num_bytes = 1
        elif (byte >> 5) == 0b110:  # 110xxxxx
            num_bytes = 2
        elif (byte >> 4) == 0b1110:  # 1110xxxx
            num_bytes = 3
        elif (byte >> 3) == 0b11110:  # 11110xxx
            num_bytes = 4
        else:
            # Invalid starting byte
            return False
        
        # Check if we have enough bytes remaining
        if i + num_bytes > len(data):
            return False
        
        # For multi-byte characters, check continuation bytes
        for j in range(1, num_bytes):
            continuation_byte = data[i + j] & 0xFF
            # Continuation bytes must be 10xxxxxx
            if (continuation_byte >> 6) != 0b10:
                return False
        
        # Move to the next character
        i += num_bytes
    
    return True
