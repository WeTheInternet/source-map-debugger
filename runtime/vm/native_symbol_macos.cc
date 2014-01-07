// Copyright (c) 2013, the Dart project authors.  Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

#include "vm/globals.h"
#if defined(TARGET_OS_MACOS)

#include "vm/native_symbol.h"
#include "vm/thread.h"

#include <cxxabi.h>  // NOLINT
#include <dlfcn.h>  // NOLINT

namespace dart {

void NativeSymbolResolver::InitOnce() {
}


void NativeSymbolResolver::ShutdownOnce() {
}


char* NativeSymbolResolver::LookupSymbolName(uintptr_t pc) {
  Dl_info info;
  int r = dladdr(reinterpret_cast<void*>(pc), &info);
  if (r == 0) {
    return NULL;
  }
  if (info.dli_sname == NULL) {
    return NULL;
  }
  int status;
  char* demangled = abi::__cxa_demangle(info.dli_sname, NULL, NULL, &status);
  if (status == 0) {
    return demangled;
  }
  return strdup(info.dli_sname);
}


void NativeSymbolResolver::FreeSymbolName(char* name) {
  free(name);
}


}  // namespace dart

#endif  // defined(TARGET_OS_MACOS)
