//
// Created by Administrator on 2019/10/8.
//

#ifndef PROJ_ANDROID_GAMEONE_H
#define PROJ_ANDROID_GAMEONE_H

#include "cocos2d.h"

class GameOne : public cocos2d::Scene{
    public:
        static cocos2d::Scene* createScene();

        virtual bool init();

        // implement the "static create()" method manually
        CREATE_FUNC(GameOne);
};


#endif //PROJ_ANDROID_GAMEONE_H
