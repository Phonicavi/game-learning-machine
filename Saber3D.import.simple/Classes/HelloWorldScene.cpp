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
    
    /*

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
     
     */
    
    
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
    
    // set something
    this->toSwim = false;
    this->toRotate = false;
    
    auto vh = VirtualHandle::create();
    vh->setPositionY(vh->postHeight());
    CCLOG("[MAIN] vh: %f %f", vh->getPositionX(), vh->getPositionY());
    CCLOG("[MAIN] anchor: %f %f", vh->getAnchorPoint().x, vh->getAnchorPoint().y);
    this->addChild(vh);
    
    
    /*
    
    // add tortoise
    
    auto sp_tortoise = Sprite3D::create("tortoise.c3b", "tortoise.png");
    sp_tortoise->setPosition(3*visibleSize.width/4, visibleSize.height/2);
    sp_tortoise->setScale(0.1);
    this->addChild(sp_tortoise, 2);
     
     */
    
    this->direction = Vec3(-1.f, 0.f, 0.f);
    this->direction.normalize();
    
    // add virtual handle
    vh->setCallback([this](VirtualHandleEvent event){
        std::string value;
        switch (event) {
            case VirtualHandleEvent::A:
                value = "A";
                this->toSwim = true;
                break;
            case VirtualHandleEvent::B:
                value = "B";
                this->toRotate = true;
                break;
            case VirtualHandleEvent::CANCEL_A:
                value = "CANCEL_A";
                this->toSwim = false;
                break;
            case VirtualHandleEvent::CANCEL_B:
                value = "CANCEL_B";
                this->toRotate = false;
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
    
    /*
     
    float speed = 35.f;
    this->schedule([this, sp_tortoise, speed](float f){
        
        if (!this->toRotate && this->toSwim && sp_tortoise->getNumberOfRunningActions() == 0) {
//            CCLOG("to swim: %zd", sp_tortoise->getNumberOfRunningActions());
            auto anim = Animate3D::create(Animation3D::create("tortoise.c3b"), 0.0, 1.933);
            auto forw = Sequence::create(MoveBy::create(0.2, 0.3*speed*this->direction),
                                         MoveBy::create(1.5, speed*this->direction),
                                         MoveBy::create(0.1, 0.1*speed*this->direction),
                                         NULL);
            sp_tortoise->runAction(Sequence::create(Spawn::create(anim, forw, NULL), NULL));
        } else if (this->toRotate && sp_tortoise->getNumberOfRunningActions() == 0) {
//            CCLOG("to rotate: %zd", sp_tortoise->getNumberOfRunningActions());
            this->direction *= -1;
            auto rot = RotateBy::create(1.f, Vec3(0.f, 180.f, 0.f));
            sp_tortoise->runAction(Spawn::create(rot,
                                                 Animate3D::create(Animation3D::create("tortoise.c3b"), 0.0, 1.933),
                                                 NULL));
        }
        // else if (sp_tortoise->getNumberOfRunningActions() == 0) {
//            CCLOG("nothing: %zd", sp_tortoise->getNumberOfRunningActions());
//            sp_tortoise->runAction(Animate3D::create(Animation3D::create("tortoise.c3b"), 0.0, 1.933));
        // }
        
    }, "Tortoise Monitor");
    
    //auto anim = RepeatForever::create(Animate3D::create(Animation3D::create("tortoise.c3b")));
    //auto anim = Animate3D::create(Animation3D::create("tortoise.c3b"), 1.933, 2.8);
    //sp_tortoise->runAction(anim);
    
//    anim->setTag(88);
    
//    sp_tortoise->runAction(MoveBy::create(3.0, Vec3(-150.f, 0.f, 0.f)));
//    sp_tortoise->runAction(rot);
    
    auto p = sp_tortoise->getPosition3D();
    CCLOG("%f %f %f", p.x, p.y, p.z);
    
    
//    if (sp_tortoise->getActionByTag(88) == NULL) {
//        CCLOG("no action");
//    } else {
//        CCLOG("have action");
//    }
     
     */
    
    auto saber =Sprite3D::create("Saber_dorisuVer1.05.c3t");
    saber->setPosition(Vec2(visibleSize.width/2, visibleSize.height/5));
    saber->setScale(1.2);
    this->addChild(saber);
    saber->getMesh()->setTexture("karada.png");
    
    CCLOG("%f, %f", saber->getContentSize().width, saber->getContentSize().height);
    
    // haifu
    saber->getMeshByIndex(0)->setTexture("kao.png");
    saber->getMeshByIndex(1)->setTexture("kao.png");
    saber->getMeshByIndex(2)->setTexture("karada.png");
    saber->getMeshByIndex(3)->setTexture("usirokami.png");
    saber->getMeshByIndex(4)->setTexture("maekami.png");
    saber->getMeshByIndex(5)->setTexture("maekami.png");
    saber->getMeshByIndex(6)->setTexture("usirokami.png");
    saber->getMeshByIndex(7)->setTexture("kao.png");
    saber->getMeshByIndex(8)->setTexture("uehuku.png");
    saber->getMeshByIndex(9)->setTexture("button.png");
    saber->getMeshByIndex(10)->setTexture("uehuku.png");
    saber->getMeshByIndex(11)->setTexture("skart.png");
    saber->getMeshByIndex(12)->setTexture("skart.png");
    saber->getMeshByIndex(13)->setTexture("skart.png");
    saber->getMeshByIndex(14)->setTexture("uehuku.png");
    saber->getMeshByIndex(15)->setTexture("skart.png");
    saber->getMeshByIndex(16)->setTexture("uehuku.png");
    saber->getMeshByIndex(17)->setTexture("skart.png");
    saber->getMeshByIndex(18)->setTexture("skart.png");
    saber->getMeshByIndex(19)->setTexture("skart.png");
    saber->getMeshByIndex(20)->setTexture("skart.png");
    saber->getMeshByIndex(21)->setTexture("button.png");
    saber->getMeshByIndex(22)->setTexture("button.png");
    saber->getMeshByIndex(23)->setTexture("button.png");
    saber->getMeshByIndex(24)->setTexture("karada.png");
    saber->getMeshByIndex(25)->setTexture("mune.png");
    saber->getMeshByIndex(26)->setTexture("karada.png");
    saber->getMeshByIndex(27)->setTexture("uehuku.png");
    saber->getMeshByIndex(28)->setTexture("pantu.png");
    saber->getMeshByIndex(29)->setTexture("karada.png");
    saber->getMeshByIndex(30)->setTexture("pantu.png");
    saber->getMeshByIndex(31)->setTexture("zubon.png");
    saber->getMeshByIndex(32)->setTexture("kao.png");
    saber->getMeshByIndex(33)->setTexture("kao.png");
    saber->getMeshByIndex(34)->setTexture("kao.png");
    saber->getMeshByIndex(35)->setTexture("kao.png");
    saber->getMeshByIndex(36)->setTexture("kao.png");
    saber->getMeshByIndex(37)->setTexture("me.png");
    saber->getMeshByIndex(38)->setTexture("hitomi.png");
    saber->getMeshByIndex(39)->setTexture("hitomi.png");
    saber->getMeshByIndex(40)->setTexture("hoho.png");
    
    
    /*
    auto s = Sprite3D::create("Saber_dorisuVer1.05.c3t");
    s->setPosition(Vec2(2*visibleSize.width/3, visibleSize.height/5));
    s->setScale(1.2);
    this->addChild(s);
    
    auto lb = Label::create();
    lb->setPosition(Vec2(50, 250));
    this->addChild(lb);
    
    for (ssize_t i = 0; i < s->getMeshCount(); ++i) {
        CCLOG("texture %zd: %s", i, s->getMesh()->getTextureFileName().c_str());
        CCLOG("texture %zd: %s", i, s->getMesh()->getName().c_str());
        CCLOG("mesh %zd: %s", i, s->getMeshByIndex(static_cast<int>(i))->getName().c_str());
        //s->getMesh()->getName();//->setTexture("");
        s->getMeshByIndex(static_cast<int>(i))->setVisible(false);
    }
    
    log("%zd", s->getMeshCount());
    
    s->setTag(0);
    s->getMeshByIndex(0)->setTexture("kao.png");
    s->getMeshByIndex(0)->setVisible(true);
    
    lb->setString(StringUtils::format("id = %d", s->getTag()));
    
    this->schedule([this, s, lb](float f){
        s->getMeshByIndex(s->getTag())->setVisible(false);
        
        s->setTag(s->getTag()+1);
        
        s->getMeshByIndex(s->getTag())->setTexture("kao.png");
        s->getMeshByIndex(s->getTag())->setVisible(true);
        lb->setString(StringUtils::format("id = %d", s->getTag()));
        
        if (s->getTag()+1 >= s->getMeshCount()) {
            s->setTag(0);
            s->getMeshByIndex(0)->setTexture("kao.png");
            s->getMeshByIndex(0)->setVisible(true);
        }
        
    }, 5.0f, "change");
     */
    
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
