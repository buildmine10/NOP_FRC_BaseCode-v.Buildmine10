/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <memory>

#include "DriveTrain.h"

#include <frc/WPILib.h>
#include <frc/AnalogInput.h>
#include "NetworkTables/NetworkTableInstance.h"

class Teleop {
 public:
  frc::Joystick* moveController;
  frc::Joystick* maniController;
  enum DriveModes {TankDrive, ArcadeDrive};
  DriveModes driveMode = DriveModes::ArcadeDrive;
  std::shared_ptr<NetworkTable> table;
  frc::AnalogInput* distanceSensor;
  std::shared_ptr<DriveTrain> driveTrain;

  float kpAngle = 0.025f;
  float kiAngle = 0.00005f;
  float kpDistance = 0.001f;
  float kdDistance = 0.0f;
  float totalErrorAngle = 0.0f;
  float pastErrorDistance = 0.0f;
  int targetDistance = 500;

  Teleop(std::shared_ptr<DriveTrain> driveTrain);

  void MasterControl();
  void AutoApproach();
  void ResetErrors();

  bool IsTargeting();
  float TargetOffsetX();
  float TargetOffsetY();
  float TargetArea();
  float TargetSkew();
};
