/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ui/GraphicBuffer.h>
#include <ui/GraphicBufferMapper.h>
#include <utils/Singleton.h>
#include <utils/Mutex.h>
#include <string>
#include <new>

namespace android {

// Instantiate legacy Singleton<GraphicBufferMapper> static symbols
template<> Mutex Singleton<GraphicBufferMapper>::sLock(Mutex::PRIVATE);
template<> GraphicBufferMapper* Singleton<GraphicBufferMapper>::sInstance(nullptr);

extern "C" {

// _ZN7android13GraphicBufferC1EjjijNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE
void _ZN7android13GraphicBufferC1EjjijNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(
        void* thisptr, uint32_t inWidth, uint32_t inHeight, int32_t inFormat,
        uint32_t inUsage, std::string requestorName) {
    new (thisptr) GraphicBuffer(inWidth, inHeight, inFormat, 1,
                                static_cast<uint64_t>(inUsage), requestorName);
}

// _ZN7android13GraphicBufferC1EjjijyNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE
void _ZN7android13GraphicBufferC1EjjijyNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(
        void* thisptr, uint32_t inWidth, uint32_t inHeight, int32_t inFormat,
        uint32_t inUsage, uint64_t inUsage2, std::string requestorName) {
    uint64_t usage = static_cast<uint64_t>(inUsage) | inUsage2;
    new (thisptr) GraphicBuffer(inWidth, inHeight, inFormat, 1,
                                usage, requestorName);
}

} // extern "C"

} // namespace android
