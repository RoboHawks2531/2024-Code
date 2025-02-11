// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <wpi/SymbolExports.h>
#include <wpi/struct/Struct.h>

#include "frc/geometry/Twist3d.h"

template <>
struct WPILIB_DLLEXPORT wpi::Struct<frc::Twist3d> {
  static constexpr std::string_view kTypeString = "struct:Twist3d";
  static constexpr size_t kSize = 48;
  static constexpr std::string_view kSchema =
      "double dx;double dy;double dz;double rx;double ry;double rz";

  static frc::Twist3d Unpack(std::span<const uint8_t, kSize> data);
  static void Pack(std::span<uint8_t, kSize> data, const frc::Twist3d& value);
};
