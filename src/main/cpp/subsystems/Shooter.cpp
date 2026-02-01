// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Shooter.h"
#include <iostream>

using namespace ctre::phoenix6;

ShooterSubsystem::ShooterSubsystem() {
  ctre::phoenix6::configs::TalonFXConfiguration configs{};

  configs::FeedbackConfigs& Feedback = configs.Feedback;
  Feedback.SensorToMechanismRatio = 9;

  configs::MotionMagicConfigs& MotionMagic = configs.MotionMagic;
  MotionMagic.MotionMagicCruiseVelocity = 10_tps;
  MotionMagic.MotionMagicAcceleration = 10_tr_per_s_sq;

  configs.Slot0.kS = 0.25;
  configs.Slot0.kV = 0.12;
  configs.Slot0.kA = 0.01;
  configs.Slot0.kP = 90.0;
  configs.Slot0.kI = 0;
  configs.Slot0.kD = 1.5;

  configs.Voltage.PeakForwardVoltage = 12_V;
  configs.Voltage.PeakReverseVoltage = -12_V;

  /* Voltage-based velocity requires a feed forward to account for the back-emf of the motor */
  configs.Slot1.kS = 0.1; // To account for friction, add 0.1 V of static feedforward
  configs.Slot1.kV = 0.116; // Kraken X60 is a 500 kV motor, 500 rpm per V = 8.333 rps per V, 1/8.33 = 0.12 volts / rotation per second

  ctre::phoenix::StatusCode status =
      ctre::phoenix::StatusCode::StatusCodeNotInitialized;
  #ifdef TURRET
  for (int i = 0; i < 5; ++i) {
    status = m_LTurretMotor.GetConfigurator().Apply(configs.Slot0);
    if (status.IsOK())
      break;
  }
  if (!status.IsOK()) {
    std::cout << "Could not apply configs, error code: " << status.GetName() << std::endl;
  }
  for (int i = 0; i < 5; ++i) {
    status = m_RTurretMotor.GetConfigurator().Apply(configs.Slot0);
    if (status.IsOK())
      break;
  }
  if (!status.IsOK()) {
    std::cout << "Could not apply configs, error code: " << status.GetName() << std::endl;
  }
  #endif
  
  #ifdef SHOOTER
  for (int i = 0; i < 5; ++i) {
    status = m_LShooterMotor.GetConfigurator().Apply(configs.Slot1);
    if (status.IsOK())
      break;
  }
  // configs::TalonFXConfiguration LShooterInverted;
  // LShooterInverted.motorOutput.Inverted = configs.motorOutput.Inverted.Clockwise_Positive;
  // status = m_LShooterMotor.GetConfigurator().Apply(LShooterInverted);
  if (!status.IsOK()) {
    std::cout << "Could not apply configs, error code: " << status.GetName() << std::endl;
  }
  for (int i = 0; i < 5; ++i) {
    status = m_RShooterMotor.GetConfigurator().Apply(configs.Slot1);
    if (status.IsOK())
      break;
  }
  if (!status.IsOK()) {
    std::cout << "Could not apply configs, error code: " << status.GetName() << std::endl;
  }
  #endif
};

// This method will be called once per scheduler run
void ShooterSubsystem::Periodic() {}

void ShooterSubsystem::SetTurretAngle(units::angle::degree_t Angle) {
  m_LTurretMotor.SetControl(m_MotionMagicRequest.WithPosition(Angle).WithSlot(0));
};

void ShooterSubsystem::SetShooterActive(bool Trigger) {
  #ifdef SHOOTER
  if (Trigger == true) {
    m_LShooterMotor.SetControl(m_ShooterVOut.WithVelocity(50*1_tps).withSlot(1));
    m_RShooterMotor.SetControl(m_ShooterVOut.WithVelocity(50*1_tps).withSlot(1));
  } else {
    m_LShooterMotor.SetControl(0.0_V).withSlot(1);
    m_RShooterMotor.SetControl(0.0_V).withSlot(1);
  } 
  #endif
};