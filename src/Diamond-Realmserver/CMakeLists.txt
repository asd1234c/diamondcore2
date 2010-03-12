########### next target ###############

SET(diamond-realmserver_SRCS
AuthCodes.cpp
AuthCodes.h
AuthSocket.cpp
AuthSocket.h
Main.cpp
RealmList.cpp
RealmList.h
RealmSocket.h
RealmSocket.cpp
RealmAcceptor.h
)

SET(diamond-realmserver_LINK_FLAGS "")

add_executable(diamond-realmserver ${diamond-realmserver_SRCS})
add_definitions(
-D_DIAMOND_REALM_CONFIG='"${CONF_DIR}/Diamond-Realmserver.conf"'
)
IF (DO_MYSQL)
   SET(diamond-realmserver_LINK_FLAGS "-pthread ${diamond-realmserver_LINK_FLAGS}")
ENDIF(DO_MYSQL)
IF (DO_POSTGRESQL)
   SET(diamond-realmserver_LINK_FLAGS "-pthread ${diamond-realmserver_LINK_FLAGS}")
ENDIF(DO_POSTGRESQL)

IF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
   SET(diamond-realmserver_LINK_FLAGS "-framework Carbon ${diamond-realmserver_LINK_FLAGS}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")

SET_TARGET_PROPERTIES(diamond-realmserver PROPERTIES LINK_FLAGS "${diamond-realmserver_LINK_FLAGS}")

target_link_libraries(
diamond-realmserver
shared
diamondframework
diamondsockets
diamonddatabase
diamondauth
diamondconfig
zlib
${SSLLIB}
${MYSQL_LIBRARIES}
${POSTGRESQL_LIBRARIES}
${OSX_LIBS}
)

install(TARGETS diamond-realmserver DESTINATION bin)


########### install files ###############

install(FILES  diamond-realmserver.conf.dist DESTINATION bin)

