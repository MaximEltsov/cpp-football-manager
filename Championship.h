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

const double EPSILON = 0.00001;

const std::string clubListFilename = "Clubs\\ItalianClubs.txt";

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
	std::deque<Team> teams_;
	MatchCalendar season_;
	//Standings table_;
	GlobalCalendar time_;
	std::string playerTeam_="";
	std::unordered_map<int, std::vector<std::pair<int, int>>> tourResults_;
	
public:

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
		std::fstream file(filename, std::ios::in | std::ios::out);
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
				std::string temp = line + " ";
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
					std::cout << player.name_ << line << std::endl;
					system("pause");
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
				std::getline(file, line);
				std::getline(file, line);
				int talant = std::stoi(line);
				if (talant > 4) {
					std::cout << player.name_;
					system("pause");
					player.talant_ = 5;
				}
				else {
					player.talant_ = talant + 1;
				}
				std::getline(file, line);
				player.position_ = std::stoi(line);
				for (int i = 0; i < 6; ++i) {
					std::getline(file, line);
				}
				std::getline(file, line);
				player.abilities.passing = std::stoi(line);
				std::getline(file, line);
				player.abilities.header = std::stoi(line);
				std::getline(file, line);
				player.abilities.shotPower = std::stoi(line);
				std::getline(file, line);
				player.abilities.shooting = std::stoi(line);
				std::getline(file, line);
				player.abilities.acceleration = std::stoi(line);
				std::getline(file, line);
				player.abilities.speed = std::stoi(line);
				std::getline(file, line);
				player.abilities.tackling = std::stoi(line);
				std::getline(file, line);
				player.abilities.dribbling = std::stoi(line);
				std::getline(file, line);
				player.abilities.technuque = std::stoi(line);
				std::getline(file, line);
				player.abilities.crossing = std::stoi(line);
				std::getline(file, line);
				player.abilities.reflexes = std::stoi(line);
				std::getline(file, line);
				player.abilities.flyingSaves = std::stoi(line);
				std::getline(file, line);
				player.abilities.aerialControl = std::stoi(line);
				std::getline(file, line);
				player.abilities.oneOnone = std::stoi(line);
				std::getline(file, line);
				player.abilities.goalKicks = std::stoi(line);
				std::getline(file, line);
				player.abilities.throwOut = std::stoi(line);
				for (int i = 0; i < 17; ++i) {
					std::getline(file, line);
				}
				std::getline(file, line);
				player.localexp_ = std::stoi(line);
				std::getline(file, line);
				player.intexp_ = std::stoi(line);
				player.CalcPosLvl();
				player.calculatelvl(player.position_);
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
			std::string playersFilename = "Clubs\\" + clubName + ".txt";
			std::cout << "Клуб: " << clubName << std::endl;
			std::cout << "Игроки:" << std::endl;
			Team team(clubName);
			readPlayersFromFile(playersFilename, team);
			std::cout << std::endl;
			team.getLvl();
			team.tactic = std::move(Tactics(team.roaster_));
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
			playerTeam_ = teams_[choice - 1].name_;
			//playerTeam_.printInformation();
		}
		else {
			std::cout << "Недопустимый выбор команды.";
		}
	}

	const std::deque<Team> GetTeams() const {
		return teams_;
	}

	void printTour(const std::vector<std::pair<int,int>>& results) const {
		std::cout << "Tour " << currentTour_-1 << std::endl;
		int i = 0;
		for (const auto& match : season_.GetTour(currentTour_-1)) {
			std::cout << "Team ";
			if (teams_[match.first].getName() == playerTeam_) {
				SetConsoleColor(10);
				std::cout << std::left << std::setw(17) << teams_[match.first].getName();
				SetConsoleColor(7);
			}
			else {
				std::cout << std::left << std::setw(17) << teams_[match.first].getName();
			}
			std::cout  << results[i].first << ":" << std::left << std::setw(6) << results[i].second;
			++i;
			if (teams_[match.second].getName() == playerTeam_) {
				SetConsoleColor(10);
				std::cout << "Team " << teams_[match.second].getName();
				SetConsoleColor(7);
			}
			else {
				std::cout << "Team " << teams_[match.second].getName();
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void printTour() const {
		std::cout << "Tour " << currentTour_ << std::endl;
		for (const auto& match : season_.GetTour(currentTour_)) {
			std::cout  << "Team ";
			if (teams_[match.first].getName() == playerTeam_) {
				SetConsoleColor(10);
				std::cout << std::left << std::setw(15) << teams_[match.first].getName();
				SetConsoleColor(7);
			}
			else {
				std::cout << std::left << std::setw(15) << teams_[match.first].getName();
			}
			std::cout << std::left << std::setw(6)  << "vs";
			if (teams_[match.second].getName() == playerTeam_) {
				SetConsoleColor(10);
				std::cout <<"Team "<< teams_[match.second].getName();
				SetConsoleColor(7);
			}
			else {
				std::cout << "Team " << teams_[match.second].getName();
			} 
			std::cout << std::endl;
			}
		std::cout << std::endl;
	}	

	void printCalendar() const {
		//std::cout << season_.getCalendar().size() << std::endl;
		for (const auto& tour : season_.getCalendar()) {
			std::cout << "Tour " << tour.first << std::endl;
			for (const auto& match : tour.second) {

				std::cout  << "Team ";
				if (teams_[match.first].getName() == playerTeam_) {
					SetConsoleColor(10);
					std::cout << std::left << std::setw(15) << teams_[match.first].getName();
					SetConsoleColor(7);
				}
				else {
					std::cout << std::left << std::setw(15) << teams_[match.first].getName();
				}
				std::cout << std::left << std::setw(6)  << "vs";
				if (teams_[match.second].getName() == playerTeam_) {
					SetConsoleColor(10);
					std::cout <<"Team "<< teams_[match.second].getName();
					SetConsoleColor(7);
				}
				else {
					std::cout << "Team " << teams_[match.second].getName();
				} 
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	}

	std::pair<int, int> simulateMatch(Team& team1, Team& team2) {
		const int K_SUCCESS = 250;
		std::random_device rd;
		std::default_random_engine engine(rd());
		double diff = 1.05*team1.lvl_ - team2.lvl_;
		double successRate1, successRate2;

		//if (diff > EPSILON) {
			successRate1 = 0.3+diff/ K_SUCCESS;
			successRate2 = 0.3- diff / K_SUCCESS;
		//}
		/*else if (diff < -EPSILON) {
			successRate1 = 0.45;
			successRate2 = 0.55;
		}
		else {
			successRate1 = 0.55;
			successRate2 = 0.5;
		}*/

		std::binomial_distribution<int> distribution1(static_cast<int>(team1.lvl_/20), successRate1);
		std::binomial_distribution<int> distribution2(static_cast<int>(team2.lvl_/20), successRate2);

		int scoreTeam1 = distribution1(engine);
		int scoreTeam2 = distribution2(engine);

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
		return { scoreTeam1 , scoreTeam2 };
	}

	void playTour() {
		for (const auto& match : season_.calendar_.at(currentTour_)) {
			Team& team1 = teams_[match.first];
			Team& team2 = teams_[match.second];
			team1.tactic.sortTeam(&team1.roaster_);
			team2.tactic.sortTeam(&team2.roaster_);

			tourResults_[currentTour_].push_back(std::move(simulateMatch(team1, team2)));
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

	void PrintTourResult() const {
		printTour(tourResults_.at(currentTour_-1));
	}

	void printTable() {
		system("cls");
		std::sort(teams_.begin(), teams_.end(), teamComparator);
		int pos = 1;
		std::cout << std::left << std::setw(6) << "Поз" << std::left << std::setw(18) <<"Команда" << "Очки" << std::endl;
		for (const Team& team : teams_) {
			if (team.name_==playerTeam_) {
				SetConsoleColor(10);
				std::cout << std::right << std::setw(2) << pos << "   " << std::setw(20) << std::left << team.getName() << team.getPts() << std::endl;
				SetConsoleColor(7);
			}
			else {
				std::cout << std::right << std::setw(2) << pos << "   " << std::setw(20) << std::left << team.getName() << team.getPts() << std::endl;
			}
			++pos;
		}
	}
};
