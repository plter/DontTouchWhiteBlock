//
//  Block.h
//  WhiteBlock
//
//  Created by plter on 14-5-4.
//
//

#ifndef __WhiteBlock__Block__
#define __WhiteBlock__Block__

#include <cocos2d.h>

USING_NS_CC;

class Block:public Sprite {
    
private:
    static Vector<Block*> * blocks;
    int lineIndex;
    
public:
    
    static Vector<Block*> * getBlocks();
    static void removeAllBlocks();
    
    static Block* createWithArgs(Color3B color,Size size,std::string label,float fontSize,Color4B textColor);
    
    virtual bool initWithArgs(Color3B color,Size size,std::string label,float fontSize,Color4B textColor);
    
    void removeBlock();
    
    int getLineIndex();
    void setLineIndex(int lineIndex);
    
    void moveDown();
};


#endif /* defined(__WhiteBlock__Block__) */
