#pragma once

#include <unordered_map>
#include <string>

#include "GlobalCalendar.h"

const std::unordered_map<std::string, std::string> nationalities{ {"1", "Albania"},{"4", "Austria"},{"6", "Belarus"},{"8", "Bosnia-Herzegovina"},{"9", "Bulgaria"},{"10", "Croatia"},
	{"12", "Czech Republic"},{"13", "Denmark"},{"14", "England"},	{"18", "France"},{"20", "Georgia"},{"21", "Germany"}, {"22", "Greece"},
	{"27", "Italy"},{"30", "Lithuania"},{"34", "Netherlands"},{"36", "Norway"},	{"38", "Portugal"}, {"39", "Romania"},{"44", "Slovenia"}, {"45", "Spain"}, {"46", "Sweden"},
	{"48", "Turkey"},{"49", "Ukraine"},{"51", "Serbia & Montenegro"},{"52", "Argentina"},
	{"54", "Brasil"},{"55", "Chile"}, {"56", "Colombia"},{"58", "Paraguay"},{"60", "Uruguay"},{"72", "Costa Rica"},{"81", "Honduras"},{"103", "Cameroon"},{"108", "Cote d' Ivoire"}, {"117", "Ghana"},
	{"123", "Libya"},{"126", "Mali"},{"129", "Morocco"}, {"133", "Nigeria"},{"136", "Senegal"}, {"138", "Sierra Leone"},{"140", "South Africa"},{"163", "Japan"}, {"195", "Australia"} };

const std::unordered_map<int, std::string> positions{ {1, "GK"}, {2, "RB"}, {3, "LB"}, {4, "CD"},
	{5, "SW"}, {6, "RWB"}, {7, "LWB"}, {8, "ANC"}, {9, "DM"}, {10, "RM"}, {11, "LM"}, {12, "CM"},
	{13, "RW"}, {14, "LW"}, {15, "AM"}, {16, "CF"}, {17, "ST"} };

class Player {
private:

	struct BirthDate {
		int day = 0;
		int month = 0;
		int year = 0;
	}  birthDate;

	struct Abilities {
		int passing = 4;
		int header = 4;
		int shotPower = 4;
		int shooting = 4;
		int acceleration = 4;
		int speed = 4;
		int tackling = 4;
		int dribbling = 4;
		int technuque = 4;
		int crossing = 4;
		int reflexes = 4;
		int flyingSaves = 4;
		int aerialControl = 4;
		int oneOnone = 4;
		int goalKicks = 4;
		int throwOut = 4;
	}  abilities;

	std::unordered_map<int, double> positionLvl_{};

	std::string name_;
	std::string nationality_;

	int position_=0;
	int age_=0;
	int talant_ = 0;
	int localexp_ = 0;
	int intexp_ = 0;
	double lvl_=4.5;

	short totalgoals_=0;
	short goalsinseason_=0;

public:

	friend class ItalianChampionship;
	friend class Team;

	Player(std::string name)
		:	name_(name)
	{
	}

	Player(const Player& other) 
		:	birthDate(other.birthDate),
			abilities(other.abilities),
			positionLvl_(other.positionLvl_),
			name_(other.name_),
			nationality_(other.nationality_),
			position_(other.position_),
			age_(other.age_),
			talant_(other.talant_),
			localexp_(other.localexp_),
			intexp_(other.intexp_),
			lvl_(other.lvl_),
			totalgoals_(other.totalgoals_),
			goalsinseason_(other.goalsinseason_)
	{
	}

	Player& operator=(const Player& other)
	{
		birthDate = other.birthDate;
		abilities = other.abilities;
		positionLvl_ = other.positionLvl_;
		name_ = other.name_;
		nationality_ = other.nationality_;
		position_ = other.position_;
		age_ = other.age_;
		talant_ = other.talant_;
		localexp_ = other.localexp_;
		intexp_ = other.intexp_;
		lvl_ = other.lvl_;
		totalgoals_ = other.totalgoals_;
		goalsinseason_ = other.goalsinseason_;

		return *this;
	}

	operator const Player() const {
		return *this;
	}

	bool operator==(const Player& other) {
		return name_ == other.name_ &&
			nationality_ == other.nationality_ &&
			position_ == other.position_ &&
			age_ == other.age_ &&
			lvl_ == other.lvl_ &&
			totalgoals_ == other.totalgoals_ &&
			goalsinseason_ == other.goalsinseason_;
	}

