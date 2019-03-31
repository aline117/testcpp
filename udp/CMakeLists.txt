cmake_minimum_required(VERSION 2.8)
PROJECT(udp)

#AUX_SOURCE_DIRECTORY(./ SRC_LIST)
set(INC_LIST
	udp_connect.h
)

set(SRC_LIST
	udp_connect.cpp
)

set(SRC_LIST_client
	udp_connect.client.cpp
)

set(SRC_LIST_server_thd
	udp_connect.server_thread.cpp
)

IF(PLF_MAC)
	set(SRC_LIST_server_kqueue ${SRC_LIST}
		udp_connect.server_kqueue.cpp
		)
ENDIF()

IF(PLF_LINUX)
	set(SRC_LIST_server_epoll ${SRC_LIST}
		udp_connect.server_epoll.cpp
		)
ENDIF()

#ADD_DEFINITIONS( -g -W -Wall -D_REENTRANT -D_FILE_OFFSET_BITS=64 -DAC_HAS_INFO
#-DAC_HAS_WARNING -DAC_HAS_ERROR -DAC_HAS_CRITICAL -DTIXML_USE_STL
#-DAC_HAS_DEBUG -DLINUX_DAEMON -std=c++11)
ADD_DEFINITIONS(${COM_DEF})
#ADD_DEFINITIONS(-std=c++11)

#INCLUDE_DIRECTORIES(${DIR_I_LIB}/include)
INCLUDE_DIRECTORIES(${DIR_UTL})


#LINK_DIRECTORIES(${DIR_I_LIB}/lib)

#ADD_XXXX必须在TARGET_LINK_LIBRARIES前面，否则会报错
#ADD_LIBRARY(${PROJECTNAME} SHARED/STATIC ${SRC_LIST})
set(EXECUTABLE_OUTPUT_PATH "${DIR_O_BIN}/udp") #ok


set(NAME_PRJ_client udp.client )
ADD_EXECUTABLE(${NAME_PRJ_client} ${INC_LIST} ${SRC_LIST_client})
TARGET_LINK_LIBRARIES(${NAME_PRJ_client}
	util
	)

set(NAME_PRJ_server_thread udp.server.thread )
ADD_EXECUTABLE(${NAME_PRJ_server_thread} ${INC_LIST} ${SRC_LIST_server_thd})
TARGET_LINK_LIBRARIES(${NAME_PRJ_server_thread}
	util
	)

IF(PLF_MAC)
	set(NAME_PRJ_server_kqueue udp.server.kqueue )
	ADD_EXECUTABLE(${NAME_PRJ_server_kqueue} ${INC_LIST} ${SRC_LIST_server_kqueue})
	TARGET_LINK_LIBRARIES(${NAME_PRJ_server_kqueue}
		util
		)
ENDIF()

IF(PLF_LINUX)
	set(NAME_PRJ_server_epoll udp.server.epoll )
	ADD_EXECUTABLE(${NAME_PRJ_server_epoll} ${INC_LIST} ${SRC_LIST_server_epoll})
	TARGET_LINK_LIBRARIES(${NAME_PRJ_server_epoll}
		util
		)
ENDIF()

