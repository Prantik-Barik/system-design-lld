#include <iostream>

using namespace std;

// Product Class and subclasses
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

class BasicWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Basic Wheat Burger with bun, patty, and ketchup!" << endl;
    }
};

class StandardWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Standard Wheat Burger with bun, patty, cheese, and lettuce!" << endl;
    }
};

class PremiumWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Wheat Burger with gourmet bun, premium patty, cheese, lettuce, and secret sauce!" << endl;
    }
};


// Factory and its concretions
class BurgerFactory {
public:
    virtual Burger* createBurger(string& type) = 0;
};

class SinghBurger : public BurgerFactory {
public:
    Burger* createBurger(string& type) override {
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

class KingBurger : public BurgerFactory {
public:
    Burger* createBurger(string& type) override {
        if (type == "basic") {
            return new BasicWheatBurger();
        } else if (type == "standard") {
            return new StandardWheatBurger();
        } else if (type == "premium") {
            return new PremiumWheatBurger();
        } else {
            cout << "Invalid burger type! " << endl;
            return nullptr;
        }
    }
};

int main() {
    string type = "premium";

    // KingBurger is a concrete factory class that creates wheat burgers.
    // BurgerFactory* myFactory = new KingBurger();
    // SinghBurger is a concrete factory class that creates non-wheat burgers.
    BurgerFactory* myFactory = new SinghBurger();

    Burger* burger = myFactory->createBurger(type);

    burger->prepare();

    return 0;
}

/* Factory Method Pattern is a creational design pattern that provides an interface for creating objects in a superclass, but allows subclasses to alter the type of objects that will be created.
In this example, the BurgerFactory class is an abstract factory class that creates burgers based on the type of burger requested.
The createBurger method is a method that creates a burger based on the type of burger requested.
The createBurger method returns a pointer to a Burger object.
The createBurger method creates a new BasicBurger, StandardBurger, or PremiumBurger object based on the type of burger requested.
The createBurger method returns a pointer to the new Burger object.
The createBurger method returns a nullptr if the type of burger requested is invalid.
*/


