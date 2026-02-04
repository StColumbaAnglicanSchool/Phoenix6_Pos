// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/ShooterSubsystem.h"


ShooterSubsystem::ShooterSubsystem() = default;

// This method will be called once per scheduler run
void ShooterSubsystem::Periodic() {
  if (m_LeftTargetTracking) {
    // Turret is actively tracking target
    //m_LeftShooter.SetTurretAngle();
  }
}

void ShooterSubsystem::TrackLeftTarget(bool TrackingOn) {
    m_LeftTargetTracking = TrackingOn;
};

frc2::CommandPtr ShooterSubsystem::TargettingOnCmd() {
    return RunOnce([this] {
        TrackLeftTarget(true);
    });
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

frc2::CommandPtr ShooterSubsystem::SetShooterSpeedCMD() {
    return StartEnd([this] {
        fmt::println("[COMMAND] Setting Shooter Speed to 60 tps");
        m_LeftShooter.SetShooterSpeed(60_tps);
    }, [this] {
        m_LeftShooter.SetShooterSpeed(0_tps);
    });
}