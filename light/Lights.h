/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <aidl/android/hardware/light/BnLights.h>
#include <mutex>
#include <string>
#include <vector>

namespace aidl {
namespace android {
namespace hardware {
namespace light {

class Lights : public BnLights {
public:
    Lights();

    ndk::ScopedAStatus setLightState(int32_t id, const HwLightState& state) override;
    ndk::ScopedAStatus getLights(std::vector<HwLight>* types) override;

private:
    std::string mBrightnessPath;
    std::string mMaxBrightnessPath;
    uint32_t mMaxBrightness = 255;
    std::mutex mLock;

    void setBacklight(const HwLightState& state);
};

}  // namespace light
}  // namespace hardware
}  // namespace android
}  // namespace aidl
