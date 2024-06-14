#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

#include <random>
#include <chrono>
#include <thread>
#include <ctime>

#include <string>
#include <sstream> 
#include <algorithm>
#include <set>
//#include <cstdlib>

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{

}

void CGameStateRun::InitializeEnemies()
{	
	//太空戰士
	SpaceMarine.enemy.LoadBitmapByString({ "resources/enemy/space_marine.bmp" }, RGB(76, 105, 113));
	SpaceMarine.enemy.SetTopLeft(1320, -40);
	SpaceMarine.floor_enemy_id = 0;
	SpaceMarine.enemy_equipment_number = 1;
	SpaceMarine.enemy_dice_amount = 3;
	SpaceMarine.enemy_level = 1;
	SpaceMarine.enemy_max_health = 14;
	SpaceMarine.enemy_current_health = SpaceMarine.enemy_max_health;
	SpaceMarine.enemy_name = "星際戰士";
	SpaceMarine.map_enemy.LoadBitmapByString({ "resources/ui_map/map_enemy_spacemarine1.bmp", "resources/ui_map/map_enemy_spacemarine2.bmp" }, RGB(76, 105, 113));

	SpaceMarine.enemy_equipment[0].LoadBitmapByString({ "resources/equipment/plasma_cannon.bmp" }, RGB(76, 105, 113));
	SpaceMarine.enemy_equipment[0].SetTopLeft(760, 380);
	SpaceMarine.positions[0] = { 760, 380 };

	SpaceMarine.importWorkFunction([this]() { this->SpaceMarineWork(); });

	SpaceMarine.enemy_required[0] = 20;
	//

	//兔子
	Gardener.enemy.LoadBitmapByString({ "resources/enemy/gardener.bmp" }, RGB(76, 105, 113));
	Gardener.enemy.SetTopLeft(1320, -40);
	Gardener.floor_enemy_id = 1;
	Gardener.enemy_equipment_number = 1;
	Gardener.enemy_dice_amount = 2;
	Gardener.enemy_level = 1;
	Gardener.enemy_max_health = 12;
	Gardener.enemy_current_health = Gardener.enemy_max_health;
	Gardener.enemy_name = "花園老伯";
	Gardener.map_enemy.LoadBitmapByString({ "resources/ui_map/map_enemy_gardener1.bmp", "resources/ui_map/map_enemy_gardener2.bmp" }, RGB(76, 105, 113));

	Gardener.enemy_equipment[0].LoadBitmapByString({ "resources/equipment/shovel.bmp" }, RGB(76, 105, 113));
	Gardener.enemy_equipment[0].SetTopLeft(760, 290);
	Gardener.positions[0] = { 760, 290 };

	Gardener.importWorkFunction([this]() { this->GardenerWork(); });

	//刺蝟
	Sneezey.enemy.LoadBitmapByString({ "resources/enemy/sneezey.bmp" }, RGB(76, 105, 113));
	Sneezey.enemy.SetTopLeft(1320, -40);
	Sneezey.floor_enemy_id = 0;
	Sneezey.enemy_equipment_number = 5;
	Sneezey.enemy_dice_amount = 3;
	Sneezey.enemy_level = 2;
	Sneezey.enemy_max_health = 24;
	Sneezey.enemy_current_health = Sneezey.enemy_max_health;
	Sneezey.enemy_name = "噴嚏刺蝟";
	Sneezey.map_enemy.LoadBitmapByString({ "resources/ui_map/map_enemy_sneezey1.bmp", "resources/ui_map/map_enemy_sneezey2.bmp" }, RGB(76, 105, 113));
	Sneezey.enemy_equipment[0].LoadBitmapByString({ "resources/equipment/sneeze.bmp" }, RGB(76, 105, 113));
	Sneezey.enemy_equipment[0].SetTopLeft(150, 290);
	Sneezey.positions[0] = { 150, 290 };
	Sneezey.enemy_equipment[1].LoadBitmapByString({ "resources/equipment/spike.bmp" }, RGB(76, 105, 113));
	Sneezey.enemy_equipment[1].SetTopLeft(150 + 480, 235);
	Sneezey.positions[1] = { 150 + 480, 235 };
	Sneezey.enemy_equipment[2].LoadBitmapByString({ "resources/equipment/spike.bmp" }, RGB(76, 105, 113));
	Sneezey.enemy_equipment[2].SetTopLeft(150 + 480 * 2, 235);
	Sneezey.positions[2] = { 150 + 480 * 2, 235 };
	Sneezey.enemy_equipment[3].LoadBitmapByString({ "resources/equipment/spike.bmp" }, RGB(76, 105, 113));
	Sneezey.enemy_equipment[3].SetTopLeft(150 + 480, 235 + 305);
	Sneezey.positions[3] = { 150 + 480, 235 + 305 };
	Sneezey.enemy_equipment[4].LoadBitmapByString({ "resources/equipment/spike.bmp" }, RGB(76, 105, 113));
	Sneezey.enemy_equipment[4].SetTopLeft(150 + 480 * 2, 235 + 305);
	Sneezey.positions[4] = { 150 + 480 * 2, 235 + 305 };

	Sneezey.enemy_required[1] = 6;
	Sneezey.enemy_required[2] = 6;
	Sneezey.enemy_required[3] = 6;
	Sneezey.enemy_required[4] = 6;

	Sneezey.importWorkFunction([this]() { this->SneezeyWork(); });

	//棉花糖
	Marshmallow.enemy.LoadBitmapByString({ "resources/enemy/marshmallow.bmp" }, RGB(76, 105, 113));
	Marshmallow.enemy.SetTopLeft(1320, -40);
	Marshmallow.floor_enemy_id = 1;
	Marshmallow.enemy_equipment_number = 2;
	Marshmallow.enemy_dice_amount = 2;
	Marshmallow.enemy_level = 2;
	Marshmallow.enemy_max_health = 28;
	Marshmallow.enemy_current_health = Marshmallow.enemy_max_health;
	Marshmallow.enemy_name = "棉花糖";
	Marshmallow.map_enemy.LoadBitmapByString({ "resources/ui_map/map_enemy_marshmallow1.bmp", "resources/ui_map/map_enemy_marshmallow2.bmp" }, RGB(76, 105, 113));

	Marshmallow.enemy_equipment[0].LoadBitmapByString({ "resources/equipment/snowball.bmp" }, RGB(76, 105, 113));
	Marshmallow.enemy_equipment[0].SetTopLeft(760, 235);
	Marshmallow.positions[0] = { 760, 235 };
	Marshmallow.enemy_equipment[1].LoadBitmapByString({ "resources/equipment/fireball.bmp" }, RGB(76, 105, 113));
	Marshmallow.enemy_equipment[1].SetTopLeft(760, 235 + 305);
	Marshmallow.positions[1] = { 760, 235 + 305};

	Marshmallow.importWorkFunction([this]() { this->MarshmallowWork(); });
	//音響頭
	Stereohead.enemy.LoadBitmapByString({ "resources/enemy/stereohead.bmp" }, RGB(76, 105, 113));
	Stereohead.enemy.SetTopLeft(1320, -40);
	Stereohead.floor_enemy_id = 2;
	Stereohead.enemy_equipment_number = 2;
	Stereohead.enemy_dice_amount = 2;
	Stereohead.enemy_level = 2;
	Stereohead.enemy_max_health = 28;
	Stereohead.enemy_current_health = Stereohead.enemy_max_health;
	Stereohead.enemy_name = "音響頭";
	Stereohead.map_enemy.LoadBitmapByString({ "resources/ui_map/map_enemy_stereohead1.bmp", "resources/ui_map/map_enemy_stereohead2.bmp" }, RGB(76, 105, 113));

	Stereohead.enemy_equipment[0].LoadBitmapByString({ "resources/equipment/sonic_wave.bmp" }, RGB(76, 105, 113));
	Stereohead.enemy_equipment[0].SetTopLeft(760, 235);
	Stereohead.positions[0] = { 760, 235 };
	Stereohead.enemy_equipment[1].LoadBitmapByString({ "resources/equipment/sonic_wave.bmp" }, RGB(76, 105, 113));
	Stereohead.enemy_equipment[1].SetTopLeft(760, 235 + 305);
	Stereohead.positions[1] = { 760, 235 + 305};
	
	Stereohead.importWorkFunction([this]() { this->StereoheadWork(); });
	//
	// 
	//烏賊寶寶
	BabySquid.enemy.LoadBitmapByString({ "resources/enemy/baby_squid.bmp" }, RGB(76, 105, 113));
	BabySquid.enemy.SetTopLeft(1320, -40);
	BabySquid.floor_enemy_id = 0;
	BabySquid.enemy_equipment_number = 2;
	BabySquid.enemy_dice_amount = 2;
	BabySquid.enemy_level = 2;
	BabySquid.enemy_max_health = 26;
	BabySquid.enemy_current_health = BabySquid.enemy_max_health;
	BabySquid.enemy_name = "烏賊寶寶";
	BabySquid.map_enemy.LoadBitmapByString({ "resources/ui_map/map_enemy_babysquid1.bmp", "resources/ui_map/map_enemy_babysquid2.bmp" }, RGB(76, 105, 113));

	BabySquid.enemy_equipment[0].LoadBitmapByString({ "resources/equipment/ink_splat.bmp" }, RGB(76, 105, 113));
	BabySquid.enemy_equipment[0].SetTopLeft(520, 320);
	BabySquid.positions[0] = { 520, 320 };
	BabySquid.enemy_equipment[1].LoadBitmapByString({ "resources/equipment/head_butt.bmp" }, RGB(76, 105, 113));
	BabySquid.enemy_equipment[1].SetTopLeft(520 + 470, 320);
	BabySquid.positions[1] = { 520 + 470, 320 };

	BabySquid.importWorkFunction([this]() { this->BabySquidWork(); });

	//惡霸
	Bully.enemy.LoadBitmapByString({ "resources/enemy/bully.bmp" }, RGB(76, 105, 113));
	Bully.enemy.SetTopLeft(1320, -40);
	Bully.floor_enemy_id = 1;
	Bully.enemy_equipment_number = 5;
	Bully.enemy_dice_amount = 2;
	Bully.enemy_level = 3;
	Bully.enemy_max_health = 34;
	Bully.enemy_current_health = Bully.enemy_max_health;
	Bully.enemy_name = "惡霸";
	Bully.map_enemy.LoadBitmapByString({ "resources/ui_map/map_enemy_bully1.bmp" }, RGB(76, 105, 113));

	Bully.enemy_equipment[0].LoadBitmapByString({ "resources/equipment/rock.bmp" }, RGB(76, 105, 113));
	Bully.enemy_equipment[0].SetTopLeft( 200, 230);
	Bully.positions[0] = { 200, 230 };
	Bully.enemy_equipment[1].LoadBitmapByString({ "resources/equipment/rock.bmp" }, RGB(76, 105, 113));
	Bully.enemy_equipment[1].SetTopLeft(200 + 480, 230);
	Bully.positions[1] = { 200 + 480, 230 };
	Bully.enemy_equipment[2].LoadBitmapByString({ "resources/equipment/rock.bmp" }, RGB(76, 105, 113));
	Bully.enemy_equipment[2].SetTopLeft(200, 230 + 305);
	Bully.positions[2] = { 200, 230 + 305 };
	Bully.enemy_equipment[3].LoadBitmapByString({ "resources/equipment/rock.bmp" }, RGB(76, 105, 113));
	Bully.enemy_equipment[3].SetTopLeft(200 + 480, 230 + 305);
	Bully.positions[3] = { 200 + 480, 230 + 305 };
	Bully.enemy_equipment[4].LoadBitmapByString({ "resources/equipment/fists.bmp" }, RGB(76, 105, 113));
	Bully.enemy_equipment[4].SetTopLeft(200 + 480 * 2, 230 + 80);
	Bully.positions[4] = { 200 + 480 * 2, 230 + 80 };

	Bully.importWorkFunction([this]() { this->BullyWork(); });
	//

	//吸塵器
	Vacuum.enemy.LoadBitmapByString({ "resources/enemy/vacuum.bmp" }, RGB(76, 105, 113));
	Vacuum.enemy.SetTopLeft(1320, -40);
	Vacuum.floor_enemy_id = 2;
	Vacuum.enemy_equipment_number = 2;
	Vacuum.enemy_dice_amount = 3;
	Vacuum.enemy_level = 3;
	Vacuum.enemy_max_health = 30;
	Vacuum.enemy_current_health = Vacuum.enemy_max_health;
	Vacuum.enemy_name = "吸塵器";
	Vacuum.map_enemy.LoadBitmapByString({ "resources/ui_map/map_enemy_vacuum1.bmp" }, RGB(76, 105, 113));

	Vacuum.enemy_equipment[0].LoadBitmapByString({ "resources/equipment/dust_cloud.bmp" }, RGB(76, 105, 113));
	Vacuum.enemy_equipment[0].SetTopLeft(520, 320);
	Vacuum.positions[0] = { 520, 320 };
	Vacuum.enemy_equipment[1].LoadBitmapByString({ "resources/equipment/blood_stuck.bmp" }, RGB(76, 105, 113));
	Vacuum.enemy_equipment[1].SetTopLeft(520, 320);
	Vacuum.positions[1] = { 520 + 470, 320 };

	Vacuum.importWorkFunction([this]() { this->VacuumWork(); });
	//
// 
	//火人
	Fireman.enemy.LoadBitmapByString({ "resources/enemy/fireman.bmp" }, RGB(76, 105, 113));
	Fireman.enemy.SetTopLeft(1320, -40);
	Fireman.floor_enemy_id = 0;
	Fireman.enemy_equipment_number = 2;
	Fireman.enemy_dice_amount = 4;
	Fireman.enemy_level = 3;
	Fireman.enemy_max_health = 34;
	Fireman.enemy_current_health = Fireman.enemy_max_health;
	Fireman.enemy_name = "火人";
	Fireman.map_enemy.LoadBitmapByString({ "resources/ui_map/map_enemy_fireman1.bmp" }, RGB(76, 105, 113));

	Fireman.enemy_equipment[0].LoadBitmapByString({ "resources/equipment/fireball.bmp" }, RGB(76, 105, 113));
	Fireman.enemy_equipment[0].SetTopLeft(760, 235);
	Fireman.positions[0] = { 760, 235 };
	Fireman.enemy_equipment[1].LoadBitmapByString({ "resources/equipment/fireball.bmp" }, RGB(76, 105, 113));
	Fireman.enemy_equipment[1].SetTopLeft(760, 235 + 305);
	Fireman.positions[1] = { 760, 235 + 305 };

	Fireman.importWorkFunction([this]() { this->FiremanWork(); });
	//

	//雪人
	Snowman.enemy.LoadBitmapByString({ "resources/enemy/snowman.bmp" }, RGB(76, 105, 113));
	Snowman.enemy.SetTopLeft(1320, -40);
	Snowman.floor_enemy_id = 1;
	Snowman.enemy_equipment_number = 4;
	Snowman.enemy_dice_amount = 4;
	Snowman.enemy_level = 4;
	Snowman.enemy_max_health = 44;
	Snowman.enemy_current_health = Snowman.enemy_max_health;
	Snowman.enemy_name = "雪人";
	Snowman.map_enemy.LoadBitmapByString({ "resources/ui_map/map_enemy_snowman1.bmp" }, RGB(76, 105, 113));

	Snowman.enemy_equipment[0].LoadBitmapByString({ "resources/equipment/snowball.bmp" }, RGB(76, 105, 113));
	Snowman.enemy_equipment[0].SetTopLeft(520, 230);
	Snowman.positions[0] = { 520, 230 };
	Snowman.enemy_equipment[1].LoadBitmapByString({ "resources/equipment/snowball.bmp" }, RGB(76, 105, 113));
	Snowman.enemy_equipment[1].SetTopLeft(520 + 480, 230);
	Snowman.positions[1] = { 520 + 480, 230 };
	Snowman.enemy_equipment[2].LoadBitmapByString({ "resources/equipment/snowball.bmp" }, RGB(76, 105, 113));
	Snowman.enemy_equipment[2].SetTopLeft(520, 230 + 305);
	Snowman.positions[2] = { 520, 230 + 305 };
	Snowman.enemy_equipment[3].LoadBitmapByString({ "resources/equipment/snowball.bmp" }, RGB(76, 105, 113));
	Snowman.enemy_equipment[3].SetTopLeft(520 + 480, 230 + 305);
	Snowman.positions[3] = { 520 + 480, 230 + 305};

	Snowman.importWorkFunction([this]() { this->SnowmanWork(); });
	//

	//小山爺爺
	WickerMan.enemy.LoadBitmapByString({ "resources/enemy/wickerman.bmp" }, RGB(76, 105, 113));
	WickerMan.enemy.SetTopLeft(1320, -40);
	WickerMan.floor_enemy_id = 2;
	WickerMan.enemy_equipment_number = 2;
	WickerMan.enemy_dice_amount = 3;
	WickerMan.enemy_level = 4;
	WickerMan.enemy_max_health = 44;
	WickerMan.enemy_current_health = WickerMan.enemy_max_health;
	WickerMan.enemy_name = "小山爺爺";
	WickerMan.map_enemy.LoadBitmapByString({ "resources/ui_map/map_enemy_wickerman1.bmp" }, RGB(76, 105, 113));

	WickerMan.enemy_equipment[0].LoadBitmapByString({ "resources/equipment/wicker_staff.bmp" }, RGB(76, 105, 113));
	WickerMan.enemy_equipment[0].SetTopLeft(520, 320);
	WickerMan.positions[0] = { 520, 320 };
	
	WickerMan.enemy_equipment[1].LoadBitmapByString({ "resources/equipment/venus_fly_trap.bmp" }, RGB(76, 105, 113));
	WickerMan.enemy_equipment[1].SetTopLeft(520 + 470, 320);
	WickerMan.positions[1] = { 520 + 470, 320 };

	WickerMan.enemy_required[0] = 12;

	WickerMan.importWorkFunction([this]() { this->WickermanWork(); });
	//

	//甲蟲王者
	RhinoBeetle.enemy.LoadBitmapByString({ "resources/enemy/rhino_beetle.bmp" }, RGB(76, 105, 113));
	RhinoBeetle.enemy.SetTopLeft(1320, -40);
	RhinoBeetle.floor_enemy_id = 0;
	RhinoBeetle.enemy_equipment_number = 2;
	RhinoBeetle.enemy_dice_amount = 3;
	RhinoBeetle.enemy_level = 4;
	RhinoBeetle.enemy_max_health = 46;
	RhinoBeetle.enemy_current_health = RhinoBeetle.enemy_max_health;
	RhinoBeetle.enemy_name = "甲蟲王者";
	RhinoBeetle.map_enemy.LoadBitmapByString({ "resources/ui_map/map_enemy_rhinobeetle1.bmp" }, RGB(76, 105, 113));

	RhinoBeetle.enemy_equipment[0].LoadBitmapByString({ "resources/equipment/battleaxe.bmp" }, RGB(76, 105, 113));
	RhinoBeetle.enemy_equipment[0].SetTopLeft(520, 320);
	RhinoBeetle.positions[0] = { 520, 320 };
	RhinoBeetle.enemy_equipment[1].LoadBitmapByString({ "resources/equipment/beetle_headbutt.bmp" }, RGB(76, 105, 113));
	RhinoBeetle.enemy_equipment[1].SetTopLeft(520 + 470, 320);
	RhinoBeetle.positions[1] = { 520 + 470, 320 };

	RhinoBeetle.enemy_required[1] = 12;

	RhinoBeetle.importWorkFunction([this]() { this->RhinoBeetleWork(); });
	//

	//烏賊克拉肯
	Kraken.enemy.LoadBitmapByString({ "resources/enemy/kraken.bmp" }, RGB(76, 105, 113));
	Kraken.enemy.SetTopLeft(1320, -40);
	Kraken.floor_enemy_id = 1;
	Kraken.enemy_equipment_number = 3;
	Kraken.enemy_dice_amount = 5;
	Kraken.enemy_level = 4;
	Kraken.enemy_max_health = 44;
	Kraken.enemy_current_health = Kraken.enemy_max_health;
	Kraken.enemy_name = "烏賊克拉肯";
	Kraken.map_enemy.LoadBitmapByString({ "resources/ui_map/map_enemy_kraken1.bmp" }, RGB(76, 105, 113));

	Kraken.enemy_equipment[0].LoadBitmapByString({ "resources/equipment/camouflage.bmp" }, RGB(76, 105, 113));
	Kraken.enemy_equipment[0].SetTopLeft(270, 320);
	Kraken.positions[0] = { 270, 320 };
	Kraken.enemy_equipment[1].LoadBitmapByString({ "resources/equipment/deep_sea.bmp" }, RGB(76, 105, 113));
	Kraken.enemy_equipment[1].SetTopLeft(270 + 470, 320);
	Kraken.positions[1] = { 270 + 470, 320 };
	Kraken.enemy_equipment[2].LoadBitmapByString({ "resources/equipment/overwhelm.bmp" }, RGB(76, 105, 113));
	Kraken.enemy_equipment[2].SetTopLeft(270 + 470 * 2, 320);
	Kraken.positions[2] = { 270 + 470 * 2, 320 };
	hitmore = 0;

	Kraken.enemy_required[0] = 5;

	Kraken.importWorkFunction([this]() { this->KrakenWork(); });
	//

	//Cornelius
	Cornelius.enemy.LoadBitmapByString({ "resources/enemy/cornelius.bmp" }, RGB(76, 105, 113));
	Cornelius.enemy.SetTopLeft(1320, -40);
	Cornelius.floor_enemy_id = 2;
	Cornelius.enemy_equipment_number = 1;
	Cornelius.enemy_dice_amount = 6;
	Cornelius.enemy_level = 5;
	Cornelius.enemy_max_health = 100;
	Cornelius.enemy_current_health = Cornelius.enemy_max_health;
	Cornelius.enemy_name = "Cornelius";
	Cornelius.map_enemy.LoadBitmapByString({ "resources/ui_map/map_enemy_cornelius1.bmp" }, RGB(76, 105, 113));

	Cornelius.enemy_equipment[0].LoadBitmapByString({ "resources/equipment/nightmare.bmp" }, RGB(76, 105, 113));
	Cornelius.enemy_equipment[0].SetTopLeft(760, 320);
	Cornelius.positions[0] = { 760, 320 };

	Cornelius.enemy_required[0] = 99;

	Cornelius.importWorkFunction([this]() { this->CorneliusWork(); });
	//

	//鼠中之王
	RatKing.enemy.LoadBitmapByString({ "resources/enemy/rat_king.bmp" }, RGB(76, 105, 113));
	RatKing.enemy.SetTopLeft(1320, -40);
	RatKing.floor_enemy_id = 3;
	RatKing.enemy_equipment_number = 6;
	RatKing.enemy_dice_amount = 3;
	RatKing.enemy_level = 5;
	RatKing.enemy_max_health = 42;
	RatKing.enemy_current_health = RatKing.enemy_max_health;
	RatKing.enemy_name = "鼠中之王";
	RatKing.map_enemy.LoadBitmapByString({ "resources/ui_map/map_enemy_ratking1.bmp" }, RGB(76, 105, 113));

	RatKing.enemy_equipment[0].LoadBitmapByString({ "resources/equipment/rat.bmp" }, RGB(76, 105, 113));
	RatKing.enemy_equipment[0].SetTopLeft(270, 230);
	RatKing.positions[0] = { 270, 230 };
	RatKing.enemy_equipment[1].LoadBitmapByString({ "resources/equipment/rat.bmp" }, RGB(76, 105, 113));
	RatKing.enemy_equipment[1].SetTopLeft(270 + 470, 230);
	RatKing.positions[1] = { 270 + 470, 230 };
	RatKing.enemy_equipment[2].LoadBitmapByString({ "resources/equipment/rat.bmp" }, RGB(76, 105, 113));
	RatKing.enemy_equipment[2].SetTopLeft(270 + 470 * 2, 230);
	RatKing.positions[2] = { 270 + 470 * 2, 230 };
	RatKing.enemy_equipment[3].LoadBitmapByString({ "resources/equipment/rat.bmp" }, RGB(76, 105, 113));
	RatKing.enemy_equipment[3].SetTopLeft(270, 230 + 305);
	RatKing.positions[3] = { 270, 230 + 305 };
	RatKing.enemy_equipment[4].LoadBitmapByString({ "resources/equipment/rat.bmp" }, RGB(76, 105, 113));
	RatKing.enemy_equipment[4].SetTopLeft(270 + 470, 230 + 305);
	RatKing.positions[4] = { 270 + 470 , 230 + 305 };
	RatKing.enemy_equipment[5].LoadBitmapByString({ "resources/equipment/rat.bmp" }, RGB(76, 105, 113));
	RatKing.enemy_equipment[5].SetTopLeft(270 + 470 * 2, +305);
	RatKing.positions[5] = { 270 + 470 * 2, 230 + 305 };

	RatKing.enemy_required[0] = 5;
	RatKing.enemy_required[1] = 5;
	RatKing.enemy_required[2] = 5;
	RatKing.enemy_required[3] = 5;
	RatKing.enemy_required[4] = 5;
	RatKing.enemy_required[5] = 5;

	RatKing.importWorkFunction([this]() { this->RatKingWork(); });
	//

	//Buster
	Buster.enemy.LoadBitmapByString({ "resources/enemy/buster.bmp" }, RGB(76, 105, 113));
	Buster.enemy.SetTopLeft(1320, -40);
	Buster.floor_enemy_id = 0;
	Buster.enemy_equipment_number = 4;
	Buster.enemy_dice_amount = 4;
	Buster.enemy_level = 6;
	Buster.enemy_max_health = 68;
	Buster.enemy_current_health = Buster.enemy_max_health;
	Buster.enemy_name = "火龍";
	Buster.map_enemy.LoadBitmapByString({ "resources/ui_map/map_enemy_buster1.bmp" }, RGB(76, 105, 113));

	Buster.enemy_equipment[0].LoadBitmapByString({ "resources/equipment/fire_breath.bmp" }, RGB(76, 105, 113));
	Buster.enemy_equipment[0].SetTopLeft(40 , 300);
	Buster.positions[0] = { 40, 300 };
	Buster.enemy_equipment[1].LoadBitmapByString({ "resources/equipment/fire_breath.bmp" }, RGB(76, 105, 113));
	Buster.enemy_equipment[1].SetTopLeft(40 + 470, 300);
	Buster.positions[1] = { 40 + 470, 300 };
	Buster.enemy_equipment[2].LoadBitmapByString({ "resources/equipment/fire_breath.bmp" }, RGB(76, 105, 113));
	Buster.enemy_equipment[2].SetTopLeft(40 + 470 * 2, 300);
	Buster.positions[2] = { 40 + 470 * 2, 300 };
	Buster.enemy_equipment[3].LoadBitmapByString({ "resources/equipment/fire_breath.bmp" }, RGB(76, 105, 113));
	Buster.enemy_equipment[3].SetTopLeft(440 + 470 * 3, 300);
	Buster.positions[3] = { 40 + 470 * 3, 300 };

	Buster.importWorkFunction([this]() { this->BusterWork(); });
	//
}

