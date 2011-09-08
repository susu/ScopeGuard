

/**
 *  This is a dummy resouce. With the destructor it shows its state
 *
 */


class DummyException
{
};



class DummyResource 
{
  public:
    DummyResource();
    virtual ~DummyResource();

    /**
     * simulates resource allocation
     */
    void allocate();
    
    /**
     * simulates resource using
     * this will throw an exception
     */
    void use();
    
    /**
     * simulates resource freeing
     */
    void free();

    bool isAllocated() const;
  private:
    bool m_allocated;
};


DummyResource::DummyResource() : m_allocated( false )
{

}

DummyResource::~DummyResource()
{
  if ( isAllocated() ) 
  {
    std::cout << "RESOURCE NOT FREED UP!" << std::endl;
  }
  else {
    std::cout << "Resource freed up normally." << std::endl;
  }
}

void
DummyResource::allocate() 
{
  if ( isAllocated() ) 
  {
    std::cout << "WARNING! Double allocation!" << std::endl;
  }
  m_allocated = true;
}

void
DummyResource::use() 
{
  throw DummyException( );
}


void 
DummyResource::free()
{
  if ( !isAllocated() )
  {
    std::cout << "WARNING! Freeing a not allocated resource!" << std::endl;
  }
  m_allocated = false;
}

bool
DummyResource::isAllocated() const
{
  return m_allocated;
}
