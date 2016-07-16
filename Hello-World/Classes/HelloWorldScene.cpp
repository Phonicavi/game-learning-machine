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
    
    auto _director = Director::getInstance();
    auto visibleSize = _director->getVisibleSize();
    Vec2 origin = _director->getVisibleOrigin();
    
    /*

    auto rect = DrawNode::create();
    rect->drawRect(Vec2(0, 0), Vec2(100, 100), Color4F(1.0, 0, 0, 1.0));
    
    auto dot = DrawNode::create();
    dot->drawDot(Vec2(0, 0), 5, Color4F(1.0, 1.0, 1.0, 1.0));
    
    
    addChild(rect);
    rect->addChild(dot);
    
    rect->setPosition(visibleSize/2);
    dot->setPosition(Vec2(30, 30));
    
    rect->setContentSize(Size(100, 100));
    rect->setAnchorPoint(Vec2(0.5, 0.5));
    
    schedule([dot, rect](float f){
        rect->setRotation(rect->getRotation()+1);
        auto p = dot->convertToWorldSpace(Vec2(0, 0));
        CCLOG("%f, %f", p.x, p.y);
    }, "Test");
    
    
    _angle = 0;

    auto dot2 = DrawNode::create();
    dot2->drawDot(Vec2(0, 0), 3, Color4F(1.0, 1.0, 0, 1.0));
    addChild(dot2);
    
    dot2->setPosition(visibleSize/2);
    
    schedule([dot2, visibleSize, this](float f){
        dot2->setPositionY(visibleSize.height/2 + cos(_angle)*50.0);
        dot2->setPositionX(visibleSize.width/2 + sin(_angle)*80.0);
        _angle += 0.1;
    }, "Test2");
    
    
    _direction.set(random(-1.0f, 1.0f), random(-1.0f, 1.0f));
    _direction.normalize();
    
    auto dot3 = DrawNode::create();
    dot3->drawDot(Vec2(0, 0), 2, Color4F(0, 1.0, 1.0, 1.0));
    addChild(dot3);
    
    dot3->setPosition(visibleSize/3);
    
    schedule([dot3, visibleSize, this](float f){
        auto p = dot3->getPosition();
        if (p.x < 0 || p.x > visibleSize.width) {
            _direction.x *= -1;
            _direction.y += random(-0.3f, 0.3f);
            _direction.normalize();
        }
        if (p.y < 0 || p.y > visibleSize.height) {
            _direction.y *= -1;
            _direction.x += random(-0.3f, 0.3f);
            _direction.normalize();
        }
        dot3->setPosition(p + _direction*2.0);
    }, "Test3");
    */
    
    
    /*
    
    auto roleImg = _director->getTextureCache()->addImage("HelloWorld.png");
    auto role = Sprite::createWithTexture(roleImg);
    
    addChild(role);
    role->setPosition(visibleSize/2);
    role->setScale(0.5);
    
    // role->runAction(MoveTo::create(1.5, Vec2(visibleSize.width-10, visibleSize.height/2)));
    
    auto move1 = MoveTo::create(1.5, Vec2(visibleSize.width-10, visibleSize.height/2));
    auto move2 = MoveBy::create(1.2, Vec2(-500, -20));
    
//    role->runAction(Sequence::create(move1, move2, NULL));
    
    auto move3 = move2->reverse();
    
//    role->runAction(Sequence::create(move1, move2, move3, NULL));
    
    auto scale = ScaleTo::create(1.5, 1.2);
    
    role->runAction(Sequence::create(
                                     Spawn::create(
                                                   move1,
                                                   scale,
                                                   NULL),
                                     move2,
                                     CallFunc::create([](){
                                        CCLOG("Action Complete");
                                    }),
                                     move3,
                                     NULL));
     
     */
    
    
    /*
    
    auto roleImg = _director->getTextureCache()->addImage("HelloWorld.png");
    auto Role = NodeGrid::create();
    Role->addChild(Sprite::createWithTexture(roleImg));
    
    Role->setPosition(visibleSize/2);
    addChild(Role);
    
    //    Role->runAction(Shaky3D::create(3.5, Size(50, 50), 5, 5));
    //    Role->runAction(ShakyTiles3D::create(3.5, Size(12, 12), 5, 5));
    //    Role->runAction(ShuffleTiles::create(0.5, Size(180, 180), 5));

    //    auto wav = Waves3D::create(2, Size(12, 10), 3, 30.0);
    //    auto wav0 = Waves3D::create(0.2, Size(12, 10), 0, 0);
    auto shk = Shaky3D::create(1.2, Size(25, 25), 3, 3);
    auto shf = ShuffleTiles::create(0.3, Size(180, 180), 25);
//    auto tof = TurnOffTiles::create(1.5, Size(100, 100));
    
//    Role->runAction(Sequence::create(wav, wav0, NULL));
    Role->runAction(Sequence::create(shk, shf, NULL));
     
     */
    
    /*
    
    auto bgi = _director->getTextureCache()->addImage("bg_02.jpg");
    auto background = Sprite::createWithTexture(bgi);
    background->setPosition(visibleSize/2);
    addChild(background);
    
    schedule([this, _director, visibleSize](float f){
        
        auto scene = Scene::create();
        auto bgis = Sprite::create("bg_01.jpg");
        bgis->setPosition(visibleSize/2);
        scene->addChild(bgis);
        
        //        auto trans = TransitionCrossFade::create(1.0, scene);
        //        auto trans = TransitionZoomFlipAngular::create(1.0, scene);
        //        auto trans = TransitionZoomFlipY::create(1.0, scene);
        //        auto trans = TransitionPageTurn::create(1.0, scene, true);
        //        auto trans = TransitionProgressRadialCW::create(1.0, scene);
        auto trans = TransitionSplitRows::create(1.0, scene);
        _director->replaceScene(trans);
        
    }, 2, "cut-background");
    
     */
    
    
    /*
     
    auto icon = Sprite::create("CloseSelected.png");
    addChild(icon);
    icon->setPosition(visibleSize/2);
    
    auto _p = icon->getContentSize();
    CCLOG("size: %f %f", _p.width, _p.height);
    
    schedule([icon](float f){
        auto size = icon->getContentSize();
        CCLOG("size: %f %f", size.width, size.height);
    }, "test");
    
//    icon->retain();
    
    Vector<Label*> vec;
    
    auto label1 = Label::create();
    auto label2 = Label::create();
    
    label1->setString("Light Up");
    label2->setString("Fire");
    label1->setSystemFontSize(25);
    label2->setSystemFontSize(25);
    
    vec.pushBack(label1);
    vec.pushBack(label2);
    
//    int i = 0;
//    for (auto label : vec) {
//        addChild(label);
//        label->setPosition(Vec2(visibleSize.width/4+i*100, visibleSize.height/1.2));
//        i++;
//    }
    
    Map<std::string, Label*> map;
    map.insert("light", label1);
    map.insert("fire", label2);
    
    addChild(map.at("fire"));
    map.at("fire")->setPosition(visibleSize/2);
     
     */
    
    Value value1 = Value("abc");
    Value value2 = Value(1);
    Value value3 = Value(true);
    
    CCLOG("%s %d %s", value1.asString().c_str(), value2.asInt(), value3.asBool()==true?"TrUe":"FaLse");
    CCLOG("%s %s %s", value1.asString().c_str(), value2.asString().c_str(), value3.asString().c_str());
    
    Value value4 = Value::Null;
    value4 = value2;
    value4 = value1;
    value4 = value3;
    
    CCLOG("%s %s", value4.getType()==Value::Type::BOOLEAN?"isBool":"notBool", value4.asString().c_str());
    
    ValueVector vv;
    vv.push_back(Value("cocos2d-x"));
    vv.push_back(value2);
    vv.push_back(value1);
    vv.push_back(value4);
    
    for (auto val : vv) {
        CCLOG("val = %s", val.asString().c_str());
    }
    
    ValueMap vm;
    vm["a"] = value1;
    vm["b"] = value2;
    
    for (auto m : vm) {
        CCLOG("%s = %s", m.first.c_str(), m.second.asString().c_str());
    }
    
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
