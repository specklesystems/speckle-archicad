#pragma once

#include "IBridge.h"
#include "IBrowserAdapter.h"
#include "Binding.h"
#include "SenderModelCard.h"

class SendBridge : public IBridge {
public:
    SendBridge(IBrowserAdapter* browser);

    ~SendBridge() = default;

private:
    std::unique_ptr<Binding> sendBinding;
    void RunMethod(const RunMethodEventArgs& args);

    void GetSendFilters(const RunMethodEventArgs& args);
    void GetSendSettings(const RunMethodEventArgs& args);
    void Send(const RunMethodEventArgs& args);

    // Speckle 4.0 native artefact send (parquet bundle + presigned upload).
    // Requires the server's v2 data endpoints — there is no legacy fallback.
    // modelCard is non-const because SendFilter::GetSelectedObjectIds() is non-const.
    void SendViaArtifacts(const RunMethodEventArgs& args, SenderModelCard& modelCard, bool includeProperties);
};
