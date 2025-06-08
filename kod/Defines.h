#ifndef DEFINES_H
#define DEFINES_H

#include <string>
#include <SFML/System/Time.hpp>

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;
const std::string GAME_TITLE = "Kosmiczny Odkurzacz";

const float PLAYER_SPEED = 200.0f;

// Bazowe wartoœci dla trudnoœci
const float BASE_TRASH_SPEED = 100.0f;
const float BASE_ASTEROID_SPEED = 120.0f; // Nieco wolniej na start dla "Easy"
const sf::Time BASE_TRASH_SPAWN_INTERVAL = sf::seconds(1.5f);
const sf::Time BASE_ASTEROID_SPAWN_INTERVAL = sf::seconds(2.8f); // Nieco rzadziej na start dla "Easy"

const int INITIAL_LIVES = 3;
const std::string HIGHSCORE_FILE = "highscores.txt";
const unsigned int MAX_HIGH_SCORES = 5;  
const unsigned int MAX_PLAYER_NAME_LENGTH = 8;  // Dlugosc nazwy gracza

// Enum dla poziomów trudnoœci
enum class DifficultyLevel {
    Easy,
    Medium,
    Hard
};

#endif // DEFINES_H