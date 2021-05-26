//
//  Background.hpp
//  BattleGame
//
//  Created by Viktor Rezvantsev on 24.05.2021.
//

#ifndef Background_hpp
#define Background_hpp

#include <cocos2d.h>

class Background: public cocos2d::Sprite {
public:
    static cocos2d::Sprite* createSprite();
    cocos2d::ParallaxNode *_backgroundNode;
    Sprite *_backgroundColor;
    virtual bool init() override;
    CREATE_FUNC(Background);
};

#endif /* Background_hpp */
