// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc2/command/CommandPtr.h>
#include "subsystems/Turret.h"
#include "Constants.h"
#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Rotation2d.h>
#include <frc2/command/FunctionalCommand.h>

using namespace ShooterConstants;

class ShooterSubsystem : public frc2::SubsystemBase {
 public:
  ShooterSubsystem();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  void TrackLeftTarget(bool TrackingOn);

  frc2::CommandPtr TargettingOnCmd();

  frc2::CommandPtr TargetToZeroCMD();

  frc2::CommandPtr TargetTo90DegreesCMD();

  frc2::CommandPtr TargetToNeg90DegreesCMD();

  frc2::CommandPtr SetShooterSpeedCMD(units::turns_per_second_t Speed);
  frc2::CommandPtr CheckShooterSpeedCMD();
  frc2::CommandPtr KillShooterCMD();

  frc2::CommandPtr SetFeederSpeedCMD(units::turns_per_second_t Speed);
  frc2::CommandPtr CheckFeederSpeedCMD();
  frc2::CommandPtr KillFeederCMD();
  
  frc2::CommandPtr SetHopperSpeedCMD(units::turns_per_second_t Speed);
  frc2::CommandPtr CheckHopperSpeedCMD();
  frc2::CommandPtr KillHopperCMD();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  Turret m_LeftShooter{kLeftShooterID, kLeftFeederID, kLeftTurretID,
                       kLeftTurretCANCoderID, "Left Shooter"};

  hardware::TalonFX m_hopperMotor{54};
  controls::VelocityVoltage m_voltageVelocity{0_tps};

  bool m_LeftTargetTracking = false;
};
