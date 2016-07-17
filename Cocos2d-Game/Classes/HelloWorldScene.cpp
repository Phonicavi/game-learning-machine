#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Ball.hpp"
#include "GameOverScene.hpp"

USING_NS_CC;
using namespace CocosDenshion;

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
    _score_b = 1500;
    _score_m = 800;
    _score_s = 100;
    _touch_flag = false;
    _touch_p = Vec2(0, 0);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Cocos2D-X Plane", "fonts/Marker Felt.ttf", 24);
    auto score_board = Label::create();
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - 2*label->getContentSize().height));
    score_board->setPosition(Vec2(origin.x + visibleSize.width/2,
                                  origin.y + visibleSize.height - 3*label->getContentSize().height -
                                  1.2*score_board->getContentSize().height));
    score_board->setSystemFontName("fonts/Marker Felt.ttf");
    score_board->setSystemFontSize(18);
    label->setTextColor(Color4B(55, 55, 55, 55));
    score_board->setTextColor(Color4B(55, 55, 55, 55));
    
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    this->addChild(score_board, 1);
    

    // add Background
    auto bgi = Sprite::create("res/bg_01.jpg");
    bgi->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    float _scale_times = MAX(visibleSize.width / bgi->getContentSize().width,
                             visibleSize.height / bgi->getContentSize().height);
    bgi->setScale(_scale_times);
    this->addChild(bgi, 0);

    // add "HelloWorld" splash
    // auto sprite = Sprite::create("HelloWorld.png");
    auto sprite = Sprite::create("res/icon72x72.png");

    // position the sprite on the center of the screen
    // sprite->setAnchorPoint(Vec2(0, 0));
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setScale(1.2);
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    // add plane
    img = Director::getInstance()->getTextureCache()->addImage("res/plane.png");
    const float _w_img = 256.0, _h_img = 256.0;
    float _cst = MAX(img->getContentSize().width / _w_img, img->getContentSize().height/ _h_img);
    float _start_height = 20;
    // Rect(2, 168, 62, 75)
    auto plane = Sprite::createWithTexture(img, Rect(2*_cst, 168*_cst, 62*_cst, 75*_cst));
    plane->setPosition(Vec2(origin.x + plane->getContentSize().width/2 +
                            random(0.0f, visibleSize.width - plane->getContentSize().width),
                            origin.y + plane->getContentSize().height/2 + _start_height));
    
    this->addChild(plane, 2);
    
    CCLOG("visibleSize: %f %f", visibleSize.width, visibleSize.height);
    CCLOG("plane contentSize: %f %f", plane->getContentSize().width, plane->getContentSize().height);
    
    
    ball = Ball::create();
    auto _rate = 0.08;
    auto _speed = 5.0;
    auto _plane_sp = 1.5;
//    ball->setScale(_rate);
//    ball->setPosition(origin.x + _rate*ball->getContentSize().width/2+20, origin.y + _rate*ball->getContentSize().height/2+20);
//    
//    this->addChild(ball);
//    _direction = Vec2(random(-1.0f, 1.0f), random(-1.0f, 1.0f));
//    _direction.normalize();
    
    
    schedule([this, visibleSize, origin, plane, score_board, _rate, _speed, _plane_sp](float f){
        
        // bounce ball
//        if (ball->getPositionX() < origin.x + _rate*ball->getContentSize().width/2
//            || ball->getPositionX() > origin.x + visibleSize.width - _rate*ball->getContentSize().width/2) {
//            _direction.x *= -1;
//            // CCLOG("x!: (%f, %f)", ball->getPositionX(), ball->getPositionY());
//            _score++;
//        }
//        if (ball->getPositionY() < origin.y + _rate*ball->getContentSize().height/2
//            || ball->getPositionY() > origin.y + visibleSize.height - _rate*ball->getContentSize().height/2) {
//            _direction.y *= -1;
//            // CCLOG("y!: (%f, %f)", ball->getPositionX(), ball->getPositionY());
//            _score--;
//        }
//        
        score_board->setString(StringUtils::format("%d", _score));
//
//        _direction.normalize();
//        
//        ball->setPosition(ball->getPosition() + _direction*_speed);
        
        // move plane
        
        if (_touch_flag) {
            auto _dir = Vec2(_touch_p.x - plane->getPositionX(), _touch_p.y - plane->getPositionY());
            _dir.normalize();
            // CCLOG("plane: %f, %f", plane->getPositionX(), plane->getPositionY());
            // CCLOG("touch: %f %f", _touch_p.x, _touch_p.y);
            plane->setPosition(plane->getPosition() + _dir*_plane_sp);
        }
        
    }, "Action");
    
    
    // move ball
