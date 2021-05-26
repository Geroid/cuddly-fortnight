//
//  Bullet.cpp
//  BattleGame
//
//  Created by Viktor Rezvantsev on 24.05.2021.
//

#include "Bullet.hpp"

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
    auto rect = this->getTextureRect();

    auto physicsBody = PhysicsBody::createBox(rect.size, PhysicsMaterial(0.1f, 1.0f,0.0f));
    physicsBody->setCategoryBitmask(0x2);
    physicsBody->setContactTestBitmask(0x1);
    physicsBody->setDynamic(false);
    this->addComponent(physicsBody);
    
    return true;
}
