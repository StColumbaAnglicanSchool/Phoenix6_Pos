// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/ShooterSubsystem.h"
#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Rotation2d.h>
#include <frc2/command/FunctionalCommand.h>
#include "subsystems/Turret.h"
#include "subsystems/Turret.h"

#include <iostream>

ShooterSubsystem::ShooterSubsystem() {
  ctre::phoenix6::configs::TalonFXConfiguration hopperConfig{};
  
  hopperConfig.Slot0.kS = 0.1;
  hopperConfig.Slot0.kV = 0.12;
  hopperConfig.Slot0.kA = 0.01;
  hopperConfig.Slot0.kP = 0;
  hopperConfig.Slot0.kI = 0;
  hopperConfig.Slot0.kD = 0;

  hopperConfig.Voltage.PeakForwardVoltage = 12_V;
  hopperConfig.Voltage.PeakReverseVoltage = -12_V;

  ctre::phoenix::StatusCode status =
      ctre::phoenix::StatusCode::StatusCodeNotInitialized;

  // Try to apply the Hopperer motor config object up to 5 times.
  for (int i = 0; i < 5; ++i) {
    status = m_hopperMotor.GetConfigurator().Apply(hopperConfig);
    if (status.IsOK())
      break;
  }
  if (!status.IsOK()) {
    std::cout << "Could not apply configs, error code: " << status.GetName()
              << std::endl;
  }
};

frc::Pose2d pose;

// This method will be called once per scheduler run
void ShooterSubsystem::Periodic() {
  if (m_LeftTargetTracking) {
    // Turret is actively tracking target
    // m_LeftShooter.SetTurretAngle();
  }
}

void ShooterSubsystem::TrackLeftTarget(bool TrackingOn) {
  m_LeftTargetTracking = TrackingOn;
};

frc2::CommandPtr ShooterSubsystem::TargettingOnCmd() {
  return RunOnce([this] { TrackLeftTarget(true); });
};

frc2::CommandPtr ShooterSubsystem::TargetToZeroCMD() {
  return RunOnce([this] {
    fmt::println("[COMMAND] Move to 0 degrees");
    m_LeftShooter.SetTurretAngle(0_deg);
  });
};

frc2::CommandPtr ShooterSubsystem::TargetTo90DegreesCMD() {
  return RunOnce([this] {
    fmt::println("[COMMAND] Move to 90 degrees");
    m_LeftShooter.SetTurretAngle(90_deg);
  });
};

frc2::CommandPtr ShooterSubsystem::TargetToNeg90DegreesCMD() {
  return RunOnce([this] {
    fmt::println("[COMMAND] Move to -90 degrees");
    m_LeftShooter.SetTurretAngle(-90_deg);
  });
};

/*
Functional Command Format:
[] {Init}
[] {Periodic}
[] {End}
[] {Is Finished}
*/

frc2::CommandPtr ShooterSubsystem::CheckShooterSpeedCMD() {
  return frc2::FunctionalCommand([] {fmt::println("[COMMAND] CheckShooterSpeedCMD commenced...");}, [] {}, [](bool interrupted) {},
                                 [this] { return m_LeftShooter.IsShooterAtSpeed(); }, {this})
                                 .ToPtr();
};
frc2::CommandPtr ShooterSubsystem::KillShooterCMD() {
  return frc2::FunctionalCommand([this] {m_LeftShooter.SetShooterSpeed(0_tps);}, [] {}, [](bool interrupted) {},
                                 [] {return true;}, {this})
                                 .ToPtr();
};
frc2::CommandPtr ShooterSubsystem::SetShooterSpeedCMD(units::turns_per_second_t Speed) {
  return RunOnce(
      [this, Speed] {
        fmt::println("[COMMAND] Setting Shooter Speed to {} tps", Speed.value());
        m_LeftShooter.SetShooterSpeed(Speed);
      });
}

frc2::CommandPtr ShooterSubsystem::CheckFeederSpeedCMD() {
  return frc2::FunctionalCommand([] {fmt::println("[COMMAND] CheckFeederSpeedCMD commenced...");}, [] {}, [](bool interrupted) {},
                                 [this] { return m_LeftShooter.IsFeederAtSpeed(); }, {this})
                                 .ToPtr();
};
frc2::CommandPtr ShooterSubsystem::KillFeederCMD() {
  return frc2::FunctionalCommand([this] {m_LeftShooter.SetFeederSpeed(0_tps);}, [] {}, [](bool interrupted) {},
                                 [] {return true;}, {this})
                                 .ToPtr();
};
frc2::CommandPtr ShooterSubsystem::SetFeederSpeedCMD(units::turns_per_second_t Speed) {
  return RunOnce(
      [this, Speed] {
        fmt::println("[COMMAND] Setting Feeder Speed to {} tps", Speed.value());
        m_LeftShooter.SetFeederSpeed(Speed);
      });
}

frc2::CommandPtr ShooterSubsystem::KillHopperCMD() {
  return frc2::FunctionalCommand([this] {m_hopperMotor.SetControl(m_voltageVelocity.WithVelocity(0_tps));}, [] {}, [](bool interrupted) {},
                                 [] {return true;}, {this})
                                 .ToPtr();
};
frc2::CommandPtr ShooterSubsystem::SetHopperSpeedCMD(units::turns_per_second_t Speed) {
  return RunOnce(
      [this, Speed] {
        fmt::println("[COMMAND] Setting Hopper Speed to {} tps", Speed.value());
        m_hopperMotor.SetControl(m_voltageVelocity.WithVelocity(Speed));
      });
}