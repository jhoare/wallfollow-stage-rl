#include "StateSpace.hpp"
#include <iostream>
#include "RobotCenterPlayer.hpp"

using namespace std;

int main(){
    //PlayerCc::PlayerClient robot("localhost", 6665);
    //PlayerCc::LaserProxy lp(&robot,0);
    RobotCenterPlayer rc;
    StateSpace ss(rc, num_of_states, num_of_actions);
    State s;

    try{
        while (1){
            rc.Read();
            s = ss.GetState();
            for (int i = 0; i < num_of_laser_regions; i++){
                cout << "s.regions[i] = " << s.readings[i] << endl;
            }
            cout << "reward: " << rewardFunc(s,false,false) << endl << endl;
        }
    } catch(exception e){
        cerr << e.what() << endl;
    }
}
