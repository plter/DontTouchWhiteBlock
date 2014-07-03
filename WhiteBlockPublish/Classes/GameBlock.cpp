//
//  Block.cpp
//  WhiteBlock
//
//  Created by plter on 14-5-4.
//
//

#include "GameBlock.h"

Vector<GameBlock*> * GameBlock::blocks = new Vector<GameBlock*>();

Vector<GameBlock*> * GameBlock::getBlocks(){
    return GameBlock::blocks;
}

void GameBlock::removeAllBlocks(){
    
    while (getBlocks()->size()) {
        getBlocks()->back()->removeFromParent();
        getBlocks()->popBack();
    }
}

GameBlock* GameBlock::createWithArgs(Color3B color,Size size,std::string label,float fontSize,Color4B textColor){
    
    auto b = new GameBlock();
    b->initWithArgs(color,size,label,fontSize,textColor);
    b->autorelease();
    
    blocks->pushBack(b);
    
    return b;
}


bool GameBlock::initWithArgs(Color3B color,Size size,std::string label,float fontSize,Color4B textColor){
    
    Sprite::init();
    
    lineIndex = 0;
    
    setContentSize(size);
    setAnchorPoint(Point::ZERO);
    setTextureRect(Rect(0, 0, size.width, size.height));
    setColor(color);
    
    auto l = Label::create();
    l->setString(label);
    l->setSystemFontSize(fontSize);
    l->setTextColor(textColor);
    addChild(l);
    l->setPosition(size.width/2,size.height/2);
    
    return true;
}


void GameBlock::removeBlock(){
//    auto c = getColor();
//    log("Remove block,color is (%d,%d,%d)",c.r,c.g,c.b);
    
    removeFromParent();
    blocks->eraseObject(this);
}


void GameBlock::setLineIndex(int v){
    this->lineIndex = v;
}


int GameBlock::getLineIndex(){
    return this->lineIndex;
}

void GameBlock::moveDown(){
    
    this->lineIndex--;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    if (getNumberOfRunningActions()!=0) {
        stopAllActions();
    }
    
    runAction(Sequence::create(MoveTo::create(0.1f, Point(getPositionX(), lineIndex*visibleSize.height/4)),
                               CallFunc::create([this](){
        
        if (lineIndex<0) {
            this->removeBlock();
        }
        
    }), NULL));
    
}


