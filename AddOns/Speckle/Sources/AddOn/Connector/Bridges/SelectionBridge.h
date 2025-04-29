#pragma once

#include "IBridge.h"
#include "IBrowserAdapter.h"
#include "Binding.h"

class SelectionBridge : public IBridge {
public:
    SelectionBridge(IBrowserAdapter* browser);

    ~SelectionBridge() = default;

private:
    std::unique_ptr<Binding> selectionBinding;
    void RunMethod(const RunMethodEventArgs& args);

    void GetSelection(const RunMethodEventArgs& args);

public:
    void OnSelectionChanged();
};
