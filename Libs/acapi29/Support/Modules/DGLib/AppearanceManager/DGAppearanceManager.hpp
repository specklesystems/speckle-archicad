#ifndef APPEARANCEMANAGER_HPP
#define APPEARANCEMANAGER_HPP

#pragma once

#include "DGEventNotifier.hpp"

namespace DG {

/**
 * @enum AppearanceMode
 * @brief Defines the appearance mode for the application.
 */
enum class AppearanceMode: UInt16
{
    FollowSystem = 0, ///< Follow the system's appearance mode.
    ForceLight = 1,   ///< Force the application to use light mode.
    ForceDark = 2     ///< Force the application to use dark mode.
};

/**
 * @enum AppearanceType
 * @brief Represents the type of appearance (light or dark).
 */
enum class AppearanceType: UInt16
{
    Light = 0, ///< Light appearance type.
    Dark = 1   ///< Dark appearance type.
};

/**
 * @class AppearanceChangedEventArg
 * @ingroup DG
 * @brief Event argument for appearance change notifications.
 */
class DG_DLL_EXPORT AppearanceChangedEventArg: public EventArg
{
public:
    AppearanceMode mode; ///< The current appearance mode.
    AppearanceType type; ///< The current appearance type.

    /**
     * @brief Constructor for AppearanceChangedEventArg.
     * @param mode The appearance mode.
     * @param type The appearance type.
     */
    AppearanceChangedEventArg (AppearanceMode mode, AppearanceType type);

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
     * @brief Gets the current appearance mode.
     * @return The current appearance mode.
     */
    static AppearanceMode GetMode ();

    /**
     * @brief Gets the application's appearance type.
     * @return The application's appearance type.
     */
    static AppearanceType GetApplicationAppearanceType ();

    /**
     * @brief Gets the operating system's appearance type.
     * @return The operating system's appearance type.
     */
    static AppearanceType GetOSAppearanceType ();

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

} // namespace DG

#endif