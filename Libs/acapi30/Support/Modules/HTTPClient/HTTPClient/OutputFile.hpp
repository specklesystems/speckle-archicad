#ifndef GS_HTTPCLIENT_OUTPUT_FILE_HPP
#define GS_HTTPCLIENT_OUTPUT_FILE_HPP

// from GSRoot
#include "CountedPtr.hpp"

// from InputOutput
#include "File.hpp"


namespace HTTPClient {

using OutputFile = GS::CountedPtr<IO::File, GS::AtomicCounter>;

} // namespace HTTPClient

#endif // GS_HTTPCLIENT_OUTPUT_FILE_HPP