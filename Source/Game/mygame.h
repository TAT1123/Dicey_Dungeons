/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/
#include <functional>
#include "Equipment.h"
#include "Enemy.h"
#include "Character.h"


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap logo;								// csie的logo

	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void InitializeEnemies();
		void InitializeEquipments();
		void ChangeEquipments();

		void DefeatEnemy();

		void CGameStateRun::SpaceMarineWork();
		void CGameStateRun::GardenerWork();
		void CGameStateRun::SneezeyWork();
		void CGameStateRun::MarshmallowWork();
		void CGameStateRun::StereoheadWork();
		void CGameStateRun::BabySquidWork();
		void CGameStateRun::BullyWork();
		void CGameStateRun::VacuumWork();
		void CGameStateRun::FiremanWork();
		void CGameStateRun::SnowmanWork();
		void CGameStateRun::WickermanWork();
		void CGameStateRun::RhinoBeetleWork();
		void CGameStateRun::KrakenWork();
		int hitmore = 0;
		void CGameStateRun::CorneliusWork();
		void CGameStateRun::RatKingWork();
		void CGameStateRun::BusterWork();


		void CGameStateRun::statusEffects();

		void useEquipmentSword(Character& Warrior, EquipmentClass& equipment_sword, std::function<void()> DefeatEnemy);
		void useEquipmentDebugSword(Character& Warrior, EquipmentClass& equipment_sword, std::function<void()> DefeatEnemy);
		void useEquipmentBattleAxe(Character& Warrior, EquipmentClass& equipment_battleaxe, std::function<void()> DefeatEnemy);
		void useEquipmentToxicOoze(Character& Warrior, EquipmentClass& equipment, std::function<void()> DefeatEnemy);
		void useEquipmentBloodStuck(Character& Warrior, EquipmentClass& equipment, std::function<void()> DefeatEnemy);
		void useEquipmentShovel(Character& Warrior, EquipmentClass& equipment, std::function<void()> DefeatEnemy);

		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);

		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠左鍵的動作
		void ui_combat_OnLButtonDown(UINT nFlags, CPoint point); //戰鬥時
		void ui_map_OnLButtonDown(UINT nFlags, CPoint point);
		void ui_backpack_OnLButtonDown(UINT nFlags, CPoint point);
		void ui_shops_OnLButtonDown(UINT nFlags, CPoint point);
		void ui_menu_OnLButtonDown(UINT nFlags, CPoint point);

		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void ui_combat_OnLButtonUp(UINT nFlags, CPoint point);  //戰鬥時
		void ui_backpack_OnLButtonUp(UINT nFlags, CPoint point);

		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠移動的動作 
	    void ui_map_OnMouseMove(UINT nFlags, CPoint point);
		void ui_combat_OnMouseMove(UINT nFlags, CPoint point); // 戰鬥時
		void ui_backpack_OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠移動的動作

		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作

	protected:
		void OnMove();									// 移動遊戲元素

		void OnShow();									// 顯示這個狀態的遊戲畫面
		void ui_combat_OnShow();
		void ui_map_OnShow();
		void ui_backpack_OnShow();
		void ui_shops_OnShow();
		void ui_menu_OnShow();


		//全物件
		CMovingBitmap menu;
		CMovingBitmap door[3];
		int mod = 0;


		int enemy_living[6][4] = { 
			{1, 1, -1, -1},
			{1, 1, 1, -1},
			{1, 1, 1, -1},
			{1, 1, 1, -1},
			{1, 1, 1, 1},
			{1, -1, -1, -1}
		};

		//背包物件
		CMovingBitmap backpack_background;
		CMovingBitmap backpack_in_test_square[4][5];
		CMovingBitmap backpack_out_test_square[3][2];
		int backpack_use[4][5] = { 0 };
		int work_use[3][2] = { 0 };


		int backpack_equipment_amount = 2;

		EquipmentClass *Backpack[20];
		EquipmentClass *Work[6];
		EquipmentClass equipment_sword;
		EquipmentClass equipment_battleaxe_origin;
		EquipmentClass equipment_venus_fly_trap_origin;
		EquipmentClass equipment_debug_sword;

		EquipmentClass equipment_battleaxe;
		EquipmentClass equipment_bump;
		EquipmentClass equipment_fire_breath;
		EquipmentClass equipment_blood_stuck;
		EquipmentClass equipment_shovel;
		EquipmentClass equipment_spike;
		EquipmentClass equipment_fireball;
		EquipmentClass equipment_venus_fly_trap;
		EquipmentClass equipment_bear_maul;
		EquipmentClass equipment_toxic_ooze;
		EquipmentClass equipment_rat;

		EquipmentClass equipment_reroll;

		//地圖物件

		//floor
		CMovingBitmap floor_map[4][4] = {};

		int enemy_poison = 0;

		// 是否有地板
		int floor1_map1_exeist[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 1, 0},
		{1, 1, 1, 0},
		{0, 1, 1, 0}
		};
		//地板上是否有東西
		int floor1_map1_item[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 3, 0},
		{0, 0, 1, 0},
		{0, 1, 7, 0}
		};

		// 是否有地板
		int floor2_map1_exeist[4][4] = {
		{0, 1, 0, 0},
		{1, 1, 1, 0},
		{1, 1, 1, 1},
		{0, 1, 1, 0}
		};
		//地板上是否有東西
		int floor2_map1_item[4][4] = {
		{0, 7, 0, 0},
		{2, 0, 1, 0},
		{4, 1, 0, 0},
		{0, 3, 1, 0}
		};

		// 是否有地板
		int floor3_map1_exeist[4][4] = {
		{0, 1, 1, 1},
		{1, 1, 1, 0},
		{1, 1, 1, 1},
		{1, 0, 1, 0}
		};
		//地板上是否有東西
		int floor3_map1_item[4][4] = {
		{0, 5, 3, 2},
		{2, 1, 1, 0},
		{0, 0, 1, 4},
		{2, 0, 0, 0}
		};

		// 是否有地板
		int floor4_map1_exeist[4][4] = {
		{0, 1, 1, 0},
		{1, 1, 1, 1},
		{1, 1, 1, 1},
		{0, 1, 1, 0}
		};

		//地板上是否有東西
		int floor4_map1_item[4][4] = {
		{0, 1, 2, 0},
		{0, 6, 0, 0},
		{1, 0, 1, 3},
		{0, 0, 7, 0}
		};

		// 是否有地板
		int floor5_map1_exeist[4][4] = {
		{1, 1, 1, 1},
		{1, 1, 1, 1},
		{0, 1, 1, 1},
		{0, 0, 1, 1}
		};

		//地板上是否有東西
		int floor5_map1_item[4][4] = {
		{7, 1, 5, 2},
		{0, 1, 4, 2},
		{0, 0, 1, 0},
		{0, 0, 1, 3}
		};

		CMovingBitmap map; //樓層地圖

		//
		CMovingBitmap background; //背景

		CMovingBitmap ui_map_downbox;

		CMovingBitmap head; //主角icon
		CMovingBitmap star;
		CMovingBitmap backpack_button;
		CMovingBitmap bone[6];

		CMovingBitmap exit;
		CMovingBitmap treasure;
		CMovingBitmap food[2];

		CMovingBitmap *map_enemy[6][4]; //敵人地圖小圖示

		CMovingBitmap map_character;  //主角地圖小圖示


		//shops
		CMovingBitmap shops;
		CMovingBitmap map_shops;
		CMovingBitmap buy_button[3];
		int floor2_shop_item[3] = { 1, 1, 1 };
		CMovingBitmap end_shops_button;
		CMovingBitmap* shops_equipment;

		int floor = 1;
		

		CMovingBitmap ui_combat_background;

		Character Warrior;

		CMovingBitmap mouse_point;
		int dice_overlap_mouse[6] = { 0 };

		//use or not
		int equipment_use[6] = { 1,1,1,1,1,1 };
		int dice_use[5] = { 1,1,1,1,1 };

		CMovingBitmap dice_fired[5];
		CMovingBitmap dice_blind[5];
		CMovingBitmap dice_locked[5];
		int isfire[5] = { 0,0,0,0,0 };
		int isblind[5] = { 0,0,0,0,0 };
		int islocked[5] = { 0,0,0,0,0 };

		//ui_combat 小圖示
		CMovingBitmap end_turn_arrow;
		CMovingBitmap uparrow_arrow;
		CMovingBitmap symbols_dice;

		//ui_combat 敵人
		EnemyClass *CurrentEnemy;
		EnemyClass SpaceMarine;
		EnemyClass Gardener;
		EnemyClass Sneezey;
		EnemyClass Marshmallow;
		EnemyClass Stereohead;
		EnemyClass BabySquid;
		EnemyClass Bully;
		EnemyClass Vacuum;
		EnemyClass Fireman;
		EnemyClass Snowman;
		EnemyClass WickerMan;
		EnemyClass RhinoBeetle;
		EnemyClass Kraken;
		EnemyClass Cornelius;
		EnemyClass RatKing;
		EnemyClass Buster; //Dragon
		
		//敵人共用
		CMovingBitmap enemy_healthbar_front;
		CMovingBitmap enemy_healthbar_back;
		CMovingBitmap enemy_dice[6];
		int enemy_equipment_use[6] = { 1,1,1,1,1,1 };
		int enemy_dice_use[6] = { 1,1,1,1,1,1 };

		bool enemyShow = 0;
		bool enemyPreview = 0;

		int state = 10;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap background;
		int counter;	// 倒數之計數器
	};
}
