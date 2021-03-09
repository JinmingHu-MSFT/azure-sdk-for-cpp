// Copyright(c) Microsoft Corporation.All rights reserved.
// SPDX - License - Identifier : MIT

#include "stress_test_common.hpp"

#include <azure/storage/blobs.hpp>

TESTCASE(CreateBlob, CreateBlob)
void CreateBlob() {
  auto containerClient = Azure::Storage::Blobs::BlobContainerClient::CreateFromConnectionString(
      GetConnectionString(), DefaultContainerName);
}
