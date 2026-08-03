/* To show the Decorator pattern in a completely different domain, let's build a coffee ordering system. 
The interface tracks both the cost and the description of a coffee order. Decorators add condiments, each with its own price. */

#include<iostream>
using namespace std;

class Coffee {
    public:
        virtual ~Coffee() = default;
        virtual double getCost() = 0;
        virtual string getDescription() = 0; 
};

class SimpleCoffee : public Coffee {
    public:
        SimpleCoffee() {}

        double getCost() override {
            return 100;
        }

        string getDescription() override {
            return "Simple coffee";
        }
};

class CoffeeDecorator : public Coffee {
    protected:
        Coffee *coffee;
    public:
        CoffeeDecorator(Coffee *c){
            this->coffee = c;
        }
};

class MilkArtDecorator : public CoffeeDecorator {
    public:
        MilkArtDecorator(Coffee *c) : CoffeeDecorator(c) {}

        double getCost() override {
            return coffee->getCost() + 50;
        }

        string getDescription() override {
            return coffee->getDescription() + " With Milk Art";
        }

};

class SugarDecorator : public CoffeeDecorator {
    public:
    SugarDecorator(Coffee *c) : CoffeeDecorator(c) {}

    double getCost() override {
        return coffee->getCost() + 5;
    }

    string getDescription() override {
        return coffee->getDescription() + " With Extra Sugar";
    }
};

class WhippedCreamDecorator : public CoffeeDecorator {
    public:
    WhippedCreamDecorator(Coffee *c) : CoffeeDecorator(c) {}

    double getCost() override {
        return coffee->getCost() + 40;
    }

    string getDescription() override {
        return coffee->getDescription() + " With Whipped Cream";
    }
};
int main(){
    SimpleCoffee simple;
    printf("Order 1: %s | Rs.%.2f\n",
        simple.getDescription().c_str(), simple.getCost());

    MilkArtDecorator milk(&simple);
    SugarDecorator milkSugar(&milk);
    printf("Order 2: %s | Rs.%.2f\n",
        milkSugar.getDescription().c_str(), milkSugar.getCost());

    SimpleCoffee simple2;
    MilkArtDecorator milk1(&simple2);
    MilkArtDecorator milk2(&milk1);
    SugarDecorator sugar(&milk2);
    WhippedCreamDecorator order3(&sugar);
    printf("Order 3: %s | Rs.%.2f\n",
        order3.getDescription().c_str(), order3.getCost());

    return 0;
}