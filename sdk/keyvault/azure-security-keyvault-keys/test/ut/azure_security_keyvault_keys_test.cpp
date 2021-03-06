// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#include "gtest/gtest.h"

#if defined(BUILD_CURL_HTTP_TRANSPORT_ADAPTER)
#include <curl/curl.h>
#endif

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  auto r = RUN_ALL_TESTS();
  return r;
}
