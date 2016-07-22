//
//  VirtualHandle.hpp
//  VirtualHandle
//
//  Created by ChiuPhonic on 16/7/19.
//
//

#ifndef VirtualHandle_hpp
#define VirtualHandle_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

enum class VirtualHandleEvent
{
    A,
    B,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    LEFT_UP,
    RIGHT_UP,
    LEFT_DOWN,
    RIGHT_DOWN,
    
    CANCEL_A,
    CANCEL_B,
    CANCEL_LEFT,
    CANCEL_RIGHT,
    CANCEL_UP,
    CANCEL_DOWN,
    CANCEL_LEFT_UP,
    CANCEL_RIGHT_UP,
    CANCEL_LEFT_DOWN,
    CANCEL_RIGHT_DOWN
};

class VirtualHandle : public Node {
protected:
    ui::Widget *_rocker_range;
    ui::Button *_rocker;
    ui::Button *_a;
    ui::Button *_b;
    Vec2 _margin;
    float _rocker_range_value;
    
    int _rockerTouchID;
    int _rockerWay; // 0:center, 1:left, 2:right, 3:up, 4:down, 5:left_up, 6:right_up, 7:left_down, 8:right_down
    cocos2d::Vec2 _rockerLastPoint; // last time position
    
    cocos2d::Vec2 _rockerDirection;
    
    std::function<void(VirtualHandleEvent)> _callback;
    
protected:
    void touchEvent(Ref *obj, ui::Widget::TouchEventType type);
    
    inline void callback(VirtualHandleEvent event);
    
    inline void updateRockerPosition(Vec2 &pos);
    inline void resetRockerPosition(Vec2 &pos);
    inline int callBackWithDirection(const double &arc);
    inline void cancelWay();
    
public:
    VirtualHandle();
    virtual ~VirtualHandle() {};
    
    virtual bool init();
    CREATE_FUNC(VirtualHandle);
    
    void setCallback(std::function<void(VirtualHandleEvent)> callback);
    
    float getRockerRangeValue() const;
    
    float postHeight() const;
    
    Vec2 getDirection() const;
};


#endif /* VirtualHandle_hpp */
