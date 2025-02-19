/*
 *
 * Copyright (C) 2024 Intel Corporation
 *
 * Under the Apache License v2.0 with LLVM Exceptions. See LICENSE.TXT.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 */

#include <stdio.h>
#include <level_zero/ze_api.h>

ze_context_handle_t lib_create_context();

int main() {
    // void* ptr = alloc();
    ze_context_handle_t context = lib_create_context();
    if (context == NULL) {
        fprintf(stderr, "ERROR: Failed to create L0 context!\n");
        return 1;
    }
}
