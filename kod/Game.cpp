#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>

Game::Game()
    : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), GAME_TITLE),
    score(0),
    gameState(GameState::DifficultySelection),
    currentDifficulty(DifficultyLevel::Easy)
    // currentTrashSpawnInterval i currentAsteroidSpawnInterval zostanπ ustawione w applyDifficultySettings
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    try {
        loadResources();
        setupDifficultySettings();
        backgroundSprite.setTexture(textureManager.get("background"));
        sf::Vector2u textureSize = textureManager.get("background").getSize();
        backgroundSprite.setScale(
            static_cast<float>(SCREEN_WIDTH) / textureSize.x,
            static_cast<float>(SCREEN_HEIGHT) / textureSize.y
        );
        setupTexts();
        setupUIIndicators();
        player = std::make_unique<Player>(textureManager);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Failed to initialize game: " << e.what() << std::endl;
        window.close();
    }
}

void Game::setupDifficultySettings() {
    difficultySettingsMap[DifficultyLevel::Easy] = {
        1.0f, BASE_ASTEROID_SPAWN_INTERVAL,
        1.0f, BASE_TRASH_SPAWN_INTERVAL,
        "Easy"
    };
    difficultySettingsMap[DifficultyLevel::Medium] = {
        1.5f, BASE_ASTEROID_SPAWN_INTERVAL * 0.7f, // Szybsze i czÍstsze asteroidy
        1.1f, BASE_TRASH_SPAWN_INTERVAL * 0.9f,
        "Medium"
    };
    difficultySettingsMap[DifficultyLevel::Hard] = {
        2.0f, BASE_ASTEROID_SPAWN_INTERVAL * 0.5f, // Jeszcze szybsze i czÍstsze
        1.2f, BASE_TRASH_SPAWN_INTERVAL * 0.8f,
        "Hard"
    };
}

void Game::updateUIIndicators() {
    const sf::Color inactiveColor(100, 100, 100, 200);
    const sf::Color activeColor = sf::Color::Yellow;

    // Strza≥ka W G”R 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        arrowUpSprite.setColor(activeColor);
    }
    else {
        arrowUpSprite.setColor(inactiveColor);
    }

    // Strza≥ka W D”£
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        arrowDownSprite.setColor(activeColor);
    }
    else {
        arrowDownSprite.setColor(inactiveColor);
    }

    // Strza≥ka W LEWO
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        arrowLeftSprite.setColor(activeColor);
    }
    else {
        arrowLeftSprite.setColor(inactiveColor);
    }

    // Strza≥ka W PRAWO
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        arrowRightSprite.setColor(activeColor);
    }
    else {
        arrowRightSprite.setColor(inactiveColor);
    }
}

void Game::applyDifficultySettings() {
    const auto& settings = difficultySettingsMap[currentDifficulty];
    currentAsteroidSpawnInterval = settings.asteroidSpawnInterval;
    currentTrashSpawnInterval = settings.trashSpawnInterval;
    // PrÍdkoúci bÍdπ uøywane bezpoúrednio z settings.asteroidSpeedMultiplier i settings.trashSpeedMultiplier
    // w metodach spawnTrash i spawnAsteroid.
    std::cout << "Difficulty set to: " << settings.name
        << " Asteroid Interval: " << currentAsteroidSpawnInterval.asSeconds() << "s"
        << " Trash Interval: " << currentTrashSpawnInterval.asSeconds() << "s" << std::endl;
}

void Game::loadResources() {
    std::cout << "Loading resources..." << std::endl;

    try {
        textureManager.load("player", "assets/player.png");
        std::cout << "Player texture loaded" << std::endl;

        textureManager.load("trash", "assets/trash.png");
        std::cout << "Trash texture loaded" << std::endl;

        textureManager.load("asteroid", "assets/asteroid.png");
        std::cout << "Asteroid texture loaded" << std::endl;

        textureManager.load("background", "assets/background.png");
        std::cout << "Background texture loaded" << std::endl;

        std::cout << "Loading arrow textures..." << std::endl;

        textureManager.load("arrow_up", "assets/arrow_up.png");
        std::cout << "Arrow up texture loaded successfully" << std::endl;

        textureManager.load("arrow_down", "assets/arrow_down.png");
        std::cout << "Arrow down texture loaded successfully" << std::endl;

        textureManager.load("arrow_left", "assets/arrow_left.png");
        std::cout << "Arrow left texture loaded successfully" << std::endl;

        textureManager.load("arrow_right", "assets/arrow_right.png");
        std::cout << "Arrow right texture loaded successfully" << std::endl;

        // Fonts
        fontManager.load("main_font", "assets/font.ttf");
        std::cout << "Font loaded successfully" << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Error loading resources: " << e.what() << std::endl;
        throw;
    }
}



