#pragma once

#include <unordered_map>
#include <string>

#include "GlobalCalendar.h"

const std::unordered_map<std::string, std::string> nationalities{ {"6", "Belarus"},{"10", "Croatia"},
	{"12", "Czech Republic"},{"13", "Denmark"},	{"18", "France"},{"20", "Georgia"}, {"22", "Greece"},
	{"27", "Italy"},{"34", "Netherlands"},	{"38", "Portugal"}, {"39", "Romania"},{"46", "Sweden"},
	{"48", "Turkey"},{"49", "Ukraine"},{"51", "Serbia & Montenegro"},{"52", "Argentina"},
	{"54", "Brasil"},{"55", "Chile"}, {"56", "Colombia"},{"58", "Paraguay"},{"60", "Uruguay"},
	{"133", "Nigeria"},{"136", "Senegal"}, {"138", "Sierra Leone"} };

class Player {
private:

	struct BirthDate {
		int day = 0;
		int month = 0;
		int year = 0;
	}  birthDate;

	std::string name_;
	std::string nationality_;
	std::string position_;

	int age_=0;
	double lvl_=0;

	short totalgoals_=0;
	short goalsinseason_=0;

public:

	friend class ItalianChampionship;
	friend class Team;

	Player(std::string name)
		:	name_(name)
	{
	}

	Player(std::string name, std::string nationality, std::string position, short age, double lvl)
		:	name_(name),
			nationality_(nationality),
			position_(position),
			age_(age),
			lvl_(lvl),
			totalgoals_(0),
			goalsinseason_(0)
	{
	}

	Player(const Player& other) 
		:	name_(other.name_),
			nationality_(other.nationality_),
			position_(other.position_),
			age_(other.age_),
			lvl_(other.lvl_),
			totalgoals_(other.totalgoals_),
			goalsinseason_(other.goalsinseason_)
	{
	}

	Player& operator=(const Player& other)
	{
		name_ = other.name_;
		nationality_ = other.nationality_;
		position_ = other.position_;
		age_ = other.age_;
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
