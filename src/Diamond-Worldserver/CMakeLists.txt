
########### next target ###############

SET(diamond-worldserver_SRCS
CliRunnable.cpp
CliRunnable.h
Main.cpp
Master.cpp
Master.h
RASocket.cpp
RASocket.h
WorldRunnable.cpp
WorldRunnable.h
)

SET(diamond-worldserver_LINK_FLAGS "")

add_executable(diamond-worldserver ${diamond-worldserver_SRCS})
add_definitions(
-D_DIAMOND_CORE_CONFIG='"${CONF_DIR}/Diamond-Worldserver.conf"'
)
IF (DO_MYSQL)
    SET(diamond-worldserver_LINK_FLAGS "-pthread ${diamond-worldserver_LINK_FLAGS}")
ENDIF(DO_MYSQL)
IF (DO_POSTGRESQL)
    SET(diamond-worldserver_LINK_FLAGS "-pthread ${diamond-worldserver_LINK_FLAGS}")
ENDIF(DO_POSTGRESQL)


IF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    SET(trinity-core_LINK_FLAGS "-framework Carbon ${diamond-worldserver_LINK_FLAGS}")
    SET(SCRIPT_LIB "")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")

SET_TARGET_PROPERTIES(diamond-worldserver PROPERTIES LINK_FLAGS "${diamond-worldserver_LINK_FLAGS}")

if(DO_SCRIPTS)
    SET(SCRIPT_LIB "scripts")
else(DO_SCRIPTS)
    SET(SCRIPT_LIB "")
endif(DO_SCRIPTS)

target_link_libraries(
diamond-worldserver
game
shared
zlib
diamondframework
diamondsockets
diamonddatabase
diamondauth
diamondconfig
vmaps
g3dlite
${SCRIPT_LIB}
${READLINE_LIBRARY}
${TERMCAP_LIBRARY}
${MYSQL_LIBRARIES}
${POSTGRESQL_LIBRARIES}
${SSLLIB}
${ACE_LIBRARY}
${ZLIB} 
${OSX_LIBS}
)

install(TARGETS diamond-worldserver DESTINATION bin)


########### install files ###############

install(FILES  diamond-worldserver.conf.dist DESTINATION bin)

