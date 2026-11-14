#include <ui/GraphicBuffer.h>
#include <ui/GraphicBufferMapper.h>
#include <ui/Rect.h>
#include <new>
#include <string>

extern "C" {
    // GraphicBuffer 4-argument constructor shim: forward to current GraphicBuffer constructor
    void _ZN7android13GraphicBufferC1EjjijNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(
            void* thisptr, uint32_t inWidth, uint32_t inHeight, int32_t inFormat, uint32_t inUsage,
            std::string requestorName) {
        new (thisptr) android::GraphicBuffer(inWidth, inHeight, inFormat, inUsage, requestorName);
    }

    // GraphicBuffer 5-argument constructor shim: forward to current GraphicBuffer constructor
    void _ZN7android13GraphicBufferC1EjjijyNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(
            void* thisptr, uint32_t inWidth, uint32_t inHeight, int32_t inFormat, uint32_t inUsage,
            uint64_t inProducerId, std::string requestorName) {
        new (thisptr) android::GraphicBuffer(inWidth, inHeight, inFormat, inUsage, inProducerId, requestorName);
    }
}
