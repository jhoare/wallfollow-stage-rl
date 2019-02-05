#include "StateSpace.hpp"
#include <iostream>
#include "RobotCenterStage.hpp"

using namespace std;
using namespace Stg;

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
    ((RobotCenterStage*)(s->rc))->laser->AddCallback(Stg::Model::CB_UPDATE, (model_callback_t)Update, s );
    ((RobotCenterStage*)(s->rc))->laser->Subscribe();
    cerr << "Init Done" << endl;
    cerr << s << endl;
}

int Update(stuff* asdf){
    s->s = s->ss->GetState();
    for (int i = 0; i < num_of_laser_regions; i++){
        cerr << "s.regions[i] = " << s->s.readings[i] << endl;
    }
    cerr << "reward: " << rewardFunc(s->s,false,false) << endl << endl;

    //count = count+1;

    //s->rc->SetSpeed(count/1000,0);
    return 0;
}
