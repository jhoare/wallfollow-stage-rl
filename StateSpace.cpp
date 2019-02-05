#include "StateSpace.hpp"
//#include <libplayerc++/playerc++.h>
#include <iostream>
#include <fstream>
using namespace std;

double rewardFunc(const State& s, bool forward, bool stalled){
    static bool was_in_goal = false;
    //if ( s.left == MEDIUM || s.right == MEDIUM )

    // If I've stalled i've hit a wall
    if ( stalled == true )
        return -10;

    for (int i = 0; i < num_of_laser_regions; i++)
        if ( s.readings[i] == LOW ){
            was_in_goal = false;
            return -1;
        }

    if ( s.readings[follow_laser_region] == MEDIUM ){
        was_in_goal = true;
        return forward ? 2 : 0.25;
        //return (s.readings[0] == HIGH) ? 2 : 1;
        //return forward ? 4 : 2;
    }
    /*
    if ( s.readings[follow_laser_region] == SLIGHTLY_CLOSE ||
         s.readings[follow_laser_region] == SLIGHTLY_FAR){
        was_in_goal = true;
        return 1;
    }
    */

    if ( was_in_goal ){
        was_in_goal = false;
        return -1;
    }

    return 0;
}
/*
double rewardFunc(const State& s, bool stalled){
    //if ( s.left == MEDIUM || s.right == MEDIUM )

    // If I've stalled i've hit a wall
    if ( stalled == true )
        return -10;

    if ( s.readings[follow_laser_region] == MEDIUM )
        return 2;
    else if ( s.readings[follow_laser_region] == SLIGHTLY_CLOSE 
           || s.readings[follow_laser_region] == SLIGHTLY_FAR )
        return 1;


    for (int i = 0; i < num_of_laser_regions; i++)
        if ( s.readings[i] == LOW )
            return -1;

    return 0;
}
*/

StateSpace::StateSpace(RobotCenter& rc, int states, int actions)
: rc(rc), Q(actions,states,0), E(actions,states,0), 
  states(states), actions(actions)
{
}

int StateSpace::GetStateIndexMapping(State& s){
    int index = 0;
    for (int i = 0; i < num_of_laser_regions; i++){
        assert(s.readings[i] < num_of_laser_states);
        cerr << "reading[" << i << "] = " << s.readings[i] << endl;
        index += pow(num_of_laser_states,i)*s.readings[i];
    }
    cerr << "index: " << index << endl;
    return index;
}

Action::ActionType StateSpace::GetBestAction(State& s){
    int bestAction = 0;
    int s_index = StateSpace::GetStateIndexMapping(s);
    double bestActionValue = Q(0,s_index);
    for (int i = 1; i < actions; i++){
        if ( Q(i,s_index) > bestActionValue ){
            bestActionValue = Q(i,s_index);
            bestAction = i;
        }
    }
    return (Action::ActionType)bestAction;
}

State StateSpace::GetState(){
    State theCurrentState;
    double sums[num_of_laser_regions];
    for (int i = 0; i < num_of_laser_regions; i++)
        sums[i] = 1000;
    vector<double> lp = rc.GetLaserReadings();
    if ( lp.size() > 0 ){
        int count = lp.size();
        int cutOff = count/(num_of_laser_regions-1);
        cout << "count: " << count << "cutOff: " << cutOff << endl;

        // Sum up the laser scans in each "area" 
        for (int i = 0; i < count; i++){
            if ( i < cutOff/2 ){
                sums[0] = min(sums[0],lp[i]);
            } else if ( i < cutOff ){
                sums[1] = min(sums[1],lp[i]);
            } else if ( i < cutOff*2 ){
                sums[2] = min(sums[2],lp[i]);
            }
            else{
                sums[3] = min(sums[3],lp[i]);
            }
            /*
            for (int j = 0; j < num_of_laser_regions; j++){
                // Special case for the remainder 
                if ( j == num_of_laser_regions-1 && i > cutOff*(j) ){
                    sums[j] = min(sums[j], lp[i]);
                    break;
                } else if ( i < cutOff*(j+1) && i > cutOff*(j) ){
                    sums[j] = min(sums[j], lp[i]);
                    break;
                }
            }
            */
        }
        /*
        for (int i = 0; i < num_of_laser_regions; i++){
            if ( i > 0 )
                sums[i] = lp[cutOff*i+2];
            else
                sums[i] = lp[cutOff*i];
        }
        // Special case for the last "region"
        sums[num_of_laser_regions-1] = lp[count-1];
        */
        for ( int i = 0; i < num_of_laser_regions; i++ ){
            theCurrentState.readings[i] = DetermineReading(sums[i]);
        }

        // Get the average
        //for (int i = 0; i < 3; i++) {
        //    sums[i] /= cutOff;
        //    //cout << "sum[" << i << "]: " << sums[i] << endl;
        //}

        //theCurrentState.left = DetermineReading(sums[2]);
        //theCurrentState.center = DetermineReading(sums[1]);
        //theCurrentState.right = DetermineReading(sums[0]);
    }
    else { 
        cerr << "Not Valid" << endl;
    }

    return theCurrentState;
}

void StateSpace::StartTrial(){
    E *= 0;
}

void StateSpace::LoadState(const char* file){
    fstream infile(file, ios::in);
    infile >> Q;
    StartTrial();
    infile.close();
}

void StateSpace::SaveState(const char* file){
    fstream outfile(file, ios::out);
    outfile << Q;
    outfile.close();
}

void StateSpace::Update(double reward, 
                        Action::ActionType a_prime, State s_prime, 
                        Action::ActionType a, State s){
    double delta;
    int s_p_index = StateSpace::GetStateIndexMapping(s_prime);
    int s_index = StateSpace::GetStateIndexMapping(s);
    /*
    cout << "a' = " << a_prime << endl
         << "a  = " << a << endl 
         << "s_p_i = " << s_p_index << endl
         << "s_index = " << s_index << endl;
         */
    delta = reward + _gamma * Q.at(a_prime,s_p_index) - Q.at(a,s_index);
    E.at(a,s_index) += 1;

    // For all s,a:
    Q += E * (alpha * delta);
    E *= _gamma * lambda;
}

reading StateSpace::DetermineReading(double reading){
    /*
    if ( reading > d_w*5 ){
        return FAR;
    } else */if ( reading > d_w + epsilon_w){//*2 ){
        return HIGH;
        /*
    } else if ( reading > d_w + epsilon_w ) { 
        return SLIGHTLY_FAR;
        */
    } else if ( reading > (d_w - epsilon_w) ){
        return MEDIUM;
        /*
    } else if ( reading > (d_w - epsilon_w*2) ){
        return SLIGHTLY_CLOSE;
        */
    } else {
        return LOW;
    }
}
