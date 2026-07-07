#pragma once

#include "IBridge.h"
#include "IBrowserAdapter.h"
#include "Binding.h"

class ReceiveBridge : public IBridge {
public:
    ReceiveBridge(IBrowserAdapter* browser);

    ~ReceiveBridge() = default;

private:
    std::unique_ptr<Binding> receiveBinding;
    void RunMethod(const RunMethodEventArgs& args);

    // Speckle 4.0 native artefact receive: downloads the version's parquet
    // bundle, generates GDL XML, converts to GSM via LP_XMLConverter (parallel
    // processes) and places the libparts — all in-process. Replaces both the
    // C# desktop-service route and the receive-via-browser fallback.
    void Receive(const RunMethodEventArgs& args);
};
