#include <iostream>
#include "NPC.h"

/* 交互提示 */
void NPC::update(float dt) {
	CCLOG("update is being called");
	if (isTrigger()) {
		triggerTip();  // 玩家进入触发范围
	}
	else {
		trggerTipRemove();   // 玩家离开触发范围
	}
}

/* 判断是否在触发范围内 */
bool NPC::isTrigger() {
	if (who == nullptr)
		return false;

	int dx = who->mySprite->getPosition().x - x;
	int dy = who->mySprite->getPosition().y - y;

	return std::pow(dx, 2) + std::pow(dy, 2) <= std::pow(DIST, 2);
}

/* 与NPC交互 */
void NPC::Chat() {
	/* 判断是否在触发范围内 */
	if (!this->isTrigger())
		return;

    /* 加入对话框chatPanel */
    auto winSize = Director::getInstance()->getWinSize();
    Vec2 where = Vec2(winSize.width / 2, winSize.height - 1100);
    auto chatPanel = Sprite::create("UI/Panel5.png");
    chatPanel->setContentSize(Size(1800, 350));
    chatPanel->setPosition(where); 
	chatPanel->setOpacity(200);
    scene->addChild(chatPanel, 2);

	/* 加入npc */
	auto npcSprite = Sprite::create("Role/" + role + "/1.png");
	npcSprite->setPosition(Vec2(winSize.width / 2 - 430, winSize.height - 1000));
	npcSprite->setScale(2.0);
	scene->addChild(npcSprite, 3);

	/* 根据npc创建互动 */
	std::unordered_map<std::string, int> stringMap = {
		{"npc0", 0},
		{"npc1", 1},
		{"npc2", 2},
		{"npc3", 3}
	};

	switch (stringMap[role]) {
	case 0:
		npc0([=]() {
			//当 npc0的对话逻辑完成后，移除UI
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			log("npc0-chat over.");
			});
		break;
	case 1:
		npc1([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			log("npc1-chat over.");
			});
		break;
	case 2:
		npc2([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			log("npc1-chat over.");
			});
		break;
	case 3:
		
		break;
	default:
		
		break;
	}

}

void  NPC::npc0(std::function<void()> callback) {
	auto winSize = Director::getInstance()->getWinSize();

	/* npc说话-1 */
	auto npcTxt1 = Label::createWithTTF("Hello! Welcome to this new world!", "fonts/Lacquer.ttf", 35);
	npcTxt1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1000));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 4);

	/* player回答选择1 */
	auto playerAns1 = Label::createWithTTF("Nice to meet you!", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
	playerAns1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns1, 4);
	/* player回答选择2 */
	auto playerAns2 = Label::createWithTTF("I like this world.", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns2->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1160));
	playerAns2->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns2, 4);

	/* player回答选择1提交按钮 */
	auto Ans1Button = ui::Button::create("Button/Choice1Button.png", "Button/Choice1ButtonClicked.png");
	Ans1Button->ignoreContentAdaptWithSize(false);
	Ans1Button->setContentSize(Size(40, 40));
	Ans1Button->setTitleFontSize(24);
	Ans1Button->setPosition(Vec2(winSize.width / 2 - 200, winSize.height - 1080));
	scene->addChild(Ans1Button, 4);
	/* player回答选择2提交按钮 */
	auto Ans2Button = ui::Button::create("Button/Choice2Button.png", "Button/Choice2ButtonClicked.png");
	Ans2Button->ignoreContentAdaptWithSize(false);
	Ans2Button->setContentSize(Size(40, 40));
	Ans2Button->setTitleFontSize(24);
	Ans2Button->setPosition(Vec2(winSize.width / 2 - 200, winSize.height - 1160));
	scene->addChild(Ans2Button, 4);

	/* 回答选择1 */
	Ans1Button->addClickEventListener([=](Ref* sender) mutable {
		// 移除第一次问答的元素
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc说话-2-choice1 */
		auto npcTxt2_1 = Label::createWithTTF("Nice to meet you too!", "fonts/Lacquer.ttf", 35);
		npcTxt2_1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
		npcTxt2_1->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_1, 4);
		/* 结束对话 */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1150));
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt2_1->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});

		});
	/* 回答选择2 */
	Ans2Button->addClickEventListener([=](Ref* sender) mutable {
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc说话-2-choice2 */
		auto npcTxt2_2 = Label::createWithTTF("Enjoy yourself here!", "fonts/Lacquer.ttf", 35);
		npcTxt2_2->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
		npcTxt2_2->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_2, 4);
		/* 结束对话 */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1150));
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt2_2->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});
		});
}

void NPC::npc1(std::function<void()> callback) {
	auto winSize = Director::getInstance()->getWinSize();

	/* npc说话-1 */
	auto npcTxt1 = Label::createWithTTF("This is npc1 speaking 1", "fonts/Lacquer.ttf", 35);
	npcTxt1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1000));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1,4);

	/* player回答选择1 */
	auto playerAns1 = Label::createWithTTF("This is player's answer 1", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
	playerAns1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns1, 4);
	/* player回答选择2 */
	auto playerAns2 = Label::createWithTTF("This is player's answer 2", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns2->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1160));
	playerAns2->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns2, 4);

	/* player回答选择1提交按钮 */
	auto Ans1Button = ui::Button::create("Button/Choice1Button.png", "Button/Choice1ButtonClicked.png");
	Ans1Button->ignoreContentAdaptWithSize(false);
	Ans1Button->setContentSize(Size(40, 40));
	Ans1Button->setTitleFontSize(24);
	Ans1Button->setPosition(Vec2(winSize.width / 2 - 200, winSize.height - 1080));
	scene->addChild(Ans1Button,4);
	/* player回答选择2提交按钮 */
	auto Ans2Button = ui::Button::create("Button/Choice2Button.png", "Button/Choice2ButtonClicked.png");
	Ans2Button->ignoreContentAdaptWithSize(false);
	Ans2Button->setContentSize(Size(40, 40));
	Ans2Button->setTitleFontSize(24);
	Ans2Button->setPosition(Vec2(winSize.width / 2 - 200, winSize.height - 1160));
	scene->addChild(Ans2Button, 4);

	/* 回答选择1 */
	Ans1Button->addClickEventListener([=](Ref* sender) mutable {
		// 移除第一次问答的元素
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc说话-2-choice1 */
		auto npcTxt2_1 = Label::createWithTTF("This is npc1 speaking 2-1", "fonts/Lacquer.ttf", 35);
		npcTxt2_1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
		npcTxt2_1->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_1, 4);
		/* 结束对话 */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1150));
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable{
			npcTxt2_1->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});

		});
	/* 回答选择2 */
	Ans2Button->addClickEventListener([=](Ref* sender) mutable {
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc说话-2-choice2 */
		auto npcTxt2_2 = Label::createWithTTF("This is npc1 speaking 2-2", "fonts/Lacquer.ttf", 35);
		npcTxt2_2->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
		npcTxt2_2->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_2, 4);
		/* 结束对话 */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1150));
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt2_2->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});

		});
}

void NPC::npc2(std::function<void()> callback) {
	auto winSize = Director::getInstance()->getWinSize();

	/* npc说话-1 */
	auto npcTxt1 = Label::createWithTTF("This is npc1 speaking 1", "fonts/Lacquer.ttf", 35);
	npcTxt1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1000));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 4);


}
