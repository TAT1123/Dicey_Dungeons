#include "stdafx.h"

#include "Equipment.h"

void EquipmentClass::importWorkFunction(std::function<void()> func) {
	workFunction = func;
}

void EquipmentClass::importShowFunction(std::function<void()> func) {
	showFunction = func;
}

void EquipmentClass::importShowTextFunction(std::function<void()> func) {
	showTextFunction = func;
}

void EquipmentClass::importMoveFunction(std::function<void()> func) {
	moveFunction = func;
}

void EquipmentClass::callWorkFunction() {
	if (workFunction) {
		workFunction();
	}
}

void EquipmentClass::callShowFunction() {
	if (showFunction) {
		showFunction();
	}
}

void EquipmentClass::callTextFunction() {
	if (showTextFunction) {
		showTextFunction();
	}
}

void EquipmentClass::callMoveFunction() {
	if (moveFunction) {
		moveFunction();
	}
}

void EquipmentClass::RestructFunction(int x_offset) {
	equipment.SetTopLeft(x_offset + 40 + 470 * (backpack_column), (backpack_row + 1)* 300);
	if (diceslot_exist == true) {
		diceslot.SetTopLeft(x_offset + 40 + 470 * (backpack_column)+134, (backpack_row + 1) * 300 + 165);
		diceslot.SetFrameIndexOfBitmap(6);
	}
}