void CGameStateRun::SpaceMarineWork() {
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> uni(1, 6);
	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++)
	{
		int random_number = uni(rng);
		enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
		CurrentEnemy->enemy_required[0] -= (enemy_dice[i].GetFrameIndexOfBitmap() + 1);
		enemy_dice_use[i] = 0;
		if (CurrentEnemy->enemy_required[0] <= 0) {
			Warrior.current_health -= 10;
			enemy_equipment_use[0] = 0;
			CurrentEnemy->enemy_required[0] = 20;
			break;
		}
	}
}

void CGameStateRun::GardenerWork() {
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> uni(1, 6);
	int maxnumber = 0;
	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
		int random_number = uni(rng);
		enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
		maxnumber = max(maxnumber, random_number);
		enemy_dice_use[i] = 0;

	}
	if (maxnumber == 6)
	{
		Warrior.weaken += 1;
	}
	Warrior.current_health -= maxnumber;
	enemy_equipment_use[0] = 0;
}

void CGameStateRun::SneezeyWork() {
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> uni(1, 6);
	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++)
	{
		int random_number = uni(rng);
		enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
	}

	bool hasPair = false;
	int pairnumber = 0;
	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
		for (int j = i + 1; j < CurrentEnemy->enemy_dice_amount; j++) {
			if (enemy_dice[i].GetFrameIndexOfBitmap() + 1 == enemy_dice[j].GetFrameIndexOfBitmap() + 1) 
			{
				hasPair = true;
				pairnumber = enemy_dice[i].GetFrameIndexOfBitmap() + 1;
				enemy_dice_use[i] = 0; 
				enemy_dice_use[j] = 0;
				break;
			}
		}
	}
	if (hasPair) 
	{
		for (int i = 1; i < 5; i++) 
		{
			CurrentEnemy->enemy_required[i] -= pairnumber;
		}
	}
	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {

		if (enemy_dice_use[i] == 1) 
		{
			for (int j = 1; j < 5; j++)
			{
				if (CurrentEnemy->enemy_required[j] > 0)
				{
					CurrentEnemy->enemy_required[j] -= (enemy_dice[i].GetFrameIndexOfBitmap() + 1);
					enemy_dice_use[i] = 0;
				}
				break;
			}
		}
	}
	for (int i = 1; i < 5; i++)
	{	
		if (CurrentEnemy->enemy_required[i] <= 0)
		{
			Warrior.current_health -= 3;
			enemy_equipment_use[i] = 0;
			CurrentEnemy->enemy_required[i] = 6;
		}
	}
}

