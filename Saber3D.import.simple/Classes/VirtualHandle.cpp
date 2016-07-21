//
//  VirtualHandle.cpp
//  VirtualHandle
//
//  Created by ChiuPhonic on 16/7/19.
//
//

#include "VirtualHandle.hpp"

VirtualHandle::VirtualHandle():
_rocker_range(nullptr),
_rocker(nullptr),
_a(nullptr),
_b(nullptr),
_callback(nullptr),
_margin(Vec2(24, 45)),
_rocker_range_value(36),
_rockerTouchID(-1),
_rockerWay(0),
_rockerLastPoint(Vec2(0, 0))
{
    //
}

bool VirtualHandle::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto winSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    _rocker_range = ui::Widget::create();
    _a = ui::Button::create("res/logo/A.png");
    _b = ui::Button::create("res/logo/B.png");
    _rocker = ui::Button::create("res/logo/X.png");
    this->_rocker_range_value = 0.78*_rocker->getContentSize().width;
    
//    CCLOG("%f", _rocker->getContentSize().width);
//    CCLOG("%f", this->_rocker_range_value/2);
    
    _rocker_range->setContentSize(Size(_rocker_range_value, _rocker_range_value));
    _rocker_range->setPosition(Vec2(_rocker_range_value/2 + _margin.x,
                                    _rocker_range_value/2));
    _rocker->setPosition(Vec2(_rocker_range_value/2,
                              _rocker_range_value/2));
    _rocker_range->addChild(_rocker);
    
    _a->setPosition(Vec2(visibleSize.width-1.5*_a->getContentSize().width-_margin.x/3+2,
                         _rocker_range_value/2-18));
    _b->setPosition(Vec2(visibleSize.width-_b->getContentSize().width/2-_margin.x/3-1,
                         _rocker_range_value/2+7));
    _rocker->setTouchEnabled(false);
    
    
    this->addChild(_rocker_range);
    this->addChild(_a);
    this->addChild(_b);
    
    // bind
    _a->addTouchEventListener(std::bind(&VirtualHandle::touchEvent, this, std::placeholders::_1, std::placeholders::_2));
    _b->addTouchEventListener(std::bind(&VirtualHandle::touchEvent, this, std::placeholders::_1, std::placeholders::_2));
    
    auto event_dispatcher = Director::getInstance()->getEventDispatcher();
    auto rocker_range_event = EventListenerTouchOneByOne::create();
    
    rocker_range_event->onTouchBegan = [this, visibleSize, origin](Touch *touch, Event *event){
        
        auto bound = _rocker_range->getBoundingBox();
        bound.origin = _rocker_range->convertToWorldSpace(Vec2(0, 0));
        
        auto orig = Vec2(bound.getMidX(), bound.getMidY());
        auto p = touch->getLocation();
        
//        CCLOG("Origin: (%04f, %04f)", orig.x, orig.y);
//        CCLOG("Touch at: (%04f, %04f)", p.x, p.y);
//        
//        CCLOG("%f, %f, %f", bound.getMaxX(), bound.getMidX(), bound.getMinX());
//        CCLOG("%f, %f, %f", bound.getMaxY(), bound.getMidY(), bound.getMinY());
        
        if (bound.containsPoint(p)) {
            _rockerTouchID = touch->getID();
            _rockerLastPoint = p;
            
            if (orig.getDistance(p) < 20) {
                // stay
//                CCLOG("stay");
                _rockerWay = 0;
            } else {
                // check direction
                auto direction = Vec2(p.x-orig.x, p.y-orig.y);
                auto arc = 180*atan2(direction.y, direction.x)/M_PI;
//                CCLOG("TID = %d, arc = %f", _rockerTouchID, arc);
                _rockerWay = callBackWithDirection(arc);
            }
            
            updateRockerPosition(_rockerLastPoint);
            
            return true;
            
        } else {
            resetRockerPosition(orig);
        }
        
        return false;
    };
    
    rocker_range_event->onTouchMoved = [this](Touch *touch, Event *event){
        if (_rockerWay == -1) {
            return ;
        }
        auto bound = _rocker_range->getBoundingBox();
        bound.origin = _rocker_range->convertToWorldSpace(Vec2(0, 0));
        auto orig = Vec2(bound.getMidX(), bound.getMidY());
        auto p = touch->getLocation();
        
        _rockerTouchID = touch->getID();
        _rockerLastPoint = p;
        auto direction = Vec2(p.x-orig.x, p.y-orig.y);
        auto arc = 180*atan2(direction.y, direction.x)/M_PI;
//        CCLOG("onMoved: %f", arc);
        _rockerWay = callBackWithDirection(arc);
        
        if (bound.containsPoint(p)) {
            _rocker->setPosition(_rocker_range->convertToNodeSpace(p));
        } else {
            direction.normalize();
            float radius = _rocker_range_value/2;
            auto edge = Vec2(orig.x + radius*direction.x,
                             orig.y + radius*direction.y);
            _rocker->setPosition(_rocker_range->convertToNodeSpace(edge));
//            CCLOG("orig: [%f, %f]", orig.x, orig.y);
//            CCLOG("edge: [%f, %f]", edge.x, edge.y);
        }
        
    };
    
    rocker_range_event->onTouchEnded = [this](Touch *touch, Event *event){
        if (_rockerWay == -1) {
            return ;
        }
        auto bound = _rocker_range->getBoundingBox();
        bound.origin = _rocker_range->convertToWorldSpace(Vec2(0, 0));
        auto orig = Vec2(bound.getMidX(), bound.getMidY());
        
        cancelWay();
        _rockerTouchID = -1;
        _rockerLastPoint = orig;
        updateRockerPosition(orig);
    };
    
    rocker_range_event->onTouchCancelled = [this](Touch *touch, Event *event){
        if (_rockerWay == -1) {
            return ;
        }
        auto bound = _rocker_range->getBoundingBox();
        bound.origin = _rocker_range->convertToWorldSpace(Vec2(0, 0));
        auto orig = Vec2(bound.getMidX(), bound.getMidY());
        
        cancelWay();
        _rockerTouchID = -1;
        _rockerLastPoint = orig;
        updateRockerPosition(orig);
    };
    
    event_dispatcher->addEventListenerWithSceneGraphPriority(rocker_range_event, _rocker_range);
    
    return true;
}


