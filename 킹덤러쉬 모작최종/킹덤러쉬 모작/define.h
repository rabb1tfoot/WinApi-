#pragma once

class CTimeMgr;
class CKEYMgr;

#define SINGLE(type) public:\
static type* GetInst()\
{\
static type obj;\
return &obj;\
 }\
private:\
type();\
~type();\

#define WINSIZE_X 1024
#define WINSIZE_Y 768

#define SUCCESS 1
#define FAILEDD -1

#define SAFE_DELETE(p) if(nullptr !=p) {delete p; p = nullptr;}

#define DT CTimeMgr::GetInst()->GetDeltaTime()
#define KEY(eType, eState) (eState == CKeyMgr::GetInst()->GetKeyState(eType))
#define KEYHOLD(eType) KEY(eType, KEY_STATE::STATE_HOLD)
#define KEYTAB(eType)  KEY(eType, KEY_STATE::STATE_TAB)
#define KEYAWAY(eType) KEY(eType, KEY_STATE::STATE_AWAY)
#define KEYNONE(eType) KEY(eType, KEY_STATE::STATE_NONE)
#define MOUSEPOS CKeyMgr::GetInst()->GetMousePos()
#define PREVMOUSEPOS CKeyMgr::GetInst()->GetPrevMousePos()
#define CLICKMOUSEPOS CKeyMgr::GetInst()->GetClickMousePos()

#define PI 3.14f
#define STAGE_NUM 2

extern int g_iSaveLoad;


enum class STAGE_TYPE
{
	TOOL,
	TEST,
	TITLE,
	SELECT,
	PLAY,
	STAGE_1,
	STAGE_2,
	STAGE_3,

	END,
};

enum class OBJ_TYPE
{
	BACKGROUND,
	TILE,
	SALMPLEANIM,
	ENEMY_UNIT,
	ENEMY_UNIT_RANGE,
	ALLY_UNIT,
	ALLY_UNIT_RANGE,
	ALLY_HERO,
	ATT_OBJECT,
	ALLY_UNIT_IGNORE,
	TEST,

	UI,
	ELDER_PANEL,
	ELDER_UI,
	MAP_INGREDIENT,

	END = 32,
};

enum class ATTACK_TYPE
{
	MELEE,
	RANGER
};

enum class UNIT_STATE
{
	IDLE,
	TRACKING,
	ATTACK,
};

enum class UNIT_DIRECTION
{
	LEFT,
	TOP,
	RIGHT,
	BOTTOM,
	LT,
	LB,
	RT,
	RB
};

enum class BUILD_SELETE
{
	BUILD_ARCHER,
	BUILD_BARRACKS,
	BUILD_MAGE,
	BUILD_CANNON,
	BUILD_UPGRADE,
	BUILD_SELL,
	BUILD_MOVEPOINT,
	NONE
};

enum MAP_SETTING
{
	MAP_BLOCK,
	MAP_NOTBLOCK,
	MAP_GROUND,
	NONE
};

enum MONSTER_TYPE
{
	GOBLIN,
	OGRE,
	BANDIT,

};


enum class DIRECITON_MODE
{
	DIR_NOMAL,
	DIR_ATTACK,
	END,
};

enum HERO_TYPE
{
	HERO_LIGHT =1,
	HERO_HAMMER,
	HERO_NONE,
	HERO_END
};