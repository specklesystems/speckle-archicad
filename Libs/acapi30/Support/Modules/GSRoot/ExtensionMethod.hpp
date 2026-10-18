#ifndef GS_EXTENSION_METHOD_HPP
#define GS_EXTENSION_METHOD_HPP

#pragma once

#include "ClassInfo.hpp"
#include "HashTable.hpp"
#include "TypeTraits.hpp"

namespace GS {

struct VoidReturn {};

template<typename T>
struct ExtensionMethodParameterTypeTraits;

template<typename T>
struct ExtensionMethodParameterTypeTraits<T&>
{
    static const GS::ClassInfo* GetClassInfo (T& v)
    {
        return v.GetClassInfo ();
    }

    template<typename DerivedT>
    static const GS::ClassInfo* GetDerivedTypeClassInfo ()
    {
        static_assert(GS::IsReference<DerivedT>, "DerivedT has to be a reference");
        return GS::Decay<DerivedT>::GetClassInfoStatic ();
    }

    template<typename DerivedT>
    static DerivedT StaticCast (T& v)
    {
        static_assert(GS::IsReference<DerivedT>, "DerivedT has to be a reference");
        return static_cast<DerivedT>(v);
    }
};


template<typename T>
struct ExtensionMethodParameterTypeTraits<T*>
{
    static const GS::ClassInfo* GetClassInfo (T* v)
    {
        return v ? v->GetClassInfo () : nullptr;
    }

    template<typename DerivedT>
    static const GS::ClassInfo* GetDerivedTypeClassInfo ()
    {
        return GS::RemovePointer<DerivedT>::GetClassInfoStatic ();
    }

    template<typename DerivedT>
    static DerivedT StaticCast (T* v)
    {
        static_assert(GS::IsPointer<DerivedT>, "DerivedT has to be a pointer");
        return static_cast<DerivedT>(v);
    }
};

template<typename>
class PublicExtensionMethod;

template<typename>
class PrivateExtensionMethod;

template <typename>
class RegisterTransientExtensionMethod;

namespace Imp {

template<typename>
class ExtensionMethodRegistry;

template<typename>
class ExtensionMethodInvoker;


template<typename R, typename BaseT, typename... Args>
class ExtensionMethodRegistry<R (BaseT, Args...)>
{
public:
    using ReturnType = GS::Conditional<IsSame<void, R>, VoidReturn, R>;
    using InvokerType = ExtensionMethodInvoker<R (BaseT, Args...)>;
    friend InvokerType;
    using BaseFunction = std::function<ReturnType (BaseT, Args...)>;

private:
    GS::HashTable<const GS::ClassInfo*, BaseFunction> overrides;

    template<
        typename DerivedT,
        typename X = R,
        GS::EnableIf<!GS::IsVoid<X>, bool> = true
    >
        static BaseFunction Wrap (std::function<R (DerivedT, Args...)>&& f)
    {
        return[f = std::move (f)] (BaseT base, auto&&... args) {
            return f (ExtensionMethodParameterTypeTraits<BaseT>::template StaticCast<DerivedT> (std::forward<BaseT> (base)), std::forward<decltype(args)> (args)...);
        };
    }

    template<
        typename DerivedT,
        typename X = R,
        GS::EnableIf<GS::IsVoid<X>, bool> = true
    >
        static BaseFunction Wrap (std::function<R (DerivedT, Args...)>&& f)
    {
        return[f = std::move (f)] (BaseT base, auto&&... args) {
            f (ExtensionMethodParameterTypeTraits<BaseT>::template StaticCast<DerivedT> (std::forward<BaseT> (base)), std::forward<decltype(args)> (args)...);
            return VoidReturn ();
        };
    }

    const BaseFunction* GetFunctionFor (BaseT base) const
    {
        const GS::ClassInfo* classInfo = ExtensionMethodParameterTypeTraits<BaseT>::GetClassInfo (base);
        while (classInfo != nullptr) {
            const BaseFunction* f;
            if (overrides.Get (classInfo, &f))
                return f;

            classInfo = classInfo->GetBaseClass ();
        }

        return nullptr;
    }

public:
    ExtensionMethodRegistry (InvokerType& invoker);
    ExtensionMethodRegistry (const ExtensionMethodRegistry&) = delete;
    ExtensionMethodRegistry& operator= (const ExtensionMethodRegistry&) = delete;

    template<typename CallableT>
    void Add (CallableT f);

    bool Remove (const GS::ClassInfo* classInfo);

    template<typename DerivedT>
    void Remove ();

