#pragma once

#include "../Library/gameutil.h"
#include <functional>

using namespace game_framework;
using std::function;

class EquipmentClass {
public:
	int size;
	CMovingBitmap backpack_square;
	CMovingBitmap equipment;
	CMovingBitmap diceslot;
	CMovingBitmap required;


	int equipment_x, equipment_y;

	int diceslot_x, diceslot_y;
	bool diceslot_exist;

	function<void()> workFunction;
	function<void()> showFunction;
	function<void()> showTextFunction;
	function<void()> moveFunction;

	int overlap_mouse; //背包用

	int backpack_column;
	int backpack_row;
	bool work;

	void importWorkFunction(function<void()> func);
	void importShowFunction(function<void()> func);
	void importShowTextFunction(function<void()> func);
	void importMoveFunction(function<void()> func);

	void callWorkFunction();
	void callShowFunction();
	void callTextFunction();
	void callMoveFunction();
	void RestructFunction(int x_offset);
};