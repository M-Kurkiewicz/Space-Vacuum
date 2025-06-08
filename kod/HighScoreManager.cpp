#include "HighScoreManager.h"

HighScoreManager::HighScoreManager(const std::string& fn) : filename(fn), scoreRegex("^([A-Za-z0-9_]{1,10})\\s+(\\d+)$") {
    loadScores();
}

void HighScoreManager::addScore(const std::string& name, int score) {
    scores.push_back({ name, score });
    std::sort(scores.begin(), scores.end());

    if (scores.size() > MAX_HIGH_SCORES) {
        scores.resize(MAX_HIGH_SCORES);
    }
    saveScores();
}

const std::vector<ScoreEntry>& HighScoreManager::getScores() const {
    return scores;
}

void HighScoreManager::loadScores() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open highscore file for reading: " << filename << std::endl;
        return;
    }

    scores.clear();
    std::string line;
    std::smatch match; // Do przechowywania wyników dopasowania wyra¿enia regularnego

    while (std::getline(file, line)) {
        if (std::regex_match(line, match, scoreRegex)) {
            if (match.size() == 3) {
                std::string name = match[1].str();
                int score = 0;
                try {
                    score = std::stoi(match[2].str());
                    scores.push_back({name, score});
                } catch (const std::invalid_argument& /*ia*/) {
                    std::cerr << "Invalid score format in highscore file: " << match[2].str() << std::endl;
                } catch (const std::out_of_range& /*oor*/) { 
                    std::cerr << "Score out of range in highscore file: " << match[2].str() << std::endl;
                }
            }
        }
        else {
            std::cerr << "Skipping malformed line in highscore file: " << line << std::endl;
        }
    }
    file.close();
    std::sort(scores.begin(), scores.end()); 
}

void HighScoreManager::saveScores() {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open highscore file for writing: " << filename << std::endl;
        return;
    }

    for (const auto& entry : scores) {
        file << entry.name << " " << entry.score << std::endl;
    }
    file.close();
}