//
//  GameOverScene.cpp
//  CocosBall
//
//  Created by ChiuPhonic on 16/7/17.
//
//

#include "GameOverScene.hpp"

bool GameOverScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    // add background
    auto bgi = Sprite::create("res/bg_02.jpg");
    bgi->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    float _scale_times = MAX(visibleSize.width / bgi->getContentSize().width,
                             visibleSize.height / bgi->getContentSize().height);
    bgi->setScale(_scale_times);
    this->addChild(bgi, 0);
    
    // add score_board
    auto label = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2));
    label->setTextColor(Color4B(55, 55, 55, 55));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    return true;
}

cocos2d::Scene* GameOverScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}

cocos2d::Scene* GameOverScene::createScene(int _score)
{
    auto scene = Scene::create();
    auto layer = Layer::create();
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    // add background
    auto bgi = Sprite::create("res/bg_02.jpg");
    bgi->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    float _scale_times = MAX(visibleSize.width / bgi->getContentSize().width,
                             visibleSize.height / bgi->getContentSize().height);
    bgi->setScale(_scale_times);
    layer->addChild(bgi, 0);
    
    // add score_board
    auto label = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 24);
    auto score_board = Label::create();
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2 + label->getContentSize().height));
    score_board->setPosition(Vec2(origin.x + visibleSize.width/2,
                                  origin.y + visibleSize.height/2 -
                                  1.2*score_board->getContentSize().height));
    score_board->setString(StringUtils::format("Total score: %d", _score));
    score_board->setSystemFontName("fonts/Marker Felt.ttf");
    score_board->setSystemFontSize(16);
    label->setTextColor(Color4B(55, 55, 55, 55));
    score_board->setTextColor(Color4B(55, 55, 55, 55));
    
    
    // add the label as a child to this layer
    layer->addChild(label, 1);
    layer->addChild(score_board, 1);
    
    scene->addChild(layer);
    return scene;
}

