cmake_minimum_required(VERSION 3.19)
project(DebugViaCom LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS 
    Core 
    Widgets
)

qt_standard_project_setup()

qt_add_executable(DebugViaCom
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    src/ui/mainWindow.cpp
    src/ui/mainWindow.h
)

target_link_libraries(DebugViaCom
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS DebugViaCom
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET DebugViaCom
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})