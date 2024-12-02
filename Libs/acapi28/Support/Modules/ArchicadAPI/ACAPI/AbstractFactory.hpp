#ifndef GS_ACAPI_IMPL_ABSTRACT_FACTORY_HPP
#define GS_ACAPI_IMPL_ABSTRACT_FACTORY_HPP

#include "ACAPI/ArchicadAPIExport.hpp"
#include "APIdefs_Registration.h"
#include <memory>

namespace ACAPI::LicenseInfo::Impl {
class ProductVersionInfoImplBase;
}

namespace ACAPI::Impl {

namespace v1 {

/**
 * @brief AbstractFactory is responsible for creating the implementation. You can make your own factory to use it in unit tests.
 * @ingroup APIInfrastructure
 * @since Archicad 28
 */
class ARCHICADAPI_EXPORT AbstractFactory {
public:
	virtual ~AbstractFactory ();
	
	/**
	 * @brief Creates an object of the ProductVersionInfoImplBase that's used by the ProductVersionInfo.
	 * @ingroup APIInfrastructure
	 * @since Archicad 28
	 * @return The ProductVersionInfoImplBase created by the registered factory.
	 */
	virtual std::shared_ptr<LicenseInfo::Impl::ProductVersionInfoImplBase> CreateLicenseInfoProductVersionInfoImpl (const API_Token&) const;
};


/**
 * @brief FactoryRegistry own the registered factory. Only one factory can be registered at the same time. Use this to register your mock factory when you're unit testing your code.
 * @ingroup APIInfrastructure
 * @since Archicad 28
 */
class ARCHICADAPI_EXPORT FactoryRegistry {
private:
	std::unique_ptr<AbstractFactory>	factory;

	FactoryRegistry ();
public:
	FactoryRegistry (const FactoryRegistry&) = delete;
	FactoryRegistry (FactoryRegistry&&) = delete;

	/**
	 * @brief Registers a new factory to the FactoryRegistry. The given factory overrides the previous one.
	 * @ingroup APIInfrastructure
	 * @since Archicad 28
	 * @param pFactory The given factory to be registered.
	 */
	void RegisterFactory (std::unique_ptr<AbstractFactory> pFactory);
	
	/**
	 * @brief Unregisters the current factory.
	 * @ingroup APIInfrastructure
	 * @since Archicad 28
	 */
	void UnregisterFactory ();

	/**
	 * @brief You can check that there is already a factory registered or not.
	 * @ingroup APIInfrastructure
	 * @since Archicad 28
	 * @return Returns true if there is a factory already registered.
	 */
	bool IsFactoryRegistered () const;

	/**
	 * @brief You can get the registered factory.
	 * @ingroup APIInfrastructure
	 * @since Archicad 28
	 * @return Returns the registered factory.
	 */
	const AbstractFactory& GetFactory () const;

	/**
	 * @brief You can get the registered factory.
	 * @ingroup APIInfrastructure
	 * @since Archicad 28
	 * @return Returns the registered factory.
	 */
	static FactoryRegistry& GetInstance ();
};

} // namespace v1

using v1::AbstractFactory;
using v1::FactoryRegistry;

} // namespace ACAPI::Impl

#endif // GS_ACAPI_IMPL_ABSTRACT_FACTORY_HPP