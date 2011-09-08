
#define private public
#define protected public
#include <cxxtest/TestSuite.h>

#include "DummyResource.hpp"

#include <SimpleGuard.hpp>


class TestScopeGuard : public CxxTest::TestSuite 
{
  public:
  void test_DummyResource( )
  {
    TS_TRACE( "===== test_DummyResource =====" );
    DummyResource resource;
    TS_ASSERT( !resource.isAllocated() );

    resource.allocate();
    TS_ASSERT( resource.isAllocated() );
  
    TS_ASSERT_THROWS( resource.use(), DummyException );

    resource.free();
    TS_ASSERT( !resource.isAllocated() );
    
    TS_TRACE( ">>>>> test_DummyResource <<<<< END." );
  }

  void test_SimpleGuard_Throw() {
    TS_TRACE( "===== test_SimpleGuard_Throw =====" );
    
    TS_TRACE( "create dummy resource" );
    DummyResource resource;
    
    // make sure its exits with an exception
    // a scopeguard will be created inside useResourceThrow function
    TS_TRACE( "allocate dummy resource" );
    resource.allocate();
    TS_ASSERT( resource.isAllocated() );

    TS_TRACE( "run use resource within a scope, protected by a SimpleGuard" );

    TS_ASSERT_THROWS(
      useResourceThrow( resource ),
      DummyException
    );

    TS_ASSERT( !resource.isAllocated() );
    
    TS_TRACE( ">>>>> test_SimpleGuard_Throw <<<<< END." );
  }
  
  void test_SimpleGuard_NoThrow() {
    TS_TRACE( "===== test_SimpleGuard_NoThrow =====" );
    
    TS_TRACE( "create dummy resource" );
    DummyResource resource;
    
    // make sure its exits with an exception
    // a scopeguard will be created inside useResourceThrow function
    TS_TRACE( "allocate dummy resource" );
    resource.allocate();
    TS_ASSERT( resource.isAllocated() );

    TS_TRACE( "run use resource within a scope, protected by a SimpleGuard" );

    TS_ASSERT_THROWS_NOTHING(
      useResourceNoThrow( resource )
    );

    TS_ASSERT( !resource.isAllocated() );
    
    TS_TRACE( ">>>>> test_SimpleGuard_NoThrow <<<<< END." );
  }

  protected:
  
  void useResourceThrow( DummyResource& resource ) {
    // create that simple guard
    SimpleGuard< DummyResource, void (DummyResource::*)() > guard(
        &resource,
        &DummyResource::free );

    resource.use(); // it will throw an exception

    // so its cannot be reached
    TS_ASSERT( false );
    resource.free();
    
    // dismiss guarding
    guard.dismiss();
  }

  void useResourceNoThrow( DummyResource& resource )
  {
    SimpleGuard< DummyResource, void (DummyResource::*)() > guard(
        &resource,
        &DummyResource::free );
    
    // blabla....no we using the resource, but no exception
    // ... still using
    // ... still using
    // done, and no exception!

    // it can be reached now
    resource.free();
    
    // dismiss guarding
    guard.dismiss();
    // NOTE: in that case we dont need freeing and dismiss,
    // since scopeguard will do the freeing
  }

};

