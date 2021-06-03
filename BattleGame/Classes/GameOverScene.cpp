//
//  GameOverScene.cpp
//  BattleGame
//
//  Created by Viktor Rezvantsev on 16.05.2021.
//

#include "GameOverScene.hpp"
#include "GameScene.hpp"
USING_NS_CC;

Scene *GameOverScene::createScene() {
    return GameOverScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}


bool GameOverScene::init() {
    if (!Scene::init()) {
        return false;
    }
    
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();

    auto label = createGameOverLabel();
    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 2 + label->getContentSize().height;
    label->setPosition(Vec2(x, y));
    this->addChild(label);
    
    auto button = createRetryButton();
    float updatedY = origin.y + visibleSize.height / 2 - button->getContentSize().height;
    button->setPosition(Vec2(x, updatedY));
    this->addChild(button);
    log("Initialize Game Over Scene");
    
    return true;
}

Label* GameOverScene::createGameOverLabel() {
    
    // create a TTFConfig
    TTFConfig labelConfig;
    labelConfig.fontFilePath = "fonts/Marker Felt.ttf";
    labelConfig.fontSize = 24;
    std::string text = "Game Over";
    auto color = Color3B(255, 0, 0);
    auto gameOverLabel = Label::createWithTTF(labelConfig, text);
    gameOverLabel->setColor(color);
   
    return gameOverLabel;
}

cocos2d::ui::Button* GameOverScene::createRetryButton() {
    auto retryButton = cocos2d::ui::Button::create();
    std::string text = "Retry";
    retryButton->setTitleText(text);
    retryButton->setTitleFontName("fonts/Marker Felt.ttf");
    retryButton->setTitleFontSize(24);
    
    
    retryButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                retryButtonCallback(sender);
            default:
                break;
        }
    });
    
    return retryButton;
}

void GameOverScene::retryButtonCallback(cocos2d::Ref *pSender) {
    auto director = Director::getInstance();
    auto gameScene = Game::createScene();
    director->replaceScene(gameScene);
}
