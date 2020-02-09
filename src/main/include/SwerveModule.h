/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <units/units.h>

#include "frc/geometry/Translation2d.h"
#include "frc/geometry/Rotation2d.h"
#include "frc/drive/Vector2d.h"
#include <frc/kinematics/SwerveModuleState.h>
#include <frc/controller/PIDController.h>

#include "rev/CANSparkMax.h"
#include "rev/CANEncoder.h"
#include "rev/CANPIDController.h"

#include "TurnEncoder.h"
#include "SwerveModuleName.h"

class SwerveModule {
 public:
  SwerveModule(frc::Translation2d pos,
               int analogEncoderPort,
               units::radian_t analogEncoderOffset,
               int driveMotorCANID,
               int turnMotorCANID,
               SwerveModuleName moduleName);

  rev::CANSparkMax m_driveMotor;
  rev::CANSparkMax m_turnMotor;

  /** This is called `setTargetVelocity` in the SDS code (which I use the algorithm from) and `SetDesiredState` in the WPILib code. Sets member variables SDS_targetSpeed and SDS_targetAngle.
   * @param state: the desired frc::SwerveModuleState
   */
  void SetDesiredState(frc::SwerveModuleState& state);
  void NormalizeState(frc::SwerveModuleState& state);
  void NormalizeState2(frc::SwerveModuleState&);
  void NormalizeState3(frc::SwerveModuleState&);

  void PutSwerveModuleState(std::string, frc::SwerveModuleState&);

  void PutDiagnostics();
  void UpdateSensors();

  SwerveModuleName m_moduleName;

  TurnEncoder m_turnEncoder;
  rev::CANEncoder m_driveEncoder = m_driveMotor.GetEncoder();

  frc::Translation2d m_modulePosition;

  units::radian_t m_currentAngle = 0_rad;

  // deprecated. See implementation in SwerveModule.cpp for (I think) some algorithms for dealing with "turn 180 or run backwards?" 
  void SDS_UpdateState();
  
  rev::CANPIDController m_onboardTurnMotorPIDController = m_turnMotor.GetPIDController();
  frc2::PIDController m_turnPIDController{2, 0, 1};
  /** Other (possible, I think wrong/not-necessary) PID constants:
   * `DEFAULT_ONBOARD_NEO_ANGLE_PID` is {0.5, 0.0, 0.0001}
   * `DEFAULT_CAN_SPARK_MAX_ANGLE_PID` is {1.5, 0.0, 0.5}`
  */

  // copied from SDS
  static constexpr double SDS_DRIVE_REDUCTION = 8.31 / 1.0; // (gear ratio)
  static constexpr double SDS_WHEEL_DIAMETER = 4.0; // (in)
  static constexpr double SDS_DEFAULT_DRIVE_ROTATIONS_PER_UNIT = (1.0 / (4.0 * wpi::math::pi)) * (60.0 / 15.0) * (18.0 / 26.0) * (42.0 / 14.0);
};