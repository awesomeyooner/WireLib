cmake_minimum_required(VERSION 3.12)

project( WireLib LANGUAGES C CXX )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_FILES
    # Wire Manager
    src/communication/wire_manager.cpp

    # General Communication
    src/communication/communication_interface.cpp
    src/communication/communication_api.cpp

    # Register Stuff
    src/registers/register_manager.cpp

    # Utils
    src/util/byte_converter.cpp
)

# Serial
    option(WIRELIB_BUILD_SERIAL
        "Compile code that uses USB CDC"
        ON
    )

    if(WIRELIB_BUILD_SERIAL)

        # SRC_FILES is a list of all `.cpp` files
        list(APPEND SRC_FILES
            src/communication/protocols/serial_api.cpp
            src/communication/protocols/serial_interface.cpp
        )

    endif()

# CANBus
    option(WIRELIB_BUILD_CAN
        "Compile code that uses `can.h`"
        ON
    )

    if(WIRELIB_BUILD_CAN)

        # SRC_FILES is a list of all `.cpp` files
        list(APPEND SRC_FILES
            src/communication/protocols/canbus/can_interface.cpp
        )

    endif()

# I2C
    option(WIRELIB_BUILD_I2C
        "Compile code that uses `i2c.h`"
        ON
    )

    if(WIRELIB_BUILD_I2C)

        # SRC_FILES is a list of all `.cpp` files
        list(APPEND SRC_FILES
            src/communication/protocols/i2c/i2c_api.cpp
            src/communication/protocols/i2c/i2c_interface.cpp
        )

    endif()

# === Main Library ===
add_library(${PROJECT_NAME} OBJECT
    ${SRC_FILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC 
        EmbeddedLib
        ActionLib
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Add the test executables only if this project is at the top level (aka not used with add_subdirectory)
if(PROJECT_IS_TOP_LEVEL)
    add_executable(Test test/test.cpp)
    target_link_libraries(Test PRIVATE 
        ${PROJECT_NAME}
    )
endif()