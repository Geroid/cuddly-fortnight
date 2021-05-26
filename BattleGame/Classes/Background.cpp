//
//  Background.cpp
//  BattleGame
//
//  Created by Viktor Rezvantsev on 24.05.2021.
//

#include "Background.hpp"

USING_NS_CC;

Sprite* Background::createSprite() {
    return Background::create();
}


bool Background::init() {
    if (!Sprite::init()) {
        return false;
    }
//    _backgroundNode = ParallaxNode::create();
//    this->addChild(_backgroundNode);


//    _backgroundColor = Sprite::create("backgroundColor.png");
//    _backgroundNode->addChild(_backgroundColor, -1, Vec2(0.0f, 0.5f), Vec2::ZERO);
    this->setTexture("backgroundColor.png");
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    auto imageSize = getContentSize();
    Vec2 origin = director->getVisibleOrigin();
    setAnchorPoint(Vec2(0,0));
    setScaleX(visibleSize.width / imageSize.width);
    setScaleY(visibleSize.height / imageSize.height);

    return true;
}


