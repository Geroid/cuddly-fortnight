//
//  Player.hpp
//  BattleGame
//
//  Created by Viktor Rezvantsev on 16.05.2021.
//

#ifndef Player_hpp
#define Player_hpp

#include <cocos2d.h>

class Player : public cocos2d::Sprite {
public:
    static cocos2d::Sprite* createSprite();
    float health;
    virtual bool init() override;
    CREATE_FUNC(Player);

    virtual void update(float) override;
    void fire();
private:
    float fireRate;
    float fireTimer;
    void initControls();
    cocos2d::Vector<cocos2d::Sprite*> bullets;
    bool moveTo(cocos2d::Touch *touch, cocos2d::Event *event);
    bool endMove(cocos2d::Touch *touch, cocos2d::Event *event);
    bool keyboardMoveTo(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    bool keyboardEndMove(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};

#endif /* Player_hpp */
