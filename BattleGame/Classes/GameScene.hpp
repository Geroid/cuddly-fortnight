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
    cocos2d::Sprite* enemy;
private:
    cocos2d::Vector<cocos2d::Sprite*> enemies;
    float timerEnemySpawn;
    float timerMeteor;
    void spawnPlayer();
    void initBackground();
    void spawnEnemy();
    void spawnMeteor();
    void gameOver();
    void despawnEnemy(cocos2d::Sprite* enemy);
    void showGameOverScene();
    bool onContactBegin(cocos2d::PhysicsContact & contact);
};

#endif /* GameScene_hpp */
