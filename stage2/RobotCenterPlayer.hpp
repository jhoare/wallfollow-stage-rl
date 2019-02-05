#pragma once 
#include "RobotCenter.hpp"
#include <libplayerc++/playerc++.h>

class RobotCenterPlayer : public RobotCenter{
    public:
        RobotCenterPlayer();
        virtual std::vector<double> GetLaserReadings();
        virtual void SetSpeed(double f, double r);
        virtual bool GetStall();
        virtual void ResetLocation();
        virtual void Read();
    private:
        PlayerCc::PlayerClient robot;
        PlayerCc::LaserProxy lp;//(&robot,0);
        PlayerCc::Position2dProxy pp;//(&robot,0);
        PlayerCc::SimulationProxy sim;//(&robot);
        int foo; 
};
