#include "RobotCenterStage.hpp"
#include<iostream>

using namespace Stg;
using namespace std;

RobotCenter::RobotCenter(){};

RobotCenterStage::RobotCenterStage(Stg::Model * mod)
: a_last(-1000), x_last(-1000),y_last(-1000)
{
    this->mod = mod;
    assert(mod);
    pos = (ModelPosition*)mod;
    assert(pos);
    laser = (ModelLaser*)mod->GetUnusedModelOfType( "laser" );
    assert(laser);
    pos->Subscribe();
    laser->Subscribe();
}

std::vector<double> RobotCenterStage::GetLaserReadings(){
    //cerr << "RCS: GetLaserReadings()" << endl;
    std::vector<double> laserReadings;
    std::vector<ModelLaser::Sample> samples = laser->GetSamples();
    for (int i = 0; i < samples.size(); i++)
        laserReadings.push_back(samples[i].range);
    return laserReadings;
}

/*
std::vector<double> RobotCenterStage::GetLaserReadings(){
    cerr << "RCS: GetLaserReadings()" << endl;
    std::vector<double> laserReadings;
    //std::vector<ModelLaser::Sample> samples = laser->GetSamples();
    for (int i = 0; i < laser->sensors.size(); i++)
        laserReadings.push_back(laser->sensors[i].range);
    return laserReadings;
}
*/

void RobotCenterStage::SetSpeed(double f, double r){
    //cerr << "RCS: SetSpeed()" << endl;
    pos->SetSpeed(f,0,r);
    //cerr << "RCS: SetSpeed:done()" << endl;
}

bool RobotCenterStage::GetStall(){
    //cerr << "RCS: GetStall()" << endl;
    //mod->TestCollision();
    // TODO: Find a better wayy
    if ( pos->est_pose.a == a_last &&
         pos->est_pose.x == x_last &&
         pos->est_pose.y == y_last )
        return true;
    else{
        a_last = pos->est_pose.a;
        x_last = pos->est_pose.x;
        y_last = pos->est_pose.y;
    }
    return false;
}

void RobotCenterStage::ResetLocation(){
    //cerr << "RCS: ResetLocation()" << endl;
    /*
    Pose pose((Stg::stg_meters_t)RAND(X_MIN,X_MAX),
              (Stg::stg_meters_t)RAND(Y_MIN,Y_MAX),
              (Stg::stg_meters_t)0,
              (Stg::stg_radians_t)RAND(-M_PI,M_PI));
              */
    // This one puts you in the little room on the bottom
    /*
    Pose pose((Stg::stg_meters_t)1,
              (Stg::stg_meters_t)-11,
              (Stg::stg_meters_t)0,
              (Stg::stg_radians_t)M_PI/2);
              */
    // This puts you on the left agains the wall
    Pose pose((Stg::stg_meters_t)-11,
              (Stg::stg_meters_t)1,
              (Stg::stg_meters_t)0,
              (Stg::stg_radians_t)M_PI/2);
    mod->SetGlobalPose(pose);
}

void RobotCenterStage::Read(){
    //cerr << "RCS: Read()" << endl;
    // Do Nothing
}
