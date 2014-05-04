#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Card.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
    
private:
    Size visibleSize;
    int linesCount;
    bool showEnd;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    virtual void update(float dt);
    
public:
    void addStartLine();
    void addEndLine();
    void addNormalLine(int index);
    void startGame();
    void moveDown();
};

#endif // __HELLOWORLD_SCENE_H__
