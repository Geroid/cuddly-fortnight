//
//  Enemy.hpp
//  BattleGame
//
//  Created by Viktor Rezvantsev on 16.05.2021.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <cocos2d.h>

class Enemy: public cocos2d::Sprite
{
public:
    static cocos2d::Sprite* createSprite();
    virtual bool init() override;
    CREATE_FUNC(Enemy);
    void spawn();
    void despawn();
    void fire();
    void hurt();
    void spawnEnemyByType(int type);
    virtual void update(float) override;
    
private:
    int type;
    int health;
    int fireRate;
    float fireTimer;
    bool initMovement();
    cocos2d::Vector<cocos2d::Sprite*> bullets;
};

#endif /* Enemy_hpp */