//    auto listener = EventListenerTouchOneByOne::create();
//    auto buttonLeft = Label::createWithTTF(">>", "fonts/arial.ttf", 24);
//    auto buttonRight = Label::createWithTTF("<<", "fonts/arial.ttf", 24);
//    buttonLeft->setTextColor(Color4B(55, 55, 55, 55));
//    buttonRight->setTextColor(Color4B(55, 55, 55, 55));
//    
//    float _mid = MAX(buttonLeft->getContentSize().width, buttonRight->getContentSize().width);
//    float _margin = 10;
//    buttonLeft->setPosition(Vec2(origin.x + _mid/2 + _margin,
//                                 origin.y + visibleSize.height/3));
//    buttonRight->setPosition(Vec2(origin.x + visibleSize.width - _mid/2 - _margin,
//                                  origin.y + visibleSize.height/3));
//
//    this->addChild(buttonLeft, 1);
//    this->addChild(buttonRight, 1);
//    
//    listener->onTouchBegan = [this, buttonLeft, buttonRight](Touch *t, Event *event){
//        
//        if (buttonLeft->getBoundingBox().containsPoint(t->getLocation())) {
//            _direction.x += 0.1;
//            // CCLOG("Left On");
//        }
//        if (buttonRight->getBoundingBox().containsPoint(t->getLocation())) {
//            _direction.x -= 0.1;
//            // CCLOG("Right On");
//        }
//
//    };
//    
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
    
    
    // move plane : Touches
    auto tp_listen = EventListenerTouchAllAtOnce::create();
    
    tp_listen->onTouchesMoved = [this, plane, _plane_sp](const std::vector<Touch*>& touches, Event *event){
        // onTouchesMoved : update _touch_p
        auto t = touches[0];
        // auto _dir = Vec2(_touch_p.x - plane->getPositionX(), _touch_p.y - plane->getPositionY());
        // _dir.normalize();
        // plane->setPosition(plane->getPosition() + _dir*_plane_sp);
        // CCLOG("Moved");
        _touch_p = t->getLocation();
    };
    
    tp_listen->onTouchesEnded = [this](const std::vector<Touch*>& touches, Event *event){
        _touch_flag = false;
        // CCLOG("Ended");
    };
    
    tp_listen->onTouchesBegan = [this, plane](const std::vector<Touch*>& touches, Event *event){
        auto t = touches[0];
        if (!plane->getBoundingBox().containsPoint(t->getLocation())) {
            _touch_flag = true;
            _touch_p = t->getLocation();
        }
        // CCLOG("Began");
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(tp_listen, 1);
    
    
    // add bullets
    // Rect(112*_cst, 2*_cst, 9*_cst, 17*_cst)
    // Rect(66*_cst, 237*_cst, 7*_cst, 20*_cst)
    schedule([this, visibleSize, origin, _cst, plane](float f){
        
        auto bullet = Sprite::createWithTexture(img, Rect(66*_cst, 237*_cst, 7*_cst, 20*_cst));
        float dur_time = 0.8; // time to fly through height
        auto fly = MoveTo::create((visibleSize.height - bullet->getPositionY()) / (visibleSize.height/dur_time),
                                  Vec2(plane->getPositionX(),
                                       visibleSize.height + bullet->getContentSize().height/2));
        
        bullet->setPosition(Vec2(plane->getPositionX(),
                                 plane->getPositionY()+bullet->getContentSize().height));
        bullet->runAction(Sequence::create(fly,
                                           CallFunc::create([this, bullet](){
            this->removeChild(bullet);
            auto index = this->_bullets.getIndex(bullet);
            if (index > -1) {
                this->_bullets.erase(index);
            }
        }),
                                           NULL)); // add explosion
        bullet->setTag(12);
        
        this->_bullets.pushBack(bullet);
        this->addChild(bullet, 1);
        
    }, 0.15, "Shoot");
    
    
    // add target_plane
    // name="enemy_b" Rect(2*_cst, 2*_cst, 108*_cst, 164*_cst)
    // name="enemy_m" Rect(130*_cst, 2*_cst, 69*_cst, 89*_cst)
    // name="enemy_s" Rect(201*_cst, 88*_cst, 39*_cst, 27*_cst)
    schedule([this, visibleSize, origin, _cst](float f){
        
        auto target = Sprite::createWithTexture(img, Rect(2*_cst, 2*_cst, 108*_cst, 164*_cst));
        float dur_time = random(15.0, 20.0); // time to fly through height
        float _tar_x = random(target->getContentSize().width/2,
                              visibleSize.width - target->getContentSize().width/2);
        
        auto fly = MoveTo::create(dur_time, Vec2(origin.x + _tar_x,
                                                 origin.y - target->getContentSize().height/2));
        
        target->setPosition(Vec2(origin.x + _tar_x,
                                 origin.y + visibleSize.height + target->getContentSize().height/2));
        target->runAction(Sequence::create(fly,
                                           CallFunc::create([this, target](){
            this->removeChild(target);
            auto index = this->_targets_b.getIndex(target);
            if (index > -1) {
                this->_targets_b.erase(index);
            }
        }),
                                           NULL));
        target->setTag(130);
        
        this->_targets_b.pushBack(target);
        this->addChild(target, 2);
        
    }, 10.0, "Enemy_b");
    
    schedule([this, visibleSize, origin, _cst](float f){
        
        auto target = Sprite::createWithTexture(img, Rect(130*_cst, 2*_cst, 69*_cst, 89*_cst));
        float dur_time = random(7.5, 11.5); // time to fly through height
        float _tar_x = random(target->getContentSize().width/2,
                              visibleSize.width - target->getContentSize().width/2);
        
        auto fly = MoveTo::create(dur_time, Vec2(origin.x + _tar_x,
                                                 origin.y - target->getContentSize().height/2));
        
        target->setPosition(Vec2(origin.x + _tar_x,
                                 origin.y + visibleSize.height + target->getContentSize().height/2));
        target->runAction(Sequence::create(fly,
                                           CallFunc::create([this, target](){
            this->removeChild(target);
            auto index = this->_targets_m.getIndex(target);
            if (index > -1) {
                this->_targets_m.erase(index);
            }
        }),
                                           NULL));
        target->setTag(230);
        
        this->_targets_m.pushBack(target);
        this->addChild(target, 2);
        
    }, 6.0, "Enemy_m");
    
    schedule([this, visibleSize, origin, _cst](float f){
        
        auto target = Sprite::createWithTexture(img, Rect(201*_cst, 88*_cst, 39*_cst, 27*_cst));
        float dur_time = random(5.5, 9.0); // time to fly through height
        float _tar_x = random(target->getContentSize().width/2,
                              visibleSize.width - target->getContentSize().width/2);
        
        auto fly = MoveTo::create(dur_time, Vec2(origin.x + _tar_x,
                                                 origin.y - target->getContentSize().height/2));
        
        target->setPosition(Vec2(origin.x + _tar_x,
                                 origin.y + visibleSize.height + target->getContentSize().height/2));
        target->runAction(Sequence::create(fly,
                                           CallFunc::create([this, target](){
            this->removeChild(target);
            auto index = this->_targets_s.getIndex(target);
            if (index > -1) {
                this->_targets_s.erase(index);
            }
        }),
                                           NULL));
        target->setTag(330);
        
        this->_targets_s.pushBack(target);
        this->addChild(target, 2);
        
    }, 0.8, "Enemy_s");
    
    
    // collision dectection
    auto audio = SimpleAudioEngine::getInstance();
    // name="explosion_01" Rect(216*_cst, 117*_cst, 26*_cst, 26*_cst)
    // name="explosion_02" Rect(144*_cst, 93*_cst, 38*_cst, 39*_cst)
    // name="explosion_03" Rect(201*_cst, 44*_cst, 40*_cst, 42*_cst)
    schedule([this, audio, visibleSize, origin, _cst](float f){
    
        Vector<Sprite*> _t_b2del;
        for (auto _t_b : this->_targets_b) {
            auto _t_rect = _t_b->getBoundingBox();
            // check all bullets
            Vector<Sprite*> bullet2del;
            for (auto _bul : this->_bullets) {
                if (_t_rect.intersectsRect(_bul->getBoundingBox())) {
                    bullet2del.pushBack(_bul);
                }
            }
            if (!bullet2del.empty()) {
                _t_b2del.pushBack(_t_b);
            }
            // del bullets
            for (auto _bul : bullet2del) {
                auto index = this->_bullets.getIndex(_bul);
                if (index > -1) {
                    this->_bullets.erase(index);
                }
                this->removeChild(_bul);
            }
        }
        // del target_b
        for (auto _t_b : _t_b2del) {
            auto index = this->_targets_b.getIndex(_t_b);
            if (index > -1) {
                this->_targets_b.erase(index);
            }
            // add explosion
            auto exp = Sprite::createWithTexture(img, Rect(201*_cst, 44*_cst, 40*_cst, 42*_cst));
            exp->setPosition(Vec2(_t_b->getPositionX(), _t_b->getPositionY()-3*_t_b->getContentSize().height/4));
            this->addChild(exp);
            audio->playEffect("res/explosion.mp3");
            exp->runAction(Sequence::create(
                                            MoveBy::create(0.5, Vec2(0, 0)),
                                            // ShuffleTiles::create(0.8, Size(180, 180), 5),
                                            CallFunc::create([this, exp](){ this->removeChild(exp);}),
                                            NULL));
            this->removeChild(_t_b);
            _score += _score_b;
        }

        Vector<Sprite*> _t_m2del;
        for (auto _t_m : this->_targets_m) {
            auto _t_rect = _t_m->getBoundingBox();
            // check all bullets
            Vector<Sprite*> bullet2del;
            for (auto _bul : this->_bullets) {
                if (_t_rect.intersectsRect(_bul->getBoundingBox())) {
                    bullet2del.pushBack(_bul);
                }
            }
            if (!bullet2del.empty()) {
                _t_m2del.pushBack(_t_m);
            }
            // del bullets
            for (auto _bul : bullet2del) {
                auto index = this->_bullets.getIndex(_bul);
                if (index > -1) {
                    this->_bullets.erase(index);
                }
                this->removeChild(_bul);
            }
        }
        // del target_m
        for (auto _t_m : _t_m2del) {
            auto index = this->_targets_m.getIndex(_t_m);
            if (index > -1) {
                this->_targets_m.erase(index);
            }
            // add explosion
            auto exp = Sprite::createWithTexture(img, Rect(144*_cst, 93*_cst, 38*_cst, 39*_cst));
            exp->setPosition(Vec2(_t_m->getPositionX(), _t_m->getPositionY()-3*_t_m->getContentSize().height/4));
            this->addChild(exp);
            audio->playEffect("res/explosion.mp3");
            exp->runAction(Sequence::create(
                                            MoveBy::create(0.3, Vec2(0, 0)),
                                            // ShuffleTiles::create(0.5, Size(180, 180), 5),
                                            CallFunc::create([this, exp](){ this->removeChild(exp);}),
                                            NULL));
            this->removeChild(_t_m);
            _score += _score_m;
        }

        Vector<Sprite*> _t_s2del;
        for (auto _t_s : this->_targets_s) {
            auto _t_rect = _t_s->getBoundingBox();
            // check all bullets
            Vector<Sprite*> bullet2del;
            for (auto _bul : this->_bullets) {
                if (_t_rect.intersectsRect(_bul->getBoundingBox())) {
                    bullet2del.pushBack(_bul);
                }
            }
            if (!bullet2del.empty()) {
                _t_s2del.pushBack(_t_s);
            }
            // del bullets
            for (auto _bul : bullet2del) {
                auto index = this->_bullets.getIndex(_bul);
                if (index > -1) {
                    this->_bullets.erase(index);
                }
                this->removeChild(_bul);
            }
        }
        // del target_s
        for (auto _t_s : _t_s2del) {
            auto index = this->_targets_s.getIndex(_t_s);
            if (index > -1) {
                this->_targets_s.erase(index);
            }
            // add explosion
            auto exp = Sprite::createWithTexture(img, Rect(216*_cst, 117*_cst, 26*_cst, 26*_cst));
            exp->setPosition(Vec2(_t_s->getPositionX(), _t_s->getPositionY()-3*_t_s->getContentSize().height/4));
            this->addChild(exp);
            audio->playEffect("res/explosion.mp3");
            exp->runAction(Sequence::create(
                                            MoveBy::create(0.2, Vec2(0, 0)),
                                            // ShuffleTiles::create(0.3, Size(180, 180), 5),
                                            CallFunc::create([this, exp](){ this->removeChild(exp);}),
                                            NULL));
            this->removeChild(_t_s);
            _score += _score_s;
        }
    
    }, "Collision");
    
    
    // scene: game over
    
//    scheduleOnce([this](float f){
//        auto _game_over = GameOverScene::createScene(this->_score);
//        // auto _game_over = GameOverScene::createScene();
//        Director::getInstance()->replaceScene(_game_over);
//    }, 10.0, "Game Over");

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
