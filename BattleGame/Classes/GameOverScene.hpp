//
//  GameOverScene.hpp
//  BattleGame
//
//  Created by Viktor Rezvantsev on 16.05.2021.
//

#ifndef GameOverScene_hpp
#define GameOverScene_hpp

#include <cocos2d.h>
#include "ui/CocosGUI.h"

class GameOverScene: public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(GameOverScene);
    
private:
    cocos2d::Label* createGameOverLabel();
    cocos2d::ui::Button* createRetryButton();
    void retryButtonCallback(cocos2d::Ref* pSender);
};

#endif /* GameOverScene_hpp */
