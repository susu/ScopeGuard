cmake_minimum_required( VERSION 2.8 )

project( ScopeGuard )

find_package( CxxTest )

if ( CXXTEST_FOUND )
  include_directories( ${CXXTEST_INCLUDE_DIR} )
  enable_testing ()
  #CXXTEST_ADD_TEST( dummyTest cxxtest.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/DummyTest.hpp )
  CXXTEST_ADD_TEST( scopeGuard cxxtest.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/ScopeGuard.hpp )
endif ()

include_directories( "include" )
include_directories( "test" )


