//
//  Bullet.cpp
//  BattleGame
//
//  Created by Viktor Rezvantsev on 24.05.2021.
//

#include "Bullet.hpp"
#include "Definitions.h"

USING_NS_CC;

Sprite* Bullet::createSprite() {
    return Bullet::create();
}

bool Bullet::init() {
    if (!Sprite::init()) {
        log("Error load bullet");
        return false;
    }
    this->damage = 50;
    this->setTexture("laserGreen.png");
//    auto rect = this->getTextureRect();
    auto size = this->getContentSize();
    auto physicsBody = PhysicsBody::createBox(size, PhysicsMaterial(0.1f, 1.0f,0.0f));
    physicsBody->setCategoryBitmask(BULLET_CATEGORY_BITMASK);
    physicsBody->setCollisionBitmask(BULLET_COLLISION_BITMASK);
    physicsBody->setContactTestBitmask(true);
    physicsBody->setDynamic(false);
    this->setPhysicsBody(physicsBody);

    return true;
}
