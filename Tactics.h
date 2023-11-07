#pragma once

#include <algorithm>
#include <deque>
#include <functional>
#include <iterator>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "Player.h"

//{ {1, "GK"}, { 2, "RB" }, { 3, "LB" }, { 4, "CD" },
//	{ 5, "SW" }, { 6, "RWB" }, { 7, "LWB" }, { 8, "ANC" }, { 9, "DM" }, { 10, "RM" }, { 11, "LM" }, { 12, "CM" },
//	{ 13, "RW" }, { 14, "LW" }, { 15, "AM" }, { 16, "CF" }, { 17, "ST" } };

const std::unordered_map<std::string, std::vector<int>> schemes{ {"4-4-1-1", {1,2,4,4,3,10, 12, 12, 11, 17, 17, 1, 4,4, 12,12, 17,17}},
	{"4-4-2", {1,2,4,4,3,9, 12, 12, 15, 16, 16, 1, 4,4, 12,12, 16,17}},
	{"4-3-2-1", {1,2,4,4,3,12, 12, 12, 15, 15, 17, 1, 4,4, 12,12, 15,17}},
	{"4-1-2-2-1", {1,6,4,4,7,9, 12, 12, 13, 17, 14, 1, 4,4, 12,12, 14,17}},
	{"3-4-3", {1, 4,4,4,10,12,12,11,13,16,14,1,4,4,12,12,16,14}},
	{"4-1-2-2-1", {1, 6,4,4,7,12,9,12,13,16,14,1,4,4,12,9,16,14}},
	{"4-3-3", {1, 6,4,4,7,12,12,12,16,17,16,1,4,4,12,12,16,17}},
	{"3-5-2", {1, 4,4,4,10,12,12,12,11,16,17,1,4,4,12,12,12,17}},
	{"3-2-2-1-2", {1, 4,4,4,9,9,10,11,15,16,17,1,4,4,9,10,15,17}},
	{ "5-3-2", {1, 6,4,4,4,7,12,12,12,16,17,1,4,4,7,12,10,17} },
	{ "4-2-3-1", {1, 2,4,4,3,12,12,13,15,14,17,1,4,4,12,12,10,17}} };

struct CompareByLevel {
	int position_;

	CompareByLevel(int position) :position_(position) {}

	bool operator()(const Player& p1, const Player& p2) const {
		if (p1.getPosition() == position_ && p2.getPosition() != position_) {
			return true;
		}
		else if (p1.getPosition() == position_ && p2.getPosition() == position_ && p1.getLevel() > p2.getLevel()) {
			return true;
		}
		else if (p1.getPosition() != position_ && p2.getPosition() != position_ && p1.GetLvlPos(position_) > p2.GetLvlPos(position_)) {
			return true;
		}
		return false;
	}
};

class Tactics {
public:

	Tactics() = default;

	Tactics(std::deque<Player>& roaster_) {
		for (Player& player: roaster_) {
			posPlayers_[player.getPosition()].insert(player);
		}
	}

	Tactics(const Tactics& other)
		: posPlayers_(other.posPlayers_)
	{
	}

	Tactics& operator=(const Tactics& other) {
		if (this != &other) {
			posPlayers_ = other.posPlayers_;
		}
		return *this;
	}

	Tactics& operator=(Tactics&& other) noexcept {
		if (this != &other) {
			std::swap(posPlayers_,other.posPlayers_);
		}
		return *this;
	}

	

	void sortTeam(std::deque<Player>* roaster_) {
		int pos = 0;
		double lvl = 0;
		for (const auto& pair : schemes) {
			for (auto iter = roaster_->begin(); pos < pair.second.size(); ++iter, ++pos) {
				std::sort(iter, roaster_->end(), CompareByLevel(pair.second[pos]));
			}
			double teamlvl = 0;
			for (int i = 0; i < 11; ++i) {	
				teamlvl += (*roaster_)[i].GetLvlPos(pair.second[i]);
			}
			if (lvl < teamlvl) {
				lvl = teamlvl;
				schemeName_ = pair.first;
			}
		}
		for (int i = 0; i < schemes.at(schemeName_).size(); ++i) {
			(*roaster_)[i].ChangePos(schemes.at(schemeName_)[i]);
		}
	}

	void sortTeam(std::vector<Player> roaster_, std::string scheme) {

	}


private:
	std::unordered_map<int, std::set<Player>> posPlayers_;
	std::string schemeName_;
};



