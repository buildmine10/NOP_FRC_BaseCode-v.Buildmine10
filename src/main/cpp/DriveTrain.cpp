/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriveTrain.h"

DriveTrain::DriveTrain() {
    this->frontLeft = new TalonSRX(1);
    this->backLeft = new TalonSRX(3);
    this->frontRight = new TalonSRX(2);
    this->backRight = new TalonSRX(4);

    this->frontLeft->ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
    this->frontRight->ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);

    this->frontLeft->SetInverted(true);
    this->backLeft->SetInverted(true);
    //this->left->SetInverted(true);  would undo the individual inversion required for mecanum

    this->frontLeft->Follow(*left);
    this->backLeft->Follow(*left);
    this->frontRight->Follow(*right);
    this-> backRight->Follow(*right);
}

void DriveTrain::MenanumDrive(float xSpeed, float ySpeed, float rotation){
    this->frontLeft->Set(ControlMode::PercentOutput, ExtraMath::Clamp((xSpeed + ySpeed) / sqrtf(2.f) + rotation, -1.f, 1.f));

    this->backRight->Set(ControlMode::PercentOutput, ExtraMath::Clamp((xSpeed + ySpeed) / sqrtf(2.f) - rotation, -1.f, 1.f));

    this->backLeft->Set(ControlMode::PercentOutput, ExtraMath::Clamp((-xSpeed + ySpeed) / sqrtf(2.f) + rotation, -1.f, 1.f));

    this->frontRight->Set(ControlMode::PercentOutput, ExtraMath::Clamp((-xSpeed + ySpeed) / sqrtf(2.f) - rotation, -1.f, 1.f));
}

void DriveTrain::AdvMenanumDrive(float xSpeed, float ySpeed, float rotation, float gyro){
    float angle = atan2f(ySpeed, xSpeed) - gyro;
    float magnitude = sqrtf(powf(xSpeed, 2) + powf(ySpeed, 2));
    float correctXSpeed = cos(angle) * magnitude;
    float correctYSpeed = sin(angle) * magnitude;

    this->frontLeft->Set(ControlMode::PercentOutput, ExtraMath::Clamp((correctXSpeed + correctYSpeed) / sqrtf(2.f) + rotation, -1.f, 1.f));

    this->backRight->Set(ControlMode::PercentOutput, ExtraMath::Clamp((correctXSpeed + correctYSpeed) / sqrtf(2.f) - rotation, -1.f, 1.f));

    this->backLeft->Set(ControlMode::PercentOutput, ExtraMath::Clamp((-correctXSpeed + correctYSpeed) / sqrtf(2.f) + rotation, -1.f, 1.f));

    this->frontRight->Set(ControlMode::PercentOutput, ExtraMath::Clamp((-correctXSpeed + correctYSpeed) / sqrtf(2.f) - rotation, -1.f, 1.f));
}

void DriveTrain::TankDrive(float left, float right){
    this->left->Set(ControlMode::PercentOutput, ExtraMath::Clamp(left, -1.f, 1.f));
    this->right->Set(ControlMode::PercentOutput, ExtraMath::Clamp(right, -1.f, 1.f));
}

void DriveTrain::ArcadeDrive(float forward, float rotation){
    this->left->Set(ControlMode::PercentOutput, ExtraMath::Clamp(forward + rotation, -1.f, 1.f));
    this->right->Set(ControlMode::PercentOutput, ExtraMath::Clamp(forward - rotation, -1.f, 1.f));
}
