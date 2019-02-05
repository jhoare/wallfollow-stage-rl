#pragma once 
#include<vector>
#define RAND(a,b) rand() * ((double)b-a) / (double)RAND_MAX + (double)a

static const float X_MAX = -7;
static const float X_MIN = -10.5;
static const float Y_MAX = 5;
static const float Y_MIN = -2;
 /*
static const float X_MAX = 3;
static const float X_MIN = 1;
static const float Y_MAX = -7;
static const float Y_MIN = -11;
*/

// A facade class so we can work as a stage plugin or for player...
class RobotCenter{
    public:
        RobotCenter();
        virtual std::vector<double> GetLaserReadings()=0;
        virtual void SetSpeed(double f, double r)=0;
        virtual bool GetStall()=0;
        virtual void ResetLocation()=0;
        virtual void Read()=0;
};

