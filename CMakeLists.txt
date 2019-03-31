cmake_minimum_required(VERSION 2.8)
project(cppTest)

set(CMAKE_CXX_STANDARD 14)


#set path
set(DIR_PRJ ${CMAKE_CURRENT_SOURCE_DIR})
set(DIR_BIN        "${DIR_PRJ}/bin")
set(DIR_LIB        "${DIR_BIN}/lib")
set(DIR_UTL        "${DIR_PRJ}/util")
set(DIR_THD        "${DIR_PRJ}/third")
message(STATUS "DIR_PRJ:${DIR_PRJ}")
message(STATUS "DIR_LIB:${DIR_LIB}")
message(STATUS "DIR_BIN:${DIR_BIN}")
message(STATUS "DIR_UTL:${DIR_UTL}")
message(STATUS "DIR_THD:${DIR_THD}")

##设置自定义cmake脚本路径
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${DIR_PRJ}/cmake/Modules")

#支持的平台(windows/Mac/Ios/android/linux/...),且只能选某一个
#message(STATUS "ID:${CMAKE_CXX_COMPILER_ID}")
message(STATUS "SYS:${CMAKE_SYSTEM}")
#message(STATUS "SYSNAME:${CMAKE_SYSTEM_NAME}")
#message(STATUS "SYSVER:${CMAKE_SYSTEM_VERSION}") #2.6.32-754.el6.x86_64
#message(STATUS "SYSPROC:${CMAKE_SYSTEM_PROCESSOR}") #x86_64

#string(FIND <string> <substring> <output variable> [REVERSE])
string(FIND ${CMAKE_SYSTEM_VERSION} "-" VER_POS)
#string(SUBSTRING <string> <begin> <length> <output variable>)
string(SUBSTRING ${CMAKE_SYSTEM_VERSION} 0 ${VER_POS} PLF_VER)
#message("pos:${VER_POS} ver:'${PLF_VER}'")


#可在cmake命令带上参数-DPLF_NAME=platform[windows/ios/mac/android/linux]
if(NOT DEFINED PLF_NAME)
    set(PLF_NAME  ${CMAKE_SYSTEM_NAME})
endif()
string(TOLOWER ${PLF_NAME} PLF_OS)

set(PLF_NAME  "")
if(WIN32)
    set(PLF_WINDOWS  1) #
    set(PLF_NAME     "win")
elseif(APPLE)
    SET(CMAKE_MACOSX_RPATH 1)
    if("${PLF_OS}" STREQUAL "ios")
        set(PLF_IOS      1)
        set(PLF_NAME     "ios")
        #elseif()
    else()
        set(PLF_MAC      1)
        set(PLF_NAME     "mac")
    endif()
else()
    if(PLF_OS STREQUAL "linux")
        set(PLF_LINUX    1)
        set(PLF_NAME     "linux${PLF_VER}")
    elseif(PLF_OS STREQUAL "android")
        set(PLF_ANDROID  1)
        set(PLF_NAME     "android")
    else()
    endif()
endif()
if(NOT PLF_NAME)
    message(FATAL_ERROR "NOT SUPPORT OS")
endif()
message(STATUS "env :${PLF_NAME}")
#message(FATAL_ERROR "-----------------------")

#设置编译结果输出路径
#set(DIR_O_BIN    "${DIR_TT}/.bin/${PLF_NAME}")
#set(DIR_I_LIB    "${DIR_TT}/.lib/${PLF_NAME}")
set(DIR_O_BIN    "${DIR_BIN}/${PLF_NAME}")
set(DIR_I_LIB    "${DIR_LIB}/${PLF_NAME}")
set(CMAKE_INSTALL_PREFIX ${DIR_I_LIB})
#确定生成的库和可执行文件目录
set(LIBRARY_OUTPUT_PATH "${DIR_O_BIN}")    #ok
set(EXECUTABLE_OUTPUT_PATH "${DIR_O_BIN}") #ok

#if(WIN32)
#    configure_file(
#            copy_lib.bat.in
#            ${DIR_O_BIN}/copy_lib.bat
#    )
#    configure_file(
#            make_pkg.bat.in
#            ${DIR_O_BIN}/make_pkg.bat
#    )
#else()
#    configure_file(
#            copy_lib.sh.in
#            ${DIR_O_BIN}/copy_lib.sh
#    )
#    configure_file(
#            make_pkg.sh.in
#            ${DIR_O_BIN}/make_pkg.sh
#    )
#    configure_file(
#            link_lib.sh.in
#            ${DIR_O_BIN}/link_lib.sh
#    )
#endif()

#确定编译FLAGS
set(COM_DEF ${COM_DEF}  -g -W -Wall )
set(COM_DEF ${COM_DEF}  -D_FILE_OFFSET_BITS=64 -D_REENTRANT )
set(COM_DEF ${COM_DEF}
        -DAC_HAS_INFO
        -DAC_HAS_WARNING
        -DAC_HAS_ERROR
        -DAC_HAS_CRITICAL
        -DAC_HAS_DEBUG
        )
set(COM_DEF ${COM_DEF}
        -DTIXML_USE_STL
        #	-DLINUX_DAEMON
        )
if(PLF_WINDOWS)
    #message(STATUS "OS:windows")
    set(COM_DEF ${COM_DEF}
            -D_WIN32
            #-D_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
            )
elseif(PLF_MAC OR PLF_IOS)
    set(CMAKE_MACOSX_RPATH 1)
    if(PLF_IOS)
        set(COM_DEF ${COM_DEF}
                -D_FS_OS_IOS
                -Wnonportable-include-path
                )
        set(ARCH_X86                    0) #"ARCH X86"
        set(ENABLE_H264IOSHDENC         1) #"h264 ios hdenc encode"
    else()
        set(COM_DEF ${COM_DEF}
                -D__APPLE__
                -D_FS_OS_MAC
                #	-Wnonportable-include-path
                )
        MESSAGE(STATUS ASM_NASM_COMPILER: "${CMAKE_ASM_NASM_COMPILER}")
        MESSAGE(STATUS CXX_COMPILER: "${CMAKE_CXX_COMPILER}")
    endif()
    set(COM_DEF ${COM_DEF}
            -Wunused-value
            -Wno-deprecated
            -Wunused-parameter
            -Wunused-function
            )
elseif(PLF_ANDROID)
elseif(PLF_LINUX) #if(LINUX)
    set(COM_DEF ${COM_DEF}
            -D_FS_OS_MAC
            -Wno-deprecated
            )
else()
    message(FATAL_ERROR "NOT SUPPORT OS")
endif()
message(STATUS "${COM_DEF}")


include(helpers)

add_subdirectory(util)
add_subdirectory(udp)


message(STATUS "OVER")






