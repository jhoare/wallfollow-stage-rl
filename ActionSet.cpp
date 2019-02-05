#include "ActionSet.hpp"

Action::Action(RobotCenter& rc) : rc(rc) {};

GoForward::GoForward(RobotCenter& rc) : Action(rc) {};
GoLeft::GoLeft(RobotCenter& rc) : Action(rc) {};
GoRight::GoRight(RobotCenter& rc) : Action(rc) {};

void GoForward::doAction(){
    rc.SetSpeed(0.5,0);
}

void GoLeft::doAction(){
    //rc.SetSpeed(0.15, 0.35);
    rc.SetSpeed(0.01, 0.35);
}

void GoRight::doAction(){
    //rc.SetSpeed(0.15, -0.35);
    rc.SetSpeed(0.01, -0.35);
}
