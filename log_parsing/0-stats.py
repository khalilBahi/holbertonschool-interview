#!/usr/bin/python3
"""
Log parsing script that reads stdin line by line and computes metrics.

Input format: <IP Address> - [<date>] "GET /projects/260 HTTP/1.1" <status code> <file size>
Prints statistics every 10 lines and on keyboard interruption (CTRL + C).
"""
import sys
import re


def print_stats(total_size, status_counts):
    """
    Print the current statistics.
    
    Args:
        total_size (int): Total file size accumulated
        status_counts (dict): Dictionary of status code counts
    """
    print("File size: {}".format(total_size))
    
    # Print status codes in ascending order
    valid_status_codes = [200, 301, 400, 401, 403, 404, 405, 500]
    for status_code in valid_status_codes:
        if status_code in status_counts and status_counts[status_code] > 0:
            print("{}: {}".format(status_code, status_counts[status_code]))


def parse_log_line(line):
    """
    Parse a log line and extract status code and file size.
    
    Args:
        line (str): Log line to parse
        
    Returns:
        tuple: (status_code, file_size) or (None, None) if invalid format
    """
    # Expected format: <IP> - [<date>] "GET /projects/260 HTTP/1.1" <status> <size>
    # Use regex to match the exact format
    pattern = r'^(\S+) - \[([^\]]+)\] "GET /projects/260 HTTP/1\.1" (\d+) (\d+)$'
    match = re.match(pattern, line.strip())
    
    if match:
        try:
            status_code = int(match.group(3))
            file_size = int(match.group(4))
            return status_code, file_size
        except ValueError:
            return None, None
    
    return None, None


def main():
    """
    Main function to process log lines from stdin.
    """
    total_size = 0
    status_counts = {}
    line_count = 0
    
    try:
        for line in sys.stdin:
            status_code, file_size = parse_log_line(line)
            
            # Skip invalid lines
            if status_code is None or file_size is None:
                continue
            
            # Update totals
            total_size += file_size
            line_count += 1
            
            # Update status code count
            if status_code in status_counts:
                status_counts[status_code] += 1
            else:
                status_counts[status_code] = 1
            
            # Print stats every 10 lines
            if line_count % 10 == 0:
                print_stats(total_size, status_counts)
    
    except KeyboardInterrupt:
        # Print final stats on keyboard interruption
        print_stats(total_size, status_counts)
        raise


if __name__ == "__main__":
    main()
