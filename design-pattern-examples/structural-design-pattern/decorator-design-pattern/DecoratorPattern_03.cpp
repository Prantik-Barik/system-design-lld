/* Design Pizza Topping System
Problem: Build a pizza ordering system where customers can add toppings to a base pizza. Each topping adds to the cost and description.

Requirements:
Component interface: Pizza with getCost() returning a double and getDescription() returning a String
ConcreteComponent: PlainPizza with a base cost of $5.00 and description "Plain pizza"
Decorators: CheeseDecorator (+$1.50), PepperoniDecorator (+$2.00), MushroomDecorator (+$1.00)
Each decorator appends its topping name to the description */

#include <iostream>
using namespace std;

class Pizza {
    public:
        virtual ~Pizza() = default;
        virtual double getCost() = 0;
        virtual string getDescription() = 0;
};

class PlainPizza  : public Pizza {
    public:
        double getCost() override {
            return 5.00;
        }

        string getDescription() override {
            return "Simple Pizza";
        }
};

class PizzaDecorator : public Pizza {
    protected:
        Pizza *pizza;
    public:
        PizzaDecorator(Pizza *p){
            this->pizza = p;
        }
};

class CheeseDecorator : public PizzaDecorator {
    public:
    CheeseDecorator(Pizza *p) : PizzaDecorator(p) {}

    double getCost() override {
        return pizza->getCost() + 1.50;
    }

    string getDescription() override {
        return pizza->getDescription() + " With Mozerella Cheese";
    }

};

class PepperoniDecorator : public PizzaDecorator{
    public:
    PepperoniDecorator(Pizza *p) : PizzaDecorator(p) {}

    double getCost() override {
        return pizza->getCost() + 2.00;
    }

    string getDescription() override {
        return pizza->getDescription() + " With Chicken Pepperoni";
    }
};

class MushroomDecorator : public PizzaDecorator {
    public:
    MushroomDecorator(Pizza *p) : PizzaDecorator(p) {}

    double getCost() override {
        return pizza->getCost() + 1.00;
    }

    string getDescription() override {
        return pizza->getDescription() + " With Mushroom Toppings";
    }
};


int main(){
    PlainPizza plain;
    printf("%s | $%.2f\n", plain.getDescription().c_str(), plain.getCost());

    PlainPizza p2;
    CheeseDecorator cheese(&p2);
    MushroomDecorator cheeseOlive(&cheese);
    printf("%s | $%.2f\n", cheeseOlive.getDescription().c_str(), cheeseOlive.getCost());

    PlainPizza p3;
    CheeseDecorator c3(&p3);
    MushroomDecorator o3(&c3);
    MushroomDecorator loaded(&o3);
    printf("%s | $%.2f\n", loaded.getDescription().c_str(), loaded.getCost());
    return 0;
}