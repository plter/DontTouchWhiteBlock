#include "HelloWorldScene.h"

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
    
    //    scheduleUpdate();
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    startGame();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* t,Event *e){
        
        Card *c;
        
        for (auto it = Card::getCards()->begin(); it!=Card::getCards()->end(); it++) {
            c = *it;
            if (c->getLineIndex()==1&&
                c->getBoundingBox().containsPoint(t->getLocation())) {
                
                if (c->getColor()==Color3B(0, 0, 0)) {
                    c->setColor(Color3B::GRAY);
                    this->moveDown();
                }else if(c->getColor()==Color3B::GREEN){
                    this->moveDown();
                }else{
                    MessageBox("失败", "游戏结束");
                }
                
                break;
            }
        }
        
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    //    addEndLine();
    return true;
}

void HelloWorld::startGame(){
    linesCount = 0;
    showEnd = false;
    
    addStartLine();
    addNormalLine(1);
    addNormalLine(2);
    addNormalLine(3);
}

void HelloWorld::addEndLine(){
    auto c = Card::createWithArgs(Size(visibleSize.width, visibleSize.height), Color3B(0, 255, 0), "Game Over" ,30);
    addChild(c);
    c->setLineIndex(4);
}

void HelloWorld::addStartLine(){
    
    auto c = Card::createWithArgs(Size(visibleSize.width,visibleSize.height/4), Color3B(255, 255, 0), "" ,28);
    c->setLineIndex(0);
    addChild(c);
}

void HelloWorld::addNormalLine(int lineIndex){
    
    int blackIndex = rand()%4;
    Card *c;
    
    for (int i=0; i<4; i++) {
        c = Card::createWithArgs(Size(visibleSize.width/4-1, visibleSize.height/4-1), i==blackIndex?Color3B(0, 0, 0):Color3B(255, 255, 255), "", 28);
        c->setPosition(i*visibleSize.width/4, lineIndex*visibleSize.height/4);
        c->setLineIndex(lineIndex);
        addChild(c);
    }
    
    linesCount++;
}


void HelloWorld::moveDown(){
    if (linesCount<50) {
        addNormalLine(4);
    }else if(!showEnd){
        addEndLine();
        showEnd = true;
    }
    
    for (auto it = Card::getCards()->begin(); it!=Card::getCards()->end(); it++) {
        (*it)->moveDown();
    }
}


void HelloWorld::update(float dt){
    log("%g",((double)clock())/1000000);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
