#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <map> // Dla mapy ustawieÒ trudnoúci

#include "Defines.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "Player.h"
#include "Trash.h"
#include "Asteroid.h"
#include "HighScoreManager.h"

// Zaktualizowany enum GameState
enum class GameState {
    DifficultySelection, // NOWY STAN
    Playing,
    GameOver,
    ShowingHighScores,
    EnteringName
};

// Struktura do przechowywania ustawieÒ dla danego poziomu trudnoúci
struct DifficultySettings {
    float asteroidSpeedMultiplier;
    sf::Time asteroidSpawnInterval;
    float trashSpeedMultiplier; // Moøemy teø dostosowaÊ úmieci
    sf::Time trashSpawnInterval;
    std::string name;
};

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time dt);
    void render();

    void loadResources();
    void setupTexts();
    void setupDifficultySettings(); // NOWA METODA
    void applyDifficultySettings(); // NOWA METODA do ustawiania interwa≥Ûw itp.
    void setupUIIndicators();      // NOWA METODA do konfiguracji strza≥ek
    void updateUIIndicators();     // NOWA METODA do aktualizacji kolorÛw strza≥ek
    void createFallbackArrows();

    void spawnTrash();
    void spawnAsteroid();
    void checkCollisions();
    void cleanupEntities();
    void resetGame(); // BÍdzie teø resetowaÊ do ekranu wyboru trudnoúci

    void displayGameOver();
    void displayHighScores();
    void displayDifficultySelection(); // NOWA METODA
    void handleNameInput(sf::Event event);


    sf::RenderWindow window;
    TextureManager textureManager;
    FontManager fontManager;
    HighScoreManager highScoreManager;

    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Entity>> gameObjects;
    sf::Sprite backgroundSprite;

    // NOWE SPRITE'Y DLA STRZA£EK WSKAèNIKOWYCH
    sf::Sprite arrowUpSprite;
    sf::Sprite arrowDownSprite;
    sf::Sprite arrowLeftSprite;
    sf::Sprite arrowRightSprite;

    int score;
    GameState gameState;
    DifficultyLevel currentDifficulty; // Aktualnie wybrany poziom
    std::map<DifficultyLevel, DifficultySettings> difficultySettingsMap; // Mapa ustawieÒ

    // Teksty UI
    sf::Text scoreText;
    sf::Text livesText;
    sf::Text gameOverText;
    sf::Text highScoreHeaderText;
    std::vector<sf::Text> highScoreDisplayTexts;
    sf::Text enterNameText;
    sf::Text playerNameInputText;
    sf::Text difficultyTitleText; // NOWE TEKSTY
    std::vector<sf::Text> difficultyOptionTexts; // Dla opcji E, M, H

    sf::Clock spawnClockTrash;
    sf::Clock spawnClockAsteroid;
    sf::Time currentTrashSpawnInterval;    
    sf::Time currentAsteroidSpawnInterval;  

    std::string currentNameInput;
};

#endif // GAME_H