void Game::setupUIIndicators() {
    const sf::Color inactiveColor(100, 100, 100, 200);
    float scale = 1.0f; // Moøna dostosowaÊ skalÍ strza≥ek

    // Strza≥ka W G”R 
    arrowUpSprite.setTexture(textureManager.get("arrow_up"));
    arrowUpSprite.setScale(scale, scale);
    arrowUpSprite.setOrigin(arrowUpSprite.getLocalBounds().width / 2.f, arrowUpSprite.getLocalBounds().height / 2.f);
    arrowUpSprite.setColor(inactiveColor);

    // Strza≥ka W D”£
    arrowDownSprite.setTexture(textureManager.get("arrow_down"));
    arrowDownSprite.setScale(scale, scale);
    arrowDownSprite.setOrigin(arrowDownSprite.getLocalBounds().width / 2.f, arrowDownSprite.getLocalBounds().height / 2.f);
    arrowDownSprite.setColor(inactiveColor);

    // Strza≥ka W LEWO
    arrowLeftSprite.setTexture(textureManager.get("arrow_left"));
    arrowLeftSprite.setScale(scale, scale);
    arrowLeftSprite.setOrigin(arrowLeftSprite.getLocalBounds().width / 2.f, arrowLeftSprite.getLocalBounds().height / 2.f);
    arrowLeftSprite.setColor(inactiveColor);

    // Strza≥ka W PRAWO
    arrowRightSprite.setTexture(textureManager.get("arrow_right"));
    arrowRightSprite.setScale(scale, scale);
    arrowRightSprite.setOrigin(arrowRightSprite.getLocalBounds().width / 2.f, arrowRightSprite.getLocalBounds().height / 2.f);
    arrowRightSprite.setColor(inactiveColor);

    // Ustalanie pozycji strza≥ek w lewym dolnym rogu
    float spriteDisplayWidth = arrowUpSprite.getGlobalBounds().width; // SzerokoúÊ po skalowaniu
    float spriteDisplayHeight = arrowUpSprite.getGlobalBounds().height; // WysokoúÊ po skalowaniu
    float padding = 5.f;    // OdstÍp miÍdzy strza≥kami
    float margin = 20.f;   // Margines od krawÍdzi ekranu

    float centralX = margin + spriteDisplayWidth + padding + spriteDisplayWidth / 2.f;
    float centralY = SCREEN_HEIGHT - margin - spriteDisplayHeight / 2.f;

    arrowDownSprite.setPosition(centralX, centralY);
    arrowUpSprite.setPosition(centralX, centralY - spriteDisplayHeight - padding);
    arrowLeftSprite.setPosition(centralX - spriteDisplayWidth - padding, centralY);
    arrowRightSprite.setPosition(centralX + spriteDisplayWidth + padding, centralY);
}


