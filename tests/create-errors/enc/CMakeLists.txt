# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License.


oeedl_file(../create_errors.edl enclave gen)

add_enclave(TARGET create_errors_enc SOURCES enc.c ${gen})

target_include_directories(create_errors_enc PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
                           ${CMAKE_CURRENT_SOURCE_DIR})
