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
        lock_guard<mutex> lock(mtx);
        if (instance == nullptr) {
            instance = new Singleton(); // only one instance is created -> lazy initialization, but thread safe creation of instance
            // this is thread safe, because the mutex locks the creation of the instance
            // so only one thread can create the instance at a time
            // this is a thread safe way to create the instance of the Singleton class
            // but it is not efficient, because we need to lock and unlock the mutex for every call to the getInstance method (expensive call of lock and unlock)
        }
        return instance;
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