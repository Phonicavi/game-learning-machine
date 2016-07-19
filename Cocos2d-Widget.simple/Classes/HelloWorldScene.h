#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class HelloWorld : public cocos2d::Layer, cocos2d::extension::TableViewDataSource, cocos2d::extension::TableViewDelegate
{
private:
    cocos2d::Sprite *ball;
    cocos2d::Vec2 _direction;
    int _score;
    
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    // scheduleUpdate
//    virtual void update(float dt);
    
public:

    virtual Size cellSizeForTable(TableView *table);
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    
public:
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
};

#endif // __HELLOWORLD_SCENE_H__
