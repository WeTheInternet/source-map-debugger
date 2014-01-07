// Copyright (c) 2011, the Dart project authors.  Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

#ifndef VM_RESOLVER_H_
#define VM_RESOLVER_H_

#include "vm/allocation.h"

namespace dart {

// Forward declarations.
class Array;
class Class;
class Instance;
class Library;
class RawFunction;
class String;
class ArgumentsDescriptor;


// Resolver abstracts functionality needed to resolve dart functions at
// invocations.
class Resolver : public AllStatic {
 public:
  // Resolve specified dart instance function.
  static RawFunction* ResolveDynamic(const Instance& receiver,
                                     const String& function_name,
                                     const ArgumentsDescriptor& args_desc);

  static RawFunction* ResolveDynamicForReceiverClass(
      const Class& receiver_class,
      const String& function_name,
      const ArgumentsDescriptor& args_desc);

  static RawFunction* ResolveDynamicAnyArgs(
      const Class& receiver_class,
      const String& function_name);

  // Resolve specified dart static function. If library.IsNull, use
  // either application library or core library if no application library
  // exists. Passing negative num_arguments means that the function
  // will be resolved by name only.
  // Otherwise null is returned if the number or names of arguments are not
  // valid for the resolved function.
  static RawFunction* ResolveStatic(const Library& library,
                                    const String& cls_name,
                                    const String& function_name,
                                    intptr_t num_arguments,
                                    const Array& argument_names);

  // Resolve specified dart static function with specified arity.
  static RawFunction* ResolveStatic(const Class&  cls,
                                    const String& function_name,
                                    intptr_t num_arguments,
                                    const Array& argument_names);
};

}  // namespace dart

#endif  // VM_RESOLVER_H_
