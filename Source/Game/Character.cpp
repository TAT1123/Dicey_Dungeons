#include "stdafx.h"

#include "Character.h"

void Character::ShowHealthBars() {
	healthbar_back.ShowBitmap();
	healthbar_front.ShowBitmap();
}

void Character::LevelUp() {
	if (exp >= exp_need[level - 1]) {

		exp -= exp_need[level - 1];
		level += 1;
		max_health += 4;
		current_health = max_health;

		if (level == 2) {
			chararter_dice_amount += 1;
		}
	}
}