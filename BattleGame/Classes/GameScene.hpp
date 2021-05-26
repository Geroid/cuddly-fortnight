//
//  GameScene.hpp
//  BattleGame
//
//  Created by Viktor Rezvantsev on 16.05.2021.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <cocos2d.h>

class Game: public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(Game);
    void update(float) override;

    cocos2d::Sprite* player;
private:
    void spawnPlayer();
    void initBackground();
    void spawnEnemy(int amount);
};

#endif /* GameScene_hpp */