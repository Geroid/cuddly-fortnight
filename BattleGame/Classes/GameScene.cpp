//
//  GameScene.cpp
//  BattleGame
//
//  Created by Viktor Rezvantsev on 16.05.2021.
//

#include "GameScene.hpp"
#include "GameOverScene.hpp"
#include "Player.hpp"
#include "Background.hpp"
#include "Enemy.hpp"
USING_NS_CC;

Scene* Game::createScene() {
    return Game::create();
}

bool Game::init() {
    if (!Scene::initWithPhysics()) {
        return false;
    }

    this->initBackground();
    this->spawnPlayer();

    log("Game Scene -- Successfully initialize");
    return true;
}

void Game::update(float delta) {
    
}

void Game::spawnPlayer() {
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    this->player = Player::createSprite();
    this->player->setPosition(origin.x+(visibleSize.width/2), origin.y+this->player->getBoundingBox().size.height/2);
    this->addChild(this->player);
}

void Game::initBackground() {
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    auto background = (Background *)Background::createSprite();
    auto pos = Vec2(origin.x, origin.y);
    background->setPosition(pos);
    this->addChild(background);
}
