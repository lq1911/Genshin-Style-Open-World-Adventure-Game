#ifndef __SET_MAP_H__
#define __SET_MAP_H__

#include <vector>
#include "cocos2d.h"
#include "Player.h"
#include "SetPlayerScene.h"
#include "BagManager.h"
#include "NPC.h"
#include "Monster.h"
#include "MapManager.h"
#include "CameraManager.h"
#include "EventManager.h"
USING_NS_CC;
using namespace std;

class SetMap :public cocos2d::Scene {
private:
	Size VisibleSize;    // 可见屏幕大小
	
	CameraManager* _cameraManager;    // 摄像机管理器
	EventManager* _eventManager;    // 事件管理器
	MapManager* _mapManager;    // 地图管理器
	BagManager* _bagManager;    // 背包管理器

	Player* PLAYER;     // 操作用户
	MonsterRespawn* _monsterRespawn;    // 怪物管理器
	NPC* npc1;    // NPC1

	vector<bool> isKeyPressed = { false,false,false,false };    // 按键是否按下:W/S/A/D
public:
	/****************************************************************/
	////////////////以下为本场景所有用到的初始化函数/////////////////
	/* 构造函数，获取屏幕的大小*/
	SetMap(); 

	/*生成场景函数*/
	static cocos2d::Scene* createScene();

	/*初始化地图函数*/
	virtual bool init();

	/*初始化摄像机*/
	void LoadCameraToScene();

	/*初始化地图*/
	void LoadMapToScene();

	/*初始化背包界面*/
	void LoadBagToScene();

	/*初始化操控角色*/
	void LoadPlayerToScene();

	/*初始化怪物管理器*/
	void LoadMonsterRespawnToScene();

	/*初始化NPC*/
	void LoadNPCToScene();

	/****************************************************************/
	////////////////以下为本场景声明的本场景特有功能函数/////////////////
	/*设置摄像机跟随玩家移动*/
	void CameraFollowController();

	/*设置主地图摄像机随玩家移动*/
	void MainCameraFollowPlayer();

	/*设置小地图摄像机随玩家移动*/
	void MicroCameraFollowPlayer();

	/**********************************************************************/
	////////////////以下为本场景所有与监视器相关的回调函数/////////////////
	/*键盘事件处理, 按下M键切换显示微地图*/
	void KeyPressedForRevealMicroMap(EventKeyboard::KeyCode keyCode, Event* event);

	/*键盘事件处理，按下B键打开背包*/
	void KeyPressedForBag(EventKeyboard::KeyCode keyCode, Event* event);

	/*键盘事件处理，按下W/A/S/D控制人物移动*/
	void KeyPressedForPlayerMove(EventKeyboard::KeyCode keyCode, Event* event);
	void KeyReleasedForPlayerMove(EventKeyboard::KeyCode keyCode, Event* event);    //玩家移动的辅助函数，释放按键玩家停止移动
	void HandlePlayerMove(const Vec2& moveBy, int keyIndex, const std::string& scheduleKey, dir direction);    //玩家移动的辅助函数

	/*键盘事件处理，按下I/J/K/L控制人物攻击*/
	void KeyPressedForPlayerAttack(EventKeyboard::KeyCode keyCode, Event* event);

	/*键盘事件处理，按下C键打开NPC交互界面*/
	void KeyPressedForNPCInteract(EventKeyboard::KeyCode keyCode, Event* event);

	/*鼠标事件处理，滚动滚轮控制地图缩放*/
	void MouseScrollForCameraZoom(EventMouse* event, Camera* camera, float MaxHeight, float MinHeight, float ScrollSpeed);

	/*键盘事件处理，按下方向键控制小地图方向*/
	void KeyPressedForMicroMapMove(EventKeyboard::KeyCode keyCode, Event* event, Camera* camera, float MaxHeight, float MinHeight, float MaxWidth, float MinWidth, float ScrollSpeed);

	CREATE_FUNC(SetMap);
};

#endif // __SET_MAP_H__