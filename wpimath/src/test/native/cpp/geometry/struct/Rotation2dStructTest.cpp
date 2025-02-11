// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <gtest/gtest.h>

#include "frc/geometry/Rotation2d.h"

using namespace frc;

namespace {

using StructType = wpi::Struct<frc::Rotation2d>;
const Rotation2d kExpectedData{Rotation2d{1.91_rad}};
}  // namespace

TEST(Rotation2dStructTest, Roundtrip) {
  uint8_t buffer[StructType::kSize];
  std::memset(buffer, 0, StructType::kSize);
  StructType::Pack(buffer, kExpectedData);

  Rotation2d unpacked_data = StructType::Unpack(buffer);

  EXPECT_EQ(kExpectedData.Radians(), unpacked_data.Radians());
}