void CGameStateRun::MarshmallowWork() {
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> uni(1, 6);
	int maxOdd = -1;
	int maxEven = -1;
	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
		int random_number = uni(rng);
		enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
		if (random_number % 2 == 0 && random_number > maxEven) 
		{
			maxEven = random_number;
		}
		else if (random_number % 2 == 1 && random_number > maxOdd)
		{
			maxOdd = random_number;
		}
	}

	if (maxOdd != -1) 
	{
		Warrior.current_health -= maxOdd;
		Warrior.freezed += 1;
	}
	if (maxEven != -1)
	{
		Warrior.current_health -= maxEven;
		Warrior.fired += 1;
	}
}

void CGameStateRun::StereoheadWork() {
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> uni(1, 6);
	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
		int random_number = uni(rng);
		enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
		if (random_number <= 4)
		{
			Warrior.current_health -= random_number;
			Warrior.weaken += 1;
			enemy_dice_use[i] = 0;
		}
	}
}

void CGameStateRun::BabySquidWork() {
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> uni(1, 6);
	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
		int random_number = uni(rng);
		enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
		if (random_number % 2 == 1 && enemy_equipment_use[0] == 1)
		{
			Warrior.blind += 1;
			enemy_equipment_use[0] = 0;
		}
		else if (random_number % 2 == 0)
		{
			Warrior.current_health -= random_number;
		}
	}
}

void CGameStateRun::BullyWork() {
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> uni(1, 6);
	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
		int random_number = uni(rng);
		enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
		if (random_number > 3 && enemy_equipment_use[3] != -1)
		{
			for (int j = 0; j < 4; j++) 
			{
				if (enemy_equipment_use[j] == 1) 
				{
					Warrior.current_health -= random_number;
					enemy_equipment_use[j] = -1;
					break;
				}
			}
		}
		else
		{
			Warrior.current_health -= 3;
		}
	}
}

void CGameStateRun::VacuumWork() {
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> uni(1, 6);
	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
		int random_number = uni(rng);
		enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
		if (random_number == 6) 
		{
			Warrior.blind += 2;
			Warrior.current_health -= 6;
			enemy_dice_use[i] = 0;
			enemy_equipment_use[0] = 0;
		}
		else if (random_number == 4) 
		{
			Warrior.current_health -= 4;
			CurrentEnemy->enemy_current_health += 4;
			enemy_dice_use[i] = 0;
			enemy_equipment_use[1] = 0;
		}
	}

	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) 
	{
		int number = enemy_dice[i].GetFrameIndexOfBitmap() + 1;
		if (number >= 5 && enemy_equipment_use[0] == 1) 
		{
			Warrior.current_health -= number;
			enemy_equipment_use[0] = 0;
		}
		else if (enemy_equipment_use[1] == 1 && number < 4)
		{
			Warrior.current_health -= number;
			CurrentEnemy->enemy_current_health += number;
			enemy_dice_use[i] = 0;
			enemy_equipment_use[1] = 0;
		}
		else if (enemy_equipment_use[0] == 1) 
		{
			Warrior.current_health -= number;
			enemy_equipment_use[0] = 0;
		}
	}
}

void CGameStateRun::FiremanWork() {
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> uni(1, 6);

	std::vector<int> even_numbers;
	int even1 = 0;
	int even2 = 0;

	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
		int random_number = uni(rng);
		enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
		if (random_number % 2 == 0) {
			even_numbers.push_back(random_number);
		}
	}

	if (even_numbers.size() >= 2) {
		std::sort(even_numbers.begin(), even_numbers.end(), std::greater<int>());
		even1 = even_numbers[0];
		even2 = even_numbers[1];

	}
	else if (even_numbers.size() == 1) {
		even1 = even_numbers[0];
		even2 = 0;
	}
	else {
		even1 = 0;
		even2 = 0;
	}

	if (even1 != 0) 
	{
		Warrior.current_health -= even1;
		Warrior.fired += 1;
	}
	if (even2 != 0)
	{
		Warrior.current_health -= even2;
		Warrior.fired += 1;
	}
}

void CGameStateRun::SnowmanWork() {
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> uni(1, 6);
	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
		int random_number = uni(rng);
		enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
		if (random_number % 2 == 1) 
		{	
			Warrior.current_health -= random_number;
			Warrior.freezed += 1;
		}
	}
}

void CGameStateRun::WickermanWork() {
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> uni(1, 6);
	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
		int random_number = uni(rng);
		enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
		if (random_number == 6)
		{
			Warrior.current_health -= random_number;
			CurrentEnemy->enemy_current_health += 2;
			enemy_dice_use[i] = 0;
			enemy_equipment_use[0] = 0;
		}
		else if (CurrentEnemy->enemy_required[0] > 0)
		{
			CurrentEnemy->enemy_required[0] -= random_number;
			enemy_dice_use[i] = 0;
		}
	}

	if (CurrentEnemy->enemy_required[0] <= 0) 
	{
		Warrior.current_health -= 9;
		Warrior.fired += 2;
		CurrentEnemy->enemy_required[0] = 12;
	}

	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
		int number;
		number = enemy_dice[i].GetFrameIndexOfBitmap() + 1;
		if (enemy_dice_use[i] == 1 && enemy_equipment_use[0] == 1)
		{	
			Warrior.current_health -= number;
			break;
		}
	}
}

void CGameStateRun::RhinoBeetleWork() {
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> uni(1, 6);
	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
		int random_number = uni(rng);
		enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
		if (random_number > 4)
		{
			Warrior.current_health -= random_number;
			CurrentEnemy->enemy_required[1] -= random_number;
			enemy_dice_use[i] = 0;
		}
		else if (random_number == 4)
		{
			Warrior.current_health -= random_number * 2;
			enemy_dice_use[i] = 0;
		}
		else
		{
			Warrior.current_health -= random_number;
			enemy_dice_use[i] = 0;
		}
	}

	if (CurrentEnemy->enemy_required[1] <= 0)
	{
		Warrior.current_health -= 5;
		Warrior.locked += 1;
		CurrentEnemy->enemy_required[1] = 12;
	}
}

void CGameStateRun::KrakenWork() {
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> uni(1, 6);
	int use = 0;
	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
		int random_number = uni(rng);
		enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
		if (random_number == 4)
		{
			Warrior.cursed += 1;
			enemy_dice_use[i] = 0;
		}
		else if (random_number % 2 == 0 && use < 2) 
		{
			Warrior.current_health -= (1 + hitmore);
			hitmore += 1;
			use += 1;
			enemy_dice_use[i] = 0;
		}
		else
		{
			CurrentEnemy->enemy_required[0] -= random_number;
		}
	}

	if (CurrentEnemy->enemy_required[0] <= 0) 
	{
		Warrior.blind += 2;
		CurrentEnemy->enemy_required[0] = 5;
	}
}

void CGameStateRun::CorneliusWork() {
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> uni(1, 6);
	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
		int random_number = uni(rng);
		enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
		CurrentEnemy->enemy_required[0] -= random_number;
	}

	if (CurrentEnemy->enemy_required[0] <= 0)
	{
		Warrior.current_health -= 999;
		CurrentEnemy->enemy_required[0] = 99;
	}
}

void CGameStateRun::RatKingWork() {
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> uni(1, 6);
	int number = 0;
	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
		int random_number = uni(rng);
		enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
		number += random_number;
	}
	for (int i = 0; i < CurrentEnemy->enemy_equipment_number; i++) {
		if (number >= CurrentEnemy->enemy_required[i]) 
		{
			number -= CurrentEnemy->enemy_required[i];
			int random_number = uni(rng);
			number += random_number;
			Warrior.poison += 1;
			CurrentEnemy->enemy_required[i] = 5;
		}
		else
		{
			CurrentEnemy->enemy_required[i] -= number;
		}
	}
}

void CGameStateRun::BusterWork() {
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> uni(1, 6);
	for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
		int random_number = uni(rng);
		enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
		Warrior.current_health -= random_number;
		Warrior.fired += 1;
	}
}

void CGameStateRun::DefeatEnemy() {

	std::mt19937 rng;
	std::uniform_int_distribution<int> uni(1, 6);
	int random_number;

	if (CurrentEnemy->enemy_current_health <= 0)
	{
		state = 0;
		Warrior.exp += CurrentEnemy->enemy_level;
		Warrior.money += 1;
		enemy_living[floor - 1][CurrentEnemy->floor_enemy_id] = 0;
		Warrior.LevelUp();
		if (mod == 3) 
		{
			Warrior.max_health -= 6;
			Warrior.current_health = Warrior.max_health;
		}

		for (int i = 0; i < Warrior.chararter_dice_amount; i++)
		{
			random_number = uni(rng);
			Warrior.dice[i].SetFrameIndexOfBitmap(random_number - 1);
			Warrior.dice[i].SetTopLeft(800 + 150 * i, 900);
		}

		for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {

			random_number = uni(rng);
			enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
			enemy_dice[i].SetTopLeft(1000 - 150 * i, 80);
		}

		CurrentEnemy->SetEnemyEquipmentPositions(CurrentEnemy->enemy_equipment_number, 2500, 0, CurrentEnemy->positions);

		for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
			dice_use[i] = 1;
		}

		for (int i = 0; i < 6; i++) {
			equipment_use[i] = 1;
		}

		//equipment_reroll
		equipment_reroll.equipment.SetTopLeft(40 + 470 * 3, 300);
		equipment_reroll.diceslot.SetTopLeft(40 + 470 * 3 + 134, 465);
		equipment_reroll.diceslot.SetFrameIndexOfBitmap(6);

		//recovery
		for (int i = 0; i < 6; ++i) {
			if (Work[i] != nullptr) {
				Work[i]->RestructFunction(0);
			}
		}

		for (int i = 0; i < Warrior.chararter_dice_amount; i++)
		{
			isfire[i] = 0;
		}

		for (int i = 0; i < Warrior.chararter_dice_amount; i++)
		{
			isblind[i] = 0;
		}

		for (int i = 0; i < Warrior.chararter_dice_amount; i++)
		{
			islocked[i] = 0;
		}
		Warrior.fired = 0;
		Warrior.freezed = 0;
		Warrior.blind = 0;
		Warrior.locked = 0;
		Warrior.cursed = 0;
		Warrior.poison = 0;

		enemy_poison = 0;

		CurrentEnemy->SetEnemyEquipmentPositions(CurrentEnemy->enemy_equipment_number, 0, 0, CurrentEnemy->positions);

		for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
			enemy_dice_use[i] = 1;
		}
		for (int i = 0; i < CurrentEnemy->enemy_equipment_number; i++) {
			enemy_equipment_use[i] = 1;
		}

		Warrior.reroll = 3;

		if (floor == 6) 
		{	
			state = -1;
			/*
			mod = 0;
			CGameStateRun::OnInit();
			*/
		}
	}
}

void rerollDice(Character& warrior, EquipmentClass& equipment_reroll) {
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> uni(1, 6);
	for (int i = 0; i < warrior.chararter_dice_amount; i++) {
		if (CMovingBitmap::IsOverlap(equipment_reroll.equipment, warrior.dice[i]) && warrior.reroll > 0) {
			int random_number = uni(rng);
			warrior.dice[i].SetFrameIndexOfBitmap(random_number - 1);
			warrior.dice[i].SetTopLeft(800 + 150 * i, 900);
			warrior.reroll -= 1;
			if (warrior.reroll == 0) {
				equipment_reroll.equipment.SetTopLeft(2500, 300);
				equipment_reroll.diceslot.SetTopLeft(2500, 465);
			}
			break;
		}
	}
}

void CGameStateRun::statusEffects() {
	if (Warrior.weaken > 0) {
		Warrior.current_health += 1;
		Warrior.weaken -= 1;
	}

	if (Warrior.poison > 0) {
		Warrior.current_health -= Warrior.poison;
		Warrior.poison -= 1;
	}
}

void CGameStateRun::useEquipmentSword(Character& Warrior, EquipmentClass& equipment_sword, std::function<void()> DefeatEnemy) {
	for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
		if (CMovingBitmap::IsOverlap(equipment_sword.equipment, Warrior.dice[i]) && dice_use[i] == 1) {
			CurrentEnemy->enemy_current_health -= (Warrior.dice[i].GetFrameIndexOfBitmap() + 1);

			dice_use[i] = 0;

			//判定贏
			DefeatEnemy();
			break;
		}
	}
}

void CGameStateRun::useEquipmentBattleAxe(Character& Warrior, EquipmentClass& equipment_battleaxe, std::function<void()> DefeatEnemy) {
	for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
		if (CMovingBitmap::IsOverlap(equipment_battleaxe.equipment, Warrior.dice[i]) && dice_use[i] == 1 && (Warrior.dice[i].GetFrameIndexOfBitmap() + 1) <= 4 ) {
			CurrentEnemy->enemy_current_health -= (Warrior.dice[i].GetFrameIndexOfBitmap() + 1) * 2;

			dice_use[i] = 0;

			//判定贏
			DefeatEnemy();
			break;
		}
	}
}

void CGameStateRun::useEquipmentToxicOoze(Character& Warrior, EquipmentClass& equipment, std::function<void()> DefeatEnemy) {
	for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
		if (CMovingBitmap::IsOverlap(equipment.equipment, Warrior.dice[i]) && dice_use[i] == 1) {
			CurrentEnemy->enemy_current_health -= (Warrior.dice[i].GetFrameIndexOfBitmap() + 1);

			if (Warrior.dice[i].GetFrameIndexOfBitmap() + 1 == 6)
			{
				enemy_poison += 2;
				dice_use[i] = 0;
			}

			//判定贏
			DefeatEnemy();
			break;
		}
	}
}

void CGameStateRun::useEquipmentBloodStuck(Character& Warrior, EquipmentClass& equipment, std::function<void()> DefeatEnemy) {
	for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
		if (CMovingBitmap::IsOverlap(equipment.equipment, Warrior.dice[i]) && dice_use[i] == 1 && (Warrior.dice[i].GetFrameIndexOfBitmap() + 1) <= 4) {
			CurrentEnemy->enemy_current_health -= (Warrior.dice[i].GetFrameIndexOfBitmap() + 1);

			Warrior.current_health += (Warrior.dice[i].GetFrameIndexOfBitmap() + 1);
			dice_use[i] = 0;

			//判定贏
			DefeatEnemy();
			break;
		}
	}
}

void CGameStateRun::useEquipmentShovel(Character& Warrior, EquipmentClass& equipment, std::function<void()> DefeatEnemy) {
	for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
		if (CMovingBitmap::IsOverlap(equipment.equipment, Warrior.dice[i]) && dice_use[i] == 1) {
			CurrentEnemy->enemy_current_health -= (Warrior.dice[i].GetFrameIndexOfBitmap() + 1);

			if (Warrior.dice[i].GetFrameIndexOfBitmap() + 1 == 6)
			{
				Warrior.current_health += 1;
			}
			dice_use[i] = 0;
			//判定贏
			DefeatEnemy();
			break;
		}
	}
}


