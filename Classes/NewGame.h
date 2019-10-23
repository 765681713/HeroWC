//
// Created by Administrator on 2019/10/8.
//

#ifndef PROJ_ANDROID_NEWGAME_H
#define PROJ_ANDROID_NEWGAME_H


#include "cocos2d.h"

USING_NS_CC;

class NewGame : public cocos2d::Scene {
public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(NewGame);
private:
    Sprite *sprite;
    Sprite3D *mySprite;

    bool onTouchBegan(Touch *tTouch, Event *eEvent);//手指按下事件
    void onTouchMoved(Touch *tTouch, Event *eEvent);//手指移动事件
    void onTouchEnded(Touch *tTouch, Event *eEvent);//手指离开事件
    const char *NEWGAME = " NEWGAME ";
};


#endif //PROJ_ANDROID_NEWGAME_H
