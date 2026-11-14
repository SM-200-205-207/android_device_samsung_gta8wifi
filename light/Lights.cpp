/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "Lights.h"

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/strings.h>
#include <unistd.h>

namespace aidl {
namespace android {
namespace hardware {
namespace light {

Lights::Lights() {
    static const std::vector<std::string> kCandidates = {
        "/sys/class/backlight/sprd_backlight",
        "/sys/class/backlight/panel0-backlight",
        "/sys/class/backlight/panel",
        "/sys/class/backlight/backlight",
    };

    for (const auto& candidate : kCandidates) {
        std::string bPath = candidate + "/brightness";
        std::string mPath = candidate + "/max_brightness";
        if (access(bPath.c_str(), W_OK) == 0) {
            mBrightnessPath = bPath;
            mMaxBrightnessPath = mPath;
            LOG(INFO) << "Found backlight sysfs node: " << mBrightnessPath;
            break;
        }
    }

    if (mBrightnessPath.empty()) {
        mBrightnessPath = "/sys/class/backlight/sprd_backlight/brightness";
        mMaxBrightnessPath = "/sys/class/backlight/sprd_backlight/max_brightness";
        LOG(WARNING) << "No candidate backlight sysfs node accessible at init; defaulting to "
                     << mBrightnessPath;
    }

    std::string maxBrightnessStr;
    if (::android::base::ReadFileToString(mMaxBrightnessPath, &maxBrightnessStr)) {
        try {
            uint32_t max = std::stoul(::android::base::Trim(maxBrightnessStr));
            if (max > 0) {
                mMaxBrightness = max;
                LOG(INFO) << "Max backlight brightness: " << mMaxBrightness;
            }
        } catch (...) {
            LOG(WARNING) << "Failed to parse max_brightness from " << mMaxBrightnessPath;
        }
    }
}

ndk::ScopedAStatus Lights::setLightState(int32_t id, const HwLightState& state) {
    if (id == static_cast<int32_t>(LightType::BACKLIGHT)) {
        std::lock_guard<std::mutex> lock(mLock);
        setBacklight(state);
        return ndk::ScopedAStatus::ok();
    }
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Lights::getLights(std::vector<HwLight>* types) {
    HwLight backlight{};
    backlight.id = static_cast<int32_t>(LightType::BACKLIGHT);
    backlight.type = LightType::BACKLIGHT;
    backlight.ordinal = 0;
    types->push_back(backlight);
    return ndk::ScopedAStatus::ok();
}

void Lights::setBacklight(const HwLightState& state) {
    uint32_t alpha = (state.color >> 24) & 0xFF;
    uint32_t red = (state.color >> 16) & 0xFF;
    uint32_t green = (state.color >> 8) & 0xFF;
    uint32_t blue = state.color & 0xFF;

    // Standard relative luminance (Rec. 601)
    uint32_t raw_brightness = (77 * red + 150 * green + 29 * blue) >> 8;
    if (raw_brightness == 0 && alpha > 0) {
        raw_brightness = alpha;
    }

    uint32_t scaled_brightness = (raw_brightness * mMaxBrightness) / 255;
    ::android::base::WriteStringToFile(std::to_string(scaled_brightness), mBrightnessPath);
}

}  // namespace light
}  // namespace hardware
}  // namespace android
}  // namespace aidl
