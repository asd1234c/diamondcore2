
########### next target ###############

SET(diamondconfig_STAT_SRCS
   dotconfpp/dotconfpp.cpp
   dotconfpp/dotconfpp.h
   dotconfpp/mempool.cpp
   dotconfpp/mempool.h
   Config.cpp
   Config.h
   ConfigEnv.h
)

add_library(diamondconfig STATIC ${diamondconfig_STAT_SRCS})

