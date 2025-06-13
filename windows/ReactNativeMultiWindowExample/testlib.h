#pragma once

#include "pch.h"
#include "resource.h"


#if __has_include("../testlib/codegen/NativeTestlibDataTypes.g.h")
  #include "../testlib/codegen/NativeTestlibDataTypes.g.h"
#endif
#include "../testlib/codegen/NativeTestlibSpec.g.h"

#include "NativeModules.h"


REACT_MODULE(Testlib)
struct Testlib
{
  using ModuleSpec = testlibCodegen::TestlibSpec;

  REACT_INIT(Initialize)
  void Initialize(React::ReactContext const &reactContext) noexcept;

  REACT_SYNC_METHOD(multiply)
  double multiply(double a, double b) noexcept;

private:
  React::ReactContext m_context;
};