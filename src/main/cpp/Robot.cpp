// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <iostream>
#include "ctre/phoenix6/SignalLogger.hpp"

using namespace ctre::phoenix6;

Robot::Robot() {

  ctre::phoenix6::SignalLogger::EnableAutoLogging(false);
  
  configs::TalonFXConfiguration configs{};

  configs::FeedbackConfigs &fdb = configs.Feedback;
  fdb.SensorToMechanismRatio = 9;

  configs::MotionMagicConfigs &mm = configs.MotionMagic;
  mm.MotionMagicCruiseVelocity = 10_tps;
  mm.MotionMagicAcceleration = 10_tr_per_s_sq;

  configs.Slot0.kS = 0.25;
  configs.Slot0.kV = 0.12;
  configs.Slot0.kA = 0.01;
  configs.Slot0.kP = 90.0;
  configs.Slot0.kI = 0;
  configs.Slot0.kD = 1.5;

  configs.Voltage.PeakForwardVoltage = 12_V;
  configs.Voltage.PeakReverseVoltage = -12_V;

  ctre::phoenix::StatusCode status = ctre::phoenix::StatusCode::StatusCodeNotInitialized;
  for (int i = 0; i < 5; ++i) {
    status = m_Turret.GetConfigurator().Apply(configs);
    if (status.IsOK()) break;
  }
  if (!status.IsOK()) {
    std::cout << "Could not apply configs, error code: " << status.GetName() << std::endl;
  }

  m_Turret.SetPosition(0_tr);
}

void Robot::RobotPeriodic() {
  if (++m_printCount >= 10) {
    m_printCount = 0;
    //std::cout << "Pos: " << m_Turret.GetPosition() << std::endl;
    //std::cout << "Vel: " << m_Turret.GetVelocity() << std::endl;
    //std::cout << std::endl;
  }
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
//   double Y = m_DriverController.GetY();
//   if (fabs(Y) < 0.1) Y = 0;

//   m_Turret.SetControl(m_mmReq.WithPosition(Y * 10_tr).WithSlot(0));

  if (m_DriverController.GetRawButton(7)) {
    m_Turret.SetControl(m_mmReq.WithPosition(360_deg).WithSlot(0));
  }

  if (m_DriverController.GetRawButton(8)) {
    m_Turret.SetControl(m_mmReq.WithPosition(0_tr).WithSlot(0));
  }

  if (m_DriverController.GetRawButton(9)) {
    m_Turret.SetControl(m_mmReq.WithPosition(-360_deg).WithSlot(0));
  }
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
