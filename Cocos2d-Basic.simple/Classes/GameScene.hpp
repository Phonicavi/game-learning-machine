//
//  GameScene.hpp
//  Cocos2d-Basic
//
//  Created by ChiuPhonic on 16/7/16.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class GameScene : public Layer
{
public:
    GameScene();
    virtual ~GameScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    
    static cocos2d::Scene* createScene();
};

#endif /* GameScene_hpp */
