// *****************************************************************************
// GSXML mian include file
// GSXML /  GSXML
//
// Namespaces:        Contact person:
//     -                  FM
//
// [SG compatible]
// *****************************************************************************
#if !defined(GSXML_HPP)
#define GSXML_HPP

#pragma once

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// Util Headers
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLException.hpp>

// SAX2 Headers...
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

// Framework...
#include <xercesc/framework/MemBufInputSource.hpp>

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#endif
