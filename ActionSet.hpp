#pragma once
//#include <libplayerc++/playerc++.h>
#include "RobotCenter.hpp"

class Action{
    public:
        enum ActionType{
            FORWARD,
            LEFT,
            RIGHT};
        Action(RobotCenter& rc);
        virtual void doAction()=0;
    protected:
        RobotCenter& rc;
        //PlayerCc::Position2dProxy& pp;
};

class GoForward : public Action{
    public:
        GoForward(RobotCenter& rc);
        virtual void doAction();
};

class GoLeft : public Action{
    public: 
        GoLeft(RobotCenter& rc);
        virtual void doAction();
};

class GoRight : public Action{
    public: 
        GoRight(RobotCenter& rc);
        virtual void doAction();
};
