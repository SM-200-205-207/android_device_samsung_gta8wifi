#include <gui/SurfaceComposerClient.h>
#include <gui/IGraphicBufferProducer.h>

extern "C" {
    // SurfaceComposerClient legacy transaction stub
    void _ZN7android21SurfaceComposerClient13openGlobalTransactionEv() {
        // Handled via SurfaceComposerClient::Transaction in Android 14
    }

    void _ZN7android21SurfaceComposerClient14closeGlobalTransactionEb(bool /* synchronous */) {
        // Handled via SurfaceComposerClient::Transaction in Android 14
    }
}
