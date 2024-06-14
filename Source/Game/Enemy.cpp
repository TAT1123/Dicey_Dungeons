#include "stdafx.h"
#include "Enemy.h"

void EnemyClass::SetEnemyEquipmentPositions(int index, int x_offset, int y_offset, const std::vector<std::pair<int, int>>& positions) {
	for (int i = 0; i < index; ++i) {
		if (i < int(positions.size())) {
			enemy_equipment[i].SetTopLeft(x_offset + positions[i].first, y_offset + positions[i].second);
		}
	}
}

void EnemyClass::importWorkFunction(std::function<void()> func) {
	workFunction = func;
}

void EnemyClass::callWorkFunction() {
	if (workFunction) {
		workFunction();
	}
}