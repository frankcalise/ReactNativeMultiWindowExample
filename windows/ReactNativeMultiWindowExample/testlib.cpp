#include "pch.h"

#include "testlib.h"

// See https://microsoft.github.io/react-native-windows/docs/native-platform for details on writing native modules

void Testlib::Initialize(React::ReactContext const &reactContext) noexcept {
  m_context = reactContext;
}

double Testlib::multiply(double a, double b) noexcept {
  return a * b;
}
