//
//  Block.cpp
//  WhiteBlock
//
//  Created by plter on 14-5-4.
//
//

#include "Block.h"

Vector<Block*> * Block::blocks = new Vector<Block*>();

Vector<Block*> * Block::getBlocks(){
    return Block::blocks;
}


Block* Block::createWithArgs(Color3B color,Size size,std::string label,float fontSize,Color4B textColor){
    
    auto b = new Block();
    b->initWithArgs(color,size,label,fontSize,textColor);
    b->autorelease();
    
    blocks->pushBack(b);
    
    return b;
}


bool Block::initWithArgs(Color3B color,Size size,std::string label,float fontSize,Color4B textColor){
    
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


void Block::removeBlock(){
    auto c = getColor();
    log("Remove block,color is (%d,%d,%d)",c.r,c.g,c.b);
    
    removeFromParent();
    blocks->eraseObject(this);
}


void Block::setLineIndex(int v){
    this->lineIndex = v;
}


int Block::getLineIndex(){
    return this->lineIndex;
}

void Block::moveDown(){
    
    this->lineIndex--;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    runAction(Sequence::create(MoveTo::create(0.1f, Point(getPositionX(), lineIndex*visibleSize.height/4)),
                               CallFunc::create([this](){
        
        if (lineIndex<0) {
            this->removeBlock();
        }
        
    }), NULL));
    
}


