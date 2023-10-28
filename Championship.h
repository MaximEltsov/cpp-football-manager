#pragma once

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <windows.h>

#include "GlobalCalendar.h"
#include "MatchCalendar.h"
#include "Team.h"

const std::string clubListFilename = "C:\\Users\\felix\\source\\repos\\TCM2004\\ItalianClubs.txt";

void SetConsoleColor(int colorCode) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(colorCode));
}

bool compareTeams(const Team& team1, const Team& team2) {
	return team1.getPts() > team2.getPts();
}

class Championship {
private:
	
	std::string name_;
	short year_=2003;
	std::vector<Team> teams_;
	Team playerTeam_;
	GlobalCalendar time_;

public:
	void addTeam(const Team& team) {
		teams_.push_back(team);
	}

	void printTable() const {
		std::cout << "Team\t" << "Points" << std::endl;
		for (const Team& team : teams_) {
			std::cout << team.getName() << "/t" << team.getPts();
		}
	}
};

class ItalianChampionship : public Championship {
private:

	int currentTour_ = 1;
	std::string name_="Seria A";
	short year_=2003;
	std::vector<Team> teams_;
	MatchCalendar season_;
	//Standings table_;
	GlobalCalendar time_;
	
public:

	Team* playerTeam_;

	ItalianChampionship()
		:	time_()
	{
		loadItalianTeams();
		season_=MatchCalendar(static_cast<int>(teams_.size()));
		std::random_device rd;
		std::default_random_engine gen(rd());
		std::shuffle(teams_.begin(), teams_.end(), gen);
		//table_ = Standings(&teams_);
	}

	void readPlayersFromFile(const std::string& filename, Team& team) {
		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cout << "Не удалось открыть файл" << std::endl;
			return;
		}

		std::string line;
		bool foundIndexPlayer = false;
		while (std::getline(file, line)) {
			// Проверяем, содержит ли строка "%INDEX%PLAYER"
			if (line.find("%INDEX%PLAYER") != std::string::npos) {
				foundIndexPlayer = true;
				continue;
			}

			// Если уже нашли строку "%INDEX%PLAYER", то считываем имена игроков
			if (foundIndexPlayer) {
				std::string temp = line+" ";
				std::getline(file, line);
				temp += line;
				std::getline(file, line);
				std::getline(file, line);
				if (!line.empty()) {
					temp = line;
				}
				Player player(temp);
				std::getline(file, line);
				std::getline(file, line);
				std::getline(file, line);
				
				if (!nationalities.count(line)) {
					std::cout << player.name_ << line<<std::endl;
					std::string a;
					std::cin >> a;
				}
				player.nationality_ = nationalities.at(line);
				std::getline(file, line);
				std::getline(file, line);
				std::getline(file, line);
				std::getline(file, line);
				player.birthDate.day = std::stoi(line);
				std::getline(file, line);
				player.birthDate.month = std::stoi(line);
				std::getline(file, line);
				player.birthDate.year = std::stoi(line);
				player.calculateAge(time_);

				team.roaster_.push_back(player);
				foundIndexPlayer = false;
			}
		}

