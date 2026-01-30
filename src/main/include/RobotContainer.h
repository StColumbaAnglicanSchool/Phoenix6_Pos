#pragma once

#include <frc/smartdashboard/SendableChooser.h>
#include <frc2/command/Command.h>
#include <frc2/command/Commands.h>
#include <frc/Joystick.h>

#include <Constants.h>
#include <subsystems/Shooter.h>

namespace ac = AutoConstants;


class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();

 private:
  frc::Joystick m_DriverController{0};
  ShooterSubsystem m_ShooterSS;

  void ConfigureButtonBindings();
};