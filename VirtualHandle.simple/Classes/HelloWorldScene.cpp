#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "VirtualHandle.hpp"

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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Virtual Handle", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
//    label->runAction(Sequence::create(Repeat::create(RotateBy::create(0.5, -180), 4),
//                                      CallFunc::create([this, label](){
//        this->removeChild(label);
//    }), NULL));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    sprite->runAction(Sequence::create(Repeat::create(RotateBy::create(1, 180), 4),
//                                       CallFunc::create([this, sprite](){
//        this->removeChild(sprite);
//    }),
//                                       NULL));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    /*
     
    // flash animation
    // add flash exported file
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("anim.plist");
    Vector<SpriteFrame*> vec;
    char name[10];
    memset(name, 0, 10);
    for (int i = 0; i < 20; ++i) {
        sprintf(name, "anim%04d", i);
        vec.pushBack(cache->getSpriteFrameByName(name));
    }
    auto anime = Animation::createWithSpriteFrames(vec, 0.1f);
    
    auto spri = Sprite::create();
    spri->setPosition(100, 240);
    auto action = Animate::create(anime);
    spri->runAction(RepeatForever::create(Sequence::create(action, action->reverse(), NULL)));
    this->addChild(spri);
     
     */
    
    /*
     
    // one point touch
    // listen
    auto l = Label::createWithTTF("Listen", "fonts/Marker Felt.ttf", 20);
    l->setPosition(210, 200);
    this->addChild(l);
    
    auto listen = EventListenerTouchOneByOne::create();
    l->setTag(1);
    listen->onTouchBegan = [l](Touch *t, Event *event){
        CCLOG("touched: %d", l->getTag());
        l->setTag(l->getTag()+1);
        CCLOG("%f %f", l->getPositionX(), l->getPositionY());
        CCLOG("%f %f", event->getCurrentTarget()->getPositionX(), event->getCurrentTarget()->getPositionY());
        return false;
    };
    // onTouchBegan : return false;
    // 则 不会触发onTouchMoved 和 onTouchEnded
    // 即 事件不再向后传递
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, l); // because here we bind 'listen' with 'l', so event->getCurrentTarget is just 'l'
     
     */
    
    
    /*
     
     // more than one points touches
    auto listen = EventListenerTouchAllAtOnce::create();
    listen->onTouchesBegan = [](const std::vector<Touch*> &ts, Event *event){
        CCLOG("touches");
    };
    listen->onTouchesMoved = [](const std::vector<Touch*> &ts, Event *event){
        CCLOG("%ld", ts.size());
        // 需要在ios/AppController.mm中修改配置 开启多点触控
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, this); // 多点触控 绑定给整个当前scene this指针
    
     */
    
    
    /*
    
    // 加速度传感器默认关闭 这里需要开启
    
    auto X = Label::create();
    // WithTTF("X = ", "fonts/Marker Felt.ttf", 18);
    X->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    this->addChild(X);
    Device::setAccelerometerEnabled(true);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(EventListenerAcceleration::create([X](Acceleration *a, Event *event){
        
        // CCLOG("x: %g, y: %g, z: %g", a->x, a->y, a->z);
        X->setString(StringUtils::format("X = %g,\nY = %g,\nZ = %g", a->x, a->y, a->z));
        
    }), this);
    
    
    // 物理按键侦听
    // auto li = EventListenerKeyboard::create();
    // li->onKeyRelease ... (for Android)
    
     */
    
    auto vh = VirtualHandle::create();
    vh->setPositionY(vh->postHeight());
    CCLOG("[MAIN] vh: %f %f", vh->getPositionX(), vh->getPositionY());
    CCLOG("[MAIN] anchor: %f %f", vh->getAnchorPoint().x, vh->getAnchorPoint().y);
    this->addChild(vh);
    
    vh->setCallback([](VirtualHandleEvent event){
        std::string value;
        switch (event) {
            case VirtualHandleEvent::A:
                value = "A";
                break;
            case VirtualHandleEvent::B:
                value = "B";
                break;
            case VirtualHandleEvent::CANCEL_A:
                value = "CANCEL_A";
                break;
            case VirtualHandleEvent::CANCEL_B:
                value = "CANCEL_B";
                break;
                
            case VirtualHandleEvent::LEFT:
                value = "LEFT";
                break;
            case VirtualHandleEvent::RIGHT:
                value = "RIGHT";
                break;
            case VirtualHandleEvent::UP:
                value = "UP";
                break;
            case VirtualHandleEvent::DOWN:
                value = "DOWN";
                break;
            case VirtualHandleEvent::LEFT_UP:
                value = "LEFT_UP";
                break;
            case VirtualHandleEvent::RIGHT_UP:
                value = "RIGHT_UP";
                break;
            case VirtualHandleEvent::LEFT_DOWN:
                value = "LEFT_DOWN";
                break;
            case VirtualHandleEvent::RIGHT_DOWN:
                value = "RIGHT_DOWN";
                break;
                
            case VirtualHandleEvent::CANCEL_LEFT:
                value = "CANCEL_LEFT";
                break;
            case VirtualHandleEvent::CANCEL_RIGHT:
                value = "CANCEL_RIGHT";
                break;
            case VirtualHandleEvent::CANCEL_UP:
                value = "CANCEL_UP";
                break;
            case VirtualHandleEvent::CANCEL_DOWN:
                value = "CANCEL_DOWN";
                break;
            case VirtualHandleEvent::CANCEL_LEFT_UP:
                value = "CANCEL_LEFT_UP";
                break;
            case VirtualHandleEvent::CANCEL_RIGHT_UP:
                value = "CANCEL_RIGHT_UP";
                break;
            case VirtualHandleEvent::CANCEL_LEFT_DOWN:
                value = "CANCEL_LEFT_DOWN";
                break;
            case VirtualHandleEvent::CANCEL_RIGHT_DOWN:
                value = "CANCEL_RIGHT_DOWN";
                break;
                
            default:
                break;
        }
        
        CCLOG("%s", value.c_str());
        
    });
    
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
