#include "Player.h"
#include "Memory.h"
#include <string>

Player::Player(Memory* application)
{
	temp = application;
	this->disqualified = false;
}

Player::Player(string inputname, Memory* application)
{
	temp = application;
	this->name = inputname;
	this->disqualified = false;
	this->points = 0;
	status inaktiv;

}

void Player::addPoints(int points)
{
	points++;

}

Player::~Player()
{

}