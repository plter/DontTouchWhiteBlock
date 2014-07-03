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
    
    srand((unsigned int)time(NULL));
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    gameLayer = Node::create();
    addChild(gameLayer);
    
    timerLabel = Label::create();
    timerLabel->setTextColor(Color4B::BLUE);
    timerLabel->setSystemFontSize(48);
    timerLabel->setPosition(visibleSize.width/2, visibleSize.height-100);
    addChild(timerLabel);
    
    
    startGame();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* t,Event* e){
        
        auto bs = GameBlock::getBlocks();
        GameBlock *b;
        
        for (auto it = bs->begin(); it!=bs->end(); it++) {
            
            b = *it;
            
            if (b->getLineIndex()==1&&
                b->getBoundingBox().containsPoint(t->getLocation())) {
                
                if (b->getColor()==Color3B::BLACK) {
                    if (!timerRunning) {
                        this->startTimer();
                    }
                    
                    b->setColor(Color3B::GRAY);
                    this->moveDown();
                }else if(b->getColor()==Color3B::GREEN){
                    this->moveDown();
                    this->stopTimer();
                }else{
                    MessageBox("你点错了", "点错了");
                    b->setColor(Color3B::RED);
                }
                
                break;
            }
        }
        
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void HelloWorld::startGame(){
    //init
    stopTimer();
    linesCount = 0;
    showEnd = false;
    timerRunning = false;
    currentEndLine = NULL;
    timerLabel->setString("0.000000");
    
    //try to clear
    GameBlock::removeAllBlocks();
    
    addStartLine();
    addNormalLine(1);
    addNormalLine(2);
    addNormalLine(3);
}


void HelloWorld::addStartLine(){
    auto b = GameBlock::createWithArgs(Color3B::YELLOW, Size(visibleSize.width, visibleSize.height/4), "", 20, Color4B::BLACK);
    gameLayer->addChild(b);
    b->setLineIndex(0);
}


void HelloWorld::addEndLine(){
    
    auto b = EndLine::createWithContext(this);
    b->setLineIndex(4);
    b->setPositionY(b->getLineIndex()*visibleSize.height/4);
    gameLayer->addChild(b);
    
    currentEndLine = b;
}


void HelloWorld::addNormalLine(int lineIndex){
    
    GameBlock *b;
    int blackIndex = rand()%4;
    
    for (int i=0; i<4; i++) {
        b = GameBlock::createWithArgs(blackIndex==i?Color3B::BLACK:Color3B::WHITE,Size(visibleSize.width/4-1, visibleSize.height/4-1),"",20,Color4B::BLACK);
        gameLayer->addChild(b);
        
        b->setPosition(i*visibleSize.width/4, lineIndex*visibleSize.height/4);
        b->setLineIndex(lineIndex);
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
    
    
    auto bs = GameBlock::getBlocks();
    
    for (auto it = bs->begin(); it!=bs->end(); it++) {
        (*it)->moveDown();
    }
    
    if (currentEndLine!=NULL) {
        
        if (currentEndLine->getLineIndex()==1) {
            //Game end
            moveDown();
            stopTimer();
        }
    }
}


void HelloWorld::update(float dt){
    
    long offset = clock()-startTime;
    
    timerLabel->setString( StringUtils::format("%g",((double)offset)/1000000));
}


void HelloWorld::startTimer(){
    if (!timerRunning) {
        scheduleUpdate();
        startTime = clock();
        
        timerRunning = true;
    }
}


void HelloWorld::stopTimer(){
    if(timerRunning){
        unscheduleUpdate();
        
        timerRunning = false;
    }
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
