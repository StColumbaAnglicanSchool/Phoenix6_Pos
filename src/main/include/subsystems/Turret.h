// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <numbers>

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
         int turretMotorCANBusID, int turretCANCoderID, std::string turretName);
  /**
   * Initialize the Turret Motor internal position register
   * using the absolute position of the turret CANCoder.
   */
  void InitializeTurretAngle();

  /**
   * Motion Magic the turret to the Angle.
   *
   * @param Angle The Angle to move to in Degrees
   */
  void SetTurretAngle(units::angle::degree_t Angle);

  /**
   * Read the turret angle based on the turret motor internal position
   *
   * @return Curret turret angle in degrees
   */
  units::angle::degree_t GetTurretAngle();

  /**
   * Set the speed of the Shooter
   *
   * @param speed in turns_per_second
   */
  void SetShooterSpeed(units::turns_per_second_t speed);

  /**
   * Checks if the shooter has reached the set speed
   *
   * @return returns True or False
   */
  bool IsShooterAtSpeed();

  /**
   * Set the speed of the Feeder
   *
   * @param speed in turns_per_second
   */
  void SetFeederSpeed(units::turns_per_second_t speed);

  /**
   * Checks if the shooter has reached the set speed
   *
   * @return returns True or False
   */
  bool IsFeederAtSpeed();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  hardware::TalonFX m_shooterMotor;
  hardware::TalonFX m_feederMotor;
  hardware::TalonFX m_turretMotor;
  hardware::CANcoder m_turretCANCoder;
  std::string m_turretName;

  // Members variables to hold the most recent setpoints
  units::turns_per_second_t m_targetVelocityShooter{0_tps};
  units::turns_per_second_t m_targetVelocityFeeder{0_tps};
  units::degree_t m_targetTurretAngle{0_deg};

  // Create control objects to use the variuos modes of control
  controls::VelocityVoltage m_voltageVelocity{0_tps};
  controls::VoltageOut m_voltageOut{0.0_V};
  controls::PositionVoltage m_positionControl{0_tr};
  controls::MotionMagicVoltage m_motionMagicControl{0_tr};

  // Example Alert messeage that can be set in code
  frc::Alert m_shooterAlertInfo{"Shooter Subsystem Info",
                                frc::Alert::AlertType::kInfo};
  frc::Alert m_shooterAlertWarning{"Shooter Subsystem Warning",
                                   frc::Alert::AlertType::kWarning};
  frc::Alert m_shooterAlertError{"Shooter Subsystem Error",
                                 frc::Alert::AlertType::kError};
};  // End of Turret Class Definition
