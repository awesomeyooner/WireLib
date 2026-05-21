cmake_minimum_required(VERSION 3.12)

project( WireLib LANGUAGES C CXX )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# === Main Library ===
add_library(${PROJECT_NAME}
    src/communication/wire_manager.cpp
    src/communication/communication_interface.cpp
    src/communication/communication_api.cpp
    
    src/registers/command_struct.cpp
    # src/registers/register_manager.cpp
    src/registers/request_struct.cpp

    src/stm32/communication/protocols/serial_api.cpp
    src/stm32/communication/protocols/serial_interface.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC EmbeddedLib
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Add the test executables only if this project is at the top level (aka not used with add_subdirectory)
if(PROJECT_IS_TOP_LEVEL)
    add_executable(Test test/test.cpp)
    target_link_libraries(Test PRIVATE 
        ${PROJECT_NAME}
    )
endif()