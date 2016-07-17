//
//  GameOverScene.hpp
//  CocosBall
//
//  Created by ChiuPhonic on 16/7/17.
//
//

#ifndef GameOverScene_hpp
#define GameOverScene_hpp

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class GameOverScene : public Layer
{
public:
    virtual bool init();
    
    CREATE_FUNC(GameOverScene);
    
    static cocos2d::Scene *createScene();
    static cocos2d::Scene *createScene(int _score);
};

#endif /* GameOverScene_hpp */
