#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto img = Director::getInstance()->getTextureCache()->addImage("icon72x72.png");
    auto imgSize = img->getContentSize();
    CCLOG("img-size: %f %f", imgSize.width, imgSize.height);
    
    /* auto logo = Sprite::create("icon72x72.png"); */
    auto logo = Sprite::createWithTexture(img);
    logo->setPosition(visibleSize/2);
    addChild(logo);
    
    // add one dot
    auto dot = DrawNode::create();
    dot->drawDot(Vec2(0, 0), 2, Color4F(0.0, 1.0, 1.0, 1.0));
    dot->setPosition(visibleSize/2);
    addChild(dot);
    
    _direction.set(random(-1.0f, 1.0f), random(-1.0f, 1.0f));
    _direction.normalize();
    
    schedule([this, visibleSize, dot](float f){
        auto p = dot->getPosition();
        if (p.x < 0 || p.x > visibleSize.width) {
            _direction.x *= -1;
        }
        if (p.y < 2 || p.y > visibleSize.height-2) {
            _direction.y *= -1;
        }
        dot->setPosition(p+_direction*8.0);
    }, "Random-Shoot");
    
    auto layer1 = Layer::create();
    auto layer2 = Layer::create();
    auto layer3 = Layer::create();
    
    auto img1 = Sprite::create("bg_01.jpg");
    auto img2 = Sprite::create("plane.png");
    auto img3 = Sprite::create("bg_02.jpg");
    
    layer1->addChild(img1);
    layer2->addChild(img2);
    layer3->addChild(img3);
    
    layer1->setPosition(Vec2(100, 100));
    layer2->setPosition(Vec2(110, 150));
    layer3->setPosition(Vec2(120, 200));
    
    addChild(layer1);
    addChild(layer2);
    addChild(layer3);
    
    scheduleOnce([this, visibleSize, logo](float f){
        
        auto scene2 = Scene::create();
        auto sc2layer = Layer::create();
        
        scene2->addChild(sc2layer);
        
        auto logo2 = Sprite::create("icon72x72.png");
        logo2->setPosition(2*visibleSize/3);
        sc2layer->addChild(logo2);
        
        Director::getInstance()->replaceScene(scene2);
        
    }, 5.0, "Once");
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
