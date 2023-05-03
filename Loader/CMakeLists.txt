set(PROJECT_NAME Loader)
set(CMAKE_CXX_STANDARD 23)
################################################################################
# Source groups
################################################################################
source_group("Fichiers d%27en-tête" FILES ${Fichiers_d27en-tte})


set(Fichiers_d27en-tte__ImGui
        "imgui/imconfig.h"
        "imgui/imgui.h"
        "imgui/imgui_impl_dx9.h"
        "imgui/imgui_impl_win32.h"
        "imgui/imgui_internal.h"
        "imgui/imstb_rectpack.h"
        "imgui/imstb_textedit.h"
        "imgui/imstb_truetype.h"
        "imgui/imgui.cpp"
        "imgui/imgui_demo.cpp"
        "imgui/imgui_draw.cpp"
        "imgui/imgui_impl_dx9.cpp"
        "imgui/imgui_impl_win32.cpp"
        "imgui/imgui_widgets.cpp"
        )
source_group("Fichiers d%27en-tête\\ImGui" FILES ${Fichiers_d27en-tte__ImGui})

set(Fichiers_sources
        "main.cpp"
        )
source_group("Fichiers sources" FILES ${Fichiers_sources})

set(ALL_FILES
        ${Fichiers_d27en-tte}
        ${Fichiers_d27en-tte__ImGui}
        ${Fichiers_sources}
        XorStr.h Ui/Ui.cpp Ui/Ui.h Globals/Globals.cpp Globals/Globals.h Globals/Font.h helper.h)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE ImGuiStandalone)

set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_GLOBAL_KEYWORD "Win32Proj"
        )
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
            INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
            )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
            INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
            )
endif()
################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
            "$<$<CONFIG:Debug>:"
            "_DEBUG;"
            "CONSOLE"
            ">"
            "$<$<CONFIG:Release>:"
            "NDEBUG;"
            "_CONSOLE"
            ">"
            "UNICODE;"
            "_UNICODE"
            )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
            "$<$<CONFIG:Debug>:"
            "_DEBUG"
            ">"
            "$<$<CONFIG:Release>:"
            "NDEBUG"
            ">"
            "WIN32;"
            "_CONSOLE;"
            "UNICODE;"
            "_UNICODE"
            )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
                $<$<CONFIG:Release>:
                /Oi;
                /Gy
                >
                /permissive-;
                /sdl;
                /W3;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
                ${DEFAULT_CXX_EXCEPTION_HANDLING}
                )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
                $<$<CONFIG:Release>:
                /Oi;
                /Gy
                >
                /permissive-;
                /sdl;
                /W3;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
                ${DEFAULT_CXX_EXCEPTION_HANDLING}
                )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
                $<$<CONFIG:Debug>:
                /INCREMENTAL
                >
                $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
                >
                /DEBUG;
                /SUBSYSTEM:WINDOWS
                )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
                $<$<CONFIG:Debug>:
                /INCREMENTAL
                >
                $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
                >
                /DEBUG;
                /SUBSYSTEM:WINDOWS
                )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
            "d3d9;"
            "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64/d3dx9.lib;"
            "dxgi;"
            "dxguid;"
            "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64/dinput8.lib"
            )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
            "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3d11.lib;"
            )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/"
        )
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

