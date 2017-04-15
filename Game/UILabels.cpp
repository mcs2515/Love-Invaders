#include "UILabels.h"



UILabels::UILabels(Player p)
{
	//get the player's starting bullet count
	 bullets = p.m_iBullets;

	 score = 0; //start with 0
	 endTimer = 30; //seconds
	 currentTimer = 0; //start with 0
}

//method displays current score
void UILabels::DisplayScore() {
	
}

UILabels::~UILabels()
{
}