void CGameStateRun::useEquipmentDebugSword(Character& Warrior, EquipmentClass& equipment_debug_sword, std::function<void()> DefeatEnemy) {
	for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
		if (CMovingBitmap::IsOverlap(equipment_debug_sword.equipment, Warrior.dice[i]) && dice_use[i] == 1) {
			CurrentEnemy->enemy_current_health -= CurrentEnemy->enemy_current_health;
			Warrior.money = 99;
			Warrior.max_health = 999;
			Warrior.current_health = Warrior.max_health;
			dice_use[i] = 0;

			//判定贏
			DefeatEnemy();
			break;
		}
	}
}




void defineMoveFunction(EquipmentClass& equipment, Character& warrior) {
	equipment.importMoveFunction([&]() {
		for (int i = 0; i < warrior.chararter_dice_amount; i++) {
			if (!CMovingBitmap::IsOverlap(equipment.equipment, warrior.dice[i])) {
				if (equipment.diceslot_exist != 0) 
				{
					equipment.diceslot.SetFrameIndexOfBitmap(6);
				}
				
			}
		}
		for (int i = 0; i < warrior.chararter_dice_amount; i++) {
			if (CMovingBitmap::IsOverlap(equipment.equipment, warrior.dice[i])) {
				int number = warrior.dice[i].GetFrameIndexOfBitmap();
				if (equipment.diceslot_exist != 0) 
				{
					equipment.diceslot.SetFrameIndexOfBitmap(number);
				}
				break;
			}
		}
		});
}

void CGameStateRun::InitializeEquipments() {
	//reroll
	equipment_reroll.importWorkFunction([&]() {
		rerollDice(Warrior, equipment_reroll);
	}); 

	equipment_reroll.importShowFunction([this]() {
		equipment_reroll.equipment.ShowBitmap();
		equipment_reroll.diceslot.ShowBitmap();
		});

	//sword
	Work[0] = &equipment_sword;
	equipment_sword.backpack_column = 0;
	equipment_sword.backpack_row = 0;

	equipment_sword.size = 1;
	equipment_sword.backpack_square.LoadBitmapByString({ "resources/equipment/backpack/sword.bmp" }, RGB(76, 105, 113));
	equipment_sword.backpack_square.SetTopLeft(1165, 610);
	equipment_sword.diceslot_exist = true;

	defineMoveFunction(equipment_sword, Warrior);

	equipment_sword.importWorkFunction([this]() {
		useEquipmentSword(Warrior, equipment_sword, [this]() { DefeatEnemy(); });
		});

	equipment_sword.importShowFunction([this]() {
		equipment_sword.equipment.ShowBitmap();
		equipment_sword.diceslot.ShowBitmap();
		});

	//debug_sword
	Backpack[19] = &equipment_debug_sword;
	equipment_debug_sword.equipment.LoadBitmapByString({ "resources/equipment/debug_sword.bmp" }, RGB(76, 105, 113));
	equipment_debug_sword.backpack_column = 3;
	equipment_debug_sword.backpack_row = 4;
	equipment_debug_sword.size = 1;
	equipment_debug_sword.backpack_square.LoadBitmapByString({ "resources/equipment/backpack/debug_sword.bmp" }, RGB(76, 105, 113));
	equipment_debug_sword.backpack_square.SetTopLeft(155 + 200 * 3, 170 + 145 * 3);
	equipment_debug_sword.diceslot_exist = false;

	defineMoveFunction(equipment_debug_sword, Warrior);

	equipment_debug_sword.importWorkFunction([this]() {
		useEquipmentDebugSword(Warrior, equipment_debug_sword, [this]() { DefeatEnemy(); });
		});

	equipment_debug_sword.importShowFunction([this]() {
		equipment_debug_sword.equipment.ShowBitmap();
		});

	//battle_axe
	equipment_battleaxe.equipment.LoadBitmapByString({ "resources/equipment/battleaxe.bmp" }, RGB(76, 105, 113)); 
	equipment_battleaxe.size = 1;
	equipment_battleaxe.backpack_square.LoadBitmapByString({ "resources/equipment/backpack/battleaxe.bmp" }, RGB(76, 105, 113));
	equipment_battleaxe.diceslot_exist = false;

	defineMoveFunction(equipment_battleaxe, Warrior);

	equipment_battleaxe.importWorkFunction([this]() {
		useEquipmentBattleAxe(Warrior, equipment_battleaxe, [this]() { DefeatEnemy(); });
		});

	equipment_battleaxe.importShowFunction([this]() {
		equipment_battleaxe.equipment.ShowBitmap();
		});

	//toxic_ooze
	equipment_toxic_ooze.equipment.LoadBitmapByString({ "resources/equipment/toxic_ooze.bmp" }, RGB(76, 105, 113));
	equipment_toxic_ooze.size = 1;
	equipment_toxic_ooze.backpack_square.LoadBitmapByString({ "resources/equipment/backpack/toxic_ooze.bmp" }, RGB(76, 105, 113));
	equipment_toxic_ooze.diceslot_exist = false;
	equipment_toxic_ooze.equipment.SetTopLeft(41, 248);

	equipment_toxic_ooze.importWorkFunction([this]() {
		useEquipmentToxicOoze(Warrior, equipment_toxic_ooze, [this]() { DefeatEnemy(); });
		});

	equipment_toxic_ooze.importShowFunction([this]() {
		equipment_toxic_ooze.equipment.ShowBitmap();
		});

	//blood_stuck
	equipment_blood_stuck.equipment.LoadBitmapByString({ "resources/equipment/blood_stuck.bmp" }, RGB(76, 105, 113));
	equipment_blood_stuck.size = 1;
	equipment_blood_stuck.backpack_square.LoadBitmapByString({ "resources/equipment/backpack/blood_stuck.bmp" }, RGB(76, 105, 113));
	equipment_blood_stuck.diceslot_exist = false;
	equipment_blood_stuck.equipment.SetTopLeft(41 + 490, 248);

	equipment_blood_stuck.importWorkFunction([this]() {
		useEquipmentBloodStuck(Warrior, equipment_blood_stuck, [this]() { DefeatEnemy(); });
		});

	equipment_blood_stuck.importShowFunction([this]() {
		equipment_blood_stuck.equipment.ShowBitmap();
		});

	//shovel
	equipment_shovel.equipment.LoadBitmapByString({ "resources/equipment/shovel.bmp" }, RGB(76, 105, 113));
	equipment_shovel.size = 1;
	equipment_shovel.backpack_square.LoadBitmapByString({ "resources/equipment/backpack/shovel.bmp" }, RGB(76, 105, 113));
	equipment_shovel.diceslot_exist = false;
	equipment_shovel.equipment.SetTopLeft(41 + 490 * 2, 248);

	equipment_shovel.importWorkFunction([this]() {
		useEquipmentShovel(Warrior, equipment_shovel, [this]() { DefeatEnemy(); });
		});

	equipment_shovel.importShowFunction([this]() {
		equipment_shovel.equipment.ShowBitmap();
		});
}

void CGameStateRun::ChangeEquipments() {

}