void Game::setupTexts() {
    const sf::Font& font = fontManager.get("main_font");

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    livesText.setFont(font);
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(10, 40);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    sf::FloatRect textRectGOT = gameOverText.getLocalBounds(); // Uøyj innej nazwy zmiennej
    gameOverText.setOrigin(textRectGOT.left + textRectGOT.width / 2.0f, textRectGOT.top + textRectGOT.height / 2.0f);
    gameOverText.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - 50);

    highScoreHeaderText.setFont(font);
    highScoreHeaderText.setCharacterSize(30);
    highScoreHeaderText.setFillColor(sf::Color::Yellow);
    highScoreHeaderText.setString("High Scores:");
    sf::FloatRect textRectHSHT = highScoreHeaderText.getLocalBounds(); // Uøyj innej nazwy zmiennej
    highScoreHeaderText.setOrigin(textRectHSHT.left + textRectHSHT.width / 2.0f, textRectHSHT.top + textRectHSHT.height / 2.0f);
    highScoreHeaderText.setPosition(SCREEN_WIDTH / 2.0f, 100);

    enterNameText.setFont(font);
    enterNameText.setCharacterSize(24);
    enterNameText.setFillColor(sf::Color::White);
    enterNameText.setString("Enter your name:");
    sf::FloatRect textRectENT = enterNameText.getLocalBounds();
    enterNameText.setOrigin(textRectENT.left + textRectENT.width / 2.0f, textRectENT.top + textRectENT.height / 2.0f);
    enterNameText.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f + 20);

    playerNameInputText.setFont(font);
    playerNameInputText.setCharacterSize(30);
    playerNameInputText.setFillColor(sf::Color::Cyan);


    // Teksty dla wyboru trudnoúci
    difficultyTitleText.setFont(font);
    difficultyTitleText.setCharacterSize(40);
    difficultyTitleText.setFillColor(sf::Color::Cyan);
    difficultyTitleText.setString("Select Difficulty:");
    sf::FloatRect titleRect = difficultyTitleText.getLocalBounds();
    difficultyTitleText.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
    difficultyTitleText.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - 150);

    difficultyOptionTexts.resize(3);
    std::vector<std::pair<DifficultyLevel, std::string>> levels = {
        {DifficultyLevel::Easy,   "[E] Easy"},
        {DifficultyLevel::Medium, "[M] Medium"},
        {DifficultyLevel::Hard,   "[H] Hard"}
    };

    float yPos = SCREEN_HEIGHT / 2.0f - 50;
    for (size_t i = 0; i < difficultyOptionTexts.size(); ++i) {
        difficultyOptionTexts[i].setFont(font);
        difficultyOptionTexts[i].setCharacterSize(30);
        difficultyOptionTexts[i].setFillColor(sf::Color::White);
        difficultyOptionTexts[i].setString(levels[i].second);
        sf::FloatRect optRect = difficultyOptionTexts[i].getLocalBounds();
        difficultyOptionTexts[i].setOrigin(optRect.left + optRect.width / 2.0f, optRect.top + optRect.height / 2.0f);
        difficultyOptionTexts[i].setPosition(SCREEN_WIDTH / 2.0f, yPos + i * 50.f);
    }
}


void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            if (gameState == GameState::Playing) { // Moøemy chcieÊ, aby ESC w grze pauzowa≥o lub wraca≥o do menu
                gameState = GameState::DifficultySelection; // PowrÛt do wyboru trudnoúci
            }
            else {
                window.close(); // Wyjúcie z innych ekranÛw
            }
        }

        if (gameState == GameState::DifficultySelection) {
            if (event.type == sf::Event::KeyPressed) {
                bool selectionMade = false;
                if (event.key.code == sf::Keyboard::E) {
                    currentDifficulty = DifficultyLevel::Easy;
                    selectionMade = true;
                }
                else if (event.key.code == sf::Keyboard::M) {
                    currentDifficulty = DifficultyLevel::Medium;
                    selectionMade = true;
                }
                else if (event.key.code == sf::Keyboard::H) {
                    currentDifficulty = DifficultyLevel::Hard;
                    selectionMade = true;
                }

                if (selectionMade) {
                    applyDifficultySettings();
                    resetGame(); // Resetuje grÍ z nowymi ustawieniami trudnoúci
                    gameState = GameState::Playing;
                }
            }
        }
        else if (gameState == GameState::GameOver) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                const auto& scores = highScoreManager.getScores();
                if (scores.size() < MAX_HIGH_SCORES || (scores.size() > 0 && score > scores.back().score)) { // Wynik musi byÊ wiÍkszy od najmniejszego z pliku
                    gameState = GameState::EnteringName;
                    currentNameInput.clear();

                    // Ustawienie poczπtkowego tekstu dla playerNameInputText z odpowiedniπ liczbπ podkreúleÒ
                    std::string placeholderText = "";
                    for (unsigned int i = 0; i < MAX_PLAYER_NAME_LENGTH; ++i) {
                        placeholderText += "_";
                        if (i < MAX_PLAYER_NAME_LENGTH - 1) {
                            placeholderText += " "; // Dodaj spacjÍ miÍdzy podkreúleniami
                        }
                    }
                    playerNameInputText.setString(placeholderText);
                    // Ustawienie pozycji dla playerNameInputText (jeúli nie jest juø ustawione globalnie)
                    // To juø powinno byÊ robione w handleNameInput lub setupTexts, ale dla pewnoúci:
                    sf::FloatRect textRect = playerNameInputText.getLocalBounds();
                    playerNameInputText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                    playerNameInputText.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f + 70);

                }
                else {
                    gameState = GameState::ShowingHighScores;
                }
            }
        }
        else if (gameState == GameState::EnteringName) {
            handleNameInput(event);
        }
        else if (gameState == GameState::ShowingHighScores) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                // resetGame(); // ResetGame jest teraz bardziej kompleksowy
                gameState = GameState::DifficultySelection; // WrÛÊ do wyboru trudnoúci
            }
        }
    }
}

