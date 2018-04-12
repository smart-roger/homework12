cmake_minimum_required(VERSION 3.2)

project(bulk_server VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
#project(bulk_server VERSION 0.0)

find_package(Boost COMPONENTS system thread REQUIRED)
SET(Boost_USE_STATIC_LIBS ON)
include_directories(
	include
)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

add_executable(bulk_server
					main.cpp
					src/TCommandStore.cpp
					src/TCommandProcessor.cpp 
					src/TBlockProcessor.cpp
					src/TConsole.cpp
					src/TObserver.cpp)

set_target_properties(bulk_server PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS -Wpedantic -Wall -Wextra

)

if(MINGW)
  target_link_libraries(bulk_server ws2_32 wsock32)
endif()

SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY})
TARGET_LINK_LIBRARIES(bulk_server ${USED_LIBS})

  

install(TARGETS bulk_server RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT __shurik@list.ru)

include(CPack)
