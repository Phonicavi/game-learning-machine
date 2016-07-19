#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Ball.hpp"

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
    if ( !Layer::init() ) // LayerColor::initWithColor(Color4B(248, 248, 248, 248) //0, 0, 0, 0
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    _score = 0;

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

    // add new MenuItemImage
    auto changeColor = MenuItemImage::create(
                                             "normal.png",
                                             "selected.png",
                                             [](Ref *ref){
                                                 CCLOG("menu selected..");
                                             });
    changeColor->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width - changeColor->getContentSize().width/2 ,
                                  origin.y + changeColor->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    // auto menu = Menu::create(closeItem, changeColor, NULL);
    
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /*
    auto menu2 = Menu::create(MenuItemImage::create("normal.png", "selected.png", [](Ref *ref){
        CCLOG("menu selected..");
    }), NULL);
    this->addChild(menu2);
     */
    

    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    
    
    auto label = Label::createWithTTF("Cocos2D-X Ball", "fonts/Marker Felt.ttf", 24);
    auto score_board = Label::create();
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - 2*label->getContentSize().height));
    score_board->setPosition(Vec2(origin.x + visibleSize.width/2,
                                  origin.y + visibleSize.height - 3*label->getContentSize().height
                                  - 1.2*score_board->getContentSize().height));
    score_board->setSystemFontName("fonts/Marker Felt.ttf");
    score_board->setSystemFontSize(18);
    label->setTextColor(Color4B(55, 55, 55, 55));
    score_board->setTextColor(Color4B(55, 55, 55, 55));
    
    
    CCLOG("visibleSize: %f, %f", visibleSize.width, visibleSize.height);
    CCLOG("origin: %f, %f", origin.x, origin.y);

    
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    this->addChild(score_board, 1);
    

    auto bgi = Sprite::create("res/bg_01.jpg");
    bgi->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //    CCLOG("sprite: %f %f", bgi->getContentSize().width, bgi->getContentSize().height);
    //    CCLOG("view: %f %f", visibleSize.width, visibleSize.height);
    float _scale_times = MAX(visibleSize.width / bgi->getContentSize().width,
                             visibleSize.height / bgi->getContentSize().height);
    //    CCLOG("times: %f %f", visibleSize.width / bgi->getContentSize().width, visibleSize.height / bgi->getContentSize().height);
    bgi->setScale(_scale_times);
    this->addChild(bgi, 0);

    // add "HelloWorld" splash
    // auto sprite = Sprite::create("HelloWorld.png");
    auto sprite = Sprite::create("res/icon72x72.png");

    // position the sprite on the center of the screen
    // sprite->setAnchorPoint(Vec2(0, 0));
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setScale(1.2);
    // sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    
    /*
      320, 320 -> 320/2+80, 320/2+0 = 240, 160
      (default)480, 320 -> 480/2+0, 320/1+0 = 240, 160
     
     */
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    /*
    // add plane
    // auto img = Director::getInstance()->getTextureCache()->addImage("res/plane.png");
    auto plane = Sprite::create("res/plane.png", Rect(2, 168, 62, 75)); // Rect(1, 78, 31, 39)
    addChild(plane);
    plane->setPosition(Vec2(plane->getContentSize().width/2+origin.x+2, plane->getContentSize().height/2+origin.y+2));
    
    // move plane
    auto _direction = Vec2(1, 1+random(-0.1f, 0.1f));
    _direction.normalize();
    auto mv = MoveBy::create(1.5, _direction*180);
    _direction.y *= -1;
    auto mv2 = MoveBy::create(1.5, _direction*180);
    plane->runAction(Sequence::create(mv, mv2, NULL));
    
    log("ok: %f", 0.55);
    
//    MessageBox("Contents", "Title");
    
    auto buttonFire = Label::create();
    buttonFire->setString("Fire");
    buttonFire->setSystemFontName("fonts/Marker Felt.ttf");
    buttonFire->setSystemFontSize(18);
    buttonFire->setPosition(Vec2(visibleSize.width/8+origin.x, 7*visibleSize.height/8+origin.y));
    addChild(buttonFire);
    
    auto buttonLight = Label::createWithTTF("Light Up", "fonts/Marker Felt.ttf", 18);
    buttonLight->setPosition(Vec2(visibleSize.width/8+origin.x, 5*visibleSize.height/8+origin.y));
    addChild(buttonLight);
    
    
    auto tf = TextFieldTTF::textFieldWithPlaceHolder("Shoot", "fonts/arial.ttf", 18);
    tf->setPosition(Vec2(visibleSize.width/4+origin.x, visibleSize.height/4+origin.y));
    addChild(tf);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this, tf, buttonLight, buttonFire](Touch *t, Event *event){
        // log(">>>>");
        if (tf->getBoundingBox().containsPoint(t->getLocation())) {
            log("x");
            tf->attachWithIME();
        } else {
            tf->detachWithIME();
        }
        
        if (buttonLight->getBoundingBox().containsPoint(t->getLocation())) {
            log("Bon");
        }
        if (buttonFire->getBoundingBox().containsPoint(t->getLocation())) {
            log("Fire...");
        }
        return false;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, tf);
    
    // 'this' is not a cocos2d::extension::TableViewdataSource instance, we need to modify the definition in HelloWorldScene.h
    auto tv = TableView::create(this, Size(300, 300));
    tv->setAnchorPoint(Vec2(0, 0));
    tv->setPosition(Vec2(100, 100));
    
    tv->setDelegate(this);
    
    this->addChild(tv);
    */
    
    
    
    ball = Ball::create();
    auto _rate = 0.12;
    auto _speed = 5.0;
    ball->setScale(_rate);
    ball->setPosition(origin.x + _rate*ball->getContentSize().width/2+20, origin.y + _rate*ball->getContentSize().height/2+20);
    
    this->addChild(ball);
    _direction = Vec2(random(-1.0f, 1.0f), random(-1.0f, 1.0f));
    _direction.normalize();
    
    // scheduleUpdate();
    
    schedule([this, visibleSize, origin, score_board, _rate, _speed](float dt){
        // CCLOG("%f", dt);
        
        if (ball->getPositionX() < origin.x + _rate*ball->getContentSize().width/2
            || ball->getPositionX() > origin.x + visibleSize.width - _rate*ball->getContentSize().width/2) {
            _direction.x *= -1;
            //CCLOG("x!: (%f, %f)", ball->getPositionX(), ball->getPositionY());
            _score++;
        }
        if (ball->getPositionY() < origin.y + _rate*ball->getContentSize().height/2
            || ball->getPositionY() > origin.y + visibleSize.height - _rate*ball->getContentSize().height/2) {
            _direction.y *= -1;
            //CCLOG("y!: (%f, %f)", ball->getPositionX(), ball->getPositionY());
            _score--;
        }
        
        score_board->setString(StringUtils::format("%d", _score));
        
        _direction.normalize();
        
        ball->setPosition(ball->getPosition() + _direction*_speed);
        
    }, "Action");
    
    auto listener = EventListenerTouchOneByOne::create();
    auto buttonLeft = Label::createWithTTF(">>", "fonts/arial.ttf", 24);
    auto buttonRight = Label::createWithTTF("<<", "fonts/arial.ttf", 24);
    buttonLeft->setTextColor(Color4B(55, 55, 55, 55));
    buttonRight->setTextColor(Color4B(55, 55, 55, 55));
    
    CCLOG("Left contentSize: %f %f", buttonLeft->getContentSize().width, buttonLeft->getContentSize().height);
    CCLOG("Right contentSize: %f %f", buttonRight->getContentSize().width, buttonRight->getContentSize().height);
    
    float _mid = MAX(buttonLeft->getContentSize().width, buttonRight->getContentSize().width);
    float _margin = 10;
    
    buttonLeft->setPosition(Vec2(origin.x + _mid/2 + _margin,
                                 origin.y + visibleSize.height/8));
    buttonRight->setPosition(Vec2(origin.x + visibleSize.width - _mid/2 - _margin,
                                  origin.y + visibleSize.height/8));

    this->addChild(buttonLeft, 1);
    this->addChild(buttonRight, 1);
    
        
    listener->onTouchBegan = [this, buttonLeft, buttonRight](Touch *t, Event *event){
        
        if (buttonLeft->getBoundingBox().containsPoint(t->getLocation())) {
            // log("Left");
            _direction.x += 0.1;
        }
        if (buttonRight->getBoundingBox().containsPoint(t->getLocation())) {
            // log("Right");
            _direction.x -= 0.1;
        }
        return false;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
    
    

    return true;
}

