// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Shooter.h"
#include <iostream>

using namespace ctre::phoenix6;

ShooterSubsystem::ShooterSubsystem() {
  ctre::phoenix6::configs::TalonFXConfiguration configs{};

  configs::FeedbackConfigs& Feedback = configs.Feedback;
  Feedback.SensorToMechanismRatio = 9;

  configs::MotionMagicConfigs& MotionMagic = configs.MotionMagic;
  MotionMagic.MotionMagicCruiseVelocity = 10_tps;
  MotionMagic.MotionMagicAcceleration = 10_tr_per_s_sq;

  configs.Slot0.kS = 0.25;
  configs.Slot0.kV = 0.12;
  configs.Slot0.kA = 0.01;
  configs.Slot0.kP = 90.0;
  configs.Slot0.kI = 0;
  configs.Slot0.kD = 1.5;

  configs.Voltage.PeakForwardVoltage = 12_V;
  configs.Voltage.PeakReverseVoltage = -12_V;

  ctre::phoenix::StatusCode status =
      ctre::phoenix::StatusCode::StatusCodeNotInitialized;
  for (int i = 0; i < 5; ++i) {
    status = m_TurretMotor.GetConfigurator().Apply(configs);
    if (status.IsOK())
      break;
  }
  if (!status.IsOK()) {
    std::cout << "Could not apply configs, error code: " << status.GetName()
              << std::endl;
  }
};

// This method will be called once per scheduler run
void ShooterSubsystem::Periodic() {}

void ShooterSubsystem::SetTurretAngle(units::angle::degree_t Angle) {

};