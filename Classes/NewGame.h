//
// Created by Administrator on 2019/10/8.
//

#ifndef PROJ_ANDROID_NEWGAME_H
#define PROJ_ANDROID_NEWGAME_H


#include "cocos2d.h"

class NewGame : public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(NewGame);

};


#endif //PROJ_ANDROID_NEWGAME_H
