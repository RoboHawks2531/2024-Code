// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <wpi/SymbolExports.h>
#include <wpi/struct/Struct.h>

#include "frc/controller/ArmFeedforward.h"

template <>
struct WPILIB_DLLEXPORT wpi::Struct<frc::ArmFeedforward> {
  static constexpr std::string_view kTypeString = "struct:ArmFeedforward";
  static constexpr size_t kSize = 32;
  static constexpr std::string_view kSchema =
      "double ks;double kg;double kv;double ka";

  static frc::ArmFeedforward Unpack(std::span<const uint8_t, kSize> data);
  static void Pack(std::span<uint8_t, kSize> data,
                   const frc::ArmFeedforward& value);
};
