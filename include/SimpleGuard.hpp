


/**
 * in its ctor got a ptr to an object, and member ptr.
 */

template< class T, class M  >
class SimpleGuard
{
  public:
    SimpleGuard( T* obj, M member );
    virtual ~SimpleGuard();

    void dismiss() {
      m_dismissed = true;
    }
  private:
    bool m_dismissed;

    T*   m_obj;
    M    m_member;
};


template< class T, class M >
SimpleGuard<T, M>::SimpleGuard( T* obj, M member )
    : m_dismissed( false ),
      m_obj( obj ),
      m_member( member )
{
}

template< class T, class M >
SimpleGuard<T, M>::~SimpleGuard()
{
  if ( !m_dismissed )
  {
    // member pointer deref
    (m_obj->*m_member)();
  }
}