void CGameStateRun::OnInit() 								// 遊戲的初值及圖形設定
{	
	for (int i = 0; i < 20; ++i) {
		Backpack[i] = nullptr;
	}

	for (int i = 0; i < 6; ++i) {
		Work[i] = nullptr;
	}

	menu.LoadBitmapByString({ "resources/backgrounds/menu.bmp" });

	for (int i = 0; i < 3; i++) {
		door[i].LoadBitmapByString({ "resources/backgrounds/door.bmp" });
		door[i].SetTopLeft(122 + 285 * i, 476);
	}

	CGameStateRun::InitializeEnemies();
	CGameStateRun::InitializeEquipments();
	
	if (mod == 0) 
	{
		state = 10;
	}

	//backpack_ui
	backpack_background.LoadBitmapByString({ "resources/backgrounds/backpack_background.bmp" });
	backpack_background.SetTopLeft(0, 0);

	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 5; j++) 
		{
			backpack_in_test_square[i][j].LoadBitmapByString({ "resources/equipment/backpack/test_square.bmp" });
			backpack_in_test_square[i][j].SetTopLeft(155 + 200 * i, 170 + 145 * j);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			backpack_out_test_square[i][j].LoadBitmapByString({ "resources/equipment/backpack/test_square.bmp" });
			backpack_out_test_square[i][j].SetTopLeft(1165 + 200 * i, 610 + 145 * j);
		}
	}

	//shops_ui
	shops.LoadBitmapByString({ "resources/backgrounds/shops.bmp" });
	shops.SetTopLeft(0, 0);

	for (int i = 0; i < 3; i++) 
	{
		buy_button[i].LoadBitmapByString({ "resources/buy_button.bmp" });
		buy_button[i].SetTopLeft(95 + 450 * i, 765);
	}

	end_shops_button.LoadBitmapByString({ "resources/end_shops_button.bmp" });
	end_shops_button.SetTopLeft(1180, 980);

	//map_ui
	map_character.LoadBitmapByString({ "resources/characters/characters_warrior_overworld_warrior1.bmp", "resources/characters/characters_warrior_overworld_warrior2.bmp", "resources/characters/characters_warrior_overworld_warrior3.bmp", "resources/characters/characters_warrior_overworld_warrior4.bmp" }, RGB(76, 105, 113));
	map_character.SetFrameIndexOfBitmap(2);

	background.LoadBitmapByString({ "resources/backgrounds/ice.bmp" });
	background.SetTopLeft(0, 0);
	map.LoadBitmapByString({ "resources/backgrounds/ice_floor1_map1.bmp", "resources/backgrounds/ice_floor2_map1.bmp", "resources/backgrounds/ice_floor3_map1.bmp", "resources/backgrounds/ice_floor4_map1.bmp", "resources/backgrounds/ice_floor5_map1.bmp","resources/backgrounds/lastfloor_map1.bmp"});
	map.SetFrameIndexOfBitmap(0);
	map.SetTopLeft(0, 0);
	ui_map_downbox.LoadBitmapByString({ "resources/backgrounds/ice_downbox.bmp" });
	ui_map_downbox.SetTopLeft(0, 962);

	head.LoadBitmapByString({ "resources/backgrounds/head_warrior.bmp" }, RGB(76, 105, 113));
	head.SetTopLeft(35, 990);

	star.LoadBitmapByString({ "resources/symbols/symbols_star.bmp" }, RGB(76, 105, 113));
	star.SetTopLeft(940, 1010);

	backpack_button.LoadBitmapByString({ "resources/ui_map/ui_map_backpack.bmp" }, RGB(76, 105, 113));
	backpack_button.SetTopLeft(1180, 980);

	for (int i = 0; i < 6; i++) {
		bone[i].LoadBitmapByString({ "resources/symbols/symbols_headbone_dark.bmp", "resources/symbols/symbols_headbone_light.bmp"}, RGB(76, 105, 113));
		bone[i].SetFrameIndexOfBitmap(0);
		bone[i].SetTopLeft(1565 + 54 * i, 980);
	}

	//地圖敵人顯示設定                   /////////////////////////////////////////////////////////
	map_enemy[0][0] = &SpaceMarine.map_enemy;
	map_enemy[0][0]->SetTopLeft(1010, 330);
	map_enemy[0][0]->SetAnimation(500, 0);

	map_enemy[0][1] = &Gardener.map_enemy;
	map_enemy[0][1]->SetTopLeft(985, 555);
	map_enemy[0][1]->SetAnimation(500, 0);

	map_enemy[1][0] = &Sneezey.map_enemy;
	map_enemy[1][0]->SetTopLeft(745 + 20, 245 - 20);
	map_enemy[1][0]->SetAnimation(500, 0);

	map_enemy[1][1] = &Marshmallow.map_enemy;
	map_enemy[1][1]->SetTopLeft(745 + 20, 485 - 20);
	map_enemy[1][1]->SetAnimation(500, 0);

	map_enemy[1][2] = &Stereohead.map_enemy;
	map_enemy[1][2]->SetTopLeft(1195 + 20, 485 - 20);
	map_enemy[1][2]->SetAnimation(500, 0);

	map_enemy[2][0] = &BabySquid.map_enemy;
	map_enemy[2][0]->SetTopLeft(520 + 20, 370 - 20);
	map_enemy[2][0]->SetAnimation(500, 0);

	map_enemy[2][1] = &Bully.map_enemy;
	map_enemy[2][1]->SetTopLeft(745 + 20, 245 - 20);

	map_enemy[2][2] = &Vacuum.map_enemy;
	map_enemy[2][2]->SetTopLeft(970 + 20, 370 - 20);

	map_enemy[3][0] = &Fireman.map_enemy;
	map_enemy[3][0]->SetTopLeft(520 + 20, 370 - 20);

	map_enemy[3][1] = &Snowman.map_enemy;
	map_enemy[3][1]->SetTopLeft(745 + 20, 245 - 20);

	map_enemy[3][2] = &WickerMan.map_enemy;
	map_enemy[3][2]->SetTopLeft(970 + 20, 370 - 20);

	map_enemy[4][0] = &RhinoBeetle.map_enemy;
	map_enemy[4][0]->SetTopLeft(295 + 20, 245 - 20);

	map_enemy[4][1] = &Kraken.map_enemy;
	map_enemy[4][1]->SetTopLeft(520 + 20, 370 - 20);

	map_enemy[4][2] = &Cornelius.map_enemy;
	map_enemy[4][2]->SetTopLeft(970 + 20, 370 - 20);

	map_enemy[4][3] = &RatKing.map_enemy;
	map_enemy[4][3]->SetTopLeft(1195 + 20, 485 - 20);

	map_enemy[5][0] = &Buster.map_enemy;
	map_enemy[5][0]->SetTopLeft(1580, 410);

	//商店
	map_shops.LoadBitmapByString({ "resources/ui_map/shop.bmp" }, RGB(76, 105, 113));
	map_shops.SetTopLeft(520, 600);

	//food
	food[0].LoadBitmapByString({ "resources/ui_map/food.bmp" }, RGB(76, 105, 113));
	food[0].SetTopLeft(295, 485);
	food[1].LoadBitmapByString({ "resources/ui_map/food.bmp" }, RGB(76, 105, 113));
	food[1].SetTopLeft(745, 715);
	//地圖地板
	
	exit.LoadBitmapByString({ "resources/ui_map/exit1.bmp", "resources/ui_map/exit2.bmp" }, RGB(76, 105, 113));
	exit.SetTopLeft(1195 + 30, 485 - 60);
	exit.SetAnimation(500, 0);

	treasure.LoadBitmapByString({ "resources/ui_map/treasure.bmp"}, RGB(76, 105, 113));
	treasure.SetTopLeft(745, 245);

	//floor
	//floor5
	floor_map[0][0].LoadBitmapByString({ "resources/backgrounds/ice_land_dark.bmp", "resources/backgrounds/ice_land_light.bmp" }, RGB(76, 105, 113));
	floor_map[0][0].SetTopLeft(295, 725);
	floor_map[0][0].SetFrameIndexOfBitmap(0);

	floor_map[0][1].LoadBitmapByString({ "resources/backgrounds/ice_land_dark.bmp", "resources/backgrounds/ice_land_light.bmp" }, RGB(76, 105, 113));
	floor_map[0][1].SetTopLeft(295, 245);
	floor_map[0][1].SetFrameIndexOfBitmap(0);

	floor_map[0][2].LoadBitmapByString({ "resources/backgrounds/ice_land_dark.bmp", "resources/backgrounds/ice_land_light.bmp" }, RGB(76, 105, 113));
	floor_map[0][2].SetTopLeft(520, 130);
	floor_map[0][2].SetFrameIndexOfBitmap(0);

	floor_map[0][3].LoadBitmapByString({ "resources/backgrounds/ice_land_dark.bmp", "resources/backgrounds/ice_land_light.bmp" }, RGB(76, 105, 113));
	floor_map[0][3].SetTopLeft(745, 15);
	floor_map[0][3].SetFrameIndexOfBitmap(0);

	floor_map[1][0].LoadBitmapByString({ "resources/backgrounds/ice_land_dark.bmp", "resources/backgrounds/ice_land_light.bmp" }, RGB(76, 105, 113));
	floor_map[1][0].SetTopLeft(295, 485);
	floor_map[1][0].SetFrameIndexOfBitmap(0);

	floor_map[1][1].LoadBitmapByString({ "resources/backgrounds/ice_land_dark.bmp", "resources/backgrounds/ice_land_light.bmp" }, RGB(76, 105, 113));
	floor_map[1][1].SetTopLeft(520, 370);
	floor_map[1][1].SetFrameIndexOfBitmap(0);

	floor_map[1][2].LoadBitmapByString({ "resources/backgrounds/ice_land_dark.bmp", "resources/backgrounds/ice_land_light.bmp" }, RGB(76, 105, 113));
	floor_map[1][2].SetTopLeft(745, 245);
	floor_map[1][2].SetFrameIndexOfBitmap(0);

	floor_map[1][3].LoadBitmapByString({ "resources/backgrounds/ice_land_dark.bmp", "resources/backgrounds/ice_land_light.bmp" }, RGB(76, 105, 113));
	floor_map[1][3].SetTopLeft(970, 130);
	floor_map[1][3].SetFrameIndexOfBitmap(0);

	floor_map[2][0].LoadBitmapByString({ "resources/backgrounds/ice_land_dark.bmp", "resources/backgrounds/ice_land_light.bmp" }, RGB(76, 105, 113));
	floor_map[2][0].SetTopLeft(520, 600);
	floor_map[2][0].SetFrameIndexOfBitmap(0);

	floor_map[2][1].LoadBitmapByString({ "resources/backgrounds/ice_land_dark.bmp", "resources/backgrounds/ice_land_light.bmp" }, RGB(76, 105, 113));
	floor_map[2][1].SetTopLeft(745, 485);
	floor_map[2][1].SetFrameIndexOfBitmap(0);

	floor_map[2][2].LoadBitmapByString({ "resources/backgrounds/ice_land_dark.bmp", "resources/backgrounds/ice_land_light.bmp" }, RGB(76, 105, 113));
	floor_map[2][2].SetTopLeft(970, 370);
	floor_map[2][2].SetFrameIndexOfBitmap(0);

	floor_map[2][3].LoadBitmapByString({ "resources/backgrounds/ice_land_dark.bmp", "resources/backgrounds/ice_land_light.bmp" }, RGB(76, 105, 113));
	floor_map[2][3].SetTopLeft(1195, 245);
	floor_map[2][3].SetFrameIndexOfBitmap(0);

	floor_map[3][0].LoadBitmapByString({ "resources/backgrounds/ice_land_dark.bmp", "resources/backgrounds/ice_land_light.bmp" }, RGB(76, 105, 113));
	floor_map[3][0].SetTopLeft(745, 715);
	floor_map[3][0].SetFrameIndexOfBitmap(0);

	floor_map[3][1].LoadBitmapByString({ "resources/backgrounds/ice_land_dark.bmp", "resources/backgrounds/ice_land_light.bmp" }, RGB(76, 105, 113));
	floor_map[3][1].SetTopLeft(970, 600);
	floor_map[3][1].SetFrameIndexOfBitmap(0);

	floor_map[3][2].LoadBitmapByString({ "resources/backgrounds/ice_land_dark.bmp", "resources/backgrounds/ice_land_light.bmp" }, RGB(76, 105, 113));
	floor_map[3][2].SetTopLeft(1195, 485);
	floor_map[3][2].SetFrameIndexOfBitmap(0);
	//floor5
	floor_map[3][3].LoadBitmapByString({ "resources/backgrounds/ice_land_dark.bmp", "resources/backgrounds/ice_land_light.bmp" }, RGB(76, 105, 113));
	floor_map[3][3].SetTopLeft(1195, 725);
	floor_map[3][3].SetFrameIndexOfBitmap(0);

	//map_ui_end

	//combat_ui
	ui_combat_background.LoadBitmapByString({ "resources/backgrounds/combat/ice.bmp" });
	ui_combat_background.SetTopLeft(0, 0);

	Warrior.character.LoadBitmapByString({ "resources/characters/warrior_fighting.bmp" }, RGB(255, 255, 255));
	Warrior.character.SetTopLeft(-50, 700);

	Warrior.healthbar_back.LoadBitmapByString({ "resources/ui_combat/ui_combat_healthbar_back.bmp" }, RGB(76, 105, 113));
	Warrior.healthbar_back.SetTopLeft(350, 900);
	Warrior.healthbar_front.LoadBitmapByString({ "resources/ui_combat/ui_combat_healthbar_front.bmp" }, RGB(76, 105, 113));
	Warrior.healthbar_front.SetTopLeft(353, 904);

	Warrior.limitbar_back.LoadBitmapByString({ "resources/ui_combat/ui_combat_limitbar_back.bmp" }, RGB(76, 105, 113));
	Warrior.limitbar_back.SetTopLeft(351, 960);
	Warrior.limitbar_front.LoadBitmapByString({ "resources/ui_combat/ui_combat_limitbar_front.bmp" }, RGB(76, 105, 113));
	Warrior.limitbar_front.SetTopLeft(354, 962);

	symbols_dice.LoadBitmapByString({ "resources/symbols/symbols_dice.bmp" }, RGB(76, 105, 113));
	symbols_dice.SetTopLeft(575, 850);

	enemy_healthbar_back.LoadBitmapByString({ "resources/ui_combat/ui_combat_healthbar_back.bmp" }, RGB(76, 105, 113));
	enemy_healthbar_back.SetTopLeft(1150, 100);
	enemy_healthbar_front.LoadBitmapByString({ "resources/ui_combat/ui_combat_healthbar_front.bmp" }, RGB(76, 105, 113));
	enemy_healthbar_front.SetTopLeft(1153, 104);

	// endturn arrow
	end_turn_arrow.LoadBitmapByString({ "resources/symbols/combat_endturnarrow.bmp" }, RGB(76, 105, 113));
	end_turn_arrow.SetTopLeft(1750, 900);

	// uparrow
	uparrow_arrow.LoadBitmapByString({ "resources/symbols/combat_uparrow.bmp" }, RGB(76, 105, 113));
	uparrow_arrow.SetTopLeft(900, 100);

	//equipment 初設
	equipment_sword.equipment.LoadBitmapByString({ "resources/equipment/sword.bmp" }, RGB(76, 105, 113));
	equipment_sword.equipment.SetTopLeft(40, 300);
	equipment_sword.diceslot.LoadBitmapByString({ "resources/dice/ui_dice_dice1.bmp", "resources/dice/ui_dice_dice2.bmp", "resources/dice/ui_dice_dice3.bmp", "resources/dice/ui_dice_dice4.bmp", "resources/dice/ui_dice_dice5.bmp", "resources/dice/ui_dice_dice6.bmp","resources/equipment/diceslot.bmp" }, RGB(76, 105, 113));
	equipment_sword.diceslot.SetTopLeft(40 + 134, 465);
	equipment_sword.diceslot.SetFrameIndexOfBitmap(6);

	//equipment 初設
	equipment_debug_sword.equipment.LoadBitmapByString({ "resources/equipment/debug_sword.bmp" }, RGB(76, 105, 113));
	equipment_debug_sword.equipment.SetTopLeft(40, 300);

	//equipment_reroll
	equipment_reroll.equipment.LoadBitmapByString({ "resources/equipment/combat_roll.bmp" }, RGB(76, 105, 113));
	equipment_reroll.equipment.SetTopLeft(40 + 470 * 3, 300);
	equipment_reroll.diceslot.LoadBitmapByString({ "resources/dice/ui_dice_dice1.bmp", "resources/dice/ui_dice_dice2.bmp", "resources/dice/ui_dice_dice3.bmp", "resources/dice/ui_dice_dice4.bmp", "resources/dice/ui_dice_dice5.bmp", "resources/dice/ui_dice_dice6.bmp","resources/equipment/diceslot.bmp" }, RGB(76, 105, 113));
	equipment_reroll.diceslot.SetTopLeft(40 + 470 * 3 + 134, 465);
	equipment_reroll.diceslot.SetFrameIndexOfBitmap(6);

	mouse_point.LoadBitmapByString({ "resources/mouse_point.bmp" }, RGB(76, 105, 113));

	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));

	std::uniform_int_distribution<int> uni(1, 6);

	for (int i = 0; i < 5; i++) {
		Warrior.dice[i].LoadBitmapByString({ "resources/dice/ui_dice_dice1.bmp", "resources/dice/ui_dice_dice2.bmp", "resources/dice/ui_dice_dice3.bmp", "resources/dice/ui_dice_dice4.bmp", "resources/dice/ui_dice_dice5.bmp", "resources/dice/ui_dice_dice6.bmp" }, RGB(76, 105, 113));
		int random_number = uni(rng);
		Warrior.dice[i].SetFrameIndexOfBitmap(random_number - 1);
		Warrior.dice[i].SetTopLeft(800 + 150 * i, 900);
	}

	for (int i = 0; i < 6; i++) {
		enemy_dice[i].LoadBitmapByString({ "resources/dice/ui_dice_dice1.bmp", "resources/dice/ui_dice_dice2.bmp", "resources/dice/ui_dice_dice3.bmp", "resources/dice/ui_dice_dice4.bmp", "resources/dice/ui_dice_dice5.bmp", "resources/dice/ui_dice_dice6.bmp" }, RGB(76, 105, 113));
		int random_number = uni(rng);
		enemy_dice[i].SetFrameIndexOfBitmap(random_number - 1);
		enemy_dice[i].SetTopLeft(1000 - 150 * i, 80);
	}

	for (int i = 0; i < 5; i++) {
		dice_fired[i].LoadBitmapByString({ "resources/dice/ui_dice_burn.bmp" }, RGB(76, 105, 113));
		dice_fired[i].SetTopLeft(800 + 150 * i - 30, 900 - 80);
	}

	for (int i = 0; i < 5; i++) {
		dice_blind[i].LoadBitmapByString({ "resources/dice/ui_dice_blind.bmp" }, RGB(76, 105, 113));
		dice_blind[i].SetTopLeft(800 + 150 * i , 900 );
	}

	for (int i = 0; i < 5; i++) {
		dice_locked[i].LoadBitmapByString({ "resources/dice/ui_dice_lock.bmp" }, RGB(76, 105, 113));
		dice_locked[i].SetTopLeft(800 + 150 * i, 900);
	}
	//combat_ui_end

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{	
	if (state == 1) 
	{
		CGameStateRun::ui_combat_OnLButtonDown(nFlags, point);
	}
	else if (state == 0)
	{
		CGameStateRun::ui_map_OnLButtonDown(nFlags, point);
	}
	else if (state == 2) 
	{
		CGameStateRun::ui_backpack_OnLButtonDown(nFlags, point);
	}
	else if (state == 3)
	{
		CGameStateRun::ui_shops_OnLButtonDown(nFlags, point);
	}
	else if (state == 10)
	{
		CGameStateRun::ui_menu_OnLButtonDown(nFlags, point);
	}
}

