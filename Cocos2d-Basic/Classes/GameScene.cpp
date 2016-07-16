//
//  GameScene.cpp
//  Cocos2d-Basic
//
//  Created by ChiuPhonic on 16/7/16.
//
//

#include "GameScene.hpp"
#include "LogoNode.hpp"

GameScene::GameScene()
{
    //
}

GameScene::~GameScene()
{
    //
}

bool GameScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    auto logo = LogoNode::create();
    
    addChild(logo);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    logo->setPosition(visibleSize/2);
    
    return true;
}


Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    
    scene->addChild(layer);
    
    return scene;
}