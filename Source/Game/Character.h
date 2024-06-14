#pragma once


#include "../Library/gameutil.h"

using namespace game_framework;


class Character {
public:
	CMovingBitmap character;
	CMovingBitmap healthbar_front;
	CMovingBitmap healthbar_back;
	CMovingBitmap limitbar_front;
	CMovingBitmap limitbar_back;
	CMovingBitmap dice[5];
	int max_health = 24;
	int current_health = 24;
	int chararter_dice_amount = 2;

	int money = 0;
	int level = 1;
	int exp_need[5] = { 2, 4, 7, 14, 18 };
	int exp = 0;

	int reroll = 3;
	int max_row = 1;
	
	//狀態
	int weaken = 0;
	int fired = 0;
	int freezed = 0;
	int blind = 0;
	int locked = 0;
	int cursed = 0;
	int poison = 0;

	void ShowHealthBars();
	void LevelUp();
};