//void HelloWorld::update(float dt)
//{
//    // CCLOG("%f", dt);
//    
//    if (ball->getPositionX() < origin.x + _rate*ball->getContentSize().width/2
//        || ball->getPositionX() > origin.x + visibleSize.width - _rate*ball->getContentSize().width/2) {
//        _direction.x *= -1;
//        //CCLOG("x!: (%f, %f)", ball->getPositionX(), ball->getPositionY());
//    }
//    if (ball->getPositionY() < origin.y + _rate*ball->getContentSize().height/2
//        || ball->getPositionY() > origin.y + visibleSize.height - _rate*ball->getContentSize().height/2) {
//        _direction.y *= -1;
//        //CCLOG("y!: (%f, %f)", ball->getPositionX(), ball->getPositionY());
//    }
//    
//    _direction.normalize();
//    
//    ball->setPosition(ball->getPosition() + _direction*5);
//    
//}

Size HelloWorld::cellSizeForTable(TableView *table)
{
    return Size(300, 50);
}

TableViewCell* HelloWorld::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    auto cell = table->dequeueCell(); // TableViewCell *cell
    Label *label;
    
    if (cell == NULL) {
        cell = TableViewCell::create();
        label = Label::create();
        label->setTag(2);
        cell->addChild(label);
    } else {
        label = (Label*)cell->getChildByTag(2);
    }
    
    label->setString(StringUtils::format("Index: %ld", idx)); // format("%d", (int)idx)
    label->setBMFontSize(12);
    label->setAnchorPoint(Vec2(0, 0));
    
    return cell;
}

ssize_t HelloWorld::numberOfCellsInTableView(TableView *table)
{
    return 100;
}

void HelloWorld::tableCellTouched(TableView* table, TableViewCell* cell)
{
    Label *label = (Label*)cell->getChildByTag(2);
    CCLOG("%s", label->getString().c_str());
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