    template<typename CallableT>
    void Remove (CallableT);
};


template<typename R, typename BaseT, typename... Args>
ExtensionMethodRegistry<R (BaseT, Args...)>::ExtensionMethodRegistry (InvokerType& invoker)
{
    invoker.registry = this;
}


template<typename R, typename BaseT, typename ...Args>
template<typename CallableT>
void ExtensionMethodRegistry<R (BaseT, Args...)>::Add (CallableT f)
{
    using DerivedT = FirstArgumentType<CallableT>;
    DBVERIFY (overrides.Add (ExtensionMethodParameterTypeTraits<BaseT>::template GetDerivedTypeClassInfo<DerivedT> (), Wrap (std::function<R (DerivedT, Args...)> (std::move (f)))));
}


template<typename R, typename BaseT, typename ...Args>
bool ExtensionMethodRegistry<R (BaseT, Args...)>::Remove (const GS::ClassInfo* classInfo)
{
    return overrides.Delete (classInfo);
}


template<typename R, typename BaseT, typename ...Args>
template<typename DerivedT>
void ExtensionMethodRegistry<R (BaseT, Args...)>::Remove ()
{
    DBVERIFY (Remove (ExtensionMethodParameterTypeTraits<BaseT>::template GetDerivedTypeClassInfo<DerivedT> ()));
}


template<typename R, typename BaseT, typename ...Args>
template<typename CallableT>
void ExtensionMethodRegistry<R (BaseT, Args...)>::Remove (CallableT)
{
    using DerivedT = FirstArgumentType<CallableT>;
    Remove<DerivedT> ();
}


template<typename R, typename BaseT, typename... Args>
class ExtensionMethodInvoker<R (BaseT, Args...)>
{
private:

    using ExtensionRegistryType = ExtensionMethodRegistry<R (BaseT, Args...)>;

    friend ExtensionRegistryType;

    const ExtensionRegistryType* registry;

public:
    template<class... ActualArgs>
    typename ExtensionRegistryType::ReturnType operator() (BaseT b, ActualArgs&&... args) const;

    bool IsCallableFor (BaseT base) const;
};


template<typename R, typename BaseT, typename ...Args>
template<class... ActualArgs>
typename ExtensionMethodInvoker<R (BaseT, Args...)>::ExtensionRegistryType::ReturnType  ExtensionMethodInvoker<R (BaseT, Args...)>::operator() (BaseT b, ActualArgs&&... args) const
{
    DBASSERT (registry);
    DBASSERT (IsCallableFor (b));
    return (*registry->GetFunctionFor (b))(b, std::forward<ActualArgs> (args)...);
}


template<typename R, typename BaseT, typename ...Args>
bool ExtensionMethodInvoker<R (BaseT, Args...)>::IsCallableFor (BaseT base) const {
    DBASSERT (registry);
    return registry->GetFunctionFor (base) != nullptr;
}

}


template<typename FunctionT>
class PublicExtensionMethod : public Imp::ExtensionMethodInvoker<FunctionT>, public Imp::ExtensionMethodRegistry<FunctionT> {
public:
    PublicExtensionMethod () : Imp::ExtensionMethodRegistry<FunctionT> (static_cast<Imp::ExtensionMethodInvoker<FunctionT>&>(*this))
    {
    }
};


template<typename FunctionT>
class PrivateExtensionMethod : public Imp::ExtensionMethodRegistry<FunctionT>, private Imp::ExtensionMethodInvoker<FunctionT> {
public:
    using InvokerType = Imp::ExtensionMethodInvoker<FunctionT>;

    using Imp::ExtensionMethodInvoker<FunctionT>::IsCallableFor;

    PrivateExtensionMethod (InvokerType& invoker) : Imp::ExtensionMethodRegistry<FunctionT> (static_cast<InvokerType&>(*this))
    {
        invoker = static_cast<InvokerType&>(*this);
    }
};


template<typename R, typename BaseT, typename... Args>
class RegisterTransientExtensionMethod<R (BaseT, Args...)>
{
public:
    using RegistryType = Imp::ExtensionMethodRegistry<R(BaseT, Args...)>;

private:
    const GS::ClassInfo* classInfo;
    RegistryType& registry;

public:
    template<typename CallableT>
    RegisterTransientExtensionMethod (RegistryType& registry, CallableT f) : classInfo (ExtensionMethodParameterTypeTraits<BaseT>::template GetDerivedTypeClassInfo<FirstArgumentType<CallableT>> ()), registry(registry)
    {
         this->registry.Add (std::move (f));        
    }
 
    ~RegisterTransientExtensionMethod ()
    {
        registry.Remove (classInfo);
    }
};

}

#endif
