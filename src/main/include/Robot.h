// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include "ctre/phoenix6/TalonFX.hpp"
#include <frc/smartdashboard/SendableChooser.h>
// #include <frc/XboxController.h>
#include <frc/Joystick.h>

#include "LimelightHelpers.h"

#define TURRET

class Robot : public frc::TimedRobot {
 public:
  Robot();
  void RobotPeriodic() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void DisabledInit() override;
  void DisabledPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;

  void SimulationInit() override;
  void SimulationPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  ctre::phoenix6::CANBus kCANBus{"rio"};
  ctre::phoenix6::controls::MotionMagicVoltage m_mmReq{0_tr};
  int m_printCount = 0;

  #ifdef TURRET
  ctre::phoenix6::hardware::TalonFX m_Turret{2, kCANBus};
  #endif

  ctre::phoenix6::controls::PositionVoltage m_turretVoltage = ctre::phoenix6::controls::PositionVoltage{0_tr}.WithSlot(0);
  ctre::phoenix6::controls::StaticBrake m_brake{};
  frc::Joystick m_DriverController{0};
};