void VirtualHandle::touchEvent(Ref *obj, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            if (obj == _a) {
                callback(VirtualHandleEvent::A);
            } else if (obj == _b) {
                callback(VirtualHandleEvent::B);
            }
            break;
        case ui::Widget::TouchEventType::ENDED:
            if (obj == _a) {
                callback(VirtualHandleEvent::CANCEL_A);
            } else if (obj == _b) {
                callback(VirtualHandleEvent::CANCEL_B);
            }
            break;
        case ui::Widget::TouchEventType::CANCELED:
            if (obj == _a) {
                callback(VirtualHandleEvent::CANCEL_A);
            } else if (obj == _b) {
                callback(VirtualHandleEvent::CANCEL_B);
            }
            break;
            
        default:
            break;
    }
}


void VirtualHandle::callback(VirtualHandleEvent event)
{
    if (this->_callback != nullptr) {
        this->_callback(event);
    }
}

void VirtualHandle::setCallback(std::function<void(VirtualHandleEvent)> callback)
{
    this->_callback = callback;
}

void VirtualHandle::updateRockerPosition(Vec2 &pos)
{
    auto moveTo = _rocker_range->convertToNodeSpace(pos);
    // CCLOG("moveTo: %f %f", moveTo.x, moveTo.y);
    _rocker->stopAllActions();
    _rocker->runAction(MoveTo::create(0.1, moveTo));
}

void VirtualHandle::resetRockerPosition(Vec2 &pos)
{
    auto center = _rocker_range->convertToNodeSpace(pos);
    _rocker->stopAllActions();
    _rocker->setPosition(center);
}

int VirtualHandle::callBackWithDirection(const double &arc)
{
    if (arc > -22.5 && arc <= 22.5) {
        callback(VirtualHandleEvent::LEFT);
        return 1;
    } else if (arc <= -157.5 || arc > 157.5) {
        callback(VirtualHandleEvent::RIGHT);
        return 2;
    } else if (arc > 67.5 && arc <= 112.5) {
        callback(VirtualHandleEvent::UP);
        return 3;
    } else if (arc > -112.5 && arc <= -67.5) {
        callback(VirtualHandleEvent::DOWN);
        return 4;
    } else if (arc > 22.5 && arc <= 67.5) {
        callback(VirtualHandleEvent::LEFT_UP);
        return 5;
    } else if (arc > 112.5 && arc <= 157.5) {
        callback(VirtualHandleEvent::RIGHT_UP);
        return 6;
    } else if (arc > -67.5 && arc <= -22.5) {
        callback(VirtualHandleEvent::LEFT_DOWN);
        return 7;
    } else if (arc > -157.5 && arc <= -112.5) {
        callback(VirtualHandleEvent::RIGHT_DOWN);
        return 8;
    }
    return -1;
}

void VirtualHandle::cancelWay()
{
    switch (_rockerWay) {
        case 1:
            callback(VirtualHandleEvent::CANCEL_LEFT);
            break;
        case 2:
            callback(VirtualHandleEvent::CANCEL_RIGHT);
            break;
        case 3:
            callback(VirtualHandleEvent::CANCEL_UP);
            break;
        case 4:
            callback(VirtualHandleEvent::CANCEL_DOWN);
            break;
        case 5:
            callback(VirtualHandleEvent::CANCEL_LEFT_UP);
            break;
        case 6:
            callback(VirtualHandleEvent::CANCEL_RIGHT_UP);
            break;
        case 7:
            callback(VirtualHandleEvent::CANCEL_LEFT_DOWN);
            break;
        case 8:
            callback(VirtualHandleEvent::CANCEL_RIGHT_DOWN);
            break;
            
        default:
            break;
    }
    
    _rockerWay = 0;
}

float VirtualHandle::getRockerRangeValue() const
{
    return this->_rocker_range_value;
}

float VirtualHandle::postHeight() const
{
    return _margin.y;
}