void CGameStateRun::ui_map_OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	int x = static_cast<int>(point.x);
	int y = static_cast<int>(point.y);
	mouse_point.SetTopLeft(x, y);

	for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
		dice_use[i] = 1;
	}

	for (int i = 0; i < 6; i++) {
		equipment_use[i] = 1;
	}

	//equipment_reroll
	equipment_reroll.equipment.SetTopLeft(40 + 470 * 3, 300);
	equipment_reroll.diceslot.SetTopLeft(40 + 470 * 3 + 134, 465);
	equipment_reroll.diceslot.SetFrameIndexOfBitmap(6);

	//recovery
	for (int i = 0; i < 6; ++i) {
		if (Work[i] != nullptr) {
			Work[i]->RestructFunction(0);
		}
	}

	Warrior.reroll = 3;
	
	if (floor == 1) 
	{
		if (CMovingBitmap::IsOverlap(mouse_point, floor_map[2][2]) && enemy_living[0][0] == 1) 
		{
			state = 1;
			CurrentEnemy = &SpaceMarine;

			Warrior.healthbar_back.SetTopLeft(350, 900);
			Warrior.healthbar_front.SetTopLeft(353, 904);

		}
		else if (CMovingBitmap::IsOverlap(mouse_point, floor_map[3][1]) && enemy_living[0][1] == 1) 
		{
			state = 1;
			CurrentEnemy = &Gardener;

			Warrior.healthbar_back.SetTopLeft(350, 900);
			Warrior.healthbar_front.SetTopLeft(353, 904);
		}
		else if (CMovingBitmap::IsOverlap(mouse_point, exit) == 1)
		{
			floor += 1;
			map.SetFrameIndexOfBitmap(floor - 1);
			exit.SetTopLeft(295 + 30, 245 - 60);
			treasure.SetTopLeft(970, 600);
		}
	}
	else if (floor == 2)
	{
		if (CMovingBitmap::IsOverlap(mouse_point, floor_map[1][2]) && enemy_living[1][0] == 1)
		{
			state = 1;
			CurrentEnemy = &Sneezey;

			Warrior.healthbar_back.SetTopLeft(350, 900);
			Warrior.healthbar_front.SetTopLeft(353, 904);
		}
		else if (CMovingBitmap::IsOverlap(mouse_point, floor_map[2][1]) && enemy_living[1][1] == 1)
		{
			state = 1;
			CurrentEnemy = &Marshmallow;

			Warrior.healthbar_back.SetTopLeft(350, 900);
			Warrior.healthbar_front.SetTopLeft(353, 904);
		}
		else if (CMovingBitmap::IsOverlap(mouse_point, floor_map[3][2]) && enemy_living[1][2] == 1)
		{
			state = 1;
			CurrentEnemy = &Stereohead;

			Warrior.healthbar_back.SetTopLeft(350, 900);
			Warrior.healthbar_front.SetTopLeft(353, 904);
		}
		else if (CMovingBitmap::IsOverlap(mouse_point, map_shops) == 1) 
		{
			state = 3;
		}
		else if (CMovingBitmap::IsOverlap(mouse_point, floor_map[1][0]) && floor2_map1_item[1][0] == 2 && Warrior.current_health < Warrior.max_health)
		{
			Warrior.current_health += 4;
			if (Warrior.current_health > Warrior.max_health) 
			{
				Warrior.current_health = Warrior.max_health;
			}
			floor2_map1_item[1][0] = 0;
		}
		else if (CMovingBitmap::IsOverlap(mouse_point, exit) == 1)
		{
			floor += 1;
			map.SetFrameIndexOfBitmap(floor - 1);
			exit.SetTopLeft(295 + 30, 285 - 60);
			treasure.SetTopLeft(520, 130);
			map_shops.SetTopLeft(1195, 245 - 60);
			food[0].SetTopLeft(745, 15);
		}
	}
	else if (floor == 3) 
	{
		if (CMovingBitmap::IsOverlap(mouse_point, floor_map[1][1]) && enemy_living[2][0] == 1)
		{
			state = 1;
			CurrentEnemy = &BabySquid;

			Warrior.healthbar_back.SetTopLeft(350, 900);
			Warrior.healthbar_front.SetTopLeft(353, 904);
		}
		else if (CMovingBitmap::IsOverlap(mouse_point, floor_map[1][2]) && enemy_living[2][1] == 1)
		{
			state = 1;
			CurrentEnemy = &Bully;

			Warrior.healthbar_back.SetTopLeft(350, 900);
			Warrior.healthbar_front.SetTopLeft(353, 904);
		}
		else if (CMovingBitmap::IsOverlap(mouse_point, floor_map[2][2]) && enemy_living[2][2] == 1)
		{
			state = 1;
			CurrentEnemy = &Vacuum;

			Warrior.healthbar_back.SetTopLeft(350, 900);
			Warrior.healthbar_front.SetTopLeft(353, 904);
		}
		else if (CMovingBitmap::IsOverlap(mouse_point, floor_map[0][3]) && floor3_map1_item[0][3] == 2 && Warrior.current_health < Warrior.max_health)
		{
			Warrior.current_health += 4;
			if (Warrior.current_health > Warrior.max_health)
			{
				Warrior.current_health = Warrior.max_health;
			}
			floor3_map1_item[0][3] = 0;
		}
		else if (CMovingBitmap::IsOverlap(mouse_point, floor_map[3][0]) && floor3_map1_item[3][0] == 2 && Warrior.current_health < Warrior.max_health)
		{
			Warrior.current_health += 4;
			if (Warrior.current_health > Warrior.max_health)
			{
				Warrior.current_health = Warrior.max_health;
			}
			floor3_map1_item[3][0] = 0;
		}
		else if (CMovingBitmap::IsOverlap(mouse_point, exit) == 1)
		{
			floor += 1;
			map.SetFrameIndexOfBitmap(floor - 1);
			exit.SetTopLeft(295 + 30, 485 - 60);
			treasure.SetTopLeft(1195, 245);
			food[0].SetTopLeft(520, 130);
		}
	}
	else if (floor == 4) 
	{
		if (CMovingBitmap::IsOverlap(mouse_point, floor_map[1][1]) && enemy_living[3][0] == 1)
		{
			state = 1;
			CurrentEnemy = &Fireman;

			Warrior.healthbar_back.SetTopLeft(350, 900);
			Warrior.healthbar_front.SetTopLeft(353, 904);
		}
		else if (CMovingBitmap::IsOverlap(mouse_point, floor_map[1][2]) && enemy_living[3][1] == 1)
		{
			state = 1;
			CurrentEnemy = &Snowman;

			Warrior.healthbar_back.SetTopLeft(350, 900);
			Warrior.healthbar_front.SetTopLeft(353, 904);
		}
		else if (CMovingBitmap::IsOverlap(mouse_point, floor_map[2][2]) && enemy_living[3][2] == 1)
		{
			state = 1;
			CurrentEnemy = &WickerMan;

			Warrior.healthbar_back.SetTopLeft(350, 900);
			Warrior.healthbar_front.SetTopLeft(353, 904);
		}
		else if (CMovingBitmap::IsOverlap(mouse_point, floor_map[0][2]) && floor4_map1_item[0][2] == 2 && Warrior.current_health < Warrior.max_health)
		{
			Warrior.current_health += 8;
			if (Warrior.current_health > Warrior.max_health)
			{
				Warrior.current_health = Warrior.max_health;
			}
			floor4_map1_item[0][2] = 0;
		}
		else if (CMovingBitmap::IsOverlap(mouse_point, exit) == 1)
		{
			floor += 1;
			map.SetFrameIndexOfBitmap(floor - 1);
			exit.SetTopLeft(295 + 30, 725 - 60);
			treasure.SetTopLeft(1195, 725);
			map_shops.SetTopLeft(745, 245 - 60);
			food[0].SetTopLeft(745, 15);
			food[1].SetTopLeft(970, 15 + 40);
		}
	}
	else if (floor == 5) 
	{
	if (CMovingBitmap::IsOverlap(mouse_point, floor_map[0][1]) && enemy_living[4][0] == 1)
	{
		state = 1;
		CurrentEnemy = &RhinoBeetle;

		Warrior.healthbar_back.SetTopLeft(350, 900);
		Warrior.healthbar_front.SetTopLeft(353, 904);
	}
	else if (CMovingBitmap::IsOverlap(mouse_point, floor_map[1][1]) && enemy_living[4][1] == 1)
	{
		state = 1;
		CurrentEnemy = &Kraken;

		Warrior.healthbar_back.SetTopLeft(350, 900);
		Warrior.healthbar_front.SetTopLeft(353, 904);
	}
	else if (CMovingBitmap::IsOverlap(mouse_point, floor_map[2][2]) && enemy_living[4][2] == 1)
	{
		state = 1;
		CurrentEnemy = &Cornelius;

		Warrior.healthbar_back.SetTopLeft(350, 900);
		Warrior.healthbar_front.SetTopLeft(353, 904);
	}
	else if (CMovingBitmap::IsOverlap(mouse_point, floor_map[3][2]) && enemy_living[4][3] == 1)
	{
		state = 1;
		CurrentEnemy = &RatKing;

		Warrior.healthbar_back.SetTopLeft(350, 900);
		Warrior.healthbar_front.SetTopLeft(353, 904);
	}
	else if (CMovingBitmap::IsOverlap(mouse_point, floor_map[0][3]) && floor5_map1_item[0][3] == 2 && Warrior.current_health < Warrior.max_health)
	{
		Warrior.current_health += 8;
		if (Warrior.current_health > Warrior.max_health)
		{
			Warrior.current_health = Warrior.max_health;
		}
		floor5_map1_item[0][3] = 0;
	}
	else if (CMovingBitmap::IsOverlap(mouse_point, floor_map[1][3]) && floor5_map1_item[1][3] == 2 && Warrior.current_health < Warrior.max_health)
	{
		Warrior.current_health += 8;
		if (Warrior.current_health > Warrior.max_health)
		{
			Warrior.current_health = Warrior.max_health;
		}
		floor5_map1_item[1][3] = 0;
	}
	else if (CMovingBitmap::IsOverlap(mouse_point, exit) == 1)
	{
		floor += 1;
		map.SetFrameIndexOfBitmap(floor - 1);
	}
	}
	else if (floor == 6)
	{
		if (CMovingBitmap::IsOverlap(mouse_point, *map_enemy[5][0]) && enemy_living[5][0] == 1)
		{
			state = 1;
			CurrentEnemy = &Buster;

			Warrior.healthbar_back.SetTopLeft(350, 900);
			Warrior.healthbar_front.SetTopLeft(353, 904);
		}
	}

	if (CMovingBitmap::IsOverlap(mouse_point, treasure))
	{	
		bool found = false;
		if (floor == 1 && floor1_map1_item[1][2] == 3)
		{
			for (int i = 0; i < 4 && !found; i++)
			{
				for (int j = 0; j < 5 && !found; j++)
				{
					if (backpack_use[i][j] == 0 && backpack_use[i][j + 1] == 0)
					{	
						int k = i + 5 * j;
						Backpack[k] = &equipment_battleaxe;
						Backpack[k]->backpack_column = i;
						Backpack[k]->backpack_row = j;
						Backpack[k]->backpack_square.SetTopLeft(backpack_in_test_square[i][j].GetLeft(), backpack_in_test_square[i][j].GetTop());
						backpack_use[i][j] = 1;
						backpack_use[i][j + 1] = 1;
						found = true;
						floor1_map1_item[1][2] = 0;
					}
				}
			}
		}
		else if (floor == 2)
		{

		}
	}

	if (CMovingBitmap::IsOverlap(mouse_point, backpack_button))
	{
		state = 2;
	}
}

void CGameStateRun::ui_backpack_OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{	
	int x = static_cast<int>(point.x);
	int y = static_cast<int>(point.y);
	mouse_point.SetTopLeft(x, y);

	for (int i = 0; i < 6; ++i) {
		if (Work[i] != nullptr && CMovingBitmap::IsOverlap(mouse_point, Work[i]->backpack_square)) {
			Work[i]->overlap_mouse = 1;
		}
	}

	for (int i = 0; i < 20; ++i) {
		if (Backpack[i] != nullptr && CMovingBitmap::IsOverlap(mouse_point, Backpack[i]->backpack_square)) {
			Backpack[i]->overlap_mouse = 1;
		}
	}
	
	if (CMovingBitmap::IsOverlap(mouse_point, backpack_button))
	{
		state = 0;
	}
}

void CGameStateRun::ui_shops_OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	int x = static_cast<int>(point.x);
	int y = static_cast<int>(point.y);
	mouse_point.SetTopLeft(x, y);

	bool found = false;
	if (floor == 2 && CMovingBitmap::IsOverlap(mouse_point, buy_button[0]) && Warrior.money >= 3 && floor2_shop_item[0] == 1)
	{
		for (int i = 0; i < 4 && !found; i++)
		{
			for (int j = 0; j < 5 && !found; j++)
			{
				if (backpack_use[i][j] == 0 && backpack_use[i][j + 1] == 0)
				{
					int k = i + 5 * j;
					Backpack[k] = &equipment_toxic_ooze;
					Backpack[k]->backpack_column = i;
					Backpack[k]->backpack_row = j;
					Backpack[k]->backpack_square.SetTopLeft(backpack_in_test_square[i][j].GetLeft(), backpack_in_test_square[i][j].GetTop());
					backpack_use[i][j] = 1;
					backpack_use[i][j + 1] = 1;
					found = true;
					floor2_shop_item[0] = 0;
				}
			}
		}
	}
	else if (floor == 2 && CMovingBitmap::IsOverlap(mouse_point, buy_button[1]) && Warrior.money >= 3 && floor2_shop_item[1] == 1)
	{
		for (int i = 0; i < 4 && !found; i++)
		{
			for (int j = 0; j < 5 && !found; j++)
			{
				if (backpack_use[i][j] == 0 && backpack_use[i][j + 1] == 0)
				{
					int k = i + 5 * j;
					Backpack[k] = &equipment_blood_stuck;
					Backpack[k]->backpack_column = i;
					Backpack[k]->backpack_row = j;
					Backpack[k]->backpack_square.SetTopLeft(backpack_in_test_square[i][j].GetLeft(), backpack_in_test_square[i][j].GetTop());
					backpack_use[i][j] = 1;
					backpack_use[i][j + 1] = 1;
					found = true;
					floor2_shop_item[1] = 0;
				}
			}
		}
	}
	else if (floor == 2 && CMovingBitmap::IsOverlap(mouse_point, buy_button[2]) && Warrior.money >= 3 && floor2_shop_item[2] == 1)
	{
		for (int i = 0; i < 4 && !found; i++)
		{
			for (int j = 0; j < 5 && !found; j++)
			{
				if (backpack_use[i][j] == 0 && backpack_use[i][j + 1] == 0)
				{
					int k = i + 5 * j;
					Backpack[k] = &equipment_shovel;
					Backpack[k]->backpack_column = i;
					Backpack[k]->backpack_row = j;
					Backpack[k]->backpack_square.SetTopLeft(backpack_in_test_square[i][j].GetLeft(), backpack_in_test_square[i][j].GetTop());
					backpack_use[i][j] = 1;
					backpack_use[i][j + 1] = 1;
					found = true;
					floor2_shop_item[2] = 0;
				}
			}
		}
	}


	if (CMovingBitmap::IsOverlap(mouse_point, end_shops_button))
	{
		state = 0;
	}
}

void CGameStateRun::ui_menu_OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	int x = static_cast<int>(point.x);
	int y = static_cast<int>(point.y);
	mouse_point.SetTopLeft(x, y);

	for (int i = 0; i < 3; i++) 
	{
		if (CMovingBitmap::IsOverlap(mouse_point, door[i]))
		{	
			mod = i + 1;
			CGameStateRun::OnInit();
			state = 0;
		}
	}
}

void CGameStateRun::ui_combat_OnLButtonDown(UINT nFlags, CPoint point)  // 戰鬥時處理滑鼠左鍵的動作
{
	int x = static_cast<int>(point.x);
	int y = static_cast<int>(point.y);
	mouse_point.SetTopLeft(x, y);

	for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
		if (isfire[i] == 1 && CMovingBitmap::IsOverlap(mouse_point, dice_fired[i]))
		{
			Warrior.current_health -= 2;
			isfire[i] = 0;
		}
	}

	for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
		if (CMovingBitmap::IsOverlap(mouse_point, Warrior.dice[i]) && islocked[i] == 0) {
			dice_overlap_mouse[i] = 1;
			break;
		}
	}
}
void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{	
	if (state == 1) 
	{
		CGameStateRun::ui_combat_OnLButtonUp(nFlags, point);
	}
	else if (state == 2) 
	{
		CGameStateRun::ui_backpack_OnLButtonUp(nFlags, point);
	}
}

