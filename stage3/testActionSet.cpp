#include "ActionSet.hpp"
#include "StateSpace.hpp"
#include "RobotCenterPlayer.hpp"
#include <iostream>

using namespace std;

int main(){
    /*
    PlayerCc::PlayerClient robot("localhost", 6665);
    PlayerCc::LaserProxy lp(&robot,0);
    PlayerCc::Position2dProxy pp(&robot,0);
    */
    RobotCenterPlayer rc;
    StateSpace ss(rc, num_of_states, num_of_actions);
    State s;

    Action* theAction;
    GoForward forward(rc);
    GoLeft left(rc);
    GoRight right(rc);

    int choice;

    cout << "Pick An Action: " << endl
         << "1: forward" << endl
         << "2: left" << endl
         << "3: right" << endl;
    cin >> choice;

    switch(choice){
    case 1:
        theAction = &forward;
        break;
    case 2:
        theAction = &left;
        break;
    case 3:
        theAction = &right;
        break;
    default:
        assert(false);
        break;
    }
    

    try{
    while (1){
        rc.Read();
        s = ss.GetState();
        theAction->doAction();
    }
    } catch(exception e){
        cerr << e.what() << endl;
    }
}