void Game::handleNameInput(sf::Event event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {
            char typedChar = static_cast<char>(event.text.unicode);
            if (std::isalnum(typedChar) && currentNameInput.length() < MAX_PLAYER_NAME_LENGTH) {
                currentNameInput += std::toupper(typedChar);
            }
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::BackSpace && !currentNameInput.empty()) {
            currentNameInput.pop_back();
        }
        if (event.key.code == sf::Keyboard::Enter && !currentNameInput.empty()) {
            highScoreManager.addScore(currentNameInput, score);
            gameState = GameState::ShowingHighScores;
        }
    }

    // Aktualizacja wyúwietlanego tekstu z odpowiedniπ liczbπ podkreúleÒ
    std::string displayText = "";
    for (size_t i = 0; i < currentNameInput.length(); ++i) {
        displayText += currentNameInput[i];
        if (i < MAX_PLAYER_NAME_LENGTH - 1) displayText += " "; // Spacja po znaku, jeúli to nie ostatni moøliwy znak
    }
    for (size_t i = currentNameInput.length(); i < MAX_PLAYER_NAME_LENGTH; ++i) {
        displayText += "_";
        if (i < MAX_PLAYER_NAME_LENGTH - 1) { // Spacja po podkreúleniu, jeúli to nie ostatnie podkreúlenie
            displayText += " ";
        }
    }

    playerNameInputText.setString(displayText);

    sf::FloatRect textRect = playerNameInputText.getLocalBounds();
    playerNameInputText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    playerNameInputText.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f + 70);
}

void Game::update(sf::Time dt) {
    if (gameState == GameState::Playing) { // Aktualizuj wskaüniki tylko podczas gry
        updateUIIndicators(); // <<< WYWO£ANIE AKTUALIZACJI STRZA£EK
    }
    else {
        // Opcjonalnie: zresetuj kolory strza≥ek do nieaktywnych, jeúli nie gramy
        const sf::Color inactiveColor(100, 100, 100, 200);
        arrowUpSprite.setColor(inactiveColor);
        arrowDownSprite.setColor(inactiveColor);
        arrowLeftSprite.setColor(inactiveColor);
        arrowRightSprite.setColor(inactiveColor);
    }


    if (gameState != GameState::Playing) {
        return;
    }

    player->update(dt.asSeconds());

    if (spawnClockTrash.getElapsedTime() > currentTrashSpawnInterval) {
        spawnTrash();
        spawnClockTrash.restart();
    }
    if (spawnClockAsteroid.getElapsedTime() > currentAsteroidSpawnInterval) {
        spawnAsteroid();
        spawnClockAsteroid.restart();
    }

    for (auto& obj : gameObjects) {
        obj->update(dt.asSeconds());
    }

    checkCollisions();
    cleanupEntities();

    scoreText.setString("Score: " + std::to_string(score));
    livesText.setString("Lives: " + std::to_string(player->getLives()));

    if (player->getLives() <= 0) {
        gameState = GameState::GameOver;
    }
}

void Game::spawnTrash() {
    float xPos = static_cast<float>(rand() % (SCREEN_WIDTH - 50) + 25);
    gameObjects.push_back(std::make_unique<Trash>(textureManager, sf::Vector2f(xPos, -50.f)));
}

void Game::spawnAsteroid() {
    float xPos = static_cast<float>(rand() % (SCREEN_WIDTH - 50) + 25);
    float yPos = -70.f;
    float dirX = static_cast<float>(rand() % 100 - 50);

    // Pobieramy mnoønik prÍdkoúci dla aktualnego poziomu trudnoúci
    const auto& settings = difficultySettingsMap[currentDifficulty];
    float currentAsteroidBaseSpeed = BASE_ASTEROID_SPEED * settings.asteroidSpeedMultiplier;

    sf::Vector2f velocity(dirX, currentAsteroidBaseSpeed);
    gameObjects.push_back(std::make_unique<Asteroid>(textureManager, sf::Vector2f(xPos, yPos), velocity));
}

void Game::checkCollisions() {
    for (auto& obj : gameObjects) {
        if (Trash* trash = dynamic_cast<Trash*>(obj.get())) {
            if (trash->isActive() && player->getBounds().intersects(trash->getBounds())) {
                score += trash->getValue();
                trash->setActive(false);
            }
        }
    }

    for (auto& obj : gameObjects) {
        if (Asteroid* asteroid = dynamic_cast<Asteroid*>(obj.get())) {
            if (asteroid->isActive() && player->getBounds().intersects(asteroid->getBounds())) {
                player->loseLife();
                player->resetPosition(); // Cofniecie do pozycji startowej po uderzeniu
                asteroid->setActive(false); // Usuniecie asteroidy
                if (player->getLives() <= 0) {
                    gameState = GameState::GameOver;
                    return;
                }
            }
        }
    }
}

