// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix6/TalonFX.hpp>

class ShooterSubsystem : public frc2::SubsystemBase {
 public:
  ShooterSubsystem();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  void SetTurretAngle(units::angle::degree_t Angle);

  void SetShooterActive(bool Trigger);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  ctre::phoenix6::CANBus kCANBus{"rio"};
  ctre::phoenix6::controls::MotionMagicVoltage m_MotionMagicRequest{0_tr};
  ctre::phoenix6::hardware::TalonFX m_TurretMotor{2, kCANBus};
};
