#pragma once

#include "IBrowserAdapter.h"
#include "Binding.h"

class SelectionBridge {
public:
    SelectionBridge(IBrowserAdapter* browser);

    ~SelectionBridge() = default;

private:
    std::unique_ptr<Binding> selectionBinding;

    void Init(IBrowserAdapter* browser);
    void OnRunMethod(const RunMethodEventArgs& args);

    void GetSelection(const RunMethodEventArgs& args);
    void SelectionChanged();
};
