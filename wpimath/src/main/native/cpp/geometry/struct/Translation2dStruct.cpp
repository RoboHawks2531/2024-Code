// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "frc/geometry/struct/Translation2dStruct.h"

namespace {
constexpr size_t kXOff = 0;
constexpr size_t kYOff = kXOff + 8;
}  // namespace

using StructType = wpi::Struct<frc::Translation2d>;

frc::Translation2d StructType::Unpack(std::span<const uint8_t, kSize> data) {
  return frc::Translation2d{
      units::meter_t{wpi::UnpackStruct<double, kXOff>(data)},
      units::meter_t{wpi::UnpackStruct<double, kYOff>(data)},
  };
}

void StructType::Pack(std::span<uint8_t, kSize> data,
                      const frc::Translation2d& value) {
  wpi::PackStruct<kXOff>(data, value.X().value());
  wpi::PackStruct<kYOff>(data, value.Y().value());
}
