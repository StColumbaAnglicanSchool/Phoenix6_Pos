// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Turret.h"
#include <iostream>

using namespace ctre::phoenix6;

Turret::Turret(int shooterMotorCANBusID, int feederMotorCANBusID,
               int turretMotorCANBusID, int turretCANCoderID,
               std::string turretName)
    : m_shooterMotor(shooterMotorCANBusID),
      m_feederMotor(feederMotorCANBusID),
      m_turretMotor(turretMotorCANBusID),
      m_turretCANCoder(turretCANCoderID),
      m_turretName(turretName) {
  // Create 3 config objects to apply to the motors and CANCoder
  ctre::phoenix6::configs::TalonFXConfiguration turretConfig{};
  ctre::phoenix6::configs::TalonFXConfiguration shooterConfig{};
  ctre::phoenix6::configs::TalonFXConfiguration feederConfig{};

  // Populate the turretConfig object
  turretConfig.MotorOutput.Inverted =
      signals::InvertedValue::Clockwise_Positive;

  turretConfig.Feedback.SensorToMechanismRatio = 20;

  turretConfig.MotionMagic.MotionMagicCruiseVelocity = 0.3_tps;
  turretConfig.MotionMagic.MotionMagicAcceleration = 10_tr_per_s_sq;

  turretConfig.Slot0.kS = 0.1;
  turretConfig.Slot0.kV = 0.12;
  turretConfig.Slot0.kA = 0.01;
  turretConfig.Slot0.kP = 60.0;
  turretConfig.Slot0.kI = 0;
  turretConfig.Slot0.kD = 0;

  turretConfig.Voltage.PeakForwardVoltage = 8_V;
  turretConfig.Voltage.PeakReverseVoltage = -8_V;

  // Create a StatusCode Object so we can collect Error information
  // if applying the config object fails
  ctre::phoenix::StatusCode status =
      ctre::phoenix::StatusCode::StatusCodeNotInitialized;

  // Try to apply the turret motor config object up to 5 times.
  for (int i = 0; i < 5; ++i) {
    status = m_turretMotor.GetConfigurator().Apply(turretConfig);
    if (status.IsOK())
      break;
  }
  if (!status.IsOK()) {
    std::cout << "Could not apply turret config, error code: "
              << status.GetName() << std::endl;
  }

  // Populate the Shooter Config Object
  //-----------TODO---------- Test and set inverted value for the shooter
  // shooterConfig.MotorOutput.Inverted =
  //    signals::InvertedValue::Clockwise_Positive;

  shooterConfig.Slot0.kS = 0.1;
  shooterConfig.Slot0.kV = 0.12;
  shooterConfig.Slot0.kA = 0.01;
  shooterConfig.Slot0.kP = 0;
  shooterConfig.Slot0.kI = 0;
  shooterConfig.Slot0.kD = 0;

  shooterConfig.Voltage.PeakForwardVoltage = 12_V;
  shooterConfig.Voltage.PeakReverseVoltage = -12_V;

  // Try to apply the Shooter motor config object up to 5 times.
  for (int i = 0; i < 5; ++i) {
    status = m_shooterMotor.GetConfigurator().Apply(shooterConfig);
    if (status.IsOK())
      break;
  }
  if (!status.IsOK()) {
    std::cout << "Could not apply configs, error code: " << status.GetName()
              << std::endl;
  }
};

void Turret::InitializeTurretAngle() {
  // --------------------------TODO--------------------------
  // Add code here to read the CANCoder
  // position and apply it to the Turret Motor
}

void Turret::SetTurretAngle(units::angle::degree_t Angle) {
  fmt::println("[METHOD] Moving to {} Degrees...", Angle);
  m_turretMotor.SetControl(
      m_motionMagicControl.WithPosition(Angle).WithSlot(0));
};

units::angle::degree_t Turret::GetTurretAngle() {
  // --------------------TODO-----------------------
  // Remove return 0_deg and add code here to return the current angle of the turret
  return 0_deg;
};

void Turret::SetShooterSpeed(units::turns_per_second_t speed) {
  fmt::println("[METHOD] Setting Shooter speed to {}", speed);
  m_shooterMotor.SetControl(m_voltageVelocity.WithVelocity(speed).WithSlot(0));
  if (speed != 0_tps) {
    m_feederMotor.SetControl(m_voltageOut.WithOutput(4.0_V));
  } else {
    m_feederMotor.SetControl(m_voltageOut.WithOutput(0.0_V));
  }
};

bool Turret::IsShooterAtSpeed() {
  // ------------------TODO----------------------
  // Remove return false add code here to check if the turret has reached the set speed
  return false;
};