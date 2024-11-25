#pragma once

#include "IBrowserAdapter.h"
#include "Binding.h"

class BaseBridge {
public:
    BaseBridge(IBrowserAdapter* browser);

    ~BaseBridge() = default;

private:
    std::unique_ptr<Binding> baseBinding;

    void OnRunMethod(const RunMethodEventArgs& args);
    void RunMethod(const RunMethodEventArgs& args);

    void AddModel(const RunMethodEventArgs& args);
    void GetConnectorVersion(const RunMethodEventArgs& args);
    void GetDocumentInfo(const RunMethodEventArgs& args);
    void GetDocumentState(const RunMethodEventArgs& args);
    void GetSourceApplicationName(const RunMethodEventArgs& args);
    void GetSourceApplicationVersion(const RunMethodEventArgs& args);
    void HighlightModel(const RunMethodEventArgs& args);
    void HighlightObjects(const RunMethodEventArgs& args);
    void OpenUrl(const RunMethodEventArgs& args);
    void RemoveModel(const RunMethodEventArgs& args);
    void UpdateModel(const RunMethodEventArgs& args);
};
