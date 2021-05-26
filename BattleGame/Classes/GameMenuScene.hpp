//
//  GameMenuScene.hpp
//  BattleGame
//
//  Created by Viktor Rezvantsev on 16.05.2021.
//

#ifndef GameMenuScene_hpp
#define GameMenuScene_hpp

#include <stdio.h>

#include <cocos2d.h>

class MainMenu: public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(MainMenu);

    void update(float) override;
    void menuCallback(cocos2d::Ref* pSender);
};

#endif /* GameMenuScene_hpp */
