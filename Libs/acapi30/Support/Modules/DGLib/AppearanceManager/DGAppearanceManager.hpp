#ifndef APPEARANCEMANAGER_HPP
#define APPEARANCEMANAGER_HPP

#pragma once

#include "DGDLLExport.h"
#include "DGEventNotifier.hpp"

namespace DG {

/**
 * @enum PreferredAppearanceMode
 * @brief Defines the preferred appearance mode for the application.
 */
enum class PreferredAppearanceMode: UInt16
{
    FollowSystem = 0, ///< Follow the system's appearance mode.
    ForceLight = 1,   ///< Force the application to use light mode.
    ForceDark = 2     ///< Force the application to use dark mode.
};

/**
 * @enum AppearanceMode
 * @brief Represents the actual appearance mode (light or dark).
 */
enum class AppearanceMode: UInt16
{
    Light = 0, ///< Light appearance mode.
    Dark = 1   ///< Dark appearance mode.
};

/**
 * @class AppearanceChangedEventArg
 * @ingroup DG
 * @brief Event argument for appearance change notifications.
 */
class DG_DLL_EXPORT AppearanceChangedEventArg: public EventArg
{
public:
    PreferredAppearanceMode preferredMode; ///< The preferred appearance mode.
    AppearanceMode mode; ///< The actual appearance mode.

    /**
     * @brief Constructor for AppearanceChangedEventArg.
     * @param preferredMode The preferred appearance mode.
     * @param mode The actual appearance mode.
     */
    AppearanceChangedEventArg (PreferredAppearanceMode preferredMode, AppearanceMode mode);

    /**
     * @brief Destructor for AppearanceChangedEventArg.
     */
    virtual ~AppearanceChangedEventArg ();
};

/**
 * @class AppearanceManager
 * @ingroup DG
 * @brief Manages the application's appearance settings and notifications.
 */
class DG_DLL_EXPORT AppearanceManager
{
public:
    /**
     * @brief Destructor for AppearanceManager.
     */
    ~AppearanceManager ();

    /**
     * @brief Gets the preferred appearance mode for the application.
     * @return The preferred appearance mode.
     */
    static PreferredAppearanceMode GetPreferredAppearanceMode ();

    /**
     * @brief Gets the application's current appearance mode.
     * @return The application's appearance mode.
     */
    static AppearanceMode GetApplicationAppearanceMode ();

    /**
     * @brief Gets the operating system's current appearance mode.
     * @return The operating system's appearance mode.
     */
    static AppearanceMode GetOSAppearanceMode ();

    /**
     * @brief Event notifier for appearance changes.
     */
    static EventNotifier<AppearanceManager, const AppearanceChangedEventArg> onAppearanceChanged;

    /**
     * @brief Gets the singleton instance of the AppearanceManager.
     * @return The singleton instance.
     */
    static AppearanceManager& GetInstance ();

private:
    /**
     * @brief Constructor for AppearanceManager.
     */
    AppearanceManager ();

    /**
     * @brief Deleted copy constructor and assignment operator to prevent copying.
     */
    AppearanceManager (const AppearanceManager& source) = delete;
    /**
     * @brief Deleted assignment operator to prevent assignment.
     */
    AppearanceManager& operator= (const AppearanceManager& source) = delete;

    /**
     * @brief Initializes the AppearanceManager.
     */
    void Init ();

    /**
     * @brief Handles appearance change events.
     */
    static void OnAppearanceChanged ();
};

/**
 * @brief Checks if the current application appearance mode is light.
 * @ingroup DG
 * @return true if the current application appearance mode is light.
 */
DG_DLL_EXPORT bool	IsLightMode ();

/**
 * @brief Checks if the current application appearance mode is dark.
 * @ingroup DG
 * @return true if the current application appearance mode is dark.
 */
DG_DLL_EXPORT bool	IsDarkMode ();

} // namespace DG

#endif
