#include <iostream>
#include <vector>
using namespace std;

// Consider an actual class.
class Obj {
  static int i, j;

public:
  static void f() { cout << i++ << endl; }
  static void g() { cout << j++ << endl; }
};

// Static member definitions:
int Obj::i = 10;
int Obj::j = 12;

// Implement a container for the above class
class ObjContainer {
  vector<Obj*> a;

public:
  void add(Obj* obj) {
    a.push_back(obj);  // call vector's standard method.
  }
  friend class SmartPointer;
};

// implement smart pointer to access member of Obj class.
class SmartPointer {
  ObjContainer oc;
  int index;

public:
  explicit SmartPointer(ObjContainer& objc) {
    oc = objc;
    index = 0;
  }

  // Return value indicates end of list:
  bool operator++() { // Prefix version
    if(index >= oc.a.size()) return false;
    if(oc.a[++index] == nullptr) return false;
    return true;
  }

  bool operator++(int) { // Postfix version
    return operator++();
  }

  // overload operator->
  Obj* operator->() const {
    if(!oc.a[index]) {
      cout << "Zero value";
      return (Obj*)nullptr;
    }

    return oc.a[index];
  }
};

int main() {
  const int sz = 10;
  Obj o[sz];
  ObjContainer oc;

  for(auto & i : o) {
    oc.add(&i);
  }

  SmartPointer sp(oc); // Create an iterator
  do {
    sp->f(); // smart pointer call
    sp->g();
  } while(sp++);

  return 0;
}