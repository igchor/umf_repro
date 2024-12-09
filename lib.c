/*
 *
 * Copyright (C) 2024 Intel Corporation
 *
 * Under the Apache License v2.0 with LLVM Exceptions. See LICENSE.TXT.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 */

#include <stdio.h>

#include "umf/ipc.h"
#include "umf/memory_pool.h"
#include "umf/pools/pool_proxy.h"
#include "umf/providers/provider_level_zero.h"

#include "examples_level_zero_helpers.h"

void* alloc(void) {
    uint32_t driver_idx = 0;
    ze_driver_handle_t driver = NULL;
    ze_device_handle_t device = NULL;
    ze_context_handle_t context = NULL;
    int ret = init_level_zero();
    if (ret != 0) {
        fprintf(stderr, "ERROR: Failed to init Level 0!\n");
        return NULL;
    }

    ret = find_driver_with_gpu(&driver_idx, &driver);
    if (ret || driver == NULL) {
        fprintf(stderr, "ERROR: Cannot find L0 driver with GPU device!\n");
        return NULL;
    }

    ret = create_context(driver, &context);
    if (ret != 0) {
        fprintf(stderr, "ERROR: Failed to create L0 context!\n");
        return NULL;
    }

    // setup params
    umf_level_zero_memory_provider_params_handle_t params = NULL;
    umf_result_t umf_ret = umfLevelZeroMemoryProviderParamsCreate(&params);
    if (umf_ret != UMF_RESULT_SUCCESS) {
        fprintf(stderr, "ERROR: umfLevelZeroMemoryProviderParamsCreate\n");
        return NULL;
    }

    umf_ret = umfLevelZeroMemoryProviderParamsSetContext(params, context);
    if (umf_ret != UMF_RESULT_SUCCESS) {
        fprintf(stderr, "ERROR: umfLevelZeroMemoryProviderParamsSetContext\n");
        return NULL;
    }

    umf_ret = umfLevelZeroMemoryProviderParamsSetDevice(params, NULL);
    if (umf_ret != UMF_RESULT_SUCCESS) {
        fprintf(stderr, "ERROR: umfLevelZeroMemoryProviderParamsSetDevice\n");
        return NULL;
    }

    umf_ret = umfLevelZeroMemoryProviderParamsSetMemoryType(params, UMF_MEMORY_TYPE_HOST);
    if (umf_ret != UMF_RESULT_SUCCESS) {
        fprintf(stderr, "ERROR: umfLevelZeroMemoryProviderParamsSetMemoryType\n");
        return NULL;
    }

    umf_memory_provider_handle_t hProvider;
    umf_ret = umfMemoryProviderCreate(umfLevelZeroMemoryProviderOps(), params, &hProvider);
    if (umf_ret != UMF_RESULT_SUCCESS) {
        fprintf(stderr, "ERROR: umfMemoryProviderCreate\n");
        return NULL;
    }

    umf_memory_pool_handle_t hPool;
    umf_ret = umfPoolCreate(umfProxyPoolOps(), hProvider, NULL, 0, &hPool);
    if (umf_ret != UMF_RESULT_SUCCESS) {
        fprintf(stderr, "ERROR: umfPoolCreate\n");
        return NULL;
    }

    return umfPoolMalloc(hPool, 1024);
}
