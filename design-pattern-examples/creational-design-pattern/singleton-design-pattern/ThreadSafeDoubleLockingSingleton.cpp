#include <iostream>
#include <mutex>

using namespace std;

class Singleton {
    private:
    static Singleton* instance;
    static mutex mtx;
    Singleton() {
        cout << "Singleton constructor" << endl;
    }   
    public:
    static Singleton* getInstance() {
        if (instance == nullptr) {  // First check (no locking)
            lock_guard<mutex> lock(mtx);  // Lock only if needed
            if (instance == nullptr) {  // Second check (after acquiring lock)
                instance = new Singleton();
                // this is a thread safe way to create the instance of the Singleton class
                // because the lock is only acquired if the instance is not already created
                // and the instance is created only once
                // this is a thread safe way to create the instance of the Singleton class
                // because the lock is only acquired if the instance is not already created
                // and the instance is created only once
                // this is a thread safe way to create the instance of the Singleton class
            }
        }
        return instance;
        // this is a thread safe way to create the instance of the Singleton class
    }

    void doSomething() {
        cout << "Singleton doSomething with object address " << this << endl;
    }
};

Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;

int main() {
    Singleton* singleton = Singleton::getInstance();
    singleton->doSomething();
    return 0;
}