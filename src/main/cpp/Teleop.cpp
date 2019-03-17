/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Teleop.h"

Teleop::Teleop(std::shared_ptr<DriveTrain> driveTrain) {
    moveController = new frc::Joystick(0);
    maniController = new frc::Joystick(1);
    distanceSensor = new frc::AnalogInput(0);
    table = NetworkTable::GetTable("limelight");
    this->driveTrain = driveTrain;
}

void Teleop::MasterControl(){
    switch(driveMode){
        case 0:
            driveTrain->TankDrive(moveController->GetRawAxis(1), moveController->GetRawAxis(5));
        break;
        case 1:
            driveTrain->ArcadeDrive(moveController->GetRawAxis(1), moveController->GetRawAxis(4));
        break;
        case 2:
            
        break;
        default:
            driveTrain->ArcadeDrive(moveController->GetRawAxis(1), moveController->GetRawAxis(4));
        break;
    }
}

void Teleop::ResetErrors(){
    totalErrorAngle = 0.0f;
    pastErrorDistance = 0.0f;
}

void Teleop::AutoApproach(){
    float errorAngle = -TargetOffsetX();
    float errorDistance = targetDistance - distanceSensor->GetValue();
    totalErrorAngle += errorAngle;
    float deltaErrorDistance = errorDistance - pastErrorDistance; 
    pastErrorDistance = errorDistance;

    float leftSpeed = (kpAngle * errorAngle) + (kiAngle * totalErrorAngle) + (kpDistance * errorDistance) + (kdDistance * deltaErrorDistance);
    float rightSpeed = -((kpAngle * errorAngle) + (kiAngle * totalErrorAngle)) + (kpDistance * errorDistance) + (kdDistance * deltaErrorDistance);

    driveTrain->TankDrive(leftSpeed, rightSpeed);
}


bool Teleop::IsTargeting(){return (table->GetNumber("tv", 0.0) == 1) ? true : false;}
float Teleop::TargetOffsetX(){return table->GetNumber("tx", 0.0);}
float Teleop::TargetOffsetY(){return table->GetNumber("ty", 0.0);}
float Teleop::TargetArea(){return table->GetNumber("ta", 0.0);}
float Teleop::TargetSkew(){return table->GetNumber("ts", 0.0);}
