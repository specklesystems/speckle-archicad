#ifndef GS_DG_SHORTCUTSCHEMECLEANER_HPP
#define GS_DG_SHORTCUTSCHEMECLEANER_HPP

#include <functional>

namespace DG {
	class Command;
	class CommandDescriptor;
	class Shortcut;
	class ShortcutScheme;

	using ShortcutPredicate = std::function <bool (const Shortcut&, const CommandDescriptor&)>;

	DG_DLL_EXPORT void CCALL CleanShortcuts (ShortcutScheme& shortcutScheme, const ShortcutPredicate& shouldRemoveShortcut);
}


#endif