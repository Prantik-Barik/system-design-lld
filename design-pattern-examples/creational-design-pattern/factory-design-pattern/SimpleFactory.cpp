#include <iostream>

using namespace std;

class Burger {
public:
    virtual void prepare() = 0;  // Pure virtual function
    virtual ~Burger() {}  // Virtual destructor
};

class BasicBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Basic Burger with bun, patty, and ketchup!" << endl;
    }
};

class StandardBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Standard Burger with bun, patty, cheese, and lettuce!" << endl;
    }
};

class PremiumBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Burger with gourmet bun, premium patty, cheese, lettuce, and secret sauce!" << endl;
    }
};

class BurgerFactory {
public:
    Burger* createBurger(string& type) {
        if (type == "basic") {
            return new BasicBurger();
        } else if (type == "standard") {
            return new StandardBurger();
        } else if (type == "premium") {
            return new PremiumBurger();
        } else {
            cout << "Invalid burger type! " << endl;
            return nullptr;
        }
    }
};

int main() {
    string type = "standard";

    BurgerFactory* myBurgerFactory = new BurgerFactory(); //BurgerFactory is a simple factory class that creates burgers based on the type of burger requested.

    // createBurger is a method that creates a burger based on the type of burger requested.
    Burger* burger = myBurgerFactory->createBurger(type); 

    burger->prepare();

    return 0;
}

/* Simple Factory Pattern is a creational design pattern that provides an interface for creating objects in a superclass, but allows subclasses to alter the type of objects that will be created.
In this example, the BurgerFactory class is a simple factory class that creates burgers based on the type of burger requested.
The createBurger method is a method that creates a burger based on the type of burger requested.
The createBurger method returns a pointer to a Burger object.
The createBurger method creates a new BasicBurger, StandardBurger, or PremiumBurger object based on the type of burger requested.
The createBurger method returns a pointer to the new Burger object.
The createBurger method returns a nullptr if the type of burger requested is invalid.
*/

