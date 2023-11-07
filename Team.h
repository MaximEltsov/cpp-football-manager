#pragma once

#include <algorithm>
#include <deque>
#include <iterator>
#include <string>
#include <vector>

#include "Player.h"
#include "Tactics.h"

class Team {
private:
	std::deque<Player> roaster_;
	std::string name_;
	std::string stadium_;

	double lvl_=0;
	int goalDifference_ = 0;
	int goalsFor_ = 0;
	int matchesWon_ = 0;
	int matchesDraw_ = 0;
	int matchesLost_ = 0;
	int rating_=0;
	short seasonPoints_=0;

	Tactics tactic;

public:

	friend class ItalianChampionship;

	Team() = default;

	Team(std::string name)
		:	name_(name), seasonPoints_(0)
	{
	}

	Team(const Team& other)
		: roaster_(other.roaster_),
		name_(other.name_),
		stadium_(other.stadium_),
		lvl_(other.lvl_),
		goalDifference_(other.goalDifference_),
		goalsFor_(other.goalsFor_),
		matchesWon_(other.matchesWon_),
		matchesDraw_(other.matchesDraw_),
		matchesLost_(other.matchesLost_),
		rating_(other.rating_),
		seasonPoints_(other.seasonPoints_),
		tactic(other.tactic)
	{
	}

	Team& operator=(const Team& other) {
		if (this != &other) {
			roaster_ = other.roaster_;
			name_ = other.name_;
			stadium_ = other.stadium_;

			lvl_ = other.lvl_;
			goalDifference_ = other.goalDifference_;
			goalsFor_ = other.goalsFor_;
			matchesWon_ = other.matchesWon_;
			matchesDraw_ = other.matchesDraw_;
			matchesLost_=other.matchesLost_;
			rating_ = other.rating_;
			seasonPoints_ = other.seasonPoints_;
			tactic = other.tactic;
		}
		return *this;
	}

	Team& operator=(Team&& other) noexcept {
		if (this != &other) {
			roaster_ = other.roaster_;
			name_ = std::move(other.name_);
			stadium_ = std::move(other.stadium_);

			lvl_ = other.lvl_;
			goalDifference_ = other.goalDifference_;
			goalsFor_ = other.goalsFor_;
			matchesWon_ = other.matchesWon_;
			matchesDraw_ = other.matchesDraw_;
			matchesLost_ = other.matchesLost_;
			rating_ = other.rating_;
			seasonPoints_ = other.seasonPoints_;
			tactic = other.tactic;

			other.name_ = "";
			other.stadium_ = "";
			other.lvl_ = 0;
			other.goalDifference_ = 0;
			other.goalsFor_ = 0;
			other.matchesWon_ = 0;
			other.matchesDraw_ = 0;
			other.matchesLost_ = 0;
			other.rating_ = 0;
			other.seasonPoints_ = 0;
		}
		return *this;
	}

	operator const Team() const {
		return *this;
	}

	void getLvl() {
		for (int i = 0; i < 11; ++i) {
			lvl_ += roaster_[i].lvl_;
		}
	}

	/*bool operator==(const Team& other) {
		return //roaster_ == other.roaster_ &&
			name_ == other.name_ &&
			stadium_ == other.stadium_ &&
			lvl_ == other.lvl_ &&
			goalDifference_ == other.goalDifference_ &&
			goalsFor_ == other.goalsFor_ &&
			matchesWon_ == other.matchesWon_ &&
			matchesDraw_ == other.matchesDraw_ &&
			rating_ == other.rating_ &&
			seasonPoints_ == other.seasonPoints_;
	}

	bool operator!=(const Team& other) {
		return roaster_ != other.roaster_ ||
			name_ != other.name_ ||
			stadium_ != other.stadium_ ||
			lvl_ != other.lvl_ ||
			goalDifference_ != other.goalDifference_ ||
			goalsFor_ != other.goalsFor_ ||
			matchesWon_ != other.matchesWon_ ||
			matchesDraw_ != other.matchesDraw_ ||
			rating_ != other.rating_ ||
			seasonPoints_ != other.seasonPoints_;
	}*/

	//void addPlayer(const Player& player) {
	//	roaster_.push_back(player);
	//}

	bool operator<(const Team& other) const {
		return seasonPoints_ < other.seasonPoints_;
	}

	//size_t getPlayerCount() const {
	//	return roaster_.size();
	//}

	short getPts() const {
		return seasonPoints_;
	}

	std::string getName() const {
		return name_;
	}

	void printTeam() {
		std::cout << name_ << std::endl;
	}

	void printTeamRoaster() {
		std::cout << std::left << std::setw(25) << "Имя" << std::left << std::setw(20) << "Национальность" << std::left << std::setw(10) << "Возраст" << std::left << std::setw(10) << "Уровень" << std::left << std::setw(10) << "Талант"<<"Позиция"<<std::endl;
		for (Player& player : roaster_) {
			std::cout << std::left << std::setw(25) << player.name_ << std::left << std::setw(20) << player.nationality_<<  std::left << std::setw(10)<<player.age_ << std::left << std::setw(10) <<std::fixed<<std::setprecision(1)<<player.lvl_ << std::left << std::setw(10) <<std::string(player.talant_, '*') << positions.at(player.position_)<< std::endl;
		}

	}

	void sortRoaster() {
		tactic.sortTeam(&roaster_);
	}
};