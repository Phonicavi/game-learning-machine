#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    bool toSwim;
    bool toRotate;
    cocos2d::Vec3 direction;
    
    bool toZoomIn;
    bool toZoomOut;
    bool toRotateHorizontal;
    bool toRotateVertical;
    cocos2d::Vec3 rotaryH;
    cocos2d::Vec3 rotaryV;
    
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
