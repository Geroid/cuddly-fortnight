//
//  Enemy.cpp
//  BattleGame
//
//  Created by Viktor Rezvantsev on 16.05.2021.
//

#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Definitions.h"

USING_NS_CC;

static const float _animationTime = 0.5f;
static const float _delay = 0.1f;

Sprite* Enemy::createSprite() {
    return Enemy::create();
}

bool Enemy::init() {

    if(!Sprite::init()) {
        return false;
    }
    this->health = 100;
    this->fireRate = 2;
    this->fireTimer = 0;
    this->setTexture("enemy.png");
    
    //poolbullets
    for (int i = 0; i < 20; i++) {
        auto bullet = Bullet::createSprite();
        bullet->setVisible(false);
        auto name = "bullet" + std::to_string(i);
        bullet->setName(name);
        this->bullets.pushBack(bullet);
    }
    
    auto size = this->getContentSize();
    this->setTag(BULLET_TAG);
    auto physicsBody = PhysicsBody::createBox(size, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
    physicsBody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
    physicsBody->setContactTestBitmask(true);
    this->setPhysicsBody(physicsBody);
    
    this->setScale(0.3);
    this->setRotation(180);
    this->initMovement();
    
    return true;
}

bool Enemy::initMovement() {
    
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    auto position = this->getPosition();
    auto size = this->getBoundingBox().size;

    // swing left to right
    auto moveLeft = MoveBy::create(1, Vec2(-size.width,0));
    auto moveRight = MoveBy::create(2, Vec2(size.width*2,0));
    
    auto swingSequence = Sequence::create(moveLeft, moveRight, moveLeft, nullptr);
    auto intervalSwing = RepeatForever::create(swingSequence);
    this->runAction(intervalSwing);
    
    return true;
}

void Enemy::update(float delta) {
    fireTimer += delta*1000;
    if(fireTimer >= 1000 / fireRate) {
        fireTimer = 0;
        fire();
    }}

void Enemy::spawn() {
    this->setVisible(true);
    // Init movement
}

void Enemy::despawn() {
    if (this->health == 0) {
        this->setVisible(false);
        this->stopAllActions();
        this->removeFromParent();
    }
}

void Enemy::fire() {
    Sprite* bullet;
    
    //find bullet to fire from pool
    for (auto & elem : this->bullets) {
        if (!elem->isVisible()) {
            bullet = elem;
            break;
        }
    }
    if (bullet == nullptr) {
        log("No bullets left :(");
        return;
    }
    
    //spawn bullet from the pool
    bullet->setVisible(true);
    auto enemyPosition = this->getPosition();
    this->getParent()->addChild(bullet);
    
    //calculate bullet padding
    auto bulletPadding = (this->getBoundingBox().size.height / 2) + (bullet->getBoundingBox().size.height / 2);
    bullet->setPosition(Vec2(enemyPosition.x,enemyPosition.y- (2 * bulletPadding)));
    
    //make sure bullets go out of screen
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    
    auto moveBy = MoveBy::create(1, Vec2(0, origin.y-visibleSize.height));
    auto callbackMoveBy = CallFunc::create([bullet]() {
        
        //return used bullet to pool
        bullet->setVisible(false);
        bullet->removeFromParent();
    });
    auto sequence = Sequence::create(moveBy, callbackMoveBy, nullptr);
    bullet->runAction(sequence);
}

void Enemy::hurt() {
    if (health > 0) {
        this->health -= 50;
    }
}
