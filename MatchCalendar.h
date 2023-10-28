#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <vector>

class MatchCalendar {
private:
	
	std::map<int, std::vector<std::pair<int, int>>> calendar_;
	//std::map<int, std::set<int>> tour_team_;

	std::vector<std::pair<int, int>> matches_;
	//std::vector<std::pair<int, int>> reserve_;

	const int CIRCLES = 2;

	int numTeams_=0;
	int toursCount_ = 0;
	int reserveDays = 1;

public:

	friend class ItalianChampionship;

	MatchCalendar() = default;

	MatchCalendar(MatchCalendar&& other) noexcept {
		calendar_ = std::move(other.calendar_);
	}

	MatchCalendar& operator=(MatchCalendar&& other) noexcept {
		if (this != &other) {
			calendar_ = std::move(other.calendar_);
		}
		return *this;
	}

	MatchCalendar(int numTeams)
		: numTeams_(numTeams), toursCount_(numTeams* CIRCLES - CIRCLES)
	{
		std::random_device rd;
		std::default_random_engine gen(rd());
		std::uniform_int_distribution<int> distribution(0, 1);

		for (int i = 0; i < numTeams_-1; ++i) {
			for (int j = i+1; j < numTeams_; ++j) {
				int random = distribution(gen);
				if (random == 1) {
					matches_.push_back(std::make_pair(i, j));
				}
				else {
					matches_.push_back(std::make_pair(j, i));
				}
			}
		}
		generateCalendar();
	}

	const int toursCount() const {
		return static_cast<int>(calendar_.size());
	}

	std::vector<std::vector<std::pair<int, int>>> genRound(bool reverse=false) {

		std::vector<std::vector<std::pair<int, int>>> round;
		std::map<int, std::set<int>> tour_team_;
		bool success = false;
		
		while (!success) {
			success = true;

			tour_team_.clear();
			round.clear();
			round.resize(numTeams_ - 1 + reserveDays, std::vector<std::pair<int, int>>());

			std::shuffle(matches_.begin(), matches_.end(), std::mt19937(std::random_device()()));
			for (int i = 0; i < matches_.size(); ++i) {
				if (reverse) {
					std::swap(matches_[i].first, matches_[i].second);
				}
				for (int j = 0; j < numTeams_-1 + reserveDays; ++j) {
					if (tour_team_[j].count(matches_[i].first) == 0 && tour_team_[j].count(matches_[i].second) == 0) {
						tour_team_[j].insert(matches_[i].first);
						tour_team_[j].insert(matches_[i].second);
						round[j].push_back(matches_[i]);
						break;
					}
					if (j == numTeams_ - 2 + reserveDays) {
						success = false;
						break;
					}
				}
				if (!success) {
					break;
				}
			}
		}
		return round;
	}

	void generateCalendar() {

		std::cout << "Генерация календаря..." << std::endl;
		
		std::vector<std::vector<std::pair<int, int>>> round1=std::move(genRound());
		std::vector<std::vector<std::pair<int, int>>> round2 = std::move(genRound(true));
		int day = 1;
		for (auto& tour : round1) {
			if (!tour.empty()) {
				calendar_[day] = std::move(tour);
				++day;
			}
		}
		for (auto it = round2.rbegin(); it!= round2.rend(); ++it) {
			if (!(*it).empty()) {
				calendar_[day] = std::move(*it);
				++day;
			}
		}

		system("cls");
	}



	/*void generateCalendar() {

		bool success = 0;

		while (!success) {
			success = 1;

			tour_team_.clear();
			calendar_.clear();
			reserve_.clear();

			std::shuffle(matches_.begin(), matches_.end(), std::mt19937(std::random_device()()));
			for (int i = 0; i < matches_.size(); ++i) {
				for (int j = 1; j <= toursCount_ + reserveDays; ++j) {
					if (tour_team_[j].count(matches_[i].first) == 0 && tour_team_[j].count(matches_[i].second) == 0) {
						tour_team_[j].insert(matches_[i].first);
						tour_team_[j].insert(matches_[i].second);
						calendar_[j].push_back(std::move(matches_[i]));
						break;
					}
				}
			}

			std::shuffle(matches_.begin(), matches_.end(), std::mt19937(std::random_device()()));

			for (int i = 0; i < matches_.size(); ++i) {
				for (int j = toursCount_ + reserveDays; j >= 1; --j) {
					if (tour_team_[j].count(matches_[i].first) == 0 && tour_team_[j].count(matches_[i].second) == 0) {
						tour_team_[j].insert(matches_[i].first);
						tour_team_[j].insert(matches_[i].second);
						std::swap(matches_[i].first, matches_[i].second);
						calendar_[j].push_back(std::move(matches_[i]));
						break;
					}
					if (j == 1) {
						success = 0;
						break;
					}
				}
			}

			if (calendar_.size() != toursCount_ + reserveDays) {
				success = 0;
			}
		}
	}*/

	std::map<int, std::vector<std::pair<int, int>>> getCalendar() const {
		return calendar_;
	}

	void printCalendar() const {
		for (const auto& tour : calendar_) {
			std::cout << "Tour " << tour.first << std::endl;
			for (const auto& match : tour.second) {
				std::cout << "Team " << match.first << " vs Team" << match.second << std::endl;
			}
		}
		
		int sum = 0;
		for (const auto& tour : calendar_) {
			
			std::cout << tour.first<<" "<<tour.second.size() << std::endl;
			sum += static_cast<int>(tour.second.size());
		}
		std::cout << sum;
		
	}
};
