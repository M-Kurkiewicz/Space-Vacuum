#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H

#include <vector>
#include <string>
#include <algorithm> 
#include <fstream> 
#include <iostream>
#include <regex>

#include "Defines.h"

struct ScoreEntry {
    std::string name;
    int score;

    bool operator<(const ScoreEntry& other) const {
        return score > other.score;
    }
};

class HighScoreManager {
public:
    HighScoreManager(const std::string& filename = HIGHSCORE_FILE);

    void addScore(const std::string& name, int score);
    const std::vector<ScoreEntry>& getScores() const;
    void loadScores();
    void saveScores();

private:
    std::string filename;
    std::vector<ScoreEntry> scores;
    const std::regex scoreRegex;
};

#endif // HIGHSCOREMANAGER_H