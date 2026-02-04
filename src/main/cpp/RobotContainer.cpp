#include <RobotContainer.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc2/command/button/JoystickButton.h>

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here

  // Add commands to the autonomous command chooser
  // Note that we do *not* move ownership into the chooser
//   m_chooser.SetDefaultOption("Simple Auto", m_simpleAuto.get());
//   m_chooser.AddOption("Complex Auto", m_complexAuto.get());

//   // Put the chooser on the dashboard
//   frc::Shuffleboard::GetTab("Autonomous").Add(m_chooser);
  // Put subsystems to dashboard.
  //frc::Shuffleboard::GetTab("Shooter").Add(&m_ShooterSS);


  // Log Shuffleboard events for command initialize, execute, finish, interrupt
  frc2::CommandScheduler::GetInstance().OnCommandInitialize(
      [](const frc2::Command& command) {
        frc::Shuffleboard::AddEventMarker(
            "Command initialized", command.GetName(),
            frc::ShuffleboardEventImportance::kNormal);
      });
  frc2::CommandScheduler::GetInstance().OnCommandExecute(
      [](const frc2::Command& command) {
        frc::Shuffleboard::AddEventMarker(
            "Command executed", command.GetName(),
            frc::ShuffleboardEventImportance::kNormal);
      });
  frc2::CommandScheduler::GetInstance().OnCommandFinish(
      [](const frc2::Command& command) {
        frc::Shuffleboard::AddEventMarker(
            "Command finished", command.GetName(),
            frc::ShuffleboardEventImportance::kNormal);
      });
  frc2::CommandScheduler::GetInstance().OnCommandInterrupt(
      [](const frc2::Command& command) {
        frc::Shuffleboard::AddEventMarker(
            "Command interrupted", command.GetName(),
            frc::ShuffleboardEventImportance::kNormal);
      });

  // Configure Button Bindings
  ConfigureButtonBindings();
};

void RobotContainer::ConfigureButtonBindings() {
  frc2::JoystickButton(&m_DriverController,7).OnTrue(m_ShooterSS.TargetTo90DegreesCMD());
  frc2::JoystickButton(&m_DriverController,9).OnTrue(m_ShooterSS.TargetToZeroCMD());
  frc2::JoystickButton(&m_DriverController,11).OnTrue(m_ShooterSS.TargetToNeg90DegreesCMD());
  frc2::JoystickButton(&m_DriverController,1).WhileTrue(m_ShooterSS.SetShooterSpeedCMD());
};