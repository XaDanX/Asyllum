set(PROJECT_NAME Asyllum)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "kiero/minhook/dll_resources/MinHook.def"
)
source_group("" FILES ${no_group_source_files})

set(Headers
        "imgui/imconfig.h"
    "imgui/imgui.h"
    "imgui/imgui_impl_dx9.h"
    "imgui/imgui_impl_win32.h"
    "imgui/imgui_internal.h"
    "imgui/imstb_rectpack.h"
    "imgui/imstb_textedit.h"
    "imgui/imstb_truetype.h"
        "kiero/kiero.h"
    "kiero/minhook/include/MinHook.h"
    "kiero/minhook/src/buffer.h"
    "kiero/minhook/src/hde/hde32.h"
    "kiero/minhook/src/hde/hde64.h"
    "kiero/minhook/src/hde/pstdint.h"
    "kiero/minhook/src/hde/table32.h"
    "kiero/minhook/src/hde/table64.h"
    "kiero/minhook/src/trampoline.h"
        )
source_group("Headers" FILES ${Headers})

set(Sources
    "imgui/imgui.cpp"
    "imgui/imgui_demo.cpp"
    "imgui/imgui_draw.cpp"
    "imgui/imgui_impl_dx9.cpp"
    "imgui/imgui_impl_win32.cpp"
    "imgui/imgui_widgets.cpp"
    "kiero/kiero.cpp"
    "kiero/minhook/src/buffer.c"
    "kiero/minhook/src/hde/hde32.c"
    "kiero/minhook/src/hde/hde64.c"
    "kiero/minhook/src/hook.c"
    "kiero/minhook/src/trampoline.c"
    "main.cpp"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${no_group_source_files}
    ${Headers}
    ${Sources}
        Core/Hooking/HookingService.cpp Core/Hooking/HookingService.cpp Core/Hooking/HookingService.h Core/Hooking/DirectX.cpp Core/Hooking/DirectX.h Core/Hooking/Helpers.h Protection/PebUnlink.h Protection/XorStr.h Core/Asyllum.cpp Core/Asyllum.h Core/Locator/Locator.cpp Core/Locator/Locator.h Math/Vector.h Math/Math.h Globals/Globals.cpp Globals/Globals.h Core/Helpers/Helpers.h Globals/Offsets.h Core/Objects/ObjectBase.cpp Core/Objects/ObjectBase.h Core/Types/Definitions.h Core/Engine/Engine.cpp Core/Engine/Engine.h Core/Objects/Hero/Hero.cpp Core/Objects/Hero/Hero.h Core/Managers/ObjectManager/ObjectManager.cpp Core/Managers/ObjectManager/ObjectManager.h Core/Managers/ObjectManager/Template.h Core/Data/UnitInfo.cpp Core/Data/UnitInfo.h Core/Data/GameData.cpp Core/Data/GameData.h Core/Data/SpellInfo.cpp Core/Data/SpellInfo.h Core/Helpers/StringUtils.h Core/Renderer/Renderer.cpp Core/Renderer/Renderer.h Core/Managers/ModuleManager/Module.h Core/Managers/ModuleManager/ModuleManager.cpp Core/Managers/ModuleManager/ModuleManager.h ../Modules/ObjectExplorer/ObjectExplorer.cpp ../Modules/ObjectExplorer/ObjectExplorer.h Core/Objects/Minion/Minion.cpp Core/Objects/Minion/Minion.h Core/Objects/Turret/Turret.cpp Core/Objects/Turret/Turret.h Core/Objects/Hero/AiManager/AiManager.cpp Core/Objects/Hero/AiManager/AiManager.h Core/Objects/Hero/SpellBook/SpellSlot.cpp Core/Objects/Hero/SpellBook/SpellSlot.h Core/Renderer/Console/Console.cpp Core/Renderer/Console/Console.h Core/Renderer/TextureManager/TextureManager.cpp Core/Renderer/TextureManager/TextureManager.h ../Modules/Awareness/Awareness.cpp ../Modules/Awareness/Awareness.h Utils/Utils.cpp Utils/Utils.h Core/HudInstance/HudInstance.cpp Core/HudInstance/HudInstance.h ../Modules/Awareness/SpellTracker/SpellTracker.cpp ../Modules/Awareness/SpellTracker/SpellTracker.h)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE ImGui_DirectX_9_Kiero_Hook_2)

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
        "_MBCS"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "_MBCS"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
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
            $<$<CONFIG:Debug>:
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
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
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG:FULL;
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG:FULL;
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "d3d9;"
            "d3dx9"
        ">"
    )
endif()

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_include_directories(${PROJECT_NAME} PUBLIC
            "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/"
            )
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
            "d3d9;"
            "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3dx9.lib;"
            "dxgi"
            )
endif()
target_include_directories(${PROJECT_NAME} PRIVATE
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

