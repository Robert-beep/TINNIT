#pragma once
#include <string>
#include "Memory.h"

enum status {aktiv, inaktiv};

class Player
{
public:
	//aus PrimeGame gestohlen
	Player(Memory* application);
	Player(string name, Memory* application);
	~Player();
	string getName();
	int gesamtpunktzahl;
	int punkte_siege;
	int gespielte_spiele;
	void addPoints(int points);
	//void add_punkte_siege(int punkte);
	//void add_gespielte_spiele();
	Player::Player();

	int boardsize;
	string name;
	bool disqualified;
	Memory* temp;
	int points;
};