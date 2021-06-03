//
//  GameMenuScene.cpp
//  BattleGame
//
//  Created by Viktor Rezvantsev on 16.05.2021.
//

#include "GameMenuScene.hpp"
#include "GameScene.hpp"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* MainMenu::createScene() {
    return MainMenu::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}

bool MainMenu::init() {
    if (!Scene::init()) {
        return false;
    }

    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();

    auto playButton = cocos2d::ui::Button::create("", "", "");
    playButton->setTitleFontSize(24);
    playButton->setTitleText("Play");
    float x = origin.x + visibleSize.width / 2 - playButton->getContentSize().width / 2;
    float y = origin.y + visibleSize.height / 2 - playButton->getContentSize().height / 2;
    playButton->setPosition(Vec2(x, y));

    playButton->addTouchEventListener([&] (Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                menuCallback(sender);
            default:
                break;
        }
    });
    this->addChild(playButton);

    log("Game Menu -- Succesfully initialize");

    return true;
}

void MainMenu::menuCallback(Ref* sender) {
    auto director = Director::getInstance();
    auto gameScene = Game::createScene();
    director->replaceScene(gameScene);
}

void MainMenu::update(float delta) {

}
