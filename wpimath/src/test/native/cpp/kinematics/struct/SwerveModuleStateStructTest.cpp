// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <gtest/gtest.h>

#include "frc/kinematics/SwerveModuleState.h"

using namespace frc;

namespace {

using StructType = wpi::Struct<frc::SwerveModuleState>;
const SwerveModuleState kExpectedData{
    SwerveModuleState{22.9_mps, Rotation2d{3.3_rad}}};
}  // namespace

TEST(SwerveModuleStateStructTest, Roundtrip) {
  uint8_t buffer[StructType::kSize];
  std::memset(buffer, 0, StructType::kSize);
  StructType::Pack(buffer, kExpectedData);

  SwerveModuleState unpacked_data = StructType::Unpack(buffer);

  EXPECT_EQ(kExpectedData.speed.value(), unpacked_data.speed.value());
  EXPECT_EQ(kExpectedData.angle, unpacked_data.angle);
}
