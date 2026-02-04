// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <numbers>

//#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/controls/MotionMagicVoltage.hpp>
#include <ctre/phoenix6/controls/VelocityVoltage.hpp>
#include <ctre/phoenix6/controls/PositionVoltage.hpp>
#include <ctre/phoenix6/CANCoder.hpp>

#include "Constants.h"
#include <frc/Alert.h>

using namespace ctre::phoenix6;

class Turret {
 public:
  Turret(int shooterMotorCANBusID, int feederMotorCANBusID,
                   int turretMotorCANBusID, int turretCANCoderID,
                   std::string turretName);

  void InitializeTurretAngle();

  void SetTurretAngle(units::angle::degree_t Angle);

  units::angle::degree_t GetTurretAngle();

  void SetShooterSpeed(units::turns_per_second_t speed);

  bool IsShooterAtSpeed();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  hardware::TalonFX m_shooterMotor;
  hardware::TalonFX m_feederMotor;
  hardware::TalonFX m_turretMotor;
  hardware::CANcoder m_turretCANCoder;
  std::string m_turretName;
  
  units::turns_per_second_t m_targetVelocity{0_tps};
  units::degree_t m_targetTurretAngle{0_deg};  

  controls::VelocityVoltage m_voltageVelocity{0_tps};
  controls::PositionVoltage m_positionControl{0_tr};
  controls::MotionMagicVoltage m_motionMagicControl{0_tr};

  frc::Alert m_shooterAlertInfo{"Shooter Subsystem Info",
                                frc::Alert::AlertType::kInfo};
  frc::Alert m_shooterAlertWarning{"Shooter Subsystem Warning",
                                   frc::Alert::AlertType::kWarning};
  frc::Alert m_shooterAlertError{"Shooter Subsystem Error",
                                 frc::Alert::AlertType::kError};
};
