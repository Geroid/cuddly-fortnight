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
    
    this->setScale(0.3);
    auto size = this->getContentSize();
    auto physicsBody = PhysicsBody::createBox(Size(size.width, size.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setDynamic(true);
    physicsBody->setCategoryBitmask(0x1);
    physicsBody->setContactTestBitmask(0x2);
    
    this->addComponent(physicsBody);
    
    this->setRotation(180);
    this->initMovement();
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
    bullet->setPosition(Vec2(enemyPosition.x,enemyPosition.y-bulletPadding));
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
    this->health -= 50;
}
