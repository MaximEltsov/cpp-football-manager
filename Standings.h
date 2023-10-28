#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Team.h"

class Standings {
private:
    struct TeamStats {
        int played;
        int won;
        int drawn;
        int lost;
        int goalsFor;
        int goalsAgainst;
        int goalDifference;
        int points;

        TeamStats() : played(0), won(0), drawn(0), lost(0), goalsFor(0), goalsAgainst(0), goalDifference(0), points(0) {}
    };

    std::map<std::string, TeamStats> standings_;

public:

    Standings() = default;

    Standings(std::vector<Team>* teams_) {
        for (const Team& team : *teams_) {
            standings_[team.getName()];
        }
    }

    Standings& operator=(Standings&& other) noexcept {
        if (this != &other) {
            standings_ = std::move(other.standings_);
        }
        return *this;
    }

    void updateStandings(const std::string& teamName, int goalsFor, int goalsAgainst) {
        standings_[teamName].played++;
        standings_[teamName].goalsFor += goalsFor;
        standings_[teamName].goalsAgainst += goalsAgainst;
        standings_[teamName].goalDifference = standings_[teamName].goalsFor - standings_[teamName].goalsAgainst;

        if (goalsFor > goalsAgainst) {
            standings_[teamName].won++;
            standings_[teamName].points += 3;
        }
        else if (goalsFor < goalsAgainst) {
            standings_[teamName].lost++;
        }
        else {
            standings_[teamName].drawn++;
            standings_[teamName].points += 1;
        }
    }

    void printStandings() const {
        std::vector<std::pair<std::string, TeamStats>> sortedStandings(standings_.begin(), standings_.end());
        std::sort(sortedStandings.begin(), sortedStandings.end(), [](const std::pair<std::string, TeamStats>& a, const std::pair<std::string, TeamStats>& b) {
            if (a.second.points != b.second.points) {
                return a.second.points > b.second.points;
            }
            else if (a.second.goalDifference != b.second.goalDifference) {
                return a.second.goalDifference > b.second.goalDifference;
            }
            else if (a.second.goalsFor != b.second.goalsFor) {
                return a.second.goalsFor > b.second.goalsFor;
            }
            else {
                return a.first < b.first;
            }
            });

        std::cout << "Team\t\tPlayed\tWon\tDrawn\tLost\tFor\tAgainst\tDifference\tPoints\n";
        for (const auto& team : sortedStandings) {
            std::cout << team.first << "\t\t" << team.second.played << "\t" << team.second.won << "\t"
                << team.second.drawn << "\t" << team.second.lost << "\t" << team.second.goalsFor << "\t"
                << team.second.goalsAgainst << "\t" << team.second.goalDifference << "\t\t" << team.second.points << std::endl;
        }
    }
};
