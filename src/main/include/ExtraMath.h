/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

class ExtraMath {
 public:
  ExtraMath();

  template <class T>
  static T Clamp(T input, T min, T max){return (input < min) ? min : (input > max) ? max : input;}
};
