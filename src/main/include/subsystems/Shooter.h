// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix6/TalonFX.hpp>

// #define SHOOTER
// #define FEEDER
// #define HOPPER
#define TURRET

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

  ctre::phoenix6::controls::VoltageOut m_FeederVOut =
      ctre::phoenix6::controls::VoltageOut{0.0_V};
  ctre::phoenix6::controls::VelocityVoltage m_ShooterVOut =
      ctre::phoenix6::controls::VelocityVoltage{0_tps}.WithSlot(1);
  ctre::phoenix6::controls::VoltageOut m_HopperVOut =
      ctre::phoenix6::controls::VoltageOut{0.0_V};
  ctre::phoenix6::controls::VoltageOut m_IntakeVOut =
      ctre::phoenix6::controls::VoltageOut{0.0_V};
  /* Be able to switch which control request to use based on a button press */
  /* Start at velocity 0, use slot 1 */
  ctre::phoenix6::controls::VelocityVoltage m_velocityVoltage =
      ctre::phoenix6::controls::VelocityVoltage{0_tps}.WithSlot(1);

#ifdef SHOOTER
  ctre::phoenix6::hardware::TalonFX m_LShooterMotor{4, kCANBus};
  ctre::phoenix6::hardware::TalonFX m_RShooterMotor{5, kCANBus};
#endif
#ifdef FEEDER
  ctre::phoenix6::hardware::TalonFX m_LFeederMotor{1, kCANBus};
  ctre::phoenix6::hardware::TalonFX m_RFeederMotor{7, kCANBus};
#endif
#ifdef HOPPER
  ctre::phoenix6::hardware::TalonFX m_LHopperMotor{3, kCANBus};
#endif
#ifdef TURRET
  ctre::phoenix6::hardware::TalonFX m_LTurretMotor{2, kCANBus};
  ctre::phoenix6::hardware::TalonFX m_RTurretMotor{6, kCANBus};
#endif
};
