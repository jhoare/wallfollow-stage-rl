#include "RobotCenterPlayer.hpp"

RobotCenter::RobotCenter(){};

RobotCenterPlayer::RobotCenterPlayer() 
  : robot("localhost",6665), 
    lp(&robot,0),
    pp(&robot,0),
    sim(&robot,0)
{}


std::vector<double> RobotCenterPlayer::GetLaserReadings(){
    std::vector<double> laserReadings;
    if ( lp.IsValid() ){
        uint32_t count = lp.GetCount();
        for(uint32_t i = 0; i < count; i++)
            laserReadings.push_back(lp[i]);
    }
    return laserReadings;
}

void RobotCenterPlayer::Read(){
    robot.Read();
}

void RobotCenterPlayer::SetSpeed(double f, double r){
    pp.SetSpeed(f,r);
}

bool RobotCenterPlayer::GetStall(){
    return pp.GetStall();
}

void RobotCenterPlayer::ResetLocation(){
    sim.SetPose2d((char *)"robotProj3",
            RAND(X_MIN,X_MAX),
            RAND(Y_MIN,Y_MAX),
            RAND(-M_PI, M_PI));
}
