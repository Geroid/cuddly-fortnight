//
//  Meteor.hpp
//  BattleGame
//
//  Created by Viktor Rezvancev on 25.05.2021.
//

#ifndef Meteor_hpp
#define Meteor_hpp

#include <cocos2d.h>

class Meteor: public cocos2d::Sprite
{
public:
    static cocos2d::Sprite* createSprite();
    virtual bool init() override;
    CREATE_FUNC(Meteor);
    void spawn();
    void despawn();
    void hurt();
    virtual void update(float) override;
    
private:
    int health;
    bool initMovement();
};

#endif /* Meteor_hpp */
