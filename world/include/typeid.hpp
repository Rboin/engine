#ifndef TYPEID_HPP
#define TYPEID_HPP

template<class T>
class TypeId
{
public:

  template<class U>
  static const long get()
  {
    static const long newId { _current_id++ };
    return newId;
  }

  static const long get()
  {
    return _current_id;
  }
private:
  static long _current_id;
};

template<class T>
long TypeId<T>::_current_id = 0;

#endif // TYPEID_HPP
