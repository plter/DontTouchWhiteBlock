//
//  Block.h
//  WhiteBlock
//
//  Created by plter on 14-5-4.
//
//

#ifndef __WhiteBlock__GameBlock__
#define __WhiteBlock__GameBlock__

#include <cocos2d.h>

USING_NS_CC;

class GameBlock:public Sprite {
    
private:
    static Vector<GameBlock*> * blocks;
    int lineIndex;
    
public:
    
    static Vector<GameBlock*> * getBlocks();
    static void removeAllBlocks();
    
    static GameBlock* createWithArgs(Color3B color,Size size,std::string label,float fontSize,Color4B textColor);
    
    virtual bool initWithArgs(Color3B color,Size size,std::string label,float fontSize,Color4B textColor);
    
    void removeBlock();
    
    int getLineIndex();
    void setLineIndex(int lineIndex);
    
    void moveDown();
};


#endif /* defined(__WhiteBlock__Block__) */