void Game::cleanupEntities() {
    gameObjects.erase(
        std::remove_if(gameObjects.begin(), gameObjects.end(),
            [](const std::unique_ptr<Entity>& e) {
                return !e->isActive();
            }),
        gameObjects.end());
}

void Game::resetGame() {
    score = 0;
    player->resetLives();
    player->resetPosition();
    player->setActive(true);
    gameObjects.clear();
    spawnClockTrash.restart();
    spawnClockAsteroid.restart();
    currentNameInput.clear();
    // gameState = GameState::Playing; // Ustawiane przez logikÍ w processEvents po wyborze
}

void Game::render() {
    window.clear(sf::Color::Black);
    window.draw(backgroundSprite);

    if (gameState == GameState::DifficultySelection) {
        displayDifficultySelection();
    }
    else if (gameState == GameState::Playing) {
        player->draw(window);
        for (const auto& obj : gameObjects) {
            obj->draw(window);
        }
        window.draw(scoreText);
        window.draw(livesText);

        // RYSOWANIE STRZA£EK WSKAèNIKOWYCH
        window.draw(arrowUpSprite);
        window.draw(arrowDownSprite);
        window.draw(arrowLeftSprite);
        window.draw(arrowRightSprite);
    }
    else if (gameState == GameState::GameOver) {
        displayGameOver();
    }
    else if (gameState == GameState::EnteringName) {
        window.draw(enterNameText);
        window.draw(playerNameInputText);
    }
    else if (gameState == GameState::ShowingHighScores) {
        displayHighScores();
    }

    window.display();
}

void Game::displayDifficultySelection() {
    window.draw(difficultyTitleText);
    for (const auto& text : difficultyOptionTexts) {
        window.draw(text);
    }
    // Moøna dodaÊ podpowiedü np. "Press E, M, or H"
    sf::Text instructionText("Press E, M, or H to select and start", fontManager.get("main_font"), 20);
    instructionText.setFillColor(sf::Color::Yellow);
    sf::FloatRect instRect = instructionText.getLocalBounds();
    instructionText.setOrigin(instRect.left + instRect.width / 2.0f, instRect.top + instRect.height / 2.0f);
    instructionText.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 80.f);
    window.draw(instructionText);
}

void Game::displayGameOver() {
    window.draw(gameOverText);

    sf::Text promptText;
    promptText.setFont(fontManager.get("main_font"));
    promptText.setCharacterSize(20);
    promptText.setFillColor(sf::Color::White);
    promptText.setString("Your Score: " + std::to_string(score) + "\nPress SPACE to continue...");
    sf::FloatRect textRect = promptText.getLocalBounds();
    promptText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    promptText.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f + 50);
    window.draw(promptText);
}

void Game::displayHighScores() {
    window.draw(highScoreHeaderText);
    highScoreManager.loadScores(); // Ensure scores are fresh
    const auto& scores = highScoreManager.getScores();
    highScoreDisplayTexts.clear();

    float startY = 150.f;
    float yOffset = 30.f;

    if (scores.empty()) {
        sf::Text noScoresText("No high scores yet!", fontManager.get("main_font"), 24);
        noScoresText.setFillColor(sf::Color::White);
        sf::FloatRect textRect = noScoresText.getLocalBounds();
        noScoresText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        noScoresText.setPosition(SCREEN_WIDTH / 2.0f, startY);
        window.draw(noScoresText);
    }
    else {
        for (size_t i = 0; i < scores.size(); ++i) {
            sf::Text entryText(scores[i].name + " : " + std::to_string(scores[i].score), fontManager.get("main_font"), 24);
            entryText.setFillColor(sf::Color::White);
            sf::FloatRect textRect = entryText.getLocalBounds();
            entryText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            entryText.setPosition(SCREEN_WIDTH / 2.0f, startY + (i * yOffset));
            highScoreDisplayTexts.push_back(entryText); // Store if needed, or just draw
            window.draw(entryText);
        }
    }

    sf::Text continuePrompt("Press SPACE to play again", fontManager.get("main_font"), 20);
    continuePrompt.setFillColor(sf::Color::Green);
    sf::FloatRect promptRect = continuePrompt.getLocalBounds();
    continuePrompt.setOrigin(promptRect.left + promptRect.width / 2.0f, promptRect.top + promptRect.height / 2.0f);
    continuePrompt.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 50.f);
    window.draw(continuePrompt);
}