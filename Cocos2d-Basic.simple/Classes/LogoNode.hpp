//
//  LogoNode.hpp
//  Cocos2d-Basic
//
//  Created by ChiuPhonic on 16/7/15.
//
//

#ifndef LogoNode_hpp
#define LogoNode_hpp

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class LogoNode : public Node
{
protected:
    Sprite* _logo;
    Sprite* _cocosLogo;
    
public:
    LogoNode();
    virtual ~LogoNode();
    
    virtual bool init();
    
    CREATE_FUNC(LogoNode);
};

#endif /* LogoNode_hpp */
