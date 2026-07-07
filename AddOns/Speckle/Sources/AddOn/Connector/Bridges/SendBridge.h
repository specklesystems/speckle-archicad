#pragma once

#include "IBridge.h"
#include "IBrowserAdapter.h"
#include "Binding.h"
#include "SendConversionResult.h"
#include "SenderModelCard.h"

class SendBridge : public IBridge {
public:
    SendBridge(IBrowserAdapter* browser);

    ~SendBridge() = default;

private:
    std::unique_ptr<Binding> sendBinding;
    std::vector<SendConversionResult> conversionResultCache;
    void RunMethod(const RunMethodEventArgs& args);

    void GetSendFilters(const RunMethodEventArgs& args);
    void GetSendSettings(const RunMethodEventArgs& args);
    void Send(const RunMethodEventArgs& args);
    void AfterSendObjects(const RunMethodEventArgs& args);

    // Speckle 4.0 native artefact send (parquet bundle + presigned upload).
    // Returns false when the server has no v2 data endpoints (-> legacy fallback).
    // modelCard is non-const because SendFilter::GetSelectedObjectIds() is non-const.
    bool TrySendViaArtifacts(const RunMethodEventArgs& args, SenderModelCard& modelCard, bool includeProperties);

    // Legacy v1 path: serialize a Base graph and hand batches to the DUI3
    // frontend to upload ("send via browser"). Kept only as the fallback for
    // servers without the v2 data endpoints.
    void SendViaBrowserLegacy(const RunMethodEventArgs& args, SenderModelCard& modelCard, bool includeProperties);
};
