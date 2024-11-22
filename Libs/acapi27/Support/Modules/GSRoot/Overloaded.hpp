#pragma once

namespace GS {

// Overloaded represents an overloaded function as one object, 
// it can be used to provide several overloaded version of an operation by overloading () operator with different paramer types.
// Usage example : visit operation for variant can be overloaded for variant's parameter types
// See https://en.cppreference.com/w/cpp/utility/variant/visit for details
template<class... Ts> struct Overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> Overloaded(Ts...) -> Overloaded<Ts...>;

} // namespace GS
