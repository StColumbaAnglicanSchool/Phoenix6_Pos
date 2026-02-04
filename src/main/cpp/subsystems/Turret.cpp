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
  ctre::phoenix6::configs::TalonFXConfiguration turretConfig{};
  ctre::phoenix6::configs::TalonFXConfiguration shooterConfig{};
  ctre::phoenix6::configs::TalonFXConfiguration feederConfig{};

  configs::FeedbackConfigs& Feedback = turretConfig.Feedback;
  Feedback.SensorToMechanismRatio = 20;

  configs::MotionMagicConfigs& MotionMagic = turretConfig.MotionMagic;
  MotionMagic.MotionMagicCruiseVelocity = 0.3_tps;
  MotionMagic.MotionMagicAcceleration = 10_tr_per_s_sq;

  turretConfig.Slot0.kS = 0.1;
  turretConfig.Slot0.kV = 0.12;
  turretConfig.Slot0.kA = 0.01;
  turretConfig.Slot0.kP = 60.0;
  turretConfig.Slot0.kI = 0;
  turretConfig.Slot0.kD = 0;

  turretConfig.Voltage.PeakForwardVoltage = 8_V;
  turretConfig.Voltage.PeakReverseVoltage = -8_V;

  turretConfig.MotorOutput.Inverted =
      signals::InvertedValue::Clockwise_Positive;


  shooterConfig.Slot0.kS = 0.1;
  shooterConfig.Slot0.kV = 0.12;
  shooterConfig.Slot0.kA = 0.01;
  shooterConfig.Slot0.kP = 0;
  shooterConfig.Slot0.kI = 0;
  shooterConfig.Slot0.kD = 0;

  shooterConfig.Voltage.PeakForwardVoltage = 12_V;
  shooterConfig.Voltage.PeakReverseVoltage = -12_V;

  
  ctre::phoenix::StatusCode status =
      ctre::phoenix::StatusCode::StatusCodeNotInitialized;

  for (int i = 0; i < 5; ++i) {
    status = m_turretMotor.GetConfigurator().Apply(turretConfig);
    if (status.IsOK())
      break;
  }
  if (!status.IsOK()) {
    std::cout << "Could not apply turret config, error code: "
              << status.GetName() << std::endl;
  }

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

void Turret::InitializeTurretAngle() {}

void Turret::SetTurretAngle(units::angle::degree_t Angle) {
  fmt::println("[METHOD] Moving to {} Degrees...", Angle);
  m_turretMotor.SetControl(m_motionMagicControl.WithPosition(Angle).WithSlot(0));
};

units::angle::degree_t Turret::GetTurretAngle() {

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

};