// Copyright(c) Microsoft Corporation.All rights reserved.
// SPDX - License - Identifier : MIT

#pragma once

#include <functional>
#include <map>
#include <string>

class StressTest {
public:
  static const std::map<std::string, std::function<void()>>& Cases() { return m_cases(); }

protected:
  static void m_addCase(std::string caseName, std::function<void()> func)
  {
    m_cases().emplace(std::move(caseName), std::move(func));
  }

private:
  static std::map<std::string, std::function<void()>>& m_cases()
  {
    static std::map<std::string, std::function<void()>> casesInstance;
    return casesInstance;
  }
};

#define TESTCASE(NAME, FUNCTION) \
  void FUNCTION(); \
\
  class StressTest##NAME : public StressTest { \
  public: \
    StressTest##NAME() { m_addCase(#NAME, FUNCTION); } \
  }; \
  namespace { \
    StressTest##NAME StressTest##NAME_; \
  }

const std::string& GetConnectionString();

constexpr const static char* DefaultContainerName = "stress-test";
