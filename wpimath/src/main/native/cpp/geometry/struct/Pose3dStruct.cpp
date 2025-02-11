// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "frc/geometry/struct/Pose3dStruct.h"

namespace {
constexpr size_t kTranslationOff = 0;
constexpr size_t kRotationOff =
    kTranslationOff + wpi::Struct<frc::Translation3d>::kSize;
}  // namespace

using StructType = wpi::Struct<frc::Pose3d>;

frc::Pose3d StructType::Unpack(std::span<const uint8_t, kSize> data) {
  return frc::Pose3d{
      wpi::UnpackStruct<frc::Translation3d, kTranslationOff>(data),
      wpi::UnpackStruct<frc::Rotation3d, kRotationOff>(data),
  };
}

void StructType::Pack(std::span<uint8_t, kSize> data,
                      const frc::Pose3d& value) {
  wpi::PackStruct<kTranslationOff>(data, value.Translation());
  wpi::PackStruct<kRotationOff>(data, value.Rotation());
}

void StructType::ForEachNested(
    std::invocable<std::string_view, std::string_view> auto fn) {
  wpi::ForEachStructSchema<frc::Translation3d>(fn);
  wpi::ForEachStructSchema<frc::Rotation3d>(fn);
}
