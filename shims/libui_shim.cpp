#include <ui/GraphicBuffer.h>
#include <ui/GraphicBufferAllocator.h>
#include <ui/GraphicBufferMapper.h>
#include <ui/Rect.h>
#include <utils/Singleton.h>
#include <utils/Mutex.h>
#include <new>
#include <string>

namespace android {

// Instantiate legacy Singleton symbols for hwcomposer
template<> Mutex Singleton<GraphicBufferAllocator>::sLock(Mutex::PRIVATE);
template<> GraphicBufferAllocator* Singleton<GraphicBufferAllocator>::sInstance(nullptr);
template<> Mutex Singleton<GraphicBufferMapper>::sLock(Mutex::PRIVATE);
template<> GraphicBufferMapper* Singleton<GraphicBufferMapper>::sInstance(nullptr);

extern "C" {
    // GraphicBuffer 4-argument constructor shim: forward to current GraphicBuffer constructor
    void _ZN7android13GraphicBufferC1EjjijNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(
            void* thisptr, uint32_t inWidth, uint32_t inHeight, int32_t inFormat, uint32_t inUsage,
            std::string requestorName) {
        new (thisptr) android::GraphicBuffer(inWidth, inHeight, inFormat, 1,
                                            static_cast<uint64_t>(inUsage), requestorName);
    }

    // GraphicBuffer 5-argument constructor shim: forward to current GraphicBuffer constructor
    void _ZN7android13GraphicBufferC1EjjijyNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(
            void* thisptr, uint32_t inWidth, uint32_t inHeight, int32_t inFormat, uint32_t inUsage,
            uint64_t inProducerId, std::string requestorName) {
        uint64_t usage = static_cast<uint64_t>(inUsage) | inProducerId;
        new (thisptr) android::GraphicBuffer(inWidth, inHeight, inFormat, 1,
                                            usage, requestorName);
    }
}

} // namespace android
