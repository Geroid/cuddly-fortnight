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
#include "Meteor.hpp"
#include "Definitions.h"
#include "ccRandom.h"
USING_NS_CC;

static const float _delay = 5.0f;


Scene* Game::createScene() {
    auto scene = Scene::createWithPhysics();
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto layer = Game::create();
    scene->addChild(layer);
    return scene;
}

bool Game::init() {
    if (!Scene::initWithPhysics()) {
        log("Error create scene with physics");
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
    // world boundaries
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 6);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);
    this->timerEnemySpawn = 0;
    this->timerMeteor = 0;

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
    Size visibleSize = Director::getInstance()->getVisibleSize();
   
    timerMeteor += delta*1000;
    if (timerMeteor > 2000) {
        timerMeteor = 0;
        spawnMeteor();
    }
    timerEnemySpawn += delta*1000;
    if (timerEnemySpawn > 4000) {
            timerEnemySpawn = 0;
            spawnEnemy();
    }
}

void Game::spawnPlayer() {
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    this->player = Player::createSprite();
    this->player->setPosition(origin.x+(visibleSize.width/2), origin.y+this->player->getBoundingBox().size.height/2);
    this->addChild(this->player, 0);
}

void Game::spawnEnemy() {
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    this->enemy = Enemy::createSprite();
    auto posX = (rand() % static_cast<int>(visibleSize.width)) + (enemy->getContentSize().width / 2);
    this->enemy->setPosition(posX, origin.y+visibleSize.height - this->enemy->getBoundingBox().size.height);
    this->addChild(this->enemy, 0);
}

void Game::spawnMeteor() {
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    auto meteor = Meteor::create();
    auto posX = (rand() % static_cast<int>(visibleSize.width)) + (meteor->getContentSize().width / 2);
    auto posY = origin.y+visibleSize.height - meteor->getBoundingBox().size.height;
    meteor->setPosition(posX, posY);
    this->addChild(meteor);
    
}

void Game::initBackground() {
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    auto background = (Background *)Background::createSprite();
    auto pos = Vec2(origin.x, origin.y);
    background->setPosition(pos);
    this->addChild(background, -1);
}

void Game::despawnEnemy(Sprite* enemy) {
    auto e = (Enemy*)enemy;
//    enemyPool.pushBack(e);
//    spawnedEnemies.eraseObject(e);
    e->despawn();
}

void Game::gameOver() {
    auto player = (Player*)this->player;
    if (player->getHealth() == 0) {
        player->die();
        showGameOverScene();
    }
}

void Game::showGameOverScene() {
    auto director = Director::getInstance();
    auto gameOverScene = GameOverScene::createScene();
    director->replaceScene(gameOverScene);
}


bool Game::onContactBegin(cocos2d::PhysicsContact &contact) {

    PhysicsBody* A = contact.getShapeA()->getBody();
    PhysicsBody* B = contact.getShapeB()->getBody();
    
    log("Contact");
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    //bullet hits enemy
    if ((A->getCollisionBitmask() == BULLET_COLLISION_BITMASK && B->getCollisionBitmask() == ENEMY_COLLISION_BITMASK)) {
        auto bullet = A->getNode();
        auto enemy = (Enemy*)B->getNode();
        log("bullet hits enemy");
        enemy->hurt();
        this->despawnEnemy(enemy);
        bullet->setVisible(false);
        bullet->removeFromParent();
    }
    //enemy hits bullet ?!
    else if ((B->getCollisionBitmask() == BULLET_COLLISION_BITMASK && A->getCollisionBitmask() == ENEMY_COLLISION_BITMASK)) {
        auto enemy = (Enemy*)A->getNode();
        auto bullet = B->getNode();
        enemy->hurt();
        log("enemy hits bullet");
        this->despawnEnemy(enemy);
        bullet->setVisible(false);
        bullet->removeFromParent();
    }
    if ((A->getCollisionBitmask() == BULLET_COLLISION_BITMASK && B->getCollisionBitmask() == PLAYER_COLLISION_BITMASK)) {
        auto bullet = nodeA;
        auto player = (Player*)nodeB;
        player->hurt();
        this->gameOver();
        bullet->setVisible(false);
        bullet->removeFromParent();
    } else if ((B->getCollisionBitmask() == BULLET_COLLISION_BITMASK && A->getCollisionBitmask() == PLAYER_COLLISION_BITMASK)) {
        auto bullet = nodeB;
        auto player = (Player*)nodeA;
        player->hurt();
        this->gameOver();
        bullet->setVisible(false);
        bullet->removeFromParent();
    }
    else if (A->getCollisionBitmask() == METEOR_COLLISION_BITMASK && B->getCollisionBitmask() == PLAYER_COLLISION_BITMASK) {
        auto meteor = (Meteor*)nodeA;
        auto player = (Player*)nodeB;
        player->hurt();
        this->gameOver();
        meteor->setVisible(false);
        meteor->removeFromParent();
    } else if (B->getCollisionBitmask() == METEOR_COLLISION_BITMASK && A->getCollisionBitmask() == PLAYER_COLLISION_BITMASK) {
        auto meteor = (Meteor*)nodeB;
        auto player = (Player*)nodeA;
        player->hurt();
        this->gameOver();
        meteor->setVisible(false);
        meteor->removeFromParent();
    }
    else if (A->getCollisionBitmask() == METEOR_COLLISION_BITMASK && B->getCollisionBitmask() == BULLET_COLLISION_BITMASK) {
        auto meteor = (Meteor*)nodeA;
        auto bullet = nodeB;

        meteor->setVisible(false);
        meteor->removeFromParent();
    } else if (B->getCollisionBitmask() == METEOR_COLLISION_BITMASK && A->getCollisionBitmask() == BULLET_COLLISION_BITMASK) {
        auto meteor = (Meteor*)nodeB;
        auto bullet = nodeA;
        meteor->setVisible(false);
        meteor->removeFromParent();
    }
    //enemy hits limit
//    else if ((A->getCategoryBitmask() == 0x1 && B->getCategoryBitmask() == 0x3) ||
//             A->getCategoryBitmask()== 0x3 && B->getCategoryBitmask()== 0x1) {
//        //            this->endGame();
//    }
    
    return true;
}

