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

  // for (int i = 0; i < 5; ++i) {
  //   status = m_shooterMotor.GetConfigurator().Apply(shooterConfig);
  //   if (status.IsOK())
  //     break;
  // }
  // // configs::TalonFXConfiguration LShooterInverted;
  // // LShooterInverted.motorOutput.Inverted =
  // configs.motorOutput.Inverted.Clockwise_Positive;
  // // status = m_LShooterMotor.GetConfigurator().Apply(LShooterInverted);
  // if (!status.IsOK()) {
  //   std::cout << "Could not apply configs, error code: " << status.GetName()
  //   << std::endl;
  // }
};

void Turret::InitializeTurretAngle() {}

void Turret::SetTurretAngle(units::angle::degree_t Angle) {
  m_turretMotor.SetControl(m_motionMagicControl.WithPosition(Angle).WithSlot(0));
};

units::angle::degree_t Turret::GetTurretAngle() {

};

void Turret::SetShooterSpeed(units::turns_per_second_t speed) {

};

bool Turret::IsShooterAtSpeed() {

};