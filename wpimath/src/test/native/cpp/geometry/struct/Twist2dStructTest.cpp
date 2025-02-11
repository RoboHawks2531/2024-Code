// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <gtest/gtest.h>

#include "frc/geometry/Twist2d.h"

using namespace frc;

namespace {

using StructType = wpi::Struct<frc::Twist2d>;
const Twist2d kExpectedData{Twist2d{2.29_m, 35.04_m, 35.04_rad}};
}  // namespace

TEST(Twist2dStructTest, Roundtrip) {
  uint8_t buffer[StructType::kSize];
  std::memset(buffer, 0, StructType::kSize);
  StructType::Pack(buffer, kExpectedData);

  Twist2d unpacked_data = StructType::Unpack(buffer);

  EXPECT_EQ(kExpectedData.dx.value(), unpacked_data.dx.value());
  EXPECT_EQ(kExpectedData.dy.value(), unpacked_data.dy.value());
  EXPECT_EQ(kExpectedData.dtheta.value(), unpacked_data.dtheta.value());
}
