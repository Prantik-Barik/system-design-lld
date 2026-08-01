#include <iostream>

using namespace std;

class Singleton {
    private:
    static Singleton* instance;
    Singleton() {
        cout << "Singleton constructor" << endl;
    }   
    public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton(); // only one instance is created -> lazy initialization, but not thread safe creation of instance
        }
        return instance;
    }

    void doSomething() {
        cout << "Singleton doSomething with object address " << this << endl;
    }
};

Singleton* Singleton::instance = nullptr;

//Singleton* Singleton::instance = new Singleton(); 
// eager initialization, but not thread safe creation of instance, but very inefficient for bloated classes 


int main() {
    Singleton* singleton = Singleton::getInstance();
    singleton->doSomething();
    return 0;
}