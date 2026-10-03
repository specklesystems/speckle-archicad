#pragma once

#include <chrono>
#include <functional>
#include <utility>

#include "IProcessWindow.h"

class IngestionProgressWindow final : public IProcessWindow
{
public:
    using Clock = std::chrono::steady_clock;
    using Report = std::function<void(const std::string&)>;
    using Now = std::function<Clock::time_point()>;

    IngestionProgressWindow(IProcessWindow& window, Report report,
        Now now = [] { return Clock::now(); })
        : window(window), report(std::move(report)), now(std::move(now)), lastReport(this->now())
    {
    }

    void Init(const std::string& title, int count) override { window.Init(title, count); }
    void SetNextProcessPhase(const std::string& title, int count) override
    {
        window.SetNextProcessPhase(title, count);
        phase = title;
        ReportIfDue();
    }
    void SetProcessValue(int value) override
    {
        window.SetProcessValue(value);
        ReportIfDue();
    }
    bool IsProcessCanceled() override { return window.IsProcessCanceled(); }
    void Close() override { window.Close(); }

private:
    void ReportIfDue()
    {
        const auto current = now();
        if (window.IsProcessCanceled() || current - lastReport < std::chrono::seconds(30))
            return;
        report(phase);
        lastReport = now();
    }

    IProcessWindow& window;
    Report report;
    Now now;
    Clock::time_point lastReport;
    std::string phase;
};
