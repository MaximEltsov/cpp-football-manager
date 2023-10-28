#include <iostream>

#include "Championship.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Ru");

	ItalianChampionship game;
	game.SetTeam();
	//game.printCalendar();
	//(*game.playerTeam_).printTeamRoaster();
	for (int i = 1; i <= game.tourCount(); ++i) {
		game.printTable();
		game.playTour();
	}

	return 0;
};