#!/usr/bin/node
/**
 * Script that prints all characters of a Star Wars movie
 * Usage: ./0-starwars_characters.js <movie_id>
 */

const request = require('request');

// Get movie ID from command line arguments
const movieId = process.argv[2];

if (!movieId) {
  console.error('Usage: ./0-starwars_characters.js <movie_id>');
  process.exit(1);
}

// Star Wars API base URL
const baseUrl = 'https://swapi.dev/api';

// Request options to handle SSL issues
const requestOptions = {
  rejectUnauthorized: false,
  timeout: 10000
};

/**
 * Fetch character name from character URL
 * @param {string} characterUrl - URL to character endpoint
 * @returns {Promise} Promise that resolves to character name
 */
function fetchCharacterName (characterUrl) {
  return new Promise((resolve, reject) => {
    request({ ...requestOptions, url: characterUrl }, (error, response, body) => {
      if (error) {
        reject(error);
        return;
      }

      if (response.statusCode !== 200) {
        reject(new Error(`HTTP ${response.statusCode}`));
        return;
      }
      try {
        const character = JSON.parse(body);
        resolve(character.name);
      } catch (parseError) {
        reject(parseError);
      }
    });
  });
}

/**
 * Fetch all character names in order
 * @param {Array} characterUrls - Array of character URLs
 * @returns {Promise} Promise that resolves to array of character names
 */
async function fetchAllCharacters (characterUrls) {
  const characterNames = [];
  // Fetch characters sequentially to maintain order
  for (const url of characterUrls) {
    try {
      const name = await fetchCharacterName(url);
      characterNames.push(name);
    } catch (error) {
      console.error(`Error fetching character from ${url}:`, error.message);
    }
  }
  return characterNames;
}

// Main execution
const filmUrl = `${baseUrl}/films/${movieId}/`;

request({ ...requestOptions, url: filmUrl }, async (error, response, body) => {
  if (error) {
    console.error('Error fetching film:', error.message);
    process.exit(1);
  }
  if (response.statusCode !== 200) {
    console.error(`Error: HTTP ${response.statusCode}`);
    process.exit(1);
  }
  try {
    const film = JSON.parse(body);
    if (!film.characters || !Array.isArray(film.characters)) {
      console.error('No characters found for this film');
      process.exit(1);
    }
    // Fetch all character names and print them
    const characterNames = await fetchAllCharacters(film.characters);
    // Print each character name on a new line
    characterNames.forEach(name => {
      console.log(name);
    });
  } catch (parseError) {
    console.error('Error parsing film data:', parseError.message);
    process.exit(1);
  }
});
