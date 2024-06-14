#pragma once

#include "../Library/gameutil.h"
#include <vector>
#include <string>
#include <utility> 

#include <functional>

using namespace game_framework;
using std::function;

class EnemyClass {
public:
	int floor_enemy_id;
	int enemy_equipment_number;
	int enemy_dice_amount;
	int enemy_level;
	int enemy_max_health;
	int enemy_current_health;

	function<void()> workFunction;

	std::vector<std::pair<int, int>> positions = {
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0}
	};

	std::string enemy_name;

	game_framework::CMovingBitmap enemy;
	game_framework::CMovingBitmap enemy_equipment[6];
	game_framework::CMovingBitmap map_enemy;
	int enemy_required[6] = { 0 };

	void importWorkFunction(function<void()> func);
	void SetEnemyEquipmentPositions(int index, int x_offset, int y_offset, const std::vector<std::pair<int, int>>& positions);
	void callWorkFunction();


};