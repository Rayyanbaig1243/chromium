// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_I18N_STRING_CONVERSIONS_H_
#define BASE_I18N_STRING_CONVERSIONS_H_

#include <string>

#include "base/string16.h"
#include "base/string_piece.h"

// These convert between UTF-8, -16, and -32 strings. They are potentially slow,
// so avoid unnecessary conversions. The low-level versions return a boolean
// indicating whether the conversion was 100% valid. In this case, it will still
// do the best it can and put the result in the output buffer. The versions that
// return strings ignore this error and just return the best conversion
// possible.
//
// Note that only the structural validity is checked and non-character
// codepoints and unassigned are regarded as valid.
// TODO(jungshik): Consider replacing an invalid input sequence with
// the Unicode replacement character or adding |replacement_char| parameter.
// Currently, it's skipped in the ouput, which could be problematic in
// some situations.
bool WideToUTF8(const wchar_t* src, size_t src_len, std::string* output);
std::string WideToUTF8(const std::wstring& wide);
bool UTF8ToWide(const char* src, size_t src_len, std::wstring* output);
std::wstring UTF8ToWide(const base::StringPiece& utf8);

bool WideToUTF16(const wchar_t* src, size_t src_len, string16* output);
string16 WideToUTF16(const std::wstring& wide);
bool UTF16ToWide(const char16* src, size_t src_len, std::wstring* output);
std::wstring UTF16ToWide(const string16& utf16);

bool UTF8ToUTF16(const char* src, size_t src_len, string16* output);
string16 UTF8ToUTF16(const std::string& utf8);
bool UTF16ToUTF8(const char16* src, size_t src_len, std::string* output);
std::string UTF16ToUTF8(const string16& utf16);

// We are trying to get rid of wstring as much as possible, but it's too big
// a mess to do it all at once.  These conversions should be used when we
// really should just be passing a string16 around, but we haven't finished
// porting whatever module uses wstring and the conversion is being used as a
// stopcock.  This makes it easy to grep for the ones that should be removed.
#if defined(OS_WIN)
# define WideToUTF16Hack
# define UTF16ToWideHack
#else
# define WideToUTF16Hack WideToUTF16
# define UTF16ToWideHack UTF16ToWide
#endif

// Defines the error handling modes of UTF16ToCodepage, CodepageToUTF16,
// WideToCodepage and CodepageToWide.
class OnStringUtilConversionError {
 public:
  enum Type {
    // The function will return failure. The output buffer will be empty.
    FAIL,

    // The offending characters are skipped and the conversion will proceed as
    // if they did not exist.
    SKIP,

    // When converting to Unicode, the offending byte sequences are substituted
    // by Unicode replacement character (U+FFFD). When converting from Unicode,
    // this is the same as SKIP.
    SUBSTITUTE,
  };

 private:
  OnStringUtilConversionError();
};

// Converts between UTF-16 strings and the encoding specified.  If the
// encoding doesn't exist or the encoding fails (when on_error is FAIL),
// returns false.
bool UTF16ToCodepage(const string16& utf16,
                     const char* codepage_name,
                     OnStringUtilConversionError::Type on_error,
                     std::string* encoded);

bool CodepageToUTF16(const std::string& encoded,
                     const char* codepage_name,
                     OnStringUtilConversionError::Type on_error,
                     string16* utf16);

// Converts between wide strings and the encoding specified.  If the
// encoding doesn't exist or the encoding fails (when on_error is FAIL),
// returns false.
bool WideToCodepage(const std::wstring& wide,
                    const char* codepage_name,
                    OnStringUtilConversionError::Type on_error,
                    std::string* encoded);
bool CodepageToWide(const std::string& encoded,
                    const char* codepage_name,
                    OnStringUtilConversionError::Type on_error,
                    std::wstring* wide);

#endif  // BASE_I18N_STRING_CONVERSIONS_H_
