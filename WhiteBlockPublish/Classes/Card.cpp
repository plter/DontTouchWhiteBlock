//
//  Card.cpp
//  Baikuai
//
//  Created by plter on 14-4-30.
//
//

#include "Card.h"


Vector<Card*>* Card::cards = new Vector<Card*>();

Vector<Card*>* Card::getCards(){
    return Card::cards;
}

Card* Card::createWithArgs(Size size,Color3B color,std::string label,float fontSize){
    Card *c = new Card();
    c->initWithArgs(size, color,label,fontSize);
    cards->pushBack(c);
    c->autorelease();
    return c;
}


bool Card::initWithArgs(cocos2d::Size size, Color3B color, std::string label,float fontSize){
    Sprite::init();
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    setAnchorPoint(Point(0, 0));
    setContentSize(size);
    setTextureRect(Rect(0, 0, size.width, size.height));
    setColor(color);
    
    auto l = Label::create();
    l->setString(label);
    l->setSystemFontSize(fontSize);
    l->setTextColor(Color4B(0, 0, 0, 255));
    addChild(l);
    
    l->setPosition(size.width/2, size.height/2);
    
    return true;
}


int Card::getLineIndex(){
    return this->lineIndex;
}

void Card::setLineIndex(int lineIndex){
    this->lineIndex = lineIndex;
}

void Card::moveDown(){
    this->lineIndex--;
    
    runAction(Sequence::create(MoveTo::create(0.1f, Point(getPositionX(), lineIndex*visibleSize.height/4)),
                               CallFunc::create([this](){
        if (this->getLineIndex()<0) {
            this->removeFromParent();
            Card::getCards()->eraseObject(this);
        }
    }),
                               NULL));
}
