cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0076 NEW)
project(KernelProject C)

set(KMOD_NAME tool)
set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(KBUILD_DIR "${CMAKE_BINARY_DIR}/kbuild")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/kernel/include")

add_custom_target(tool_module)

add_subdirectory(kernel)

execute_process(
    COMMAND uname -r 
    OUTPUT_VARIABLE KERNEL_RELEASE 
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

get_target_property(ALL_SOURCES tool_module SOURCES)

set(COPY_COMMANDS)
set(OBJ_LIST "")

foreach(SRC ${ALL_SOURCES})
    get_filename_component(SRC_NAME ${SRC} NAME)
    get_filename_component(OBJ_NAME ${SRC} NAME_WE)
    
    list(APPEND COPY_COMMANDS COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SRC} ${KBUILD_DIR}/${SRC_NAME})
    
    set(OBJ_LIST "${OBJ_LIST} ${OBJ_NAME}.o")
endforeach()

add_custom_command(TARGET tool_module POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${KBUILD_DIR}
    ${COPY_COMMANDS}
    # 1. obj-m defines the module name
    COMMAND echo "obj-m := ${KMOD_NAME}.o" > ${KBUILD_DIR}/Kbuild
    # 2. <name>-y defines the objects to link
    COMMAND echo "${KMOD_NAME}-y := ${OBJ_LIST}" >> ${KBUILD_DIR}/Kbuild
    # 3. ccflags-y adds the include directory to the search path
    COMMAND echo "ccflags-y := -I${INCLUDE_DIR}" >> ${KBUILD_DIR}/Kbuild
    
    # Run the make command
    COMMAND $(MAKE) -C /lib/modules/${KERNEL_RELEASE}/build M=${KBUILD_DIR} modules
    
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${KBUILD_DIR}/${KMOD_NAME}.ko ${BIN_DIR}/
    WORKING_DIRECTORY ${KBUILD_DIR}
    COMMENT "Building Kernel Module [${KMOD_NAME}.ko] with headers in ${INCLUDE_DIR}"
)

add_custom_target(kernel-mod DEPENDS tool_module)