void CGameStateRun::ui_combat_OnLButtonUp(UINT nFlags, CPoint point)	// 處理戰鬥時滑鼠左鍵的動作
{	

	for (int i = 0; i < Warrior.chararter_dice_amount; i++) 
	{
		if (dice_overlap_mouse[i] == 1) {
			dice_overlap_mouse[i] = 0;
		}
	}

	equipment_reroll.callWorkFunction();

	for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
		if (isblind[i] == 1) 
		{
			dice_blind[i].SetTopLeft(800 + 150 * i, 900);
		}
	}

	for (int j = 0; j < Warrior.chararter_dice_amount; j++)
	{
		for (int i = 0; i < 6; ++i)
		{
			if (Work[i] != nullptr && equipment_use[i] == 1 && CMovingBitmap::IsOverlap(Work[i]->equipment, Warrior.dice[j]) )
			{	
				if (Warrior.cursed >= 1) 
				{	
					std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
					std::uniform_int_distribution<int> uni(1, 100);
					int probability = uni(rng);
					if (probability >= 51) 
					{
						Work[i]->callWorkFunction();
					}
					else 
					{
						Warrior.cursed -= 1;
					}
				}
				else
				{
					Work[i]->callWorkFunction();
				}
				equipment_use[i] = 0;
			}
		}
	}

	//preview
	if (CMovingBitmap::IsOverlap(mouse_point, uparrow_arrow))
	{
		enemyPreview = !(enemyPreview);
	}

	if (CMovingBitmap::IsOverlap(mouse_point, end_turn_arrow)) 
	{
		std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
		std::uniform_int_distribution<int> uni(1, 6);
		//end_turn 自己回合按下
		if (enemyShow == 0) {

			for (int i = 0; i < Warrior.chararter_dice_amount; i++)
			{
				isfire[i] = 0;
			}

			for (int i = 0; i < Warrior.chararter_dice_amount; i++)
			{
				isblind[i] = 0;
			}

			for (int i = 0; i < Warrior.chararter_dice_amount; i++)
			{
				islocked[i] = 0;
			}
			Warrior.fired = 0;
			Warrior.freezed = 0;
			Warrior.blind = 0;
			Warrior.locked = 0;
			Warrior.cursed = 0;

			if (mod == 2) 
			{
				Warrior.cursed += 1;
			}

			int random_number = uni(rng);

			for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
				int random_number = uni(rng);
				Warrior.dice[i].SetFrameIndexOfBitmap(random_number - 1);
				Warrior.dice[i].SetTopLeft(800 + 150 * i, 900);
				dice_use[i] = 1;
			}

			for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
				dice_blind[i].SetTopLeft(800 + 150 * i, 900);
			}

			for (int i = 0; i < 6; i++) {
				equipment_use[i] = 1;
			}

			for (int i = 0; i < 6; ++i) {
				if (Work[i] != nullptr) {
					Work[i]->RestructFunction(-2500);
				}
			}

			enemyShow = 1;
			
			for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
				Warrior.dice[i].SetTopLeft(800 + 150 * i, 1500);
			}

			if (enemy_poison > 0) 
			{
				CurrentEnemy->enemy_current_health -= enemy_poison;
				enemy_poison -= 1;
			}

			CurrentEnemy->callWorkFunction();


			CurrentEnemy->SetEnemyEquipmentPositions(CurrentEnemy->enemy_equipment_number, 0, 0, CurrentEnemy->positions);

			if (CurrentEnemy->enemy_current_health > CurrentEnemy->enemy_max_health) 
			{
				CurrentEnemy->enemy_current_health = CurrentEnemy->enemy_max_health;
			}

			for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
				enemy_dice[i].SetTopLeft(1000 - 150 * i, 80);
			}


		}
		else { // 敵人回合按下
			for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
				int random_number = uni(rng);
				Warrior.dice[i].SetFrameIndexOfBitmap(random_number - 1);
				Warrior.dice[i].SetTopLeft(800 + 150 * i, 900);
			}

			for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
				enemy_dice[i].SetTopLeft(1000 - 150 * i, -200);
			}


			for (int i = 0; i < 6; ++i) {
				if (Work[i] != nullptr) {
					Work[i]->RestructFunction(0);
				}
			}

			//fire
			for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
				if (i <= Warrior.fired - 1)
				{
					isfire[i] = 1;
				}
			}

			//blind
			for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
				if (i <= Warrior.blind - 1)
				{
					isblind[i] = 1;
				}
			}

			//lock
			for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
				if (i <= Warrior.locked - 1)
				{
					islocked[i] = 1;
				}
			}

			std::vector<std::pair<int, int>> diceValues;

			//freeze
			for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
				int diceValue = Warrior.dice[i].GetFrameIndexOfBitmap() + 1;
				diceValues.push_back({ diceValue, i });
			}

			std::sort(diceValues.begin(), diceValues.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
				return a.first > b.first;
				});

			for (int i = 0; i < Warrior.freezed; i++) {
				int index = diceValues[i].second;
				Warrior.dice[index].SetFrameIndexOfBitmap(0);
			}

			//equipment_reroll
			equipment_reroll.equipment.SetTopLeft(40 + 470 * 3, 300);
			equipment_reroll.diceslot.SetTopLeft(40 + 470 * 3 + 134, 465);
			equipment_reroll.diceslot.SetFrameIndexOfBitmap(6);


			statusEffects();

			enemyShow = 0;
		}

		//recovery_to_warrior
		CurrentEnemy->SetEnemyEquipmentPositions(CurrentEnemy->enemy_equipment_number, 0, 0, CurrentEnemy-> positions);

		for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++) {
			enemy_dice_use[i] = 1;
		}

		for (int i = 0; i < CurrentEnemy->enemy_equipment_number; i++) 
		{	
			if (enemy_equipment_use[i] != -1)
			{
				enemy_equipment_use[i] = 1;
			}
		}


		for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
			dice_use[i] = 1;
		}

		for (int i = 0; i < 6; i++) {
			equipment_use[i] = 1;
		}

		Warrior.reroll = 3;

	}
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠移動的動作
{	
	if (state == 1) 
	{
		CGameStateRun::ui_combat_OnMouseMove(nFlags, point);
	}
	else if (state == 0)
	{
		CGameStateRun::ui_map_OnMouseMove(nFlags, point);
	}
	else if (state == 2) 
	{
		CGameStateRun::ui_backpack_OnMouseMove(nFlags, point);
	}
}

void CGameStateRun::ui_backpack_OnLButtonUp(UINT nFlags, CPoint point)
{	
	bool found = false;

	for (int i = 0; i < 4 && !found; i++)
	{
		for (int j = 0; j < 5 && !found; j++)
		{	
			for (int k = 0; k < 6; k++)
			{
				if (Work[k] != nullptr && CMovingBitmap::IsOverlap(backpack_in_test_square[i][j], mouse_point) && Work[k]->overlap_mouse == 1) {
					if (!(Work[k]->size == 1 && j == 4) && backpack_use[i][j] == 0) {
						Work[k]->overlap_mouse = 0;
						if ( !(Work[k]->backpack_column == i && Work[k]->backpack_row == j) ) {
							Work[k]->backpack_square.SetTopLeft(backpack_in_test_square[i][j].GetLeft(), backpack_in_test_square[i][j].GetTop());
							backpack_use[Work[k]->backpack_column][Work[k]->backpack_row] = 0;
							backpack_use[Work[k]->backpack_column][Work[k]->backpack_row + Work[k]->size] = 0;
							Work[k]->backpack_column = i;
							Work[k]->backpack_row = j;
							backpack_use[i][j] = 1;
							backpack_use[i][j + Work[k]->size] = 2;
							Backpack[i + j] = Work[k];
							Work[k] = nullptr;
						}
						found = true;
						break;
					}
				}
			}
			if (found) break;
			for (int k = 0; k < 20; k++)
			{
				if (Backpack[k] != nullptr && CMovingBitmap::IsOverlap(backpack_in_test_square[i][j], mouse_point) && Backpack[k]->overlap_mouse == 1) {
					if (!(Backpack[k]->size == 1 && j == 4) && work_use[i][j] == 0) {
						Backpack[k]->overlap_mouse = 0;
						if ( !(Backpack[k]->backpack_column == i && Backpack[k]->backpack_row == j) ) {
							Backpack[k]->backpack_square.SetTopLeft(backpack_in_test_square[i][j].GetLeft(), backpack_in_test_square[i][j].GetTop());
							backpack_use[Backpack[k]->backpack_column][Backpack[k]->backpack_row] = 0;
							backpack_use[Backpack[k]->backpack_column][Backpack[k]->backpack_row + Backpack[k]->size] = 0;
							Backpack[k]->backpack_column = i;
							Backpack[k]->backpack_row = j;
							backpack_use[i][j] = 1;
							backpack_use[i][j + Backpack[k]->size] = 2;
							Backpack[i + 5 * j] = Backpack[k];
							Backpack[k] = nullptr;
						}
						found = true;
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < 3 && !found; i++)
	{
		for (int j = 0; j < 2 && !found; j++)
		{	
			for (int k = 0; k < 6; k++) 
			{
				if (Work[k] != nullptr && CMovingBitmap::IsOverlap(backpack_out_test_square[i][j], mouse_point) && Work[k]->overlap_mouse == 1) {
					if (!(Work[k]->size == 1 && j == 1) && backpack_use[i][j] == 0) {
						Work[k]->overlap_mouse = 0;
						if ( !(Work[k]->backpack_column == i && Work[k]->backpack_row == j) ) {
							Work[k]->backpack_square.SetTopLeft(backpack_out_test_square[i][j].GetLeft(), backpack_out_test_square[i][j].GetTop());
							work_use[Work[k]->backpack_column][Work[k]->backpack_row] = 0;
							work_use[Work[k]->backpack_column][Work[k]->backpack_row + Work[k]->size] = 0;
							Work[k]->backpack_column = i;
							Work[k]->backpack_row = j;
							work_use[i][j] = 1;
							work_use[i][j + Work[k]->size] = 2;
							Work[i + 3 * j] = Work[k];
							Work[k] = nullptr;
						}
						found = true;
						break;
					}
				}
			}
			if (found) break;
			for (int k = 0; k < 20; k++)
			{
				if (Backpack[k] != nullptr && CMovingBitmap::IsOverlap(backpack_out_test_square[i][j], mouse_point) && Backpack[k]->overlap_mouse == 1) {
					if (!(Backpack[k]->size == 1 && j == 1) && work_use[i][j] == 0) {
						Backpack[k]->overlap_mouse = 0;
						if ( !(Backpack[k]->backpack_column == i && Backpack[k]->backpack_row == j) ) {
							Backpack[k]->backpack_square.SetTopLeft(backpack_out_test_square[i][j].GetLeft(), backpack_out_test_square[i][j].GetTop());
							work_use[Backpack[k]->backpack_column][Backpack[k]->backpack_row] = 0;
							work_use[Backpack[k]->backpack_column][Backpack[k]->backpack_row + Backpack[k]->size] = 0;
							Backpack[k]->backpack_column = i;
							Backpack[k]->backpack_row = j;
							work_use[i][j] = 1;
							work_use[i][j + Backpack[k]->size] = 2;
							Work[i + j] = Backpack[k];
							Backpack[k] = nullptr;
						}
						found = true;
						break;
					}
				}
			}
		}

		for (int i = 0; i < 6; ++i) {
			if (Work[i] != nullptr) {
				Work[i]->RestructFunction(0);
			}
		}
	}
}

void CGameStateRun::ui_map_OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠移動的動作
{	
	int x = static_cast<int>(point.x);
	int y = static_cast<int>(point.y);
	mouse_point.SetTopLeft(x, y);


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{	
			if (floor == 1) 
			{
				if (floor1_map1_exeist[i][j] == 1)
				{
					if (CMovingBitmap::IsOverlap(mouse_point, floor_map[i][j]))
					{
						floor_map[i][j].SetFrameIndexOfBitmap(1);
					}
					else
					{
						floor_map[i][j].SetFrameIndexOfBitmap(0);
					}
				}
			}
			else if (floor == 2) 
			{
				if (floor2_map1_exeist[i][j] == 1)
				{
					if (CMovingBitmap::IsOverlap(mouse_point, floor_map[i][j]))
					{
						floor_map[i][j].SetFrameIndexOfBitmap(1);
					}
					else
					{
						floor_map[i][j].SetFrameIndexOfBitmap(0);
					}
				}
			}
			else if (floor == 3)
			{
				if (floor3_map1_exeist[i][j] == 1)
				{
					if (CMovingBitmap::IsOverlap(mouse_point, floor_map[i][j]))
					{
						floor_map[i][j].SetFrameIndexOfBitmap(1);
					}
					else
					{
						floor_map[i][j].SetFrameIndexOfBitmap(0);
					}
				}
			}
			else if (floor == 4)
			{
				if (floor4_map1_exeist[i][j] == 1)
				{
					if (CMovingBitmap::IsOverlap(mouse_point, floor_map[i][j]))
					{
						floor_map[i][j].SetFrameIndexOfBitmap(1);
					}
					else
					{
						floor_map[i][j].SetFrameIndexOfBitmap(0);
					}
				}
			}
			else if (floor == 5)
			{
				if (floor5_map1_exeist[i][j] == 1)
				{
					if (CMovingBitmap::IsOverlap(mouse_point, floor_map[i][j]))
					{
						floor_map[i][j].SetFrameIndexOfBitmap(1);
					}
					else
					{
						floor_map[i][j].SetFrameIndexOfBitmap(0);
					}
				}
			}
		}
	}

}

void CGameStateRun::ui_combat_OnMouseMove(UINT nFlags, CPoint point)	// 戰鬥時處理滑鼠的動作
{
	int x = static_cast<int>(point.x);
	int y = static_cast<int>(point.y);

	int dx = point.x - mouse_point.GetLeft();
	int dy = point.y - mouse_point.GetTop();

	mouse_point.SetTopLeft(x, y);

	for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
		if (dice_overlap_mouse[i] == 1) {
			Warrior.dice[i].SetTopLeft(Warrior.dice[i].GetLeft() + dx, Warrior.dice[i].GetTop() + dy);
		}
	}

	for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
		if (dice_overlap_mouse[i] == 1) {
			dice_blind[i].SetTopLeft(Warrior.dice[i].GetLeft() + dx, Warrior.dice[i].GetTop() + dy);
		}
	}


	for (int i = 0; i < 6; ++i) {
		if (Work[i] != nullptr) {
			if (!isblind[i]) {
				Work[i]->callMoveFunction();
			}
		}
	}
}

void CGameStateRun::ui_backpack_OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠移動的動作
{
	int x = static_cast<int>(point.x);
	int y = static_cast<int>(point.y);

	int dx = point.x - mouse_point.GetLeft();
	int dy = point.y - mouse_point.GetTop();

	mouse_point.SetTopLeft(x, y);
	for (int i = 0; i < 20; ++i) {
		if (Backpack[i] != nullptr && Backpack[i]->overlap_mouse == 1) {
			Backpack[i]->backpack_square.SetTopLeft(Backpack[i]->backpack_square.GetLeft() + dx, Backpack[i]->backpack_square.GetTop() + dy);
		}
	}

	for (int i = 0; i < 6; ++i) {
		if (Work[i] != nullptr && Work[i]->overlap_mouse == 1) {
			Work[i]->backpack_square.SetTopLeft(Work[i]->backpack_square.GetLeft() + dx, Work[i]->backpack_square.GetTop() + dy);
		}
	}
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{	
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{	
	if (Warrior.current_health <= 0) 
	{
		state = -1;
	}
	if (state == 1) {
		CGameStateRun::ui_combat_OnShow();
	}
	else if (state == 0)
	{
		CGameStateRun::ui_map_OnShow();
	}
	else if (state == 2)
	{
		CGameStateRun::ui_backpack_OnShow();
	}
	else if (state == 3)
	{
		CGameStateRun::ui_shops_OnShow();
	}
	else if (state == 10)
	{
		CGameStateRun::ui_menu_OnShow();
	}
}

void CGameStateRun::ui_map_OnShow() 
{	
	background.ShowBitmap();
	map.ShowBitmap();
	

	//land_floor1
	if (floor == 1) 
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (floor1_map1_exeist[i][j] == 1)
				{
					floor_map[i][j].ShowBitmap();
				}
			}
		}
	}
	else if (floor == 2) 
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (floor2_map1_exeist[i][j] == 1)
				{
					floor_map[i][j].ShowBitmap();
				}
			}
		}
	}
	else if (floor == 3)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (floor3_map1_exeist[i][j] == 1)
				{
					floor_map[i][j].ShowBitmap();
				}
			}
		}
	}
	else if (floor == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (floor4_map1_exeist[i][j] == 1)
				{
					floor_map[i][j].ShowBitmap();
				}
			}
		}
	}
	else if (floor == 5)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (floor5_map1_exeist[i][j] == 1)
				{
					floor_map[i][j].ShowBitmap();
				}
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (enemy_living[floor - 1][i] == 1)
		{
			map_enemy[floor - 1][i]->ShowBitmap();
		}
	}

	if (floor == 2 || floor == 3 || floor == 5) {
		map_shops.ShowBitmap();
	}

	ui_map_downbox.ShowBitmap();
	head.ShowBitmap();

	star.ShowBitmap();

	backpack_button.ShowBitmap();

	if (floor < 6)
	{
		exit.ShowBitmap();
	}

	if (floor < 6)
	{	
		if (floor == 1 && floor1_map1_item[1][2] == 3) 
		{
			treasure.ShowBitmap();
		}
		else if (floor == 2 && floor2_map1_item[3][1] == 3)
		{
			treasure.ShowBitmap();
		}
		else if (floor == 3 && floor3_map1_item[0][2] == 3)
		{
			treasure.ShowBitmap();
		}
		else if (floor == 4 && floor4_map1_item[2][3] == 3)
		{
			treasure.ShowBitmap();
		}
		else if (floor == 5 && floor4_map1_item[3][3] == 3)
		{
			treasure.ShowBitmap();
		}
	}

	if (floor < 6 && floor != 1) 
	{	
		if (floor2_map1_item[1][0] == 2 && floor == 2)
		{
			food[0].ShowBitmap();
		}
		else if (floor3_map1_item[0][3] == 2 && floor == 3)
		{
			food[0].ShowBitmap();
		}
		else if (floor4_map1_item[0][2] == 2 && floor == 4)
		{
			food[0].ShowBitmap();
		}
		else if (floor5_map1_item[0][3] == 2 && floor == 5)
		{
			food[0].ShowBitmap();
		}
	}

	if (floor == 3 || floor == 5) 
	{	
		if (floor3_map1_item[3][0] == 2 && floor == 3)
		{
			food[1].ShowBitmap();
		}
		else if (floor5_map1_item[1][3] == 2 && floor == 5)
		{
			food[1].ShowBitmap();
		}
	}

	//downbox_start
	//health
	Warrior.healthbar_back.SetTopLeft(390, 970);
	Warrior.healthbar_front.SetTopLeft(393, 974);
	Warrior.healthbar_back.ShowBitmap();
	Warrior.healthbar_front.ShowBitmap();
	//floor
	for (int i = 0; i < 6; i++) 
	{
		if (floor >= i + 1)
		{
			bone[i].SetFrameIndexOfBitmap(1);
		}
		bone[i].ShowBitmap();
	}
	CDC *pDC = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(255, 255, 255), 500);

	CTextDraw::Print(pDC, 120, 1010, "阿兵哥");

	//health
	std::stringstream sf;
	sf << Warrior.current_health << "/" << Warrior.max_health;
	std::string health_string = sf.str();
	CTextDraw::Print(pDC, 390 + 125, 980, health_string);

	//level
	std::stringstream slevel;
	slevel << "等級"<< Warrior.level;
	std::string level_string = slevel.str();
	CTextDraw::Print(pDC, 890, 980, level_string);

	//experience
	std::stringstream sexp_need;
	sexp_need << "升級還需要     " << Warrior.exp_need[Warrior.level - 1] - Warrior.exp;
	std::string exp_need_string = sexp_need.str();
	CTextDraw::Print(pDC, 810, 1010, exp_need_string);

	//floor
	std::stringstream sfloor;
	sfloor << "樓層" << floor;
	std::string floor_string = sfloor.str();
	CTextDraw::Print(pDC, 1680, 1025, floor_string);

	std::stringstream smoney;
	smoney << Warrior.money;
	std::string money_string = smoney.str();
	CTextDraw::Print(pDC, 425, 1025, money_string);

	std::stringstream sdice_amount;
	sdice_amount << "x" << Warrior.chararter_dice_amount;
	std::string dice_amount_string = sdice_amount.str();
	CTextDraw::Print(pDC, 660, 1025, dice_amount_string);
	//downbox_end

	CDDraw::ReleaseBackCDC();
}

