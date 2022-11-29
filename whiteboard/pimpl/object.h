class ObjectImpl;

class Object {

  Object(int x);
  ~Object();
  void foo();

  private:
    ObjectImpl* pimpl_;  // Pointer to implementation
};