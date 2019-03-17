/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <cmath>

#include "ExtraMath.h"

#include <ctre/Phoenix.h>
#include <algorithm>

class DriveTrain {
 public:
  TalonSRX* frontLeft;
  TalonSRX* backLeft;
  TalonSRX* frontRight;
  TalonSRX* backRight;
  BaseMotorController* left;
  BaseMotorController* right;


  DriveTrain();

  void MenanumDrive(float xSpeed, float ySpeed, float rotation);
  void AdvMenanumDrive(float xSpeed, float ySpeed, float rotation, float gyro);
  void TankDrive(float left, float right);
  void ArcadeDrive(float forward, float rotation);
};