void CGameStateRun::ui_combat_OnShow()
{	
	//combat_ui
	ui_combat_background.ShowBitmap();
	Warrior.character.ShowBitmap();

	Warrior.healthbar_back.ShowBitmap();
	Warrior.healthbar_front.ShowBitmap();

	Warrior.limitbar_back.ShowBitmap();
	Warrior.limitbar_front.ShowBitmap();

    CurrentEnemy->enemy.ShowBitmap();

	enemy_healthbar_back.ShowBitmap();
	enemy_healthbar_front.ShowBitmap();

	//equipment
	if (enemyPreview == 0)
	{
		for (int i = 0; i < 6; ++i) {
			if (Work[i] != nullptr && equipment_use[i] == 1) {
				Work[i]->callShowFunction();
			}
		}
	}

	//equipment_reroll
	if (enemyPreview == 0 && enemyShow == 0) {
		equipment_reroll.callShowFunction();
	}

	if (enemyShow == 0) {
		uparrow_arrow.ShowBitmap();
	}

	//enemy
	if (enemyShow == 1) {
		for (int i = 0; i < CurrentEnemy->enemy_dice_amount; i++)
		{
			enemy_dice[i].ShowBitmap();
		}
	}

	if (enemyShow == 1 || enemyPreview == 1) {
		for (int i = 0; i < CurrentEnemy->enemy_equipment_number; i++) {
			if (enemy_equipment_use[i] == 1)
			{
				CurrentEnemy->enemy_equipment[i].ShowBitmap();
			}
		}
	}

	symbols_dice.ShowBitmap();

	//fired
	for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
		if (dice_use[i] == 1 && enemyPreview == 0) 
		{	
			if (isfire[i] == 1) 
			{
				dice_fired[i].ShowBitmap();
			}
		}
	}


	for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
		if (dice_use[i] == 1 && enemyPreview == 0) 
		{
			if (!isblind[i]) 
			{
				Warrior.dice[i].ShowBitmap();
			}
		}
	}

	//blind
	for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
		if (dice_use[i] == 1 && enemyPreview == 0)
		{
			if (isblind[i] == 1)
			{
				dice_blind[i].ShowBitmap();
			}
		}
	}

	//lock
	for (int i = 0; i < Warrior.chararter_dice_amount; i++) {
		if (dice_use[i] == 1 && enemyPreview == 0)
		{
			if (islocked[i] == 1)
			{
				dice_locked[i].ShowBitmap();
			}
		}
	}

	//end_turn_part1
	if (enemyPreview == 0) {
		end_turn_arrow.ShowBitmap();
	}

	CDC *pDC = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(255, 255, 255), 500);
	CTextDraw::Print(pDC, 350, 860, "阿兵哥");
	std::stringstream sdice_amount;
	sdice_amount << "x" << Warrior.chararter_dice_amount;
	std::string dice_amount_string = sdice_amount.str();
	CTextDraw::Print(pDC, 625, 860, dice_amount_string);

	if (enemyShow == 0) {
		CTextDraw::Print(pDC, 900, 60, "敵方行動");
	}


	CTextDraw::Print(pDC, 1150, 60, CurrentEnemy->enemy_name);

	//equipment_reroll
	if (Warrior.reroll != 0 && enemyShow == 0 && enemyPreview == 0) {
		std::stringstream ss;
		ss << "本回合可以使用" << Warrior.reroll << "次";
		std::string reroll_string = ss.str();
		CTextDraw::Print(pDC, 40 + 470 * 3 + 134, 675, reroll_string);
	}

	//health
	std::stringstream sf;
	sf << Warrior.current_health << "/" << Warrior.max_health;
	std::string health_string = sf.str();
	CTextDraw::Print(pDC, 475, 910, health_string);

	//enemy_health
	std::stringstream sm;
	sm << CurrentEnemy->enemy_current_health << "/" << CurrentEnemy->enemy_max_health;
	std::string enemy_health_string = sm.str();
	CTextDraw::Print(pDC, 1275, 110, enemy_health_string);

	if (enemyShow == 1 || enemyPreview == 1)
	{
		for (int i = 0; i < 6; i++) 
		{	
			if (CurrentEnemy->enemy_required[i] != 0)
			{
				std::string required_str = std::to_string(CurrentEnemy->enemy_required[i]);
				int x_pos = CurrentEnemy->positions[i].first + 150;
				int y_pos = CurrentEnemy->positions[i].second + 100;
				CTextDraw::Print(pDC, x_pos, y_pos, required_str);
			}
		}
	}

	//end_turn_part2
	if (enemyPreview == 0) {
		CTextDraw::Print(pDC, 1705, 1000, "結束這一回合");
	}

	CDDraw::ReleaseBackCDC();

	//combat_ui_end 
}

void CGameStateRun::ui_backpack_OnShow()
{	
	backpack_background.ShowBitmap();

	ui_map_downbox.ShowBitmap();
	head.ShowBitmap();

	star.ShowBitmap();

	backpack_button.ShowBitmap();

	for (int i = 0; i < 20; ++i) {
		if (Backpack[i] != nullptr) {
			Backpack[i]->backpack_square.ShowBitmap();
		}
	}

	for (int i = 0; i < 6; ++i) {
		if (Work[i] != nullptr) {
			Work[i]->backpack_square.ShowBitmap();
		}
	}
	//downbox_start
	//health
	Warrior.healthbar_back.SetTopLeft(390, 970);
	Warrior.healthbar_front.SetTopLeft(393, 974);
	Warrior.ShowHealthBars();
	//floor
	for (int i = 0; i < 6; i++)
	{
		if (floor >= i + 1)
		{
			bone[i].SetFrameIndexOfBitmap(1);
		}
		bone[i].ShowBitmap();
	}
	CDC *pDC = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(255, 255, 255), 500);

	CTextDraw::Print(pDC, 120, 1010, "阿兵哥");

	//downbox_start
	//health
	std::stringstream sf;
	sf << Warrior.current_health << "/" << Warrior.max_health;
	std::string health_string = sf.str();
	CTextDraw::Print(pDC, 390 + 125, 980, health_string);

	//level
	std::stringstream slevel;
	slevel << "等級" << Warrior.level;
	std::string level_string = slevel.str();
	CTextDraw::Print(pDC, 890, 980, level_string);

	//experience
	std::stringstream sexp_need;
	sexp_need << "升級還需要     " << Warrior.exp_need[Warrior.level - 1] - Warrior.exp;
	std::string exp_need_string = sexp_need.str();
	CTextDraw::Print(pDC, 810, 1010, exp_need_string);

	//floor
	std::stringstream sfloor;
	sfloor << "樓層" << floor;
	std::string floor_string = sfloor.str();
	CTextDraw::Print(pDC, 1680, 1025, floor_string);

	std::stringstream smoney;
	smoney << Warrior.money;
	std::string money_string = smoney.str();
	CTextDraw::Print(pDC, 425, 1025, money_string);

	std::stringstream sdice_amount;
	sdice_amount << "x" << Warrior.chararter_dice_amount;
	std::string dice_amount_string = sdice_amount.str();
	CTextDraw::Print(pDC, 660, 1025, dice_amount_string);
	//downbox_end

	CDDraw::ReleaseBackCDC();
}

void CGameStateRun::ui_shops_OnShow()
{	

	shops.ShowBitmap();

	ui_map_downbox.ShowBitmap();
	head.ShowBitmap();

	star.ShowBitmap();

	for (int i = 0; i < 3; i++) 
	{
		buy_button[i].ShowBitmap();
	}

	if (floor == 2) 
	{
		if (floor2_shop_item[0] == 1) 
		{
			equipment_toxic_ooze.equipment.ShowBitmap();
		}
		if (floor2_shop_item[1] == 1)
		{	
			equipment_blood_stuck.equipment.ShowBitmap();
		}
		if (floor2_shop_item[2] == 1)
		{
			equipment_shovel.equipment.ShowBitmap();
		}

	}
	end_shops_button.ShowBitmap();

	//
	CDC* pDC = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(255, 255, 255), 500);

	CTextDraw::Print(pDC, 120, 1010, "阿兵哥");

	//downbox_start
	//health
	std::stringstream sf;
	sf << Warrior.current_health << "/" << Warrior.max_health;
	std::string health_string = sf.str();
	CTextDraw::Print(pDC, 390 + 125, 980, health_string);

	//level
	std::stringstream slevel;
	slevel << "等級" << Warrior.level;
	std::string level_string = slevel.str();
	CTextDraw::Print(pDC, 890, 980, level_string);

	//experience
	std::stringstream sexp_need;
	sexp_need << "升級還需要     " << Warrior.exp_need[Warrior.level - 1] - Warrior.exp;
	std::string exp_need_string = sexp_need.str();
	CTextDraw::Print(pDC, 810, 1010, exp_need_string);

	//floor
	std::stringstream sfloor;
	sfloor << "樓層" << floor;
	std::string floor_string = sfloor.str();
	CTextDraw::Print(pDC, 1680, 1025, floor_string);

	std::stringstream smoney;
	smoney << Warrior.money;
	std::string money_string = smoney.str();
	CTextDraw::Print(pDC, 425, 1025, money_string);

	std::stringstream sdice_amount;
	sdice_amount << "x" << Warrior.chararter_dice_amount;
	std::string dice_amount_string = sdice_amount.str();
	CTextDraw::Print(pDC, 660, 1025, dice_amount_string);
	//downbox_end
	//
	for (int i = 0; i < 3; i++) 
	{
		CTextDraw::Print(pDC, 95 + 450 * i, 765 + 80, " 售價 : 3金幣");
	}

	CDDraw::ReleaseBackCDC();
}

void CGameStateRun::ui_menu_OnShow() 
{
	menu.ShowBitmap();
	for (int i = 0; i < 3; i++) 
	{
		door[i].ShowBitmap();
	}
}