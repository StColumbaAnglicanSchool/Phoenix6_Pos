#include <RobotContainer.h>
#include <frc/shuffleboard/Shuffleboard.h>

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here

  // Add commands to the autonomous command chooser
  // Note that we do *not* move ownership into the chooser
//   m_chooser.SetDefaultOption("Simple Auto", m_simpleAuto.get());
//   m_chooser.AddOption("Complex Auto", m_complexAuto.get());

//   // Put the chooser on the dashboard
//   frc::Shuffleboard::GetTab("Autonomous").Add(m_chooser);
  // Put subsystems to dashboard.
  frc::Shuffleboard::GetTab("Shooter").Add(m_ShooterSS);


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

  // Set default command for Shooter
  m_ShooterSS.SetDefaultCommand(frc2::cmd::Run(
    [this] {
        m_ShooterSS.SetShooterActive(m_DriverController.GetTrigger());
        m_ShooterSS.SetTurretAngle(m_DriverController.GetZ() * 1_deg);
    },
    {&m_ShooterSS}));
};