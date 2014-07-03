//
//  EndLine.h
//  WhiteBlockPublish
//
//  Created by plter on 14-5-5.
//
//

#ifndef __WhiteBlockPublish__EndLine__
#define __WhiteBlockPublish__EndLine__

#include <iostream>
#include "GameBlock.h"
#include "HelloWorldScene.h"

class HelloWorld;

class EndLine:public GameBlock {
    
private:
    Size visibleSize;
    HelloWorld *context;
    
public:
    static EndLine* createWithContext(HelloWorld *context);
    bool initWithContext(HelloWorld *context);
};

#endif /* defined(__WhiteBlockPublish__EndLine__) */
