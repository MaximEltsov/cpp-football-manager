#include <iostream>

#include "Championship.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Ru");

	ItalianChampionship game;
	game.SetTeam();
	//game.printCalendar();
	/*(*game.playerTeam_).printTeamRoaster();
	(*game.playerTeam_).sortRoaster();
	(*game.playerTeam_).printTeamRoaster();*/
	for (int i = 1; i <= game.tourCount(); ++i) {
		//game.printTour();
		game.playTour();
		//game.PrintTourResult();
		game.printTable();
	}
	//game.printTable();


	return 0;
};