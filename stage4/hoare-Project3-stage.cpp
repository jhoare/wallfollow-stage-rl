#include "ActionSet.hpp"
#include "StateSpace.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "RobotCenterStage.hpp"
#include <sstream>

using namespace std;
using namespace Stg;


/////// CHANGE THESE PARAMETERS
static const bool update = false;
//double epsilon = 0.95;
double epsilon = 0;
int episodes = 648;


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
    //epsilon *= 0.999;
    return myret;
}

enum MY_STAGE{START,FIRST,WAIT,WAIT_DONE};

struct stuff{
    RobotCenter* rc;
    StateSpace* ss;
    State s;
    State s_prime;
    Action::ActionType a;
    Action::ActionType a_prime;
    Action* forward;
    Action* left;
    Action* right;
    MY_STAGE mystage;
    int counter;
};

int Update(stuff* s);

stuff* s;

extern "C" int Init( Model* mod )
{
    s = new stuff;
    s->rc = new RobotCenterStage(mod);
    s->ss = new StateSpace(*(s->rc),num_of_states,num_of_actions);
    s->forward = new GoForward(*(s->rc));
    s->left    = new GoLeft(*(s->rc));
    s->right   = new GoRight(*(s->rc));
    s->mystage = FIRST;
    mod->AddCallback(Stg::Model::CB_UPDATE, (model_callback_t)Update, s );
    cerr << "Init Done" << endl;
    cerr << s << endl;
    
    // Load a saved state

    fstream infile("state.dat", ios::in);
    if (!infile.fail()){
        infile.close();
        s->ss->LoadState("state.dat");
    }
}
void EndEpisode(){
    /// Reset the robot's location
    episodes++;
    std::cerr << "Episode " << episodes << " complete!" << endl;
    if ( update && episodes % 50 == 0){
        stringstream myss;
        myss << "savestates/state-" << episodes << ".dat";
        s->ss->SaveState(myss.str().c_str());
    }
    s->rc->ResetLocation();
    if ( update )
        s->ss->SaveState("state.dat");
    epsilon *= 0.999;
    s->mystage = START;
}

int lostCount = 0;

// TODO: For some reason the parameter here isn't what I'd expect it to be... 
// So i've just made it a global...
int Update(stuff* s_bleh){
    //cerr << "Update" << endl;
    //cerr << s << endl;
    bool IsStalled = s->rc->GetStall();
    if ( IsStalled ){
        EndEpisode();
        return 0;
    }

    double r;

    switch(s->mystage){
    case START:
        s->ss->StartTrial();
    case FIRST:
        s->s = s->ss->GetState();
        s->a = eps_greedy(epsilon, *(s->ss), s->s);
        switch(s->a){
        case Action::FORWARD:
            s->forward->doAction();
            break;
        case Action::LEFT:
            s->left->doAction();
            break;
        case Action::RIGHT:
            s->right->doAction();
            break;
        default:
            cerr << "WHAT THE WHAT" << endl;
            assert(false);
            break;
        }
        s->counter = 0;
        s->mystage = WAIT;
    case WAIT:
        s->counter++;
        if ( s->counter > 4 )
            s->mystage = WAIT_DONE;
        break;
    case WAIT_DONE:
        s->s_prime = s->ss->GetState();
        s->a_prime = eps_greedy(epsilon, *(s->ss), s->s_prime);
        r = rewardFunc(s->s_prime, (s->a==Action::FORWARD), IsStalled);
        if ( r == 0 ){
            lostCount++;
            if ( lostCount > 10 ) {
                lostCount=0;
                EndEpisode();
                if (update)
                    s->ss->Update(-10, s->a_prime, s->s_prime, s->a, s->s);
                return 0;
            }
        }
        else{
            lostCount = 0;
        }
        if ( update )
            s->ss->Update(r, s->a_prime, s->s_prime, s->a, s->s);
        cerr << "Reward: " << r << endl
            << "Epsilon: " << epsilon << endl;
        cerr << "Episode " << episodes << endl;
        s->s = s->s_prime;
        s->a = s->a_prime;
        s->mystage = FIRST;
        break;
    default:
        cerr << "WTF" << endl;
        break;
    }



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
        //ss.SaveState("state.dat");
    return 0;
}
