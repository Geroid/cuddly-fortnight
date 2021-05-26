//
//  Player.cpp
//  BattleGame
//
//  Created by Viktor Rezvantsev on 16.05.2021.
//

#include "Player.hpp"
#include "Bullet.hpp"
USING_NS_CC;

Sprite* Player::createSprite() {
    return Player::create();
}

bool Player::init() {
    if(!Sprite::init()) {
        return false;
    }

    this->setName("Player");
    this->setTexture("player.png");
    this->health = 3;
    this->fireTimer = 0;
    this->fireRate = 3;

    //pool of bullets
    for (int i = 0; i < 20; i++) {
        auto bullet = Bullet::createSprite();
        bullet->setVisible(false);
        auto name = "bullet" + std::to_string(i);
        bullet->setName(name);
        this->bullets.pushBack(bullet);
    }
    
    initControls();
    
    //update loop
    this->scheduleUpdate();

    log("Player -- successfully initialize");
    return true;
}

void Player::update(float delta) {
    fireTimer += delta*1000;
    if(fireTimer >= 1000 / fireRate) {
        fireTimer = 0;
        fire();
    }
}

void Player::fire() {
    Sprite * bullet;
    
    for (auto & elem: this->bullets) {
        if (!elem->isVisible()) {
            bullet = elem;
            break;
        }
    }
    if (bullet == nullptr) {
        log("No bullets left");
        return;
    }
    
    //spawn bullet from the pool
    bullet->setVisible(true);
    auto playerPos = this->getPosition();
    this->getParent()->addChild(bullet);
    
    //calculate bullet padding
    auto bulletPadding = (this->getBoundingBox().size.height / 2) + (bullet->getBoundingBox().size.height / 2);
    bullet->setPosition(Vec2(playerPos.x,playerPos.y+bulletPadding));
    
    //make sure bullets go out of screen
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    
    auto moveBy = MoveBy::create(1, Vec2(0, origin.y+visibleSize.height));
    auto callbackMoveBy = CallFunc::create([bullet]() {
        //return used bullet to pool
        bullet->setVisible(false);
        bullet->removeFromParent();
    });
    auto sequence = Sequence::create(moveBy, callbackMoveBy, nullptr);
    bullet->runAction(sequence);
}

void Player::initControls() {
    auto director = Director::getInstance();
    auto eventDispatcher = director->getEventDispatcher();
    
    // Control player via keyboard
    
    auto keyboardListener = EventListenerKeyboard::create();

    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::keyboardMoveTo, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::keyboardEndMove, this);
    
    eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // Work with touches and control player
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(Player::moveTo, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Player::endMove, this);
    
    eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

// --------------------------------------
// Use keyboard to control player ship
// --------------------------------------

bool Player::keyboardMoveTo(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
    
    auto moveSpeed = 250;
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    
    // calculate left and right touch area
    auto leftBoundary = (origin.x + visibleSize.width)*0.3f;
    auto rightBoundary = (origin.x + visibleSize.width)*0.7f;
    
    // calculate left and right limits player can move
    auto leftLimit = origin.x + getBoundingBox().size.width / 2;
    auto rightLimit = origin.x + visibleSize.width - getBoundingBox().size.width / 2;

    auto position = getPosition();
    
    // Move to left
    if(keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A ) {
        log("Key with keycode %d pressed", keyCode);
        auto time = abs(leftLimit - position.x) / moveSpeed;
        this->setTexture("playerLeft.png");
        auto moveTo = MoveTo::create(time, Vec2(leftLimit, position.y));
        
        runAction(moveTo);
    }
    
    // Move to right
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D) {
        log("Key with keycode %d pressed", keyCode);
        auto time = abs(rightLimit - position.x) / moveSpeed;
        this->setTexture("playerRight.png");
        auto moveTo = MoveTo::create(time, Vec2(rightLimit, position.y));
        runAction(moveTo);
    }
    return true;
}

bool Player::keyboardEndMove(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
    stopAllActions();
    this->setTexture("player.png");
    return true;
}

// ----------------
// Use touches to control player ship,
// but now hasn't been used
// ----------------

bool Player::moveTo(cocos2d::Touch *touch, cocos2d::Event *event) {
    auto moveSpeed = 250;
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    auto location = touch->getLocation();

    // calculate left and right touch area
    auto leftBoundary = (origin.x + visibleSize.width)*0.3f;
    auto rightBoundary = (origin.x + visibleSize.width)*0.7f;
    
    // calculate left and right limits player can move
    auto leftLimit = origin.x + getBoundingBox().size.width / 2;
    auto rightLimit = origin.x + visibleSize.width - getBoundingBox().size.width / 2;

    auto position = this->getPosition();

    // move to right
    if (location.x >= rightBoundary) {
        auto time = abs(rightLimit - position.x) / moveSpeed;
        auto moveTo = MoveTo::create(time, Vec2(rightLimit, position.y));
        runAction(moveTo);
    }
    // move to left
    else if (location.x <= leftBoundary) {
        auto time = abs(leftLimit - position.x) / moveSpeed;
        auto moveTo = MoveTo::create(time, Vec2(leftLimit, position.y));
        runAction(moveTo);
    }
    return true;
}

bool Player::endMove(cocos2d::Touch *touch, cocos2d::Event *event) {
    stopAllActions();
    return true;
}
