// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <iostream>
#include "ctre/phoenix6/SignalLogger.hpp"
#include <frc2/command/CommandScheduler.h>

using namespace ctre::phoenix6;

Robot::Robot() {
  ctre::phoenix6::SignalLogger::EnableAutoLogging(false);
}

void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
//   double Y = m_DriverController.GetY();
//   if (fabs(Y) < 0.1) Y = 0;

//   m_Turret.SetControl(m_mmReq.WithPosition(Y * 10_tr).WithSlot(0));

  // if (m_DriverController.GetRawButton(7)) {
  //   m_Turret.SetControl(m_mmReq.WithPosition(360_deg).WithSlot(0));
  // }

  // if (m_DriverController.GetRawButton(8)) {
  //   m_Turret.SetControl(m_mmReq.WithPosition(0_tr).WithSlot(0));
  // }

  // if (m_DriverController.GetRawButton(9)) {
  //   m_Turret.SetControl(m_mmReq.WithPosition(-360_deg).WithSlot(0));
  // }
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
