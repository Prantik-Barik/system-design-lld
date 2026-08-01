#include <iostream>

using namespace std;

// Product Burger Class and subclasses -> Product 1
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

// Product GarlicBread Class and subclasses -> Product 2
class GarlicBread {
public:
    virtual void prepare() = 0;  // Pure virtual function
    virtual ~GarlicBread() {}  // Virtual destructor
};

class ButterGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing Butter Garlic Bread with garlic butter!" << endl;
    }
};

class CheeseGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing Cheese Garlic Bread with garlic butter!" << endl;
    }
};


class ButterWheatGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing Butter Wheat Garlic Bread with garlic butter!" << endl;
    }
};

class CheeseWheatGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing Cheese Wheat Garlic Bread with garlic butter!" << endl;
    }
};  

// Abstract Factory Class and subclasses
class FoodFactory {
public:
    virtual Burger* createBurger(string& type) = 0;
    virtual GarlicBread* createGarlicBread(string& type) = 0;
};


class SinghFoodFactory : public FoodFactory {
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

    GarlicBread* createGarlicBread(string& type) override {
        if (type == "butter") {
            return new ButterGarlicBread();
        } else if (type == "cheese") {
            return new CheeseGarlicBread();
        } else {
            cout << "Invalid garlic bread type! " << endl;
            return nullptr;
        }
    }
};

// Sells Wheat Burgers and Garlic Bread
class KingFoodFactory : public FoodFactory {
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

    GarlicBread* createGarlicBread(string& type) override {
        if (type == "butter") {
            return new ButterWheatGarlicBread();
        } else if (type == "cheese") {
            return new CheeseWheatGarlicBread();
        } else {
            cout << "Invalid garlic bread type! " << endl;
            return nullptr;
        }
    }
};

int main() {
    string burgerType = "premium";
    string garlicBreadType = "cheese";

    FoodFactory* myFactory = new SinghFoodFactory();

    Burger* burger = myFactory->createBurger(burgerType);
    GarlicBread* garlicBread = myFactory->createGarlicBread(garlicBreadType);

    burger->prepare();
    garlicBread->prepare();
    cout << "Enjoy your meal!" << endl;
    return 0;
}


