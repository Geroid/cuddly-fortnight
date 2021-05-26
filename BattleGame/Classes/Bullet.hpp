//
//  Bullet.hpp
//  BattleGame
//
//  Created by Viktor Rezvantsev on 24.05.2021.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <cocos2d.h>

class Bullet: cocos2d::Sprite {
public:
    static cocos2d::Sprite* createSprite();
    virtual bool init() override;
    CREATE_FUNC(Bullet);

    int damage;
};

#endif /* Bullet_hpp */
