#pragma once 
#include "RobotCenter.hpp"
#include <stage.h>

class RobotCenterStage : public RobotCenter{
    public:
        RobotCenterPlayer(Stg::Model* mod);
        virtual std::vector<double> GetLaserReadings();
        virtual void SetSpeed(double f, double r);
        virtual bool GetStall();
        virtual void ResetLocation();
        virtual void Read();
    private:
        Stg::Model* mod;
        Stg::ModelPosition* pos;
        Stg::ModelLaser* laser;
};
