#!/usr/bin/python3
"""
Recursive function that queries the Reddit API and counts keywords
in hot article titles.
"""
import re
import requests


def count_words(subreddit, word_list, after=None, word_count=None):
    """
    Recursively queries the Reddit API, parses the title of all hot articles,
    and prints a sorted count of given keywords.

    Args:
        subreddit (str): The subreddit to query
        word_list (list): List of keywords to count (case-insensitive)
        after (str): Reddit pagination parameter for next page
        word_count (dict): Dictionary to accumulate word counts
    """
    # Initialize word_count dictionary on first call
    if word_count is None:
        word_count = {}
        # Initialize all words in word_list to 0 (case-insensitive)
        for word in word_list:
            word_lower = word.lower()
            word_count[word_lower] = 0

    # Set up the request
    url = f"https://www.reddit.com/r/{subreddit}/hot.json"
    headers = {
        "User-Agent": "count_words_script:v1.0(by /u/holberton_student)"
    }
    params = {"limit": 100}

    if after:
        params["after"] = after

    try:
        # Make the request (don't follow redirects)
        response = requests.get(
            url, headers=headers, params=params, allow_redirects=False
        )

        # Check if subreddit is invalid (redirects or not found)
        if response.status_code != 200:
            return

        data = response.json()

        # Check if we got valid subreddit data
        if "data" not in data or "children" not in data["data"]:
            return

        posts = data["data"]["children"]

        # If no posts, we're done
        if not posts:
            # Print results only on the final call
            _print_results(word_count)
            return

        # Process each post title
        for post in posts:
            if "data" in post and "title" in post["data"]:
                title = post["data"]["title"].lower()

                # Count occurrences of each word in the title
                for word in word_list:
                    word_lower = word.lower()
                    # Use word boundaries to match whole words only
                    pattern = r"\b" + re.escape(word_lower) + r"\b"
                    matches = re.findall(pattern, title)
                    word_count[word_lower] += len(matches)

        # Check if there are more pages
        after_token = data["data"].get("after")

        if after_token:
            # Recursive call for next page
            count_words(subreddit, word_list, after_token, word_count)
        else:
            # No more pages, print results
            _print_results(word_count)

    except (requests.RequestException, ValueError, KeyError):
        # If any error occurs, silently return (print nothing)
        return


def _print_results(word_count):
    """
    Print the word count results in the required format.

    Args:
        word_count (dict): Dictionary with word counts
    """
    # Filter out words with zero counts
    filtered_counts = {word: count for word,
                       count in word_count.items() if count > 0}

    if not filtered_counts:
        return

    # Sort by count (descending) then by word (ascending)
    sorted_words = sorted(filtered_counts.items(), key=lambda x: (-x[1], x[0]))

    # Print results
    for word, count in sorted_words:
        print(f"{word}: {count}")
