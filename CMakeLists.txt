cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0076 NEW)
project(KernelProject C)

set(KMOD_NAME tool)
set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(KBUILD_DIR ${CMAKE_BINARY_DIR}/kbuild)

add_custom_target(tool_module)
add_subdirectory(kernel)
get_target_property(ALL_SOURCES tool_module SOURCES)
execute_process(COMMAND uname -r OUTPUT_VARIABLE KERNEL_RELEASE OUTPUT_STRIP_TRAILING_WHITESPACE)

set(COPY_COMMANDS)
foreach(SRC ${ALL_SOURCES})
    get_filename_component(SRC_NAME ${SRC} NAME)
    list(APPEND COPY_COMMANDS COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SRC} ${KBUILD_DIR}/${SRC_NAME})
endforeach()

add_custom_command(TARGET tool_module POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${KBUILD_DIR}
    ${COPY_COMMANDS}
    COMMAND echo "obj-m := ${KMOD_NAME}.o" > ${KBUILD_DIR}/Kbuild
    COMMAND $(MAKE) -C /lib/modules/${KERNEL_RELEASE}/build M=${KBUILD_DIR} modules
    COMMAND ${CMAKE_COMMAND} -E copy ${KBUILD_DIR}/${KMOD_NAME}.ko ${BIN_DIR}/
    COMMENT "Building Kernel Module: ${KMOD_NAME}.ko"
)

add_custom_target(kernel-mod DEPENDS tool_module)