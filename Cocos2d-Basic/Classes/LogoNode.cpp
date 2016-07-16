//
//  LogoNode.cpp
//  Cocos2d-Basic
//
//  Created by ChiuPhonic on 16/7/15.
//
//

#include "LogoNode.hpp"

LogoNode::LogoNode():_logo(nullptr), _cocosLogo(nullptr) {
    //
}
LogoNode::~LogoNode() {
    
}

bool LogoNode::init() {
    if (!Node::init()) {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    _logo = Sprite::create("github.png");
    _cocosLogo = Sprite::create("icon48x48.png");
    
    addChild(_logo);
    addChild(_cocosLogo);
    
    _logo->setPosition(visibleSize/2);
    _cocosLogo->setPosition(visibleSize/2);
    
    CCLOG("VSZ: %f %f", visibleSize.width, visibleSize.height);
    
    _logo->setVisible(false);
    
    schedule([this](float f){
    
        _logo->setVisible(!_logo->isVisible());
        _cocosLogo->setVisible(!_cocosLogo->isVisible());
        
    }, 1, "Cut-logo");
    
    return true;
    
}