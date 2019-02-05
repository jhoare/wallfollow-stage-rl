#pragma once 
#include "RobotCenter.hpp"
#include <stage.hh>

class RobotCenterStage : public RobotCenter{
    public:
        RobotCenterStage(Stg::Model* mod);
        virtual std::vector<double> GetLaserReadings();
        virtual void SetSpeed(double f, double r);
        virtual bool GetStall();
        virtual void ResetLocation();
        virtual void Read();
    public:
        Stg::Model* mod;
        Stg::ModelPosition* pos;
        //Stg::ModelRanger* laser;
        Stg::ModelRanger* laser;

        Stg::radians_t a_last;
        Stg::meters_t x_last;
        Stg::meters_t y_last;
};