		file.close();
	}

	void loadItalianTeams() {
		// Загрузка информации о командах из базы данных или файла
		// ...
		/*Team Milan("Milan");
		Team Roma("Roma");
		Team Juventus("Juventus");
		Team Inter("Inter");
		Team Parma("Parma");
		Team Lazio("Lazio");
		Team Udinese("Udinese");
		Team Samptdoria("Samptdoria");
		Team Chievo_Verona("Chievo Verona");
		Team Lecce("Lecce");
		Team Brescia("Brescia");
		Team Bologna("Bologna");
		Team Redgina("Redgina");
		Team Siena("Siena");
		Team Perudja("Perudja");
		Team Modena("Modena");
		Team Empoli("Empoli");
		Team Ankona("Ankona");
		teams_.push_back(Milan);
		teams_.push_back(Roma);
		teams_.push_back(Juventus);
		teams_.push_back(Inter);
		teams_.push_back(Parma);
		teams_.push_back(Lazio);
		teams_.push_back(Udinese);
		teams_.push_back(Samptdoria);
		teams_.push_back(Chievo_Verona);
		teams_.push_back(Lecce);
		teams_.push_back(Brescia);
		teams_.push_back(Bologna);
		teams_.push_back(Redgina);
		teams_.push_back(Siena);
		teams_.push_back(Perudja);
		teams_.push_back(Modena);
		teams_.push_back(Empoli);
		teams_.push_back(Ankona);*/
		std::ifstream clubFile(clubListFilename);
		if (!clubFile.is_open()) {
			std::cout << "Не удалось открыть файл с командами" << std::endl;
			return;
		}

		std::string clubName;
		while (std::getline(clubFile, clubName)) {
			std::string playersFilename = "C:\\Users\\felix\\source\\repos\\TCM2004\\" + clubName + ".txt";
			std::cout << "Клуб: " << clubName << std::endl;
			std::cout << "Игроки:" << std::endl;
			Team team(clubName);
			readPlayersFromFile(playersFilename, team);
			std::cout << std::endl;
			teams_.push_back(team);
		}

		clubFile.close();
	}

	void SetTeam() {
		printTeams();
		std::cout << "Выберите команду" << std::endl;
		int choice;
		std::cin >> choice;
		if (choice >= 1 && choice <= teams_.size()) {
			playerTeam_ = &teams_[choice - 1];
			//playerTeam_.printInformation();
		}
		else {
			std::cout << "Недопустимый выбор команды.";
		}
	}

	void printCalendar() const {
		//std::cout << season_.getCalendar().size() << std::endl;
		for (const auto& tour : season_.getCalendar()) {
			std::cout << "Tour " << tour.first << std::endl;
			for (const auto& match : tour.second) {

				std::cout << "Team ";
				if (teams_[match.first].getName() == (*playerTeam_).getName()) {
					SetConsoleColor(10);
					std::cout << teams_[match.first].getName();
					SetConsoleColor(7);
				}
				else {
					std::cout << teams_[match.first].getName();
				}
				std::cout << "\tvs\tTeam ";
				if (teams_[match.second].getName() == (*playerTeam_).getName()) {
					SetConsoleColor(10);
					std::cout << teams_[match.second].getName();
					SetConsoleColor(7);
				}
				else {
					std::cout << teams_[match.second].getName();
				} 
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	}

	void simulateMatch(Team& team1, Team& team2) {
		std::random_device rd;
		std::default_random_engine engine(rd());
		std::uniform_int_distribution<int> distribution(0, 5);
		int scoreTeam1 = distribution(engine);
		int scoreTeam2 = distribution(engine);

		team1.goalsFor_ += scoreTeam1;
		team1.goalDifference_ += scoreTeam1 - scoreTeam2;
		team2.goalsFor_ += scoreTeam2;
		team2.goalDifference_ += scoreTeam2 - scoreTeam1;

		if (scoreTeam1 > scoreTeam2) {
			team1.seasonPoints_ += 3;
			team1.matchesWon_++;
			team2.matchesLost_++;
		}
		else if (scoreTeam1 < scoreTeam2) {
			team2.seasonPoints_ += 3;
			team2.matchesWon_++;
			team1.matchesLost_++;
		}
		else {
			team1.seasonPoints_++;
			team1.matchesDraw_++;
			team2.seasonPoints_++;
			team2.matchesDraw_++;
		}
	}

	void playTour() {
		for (const auto& match : season_.calendar_.at(currentTour_)) {
			Team& team1 = teams_[match.first];
			Team& team2 = teams_[match.second];

			simulateMatch(team1, team2);
		}
		++currentTour_;
	}

	void printTeams() {
		int num = 1;
		for (Team& team : teams_) {
			std::cout << num<<"  ";
			team.printTeam();
			++num;
		}
	}

	const int tourCount() const {
		return season_.toursCount();
	}

	static bool teamComparator(const Team& team1, const Team& team2) {
		if (team1.seasonPoints_ != team2.seasonPoints_) {
			return team1.seasonPoints_ > team2.seasonPoints_;
		}
		else if (team1.goalDifference_ != team2.goalDifference_) {
			return team1.goalDifference_ > team2.goalDifference_;
		}
		else if (team1.goalsFor_ != team2.goalsFor_) {
			return team1.goalsFor_ > team2.goalsFor_;
		}
		else if (team1.matchesWon_ != team2.matchesWon_) {
			return team1.matchesWon_ > team2.matchesWon_;
		}
		else if (team1.matchesDraw_ != team2.matchesDraw_) {
			return team1.matchesDraw_ > team2.matchesDraw_;
		}
		else {
			return team1.rating_ < team2.rating_;
		}
	}

	void printTable() {
		system("cls");
		std::sort(teams_.begin(), teams_.end(), teamComparator);
		int pos = 1;
		std::cout << std::left << std::setw(6) << "Поз" << std::left << std::setw(10) <<"Команда" << "Очки" << std::endl;
		for (const Team& team : teams_) {
			std::cout << std::right << std::setw(2)  << pos <<"   "<<  std::setw(13) << std::left << team.getName() << team.getPts() << std::endl;
			++pos;
		}
	}
};
