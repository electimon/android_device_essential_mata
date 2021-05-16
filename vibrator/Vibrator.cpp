/*
 * Copyright (C) 2019 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "Electi-VibratorService"

#include <android-base/logging.h>
#include <hardware/hardware.h>
#include <hardware/vibrator.h>

#include "Vibrator.h"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

// Refer to non existing
// kernel documentation on the detail usages for ABIs below
static constexpr char ACTIVATE_PATH[] = "/sys/class/leds/vibrator/activate";
static constexpr char DURATION_PATH[] = "/sys/class/leds/vibrator/duration";
static constexpr char LOOP_PATH[] = "/sys/class/leds/vibrator/wf_rep_count";
static constexpr char MODE_PATH[] = "/sys/class/leds/vibrator/play_mode";
static constexpr char REPEAT_PATH[] = "/sys/class/leds/vibrator/wf_s_rep_count";
static constexpr char STATE_PATH[] = "/sys/class/leds/vibrator/state";
static constexpr char VMAX_PATH[] = "/sys/class/leds/vibrator/vmax_mv";

// Effects
static constexpr DaEffect WAVEFORM_CLICK_EFFECT {
    .vmax = 1950,
};

static constexpr DaEffect WAVEFORM_HEAVY_CLICK_EFFECT {
    .vmax = 2250,
    .repeats = 2,
};

namespace android {
namespace hardware {
namespace vibrator {
namespace V1_2 {
namespace implementation {

/*
 * Write value to path and close file.
 */
template <typename T>
static void set(const std::string& path, const T& value) {
    std::ofstream file(path);

    if (!file.is_open()) {
        LOG(ERROR) << "Unable to open: " << path << " (" <<  strerror(errno) << ")";
        return;
    }

    file << value;
}

Vibrator::Vibrator() {
}

Return<Status> Vibrator::on(uint32_t timeoutMs) {
    set(MODE_PATH, "direct");
    set(STATE_PATH, 1);
    set(DURATION_PATH, timeoutMs);
    set(ACTIVATE_PATH, 1);
    return Status::OK;
}

Return<Status> Vibrator::off()  {
    return Status::OK;
}

Return<bool> Vibrator::supportsAmplitudeControl()  {
    return false;
}

Return<Status> Vibrator::setAmplitude(uint8_t) {
    return Status::UNSUPPORTED_OPERATION;
}

Return<void> Vibrator::perform(V1_0::Effect effect, EffectStrength strength, perform_cb _hidl_cb) {
    return performEffect(static_cast<Effect>(effect), strength, _hidl_cb);
}

Return<void> Vibrator::perform_1_1(V1_1::Effect_1_1 effect, EffectStrength strength,
        perform_cb _hidl_cb) {
    return performEffect(static_cast<Effect>(effect), strength, _hidl_cb);
}

Return<void> Vibrator::perform_1_2(Effect effect, EffectStrength strength, perform_cb _hidl_cb) {
    return performEffect(static_cast<Effect>(effect), strength, _hidl_cb);
}

Return<void> Vibrator::performEffect(Effect effect, EffectStrength strength, perform_cb _hidl_cb) {
    [[maybe_unused]] const auto convertEffectStrength = [](EffectStrength strength) {
        switch (strength) {
            case EffectStrength::LIGHT:
                return 1375; // 50%
                break;
            case EffectStrength::MEDIUM:
                return 1650; // 75%
                break;
            case EffectStrength::STRONG:
                return 2250; // 100%
                break;
            default:
                return 0;
        }
    };

    const auto setEffect = [&](const DaEffect& effect) {
        set(MODE_PATH, "buffer");
        set(VMAX_PATH, *effect.vmax);

        if (effect.loops.has_value()) {
            set(LOOP_PATH, *effect.loops);
        }

        if (effect.repeats.has_value()) {
            set(REPEAT_PATH, *effect.repeats);
        }

        set(ACTIVATE_PATH, 1);
    };

    Status status = Status::OK;
    uint32_t timeMS = 0;
    [[maybe_unused]] EffectStrength xers = strength;

    // Set defaults
    set(LOOP_PATH, 0);
    set(REPEAT_PATH, 0);

    // Rawr xD
    //LOG(ERROR) << "MOTHER SAYS: " << Effect;

    switch (effect) {
        case Effect::CLICK:
            setEffect(WAVEFORM_CLICK_EFFECT);
            break;
        case Effect::DOUBLE_CLICK:
            break;
        case Effect::TICK:
            break;
        case Effect::HEAVY_CLICK:
            setEffect(WAVEFORM_HEAVY_CLICK_EFFECT);
            break;
        case Effect::POP:
            break;
        case Effect::THUD:
            break;
        default:
            _hidl_cb(Status::UNSUPPORTED_OPERATION, 0);
            return Void();
    }

    _hidl_cb(status, timeMS);
    return Void();
}

}  // namespace implementation
}  // namespace V1_2
}  // namespace vibrator
}  // namespace hardware
}  // namespace android
