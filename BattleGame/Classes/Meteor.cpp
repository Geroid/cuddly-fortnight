//
//  Meteor.cpp
//  BattleGame
//
//  Created by Viktor Rezvancev on 25.05.2021.
//

#include "Meteor.hpp"
#include "Definitions.h"
USING_NS_CC;

static const float _animationTime = 0.5f;

Sprite* Meteor::createSprite() {
    return Meteor::create();
}

bool Meteor::init() {

    if(!Sprite::init()) {
        return false;
    }
    
    this->health = 50;
    this->setTexture("meteorSmall.png");
    
    
    auto size = this->getContentSize();
    this->setTag(BULLET_TAG);
    auto physicsBody = PhysicsBody::createBox(size, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(METEOR_CATEGORY_BITMASK);
    physicsBody->setCollisionBitmask(METEOR_COLLISION_BITMASK);
    physicsBody->setContactTestBitmask(true);
    this->setPhysicsBody(physicsBody);
    
//    this->setScale(0.3);
    this->setRotation(180);
    this->initMovement();
    
    return true;
}

bool Meteor::initMovement() {
    
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    auto position = this->getPosition();
    auto size = this->getBoundingBox().size;
    
    //     move down
    auto moveDown = MoveBy::create(_animationTime, Vec2(0, -size.height * 2));
    auto sequenceDown = Sequence::create(moveDown, nullptr, nullptr);
    auto intervalAction = RepeatForever::create(sequenceDown);
    this->runAction(intervalAction);
    
    return true;
}

void Meteor::update(float delta) {
    
}

void Meteor::spawn() {
    this->setVisible(true);
    // Init movement
}

void Meteor::despawn() {
    if (this->health == 0) {
        this->setVisible(false);
        this->stopAllActions();
        this->removeFromParent();
    }
}

void Meteor::hurt() {
    this->health -= 50;
}
