#pragma once 
//#include <libplayerc++/playerc++.h>
#include "Matrix.hpp"
#include "ActionSet.hpp"
#include <cmath>

/// Distance from the wall
static const double d_w = 0.75;
/// How far we can be from d_w and still be "at" d_w
static const double epsilon_w = 0.25;

/// The number of states that a laser region can have
static const int num_of_laser_states = 3;
/// The number of laser regions
static const int num_of_laser_regions = 4;

static const int follow_laser_region = (num_of_laser_regions-1);

static const int num_of_actions = 3;
static const int num_of_states = std::pow(num_of_laser_states,num_of_laser_regions);

// Stupid User-Defined Parameters
static const double lambda = 0.9;
static const double _gamma = 0.7;
static const double alpha = 0.1;

enum reading{
    LOW=0,
    MEDIUM=1,
    HIGH=2};
/*
enum reading{
    LOW=0,
    SLIGHTLY_CLOSE=1,
    MEDIUM=2,
    SLIGHTLY_FAR=3,
    HIGH=4};
    */

struct State{
    reading readings[num_of_laser_regions];
    //reading left;
    //reading center;
    //reading right;
    //double leftDistance;
    //double rightDistance;
};

double rewardFunc(const State& s, bool forward, bool stalled);

class StateSpace{
    public:
    StateSpace(RobotCenter& rc, int states, int actions);
    State GetState();
    void Update(double reward, Action::ActionType a_prime, State s_prime, Action::ActionType a, State s);
    // Start a "learning" trial... 
    void StartTrial();
    Action::ActionType GetBestAction(State& s);
    static int GetStateIndexMapping(State& s);
    void LoadState(const char* file);
    void SaveState(const char* file);

    private:
    reading DetermineReading(double reading);

    private:
    RobotCenter& rc;
    //PlayerCc::LaserProxy& lp;
    dMatrix Q;
    dMatrix E;
    int states, actions;
};