	bool operator!=(const Player& other) {
		return name_ != other.name_ ||
			nationality_ != other.nationality_ ||
			position_ != other.position_ ||
			age_ != other.age_ ||
			lvl_ != other.lvl_ ||
			totalgoals_ != other.totalgoals_ ||
			goalsinseason_ != other.goalsinseason_;
	}

	void scoreGoal() {
		++totalgoals_;
		++goalsinseason_;
	}

	void addLvl(int temp, double k=1) {
		if (temp == 0) {
			lvl_ -= 1*k;
		}
		else if (temp == 2) {
			lvl_ += 1*k;
		}
		else if (temp == 2) {
			lvl_ += 2*k;
		}
	}

	const int getPosition() const {
		return position_;
	}

	const double GetLvlPos(int pos) const {
		return positionLvl_.at(pos);
	}

	void CalcPosLvl() {
		for (const auto& pair : positions) {
			calculatelvl(pair.first);
			positionLvl_[pair.first] = lvl_;
		}
		lvl_ = positionLvl_[position_];
	}

	void calculatelvl(int pos) {
		lvl_=4.5;
		if (pos == 1) {
			addLvl((abilities.reflexes - 1) / 3);
			addLvl((abilities.flyingSaves - 1) / 3);
			addLvl((abilities.aerialControl - 1) / 3);
			addLvl((abilities.oneOnone - 1) / 3);
			addLvl((abilities.goalKicks - 1) / 3);
			addLvl((abilities.throwOut - 1) / 3);
		}
		else if (pos == 2 || pos==3) {
			addLvl((abilities.passing - 1) / 3, 0.5);
			addLvl((abilities.header - 1) / 3, 0.5);
			addLvl((abilities.acceleration - 1) / 3);
			addLvl((abilities.speed - 1) / 3);
			addLvl((abilities.tackling - 1) / 3);
			addLvl((abilities.technuque - 1) / 3, 0.5);
			addLvl((abilities.crossing - 1) / 3, 0.5);
			//Добавить коэффициент, если неправильная нога
		}
		else if (pos == 4 || pos == 5) {
			addLvl((abilities.passing - 1) / 3, 0.5);
			addLvl((abilities.header - 1) / 3);
			addLvl((abilities.acceleration - 1) / 3);
			addLvl((abilities.speed - 1) / 3);
			addLvl((abilities.tackling - 1) / 3);
			addLvl((abilities.technuque - 1) / 3, 0.5);
		}
		else if (pos == 6 || pos==7) {
			addLvl((abilities.passing - 1) / 3, 0.5);
			addLvl((abilities.header - 1) / 3, 0.3);
			addLvl((abilities.acceleration - 1) / 3);
			addLvl((abilities.speed - 1) / 3);
			addLvl((abilities.tackling - 1) / 3, 0.7);
			addLvl((abilities.dribbling - 1) / 3, 0.5);
			addLvl((abilities.technuque - 1) / 3, 0.3);
			addLvl((abilities.crossing - 1) / 3, 0.7);
			//Добавить коэффициент, если неправильная нога
		}
		else if (pos ==8) {
			addLvl((abilities.passing - 1) / 3);
			addLvl((abilities.header - 1) / 3);
			addLvl((abilities.shotPower - 1) / 3, 0.3);
			addLvl((abilities.shooting - 1) / 3, 0.3);
			addLvl((abilities.acceleration - 1) / 3, 0.5);
			addLvl((abilities.speed - 1) / 3, 0.5);
			addLvl((abilities.tackling - 1) / 3);
			addLvl((abilities.dribbling - 1) / 3, 0.3);
			addLvl((abilities.technuque - 1) / 3, 0.3);
		}
		else if (pos == 9) {
			addLvl((abilities.passing - 1) / 3, 0.7);
			addLvl((abilities.header - 1) / 3, 0.7);
			addLvl((abilities.shotPower - 1) / 3, 0.5);
			addLvl((abilities.shooting - 1) / 3, 0.5);
			addLvl((abilities.acceleration - 1) / 3, 0.5);
			addLvl((abilities.speed - 1) / 3, 0.5);
			addLvl((abilities.tackling - 1) / 3);
			addLvl((abilities.dribbling - 1) / 3, 0.3);
			addLvl((abilities.technuque - 1) / 3, 0.3);
		}
		else if (pos == 10 || pos == 11) {
			addLvl((abilities.passing - 1) / 3, 0.5);
			addLvl((abilities.header - 1) / 3, 0.3);
			addLvl((abilities.shotPower - 1) / 3, 0.3);
			addLvl((abilities.shooting - 1) / 3, 0.3);
			addLvl((abilities.acceleration - 1) / 3, 0.7);
			addLvl((abilities.speed - 1) / 3, 0.7);
			addLvl((abilities.tackling - 1) / 3, 0.5);
			addLvl((abilities.dribbling - 1) / 3, 0.7);
			addLvl((abilities.technuque - 1) / 3, 0.3);
			addLvl((abilities.crossing - 1) / 3);
			//Добавить коэффициент, если неправильная нога
		}
		else if (pos == 12) {
			addLvl((abilities.passing - 1) / 3);
			addLvl((abilities.header - 1) / 3, 0.3);
			addLvl((abilities.shotPower - 1) / 3, 0.5);
			addLvl((abilities.shooting - 1) / 3, 0.5);
			addLvl((abilities.acceleration - 1) / 3, 0.5);
			addLvl((abilities.speed - 1) / 3, 0.5);
			addLvl((abilities.dribbling - 1) / 3);
			addLvl((abilities.technuque - 1) / 3);
		}
		else if (pos == 13 || pos == 14) {
			addLvl((abilities.passing - 1) / 3, 0.5);
			addLvl((abilities.shotPower - 1) / 3, 0.3);
			addLvl((abilities.shooting - 1) / 3, 0.5);
			addLvl((abilities.acceleration - 1) / 3, 0.7);
			addLvl((abilities.speed - 1) / 3, 0.7);
			addLvl((abilities.dribbling - 1) / 3, 0.7);
			addLvl((abilities.technuque - 1) / 3, 0.5);
			addLvl((abilities.crossing - 1) / 3);
			//Добавить коэффициент, если неправильная нога
		}
		else if (pos == 15) {
			addLvl((abilities.passing - 1) / 3, 0.5);
			addLvl((abilities.header - 1) / 3, 0.3);
			addLvl((abilities.shotPower - 1) / 3, 0.5);
			addLvl((abilities.shooting - 1) / 3, 0.7);
			addLvl((abilities.acceleration - 1) / 3, 0.7);
			addLvl((abilities.speed - 1) / 3);
			addLvl((abilities.dribbling - 1) / 3, 0.7);
			addLvl((abilities.technuque - 1) / 3, 0.7);
			addLvl((abilities.crossing - 1) / 3, 0.5);
		}
		else if (pos == 16) {
			addLvl((abilities.passing - 1) / 3, 0.5);
			addLvl((abilities.header - 1) / 3, 0.5);
			addLvl((abilities.shotPower - 1) / 3, 0.7);
			addLvl((abilities.shooting - 1) / 3);
			addLvl((abilities.acceleration - 1) / 3);
			addLvl((abilities.speed - 1) / 3, 0.7);
			addLvl((abilities.dribbling - 1) / 3, 0.7);
			addLvl((abilities.technuque - 1) / 3, 0.5);
			addLvl((abilities.crossing - 1) / 3, 0.3);
		}
		else {
			addLvl((abilities.passing - 1) / 3, 0.3);
			addLvl((abilities.header - 1) / 3);
			addLvl((abilities.shotPower - 1) / 3, 0.3);
			addLvl((abilities.shooting - 1) / 3);
			addLvl((abilities.acceleration - 1) / 3);
			addLvl((abilities.speed - 1) / 3, 0.7);
			addLvl((abilities.dribbling - 1) / 3, 0.7);
			addLvl((abilities.technuque - 1) / 3, 0.7);
			addLvl((abilities.crossing - 1) / 3, 0.3);
			}
		lvl_ += localexp_ * 0.5+intexp_*0.5;
	}

	bool operator<(const Player& other) const {
		return lvl_ < other.lvl_;
	}

	bool operator>(const Player& other) const {
		return lvl_ > other.lvl_;
	}

	const double getLevel() const {
		return lvl_;
	}

	void ChangePos(int pos) {
		position_ = pos;
		lvl_ = positionLvl_[pos];
	}

	void calculateAge(const GlobalCalendar& time) {
		int currentYear = time.getYear();

		if (time.getMonth() < birthDate.month) {
			currentYear--;
		}
		// Если текущий месяц равен месяцу рождения и текущий день меньше дня рождения, то также вычитаем из текущего года 1
		else if (time.getMonth() == birthDate.month && time.getDay() < birthDate.day) {
			currentYear--;
		}

		// Вычисляем разницу в годах между текущим годом и годом рождения
		age_ = currentYear - birthDate.year;
	}
};

struct PlayerPtrComparator {
	bool operator()(const Player* p1, const Player* p2) const {
		return *p1 < *p2;
	}
};
