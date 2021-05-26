//
//  Enemy.cpp
//  BattleGame
//
//  Created by Viktor Rezvantsev on 16.05.2021.
//

#include "Enemy.hpp"
#include "Bullet.hpp"
USING_NS_CC;

static const float _animationTime = 0.5f;
static const float _delay = 5.0f;

Sprite* Enemy::createSprite() {
    return Enemy::create();
}

bool Enemy::init() {

    if(!Sprite::init()) {
        return false;
    }
    this->health = 100;
    this->fireRate = 2;
    this->setTexture("enemy.png");
    auto size = this->getContentSize();
    auto physicsBody = PhysicsBody::createBox(size, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setCategoryBitmask(0x1);
    physicsBody->setContactTestBitmask(0x2);
    physicsBody->setDynamic(false);
    this->addComponent(physicsBody);
    this->setScale(0.3);
    this->setRotation(180);
    
    //update loop
    this->scheduleUpdate();
    
    return true;
}

bool Enemy::initMovement() {
    
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    auto position = this->getPosition();
    auto size = this->getBoundingBox().size;
//    auto moveByY = (origin.y - size.height / 2) - position.y;
    
    // move down
    auto moveDown = MoveBy::create(_animationTime, Vec2(0, -size.height * 2));
    auto delay = DelayTime::create(_delay);
    auto sequenceDown = Sequence::create(moveDown, delay, nullptr);
    
    // swing left to right
    auto moveLeft = MoveBy::create(1, Vec2(-size.width,0));
    auto moveRight = MoveBy::create(2, Vec2(size.width*2,0));
    
    auto swingSequence = Sequence::create(moveLeft, moveRight, moveLeft, nullptr);
        
    auto intervalAction = RepeatForever::create(sequenceDown);
    auto intervalSwing = RepeatForever::create(swingSequence);
    
    this->runAction(intervalAction);
    this->runAction(intervalSwing);
    
    return true;
}

void Enemy::spawn() {
    this->setVisible(true);
    // Init movement
}

void Enemy::despawn() {
    this->setVisible(false);
    this->stopAllActions();
    this->removeFromParent();
}

void Enemy::fire() {
    
}

void Enemy::hurt() {
    this->health -= 50;
}
