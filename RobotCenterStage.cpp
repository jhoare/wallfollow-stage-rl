#include "RobotCenterPlayer.hpp"

using namespace Stg;


RobotCenterStage::RobotCenterStage(Stg::Model * mod)
{
    this->mod = mod;
    assert(mod);
    pos = (ModelPosition*)mod;
    assert(pos);
    laser = (ModelRanger*)mod->GetUnusedModelOfType( "laser" );
    assert(laser);
}


std::vector<double> RobotCenterStage::GetLaserReadings(){
    std::vector<double> laserReadings;
    std::vector<ModelLaser::Sample> samples& = laser->GetSamples();
    for (int i = 0; i < samples.size(); i++)
        laserReadings.push_back(samples[i].range);
    return laserReadings;
}

void RobotCenterStage::SetSpeed(double f, double r){
    pos->SetSpeed(f,0,r);
}

bool RobotCenterStage::GetStall(){
    mod->TestCollision();
}

void RobotCenterStage::ResetLocation(){
    Pose pose(RAND(X_MIN,X_MAX),RAND(Y_MIN,Y_MAX),RAND(-M_PI,M_PI));
    mod->SetGlobalPose(pose);
}

void RobotCenterStage::Read(){
    // Do Nothing
}
