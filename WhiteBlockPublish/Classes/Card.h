//
//  Card.h
//  Baikuai
//
//  Created by plter on 14-4-30.
//
//

#ifndef __Baikuai__Card__
#define __Baikuai__Card__

#include <iostream>
#include <cocos2d.h>

USING_NS_CC;


class Card:public Sprite {
    
private:
    int lineIndex;
    Size visibleSize;
    static Vector<Card*> *cards;
    
public:
    virtual bool initWithArgs(Size size,Color3B color,std::string label,float fontSize);
    
    static Card* createWithArgs(Size size,Color3B color,std::string label,float fontSize);
    
    static Vector<Card*>* getCards();
    
    int getLineIndex();
    void setLineIndex(int lineIndex);
    
    void moveDown();
};

#endif /* defined(__Baikuai__Card__) */
