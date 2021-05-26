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
    this->spawnEnemy();
    
    
    // contact event
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Game::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    this->scheduleUpdate();

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

void Game::spawnEnemy() {
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    this->enemy = Enemy::createSprite();
    this->enemy->setPosition(origin.x+(visibleSize.width/2), origin.y+visibleSize.height - this->enemy->getBoundingBox().size.height);
    this->addChild(this->enemy);
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

void Game::despawnEnemy(Sprite* enemy) {
    auto e = (Enemy*)enemy;
//    enemyPool.pushBack(e);
//    spawnedEnemies.eraseObject(e);
    e->despawn();
}


bool Game::onContactBegin(cocos2d::PhysicsContact &contact) {
    PhysicsBody* A = contact.getShapeA()->getBody();
    PhysicsBody* B = contact.getShapeB()->getBody();
    
    //bullet hits enemy
    if (A->getCategoryBitmask() == 0x2 && B->getCategoryBitmask() == 0x1) {
        auto bullet = A->getNode();
        auto enemy = (Enemy*)B->getNode();
        enemy->hurt();
        this->despawnEnemy(enemy);
        bullet->setVisible(false);
        bullet->removeFromParent();
    }
    //enemy hits bullet ?!
    else if (A->getCategoryBitmask() == 0x1 && B->getCategoryBitmask() == 0x2) {
        auto enemy = (Enemy*)A->getNode();
        auto bullet = B->getNode();
        enemy->hurt();
        this->despawnEnemy(enemy);
        bullet->setVisible(false);
        bullet->removeFromParent();
    }
    //enemy hits limit
    else if ((A->getCategoryBitmask() == 0x1 && B->getCategoryBitmask() == 0x3) ||
             A->getCategoryBitmask()== 0x3 && B->getCategoryBitmask()== 0x1) {
        //            this->endGame();
    }
    
    return true;
}

