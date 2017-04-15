#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Player.cpp"

class UILabels
{
public:
	UILabels(Player p);
	~UILabels();

	//method to get player obj score
	void DisplayScore(void);

	void IncrementScore(void);

	//method to get play obj bullet count
	void DisplayAmmoCount();

	//method to check if player obj reached goal
	void DisplayGoal();

	void CheckGoal(bool);

private:
	//timer
	float endTimer;
	float currentTimer;
	//win/lose
	bool roundCleared;
	//score
	int score;
	//bullets
	int bullets;
	//goal
	int goalNum;

};

