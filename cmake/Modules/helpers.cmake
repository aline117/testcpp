
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(_lib_suffix 64)
else()
    set(_lib_suffix 32)
endif()

function(copy_include)
    #message(STATUS "------ARGC-----${ARGC}")
    if(DEFINED ARGV0)
        set(INC_DIR "${ARGV0}")
        #FOREACH(loop_var RANGE start stop [step])
        foreach(idx RANGE 1 ${ARGC} )
            string(LENGTH "${ARGV${idx}}" str_len)
            if( str_len )
                #message(STATUS "${idx} copy '${ARGV${idx}}' ==>'${INC_DIR}'")
                file(COPY "${ARGV${idx}}" DESTINATION "${INC_DIR}")
            endif()
        endforeach()

        #message(STATUS "start-----------")
        #set(INC_DIR "${ARGV0}")
        #if(NOT EXISTS ${INC_DIR} )
        #    message(STATUS "---mkdir:'${ARGV0}'")
        #    break()
        #    #make_directory(${ARGV0})
        #endif()
        ##message(STATUS "---ARGV0:${ARGV0}")
        ##message(STATUS "================ARGN:${ARGN}")
        #foreach(inc ${ARGN})
        #    if( ${INC_DIR} STREQUAL ${inc} )
        #    #    message(STATUS "======not:${inc}")
        #    else()
        #        message(STATUS "-----copy:${inc}")
        #    endif()
        #
        #    #file(COPY "${inc}" DESTINATION "${AVCORE_INC}")
        #    #if(EXISTS "./${inc}")
        #    #    message(STATUS "---------------cp:${inc}")
        #    #endif()
        #endforeach()
    endif()
endfunction()


function(install_server)
    set(tgt_dir "") #target dir
    set(target  "") #target
    set(conf    "") #target config
    set(logconf "") #target log config
    if(DEFINED ARGV0)
        set(tgt_dir "${ARGV0}") #target dir
    endif()
    if(DEFINED ARGV1)
        set(target  "${ARGV1}") #dst
    endif()
    if(DEFINED ARGV2)
        set(conf    "${ARGV2}") #dst config
    endif()
    if(DEFINED ARGV3)
        set(logconf "${ARGV3}") #dst log config
    endif()

    #message(STATUS "${EXECUTABLE_OUTPUT_PATH}")
    #set(all_dir "${EXECUTABLE_OUTPUT_PATH}/${tgt_dir}") #target dir
    set(all_dir "${EXECUTABLE_OUTPUT_PATH}") #target dir
    if( NOT EXISTS ${all_dir})
        make_directory(${all_dir})
    endif()
    if( EXISTS ${all_dir})
      #message(STATUS "${conf}")
      if( conf )
        file(COPY "${conf}"    DESTINATION "${all_dir}")
      endif()
      #message(STATUS "${logconf}")
      if( logconf )
        file(COPY "${logconf}" DESTINATION "${all_dir}")
      endif()
      #file(target "${EXECUTABLE_OUTPUT_PATH}/${target}"  DESTINATION "${all_dir}")
    endif()
endfunction()

