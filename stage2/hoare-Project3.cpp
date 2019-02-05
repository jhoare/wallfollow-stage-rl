#include "ActionSet.hpp"
#include "StateSpace.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "RobotCenterPlayer.hpp"

using namespace std;
/*
static const float X_MAX = -7;
static const float X_MIN = -10.5;
static const float Y_MAX = 5;
static const float Y_MIN = -2;
*/
/*
static const float X_MAX = 3;
static const float X_MIN = 1;
static const float Y_MAX = -7;
static const float Y_MIN = -11;
#define RAND(a,b) rand() * ((double)b-a) / (double)RAND_MAX + (double)a
*/

void print_usage(char* argv){
    cout << "Usage: " << argv << "epsilon_initial [filename] " << endl
         << "Where filname is an optional parameter to \"start\" the " << endl
         << "  learning at." << endl;
}

Action::ActionType eps_greedy(double& epsilon, StateSpace& ss, State& s){
    double chance = (std::rand() % 101 )/100.0;
    Action::ActionType best = ss.GetBestAction(s);
    Action::ActionType myret = best;
    if ( chance > epsilon ) {
        return best;
    }
    else{
        //while ( myret == best )
            myret = (Action::ActionType) (std::rand() % num_of_actions);
    }
    // Decay Epsilon
    epsilon *= 0.999;
    return myret;
}

int main(int argc, char* argv[]){
    /*
    PlayerCc::PlayerClient robot("localhost", 6665);
    PlayerCc::LaserProxy lp(&robot,0);
    PlayerCc::Position2dProxy pp(&robot,0);
    PlayerCc::SimulationProxy sim(&robot);
    */
    RobotCenterPlayer rc;
    cout << "Num of states: " << num_of_states << endl
         << "Num of actions: " << num_of_actions << endl;
    StateSpace ss(rc, num_of_states, num_of_actions);
    State s,s_prime;


    if ( argc != 2 && argc != 3 ){
        print_usage(argv[0]);
        exit(1);
    }

    double epsilon = atof(argv[1]);
    
    cout << "Starting with epsilon=" << epsilon << endl;

    if ( argc == 3 ) { 
        {
            // Check to see if this file exists...
            fstream infile(argv[2], ios::in);
            if (infile.fail()){
                print_usage(argv[0]);
                exit(1);
            }
            infile.close();
        }
        // If we have two arguments, 
        ss.LoadState(argv[2]);
    }

    Action* theAction;
    GoForward forward(rc);
    GoLeft left(rc);
    GoRight right(rc);
    double r;

    try{
        rc.Read();
        rc.Read();
        rc.Read();
        while (1) {
            rc.Read();
            ss.StartTrial();
            s = ss.GetState();
            Action::ActionType a = eps_greedy(epsilon, ss, s);
            while (rc.GetStall() == false){
                switch(a){
                case Action::FORWARD:
                    theAction = &forward;
                    break;
                case Action::LEFT:
                    theAction = &left;
                    break;
                case Action::RIGHT:
                    theAction = &right;
                    break;
                default:
                    cerr << "WHAT THE WHAT" << endl;
                    assert(false);
                    break;
                }
                theAction->doAction();
                rc.Read();
                rc.Read();
                rc.Read();
                rc.Read();
                rc.Read();
                s_prime = ss.GetState();
                Action::ActionType a_prime = eps_greedy(epsilon, ss, s_prime);
                r = rewardFunc(s_prime, (a==Action::FORWARD), rc.GetStall());
                //ss.Update(r, a_prime, s_prime, a,s);
                cout << "Reward: " << r << endl
                     << "Epsilon: " << epsilon << endl;
                s = s_prime;
                a = a_prime;
            }
            /// Reset the robot's location
            rc.ResetLocation();
            /*
            sim.SetPose2d((char *)"robotProj3",
                    1,
                    -11,
                    M_PI/2);
                    */
            /*
            sim.SetPose2d((char *)"robotProj3",
                    RAND(X_MIN,X_MAX),
                    RAND(Y_MIN,Y_MAX),
                    RAND(-M_PI, M_PI));
                    */
            ss.SaveState("state.dat");
        }
    } catch(exception e){
        cerr << e.what() << endl;
    }
}
