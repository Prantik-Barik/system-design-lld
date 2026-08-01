#include <iostream>
#include <string>
using namespace std;

class Car {
private:
    string engine;
    int wheels;
    int seats;
    string color;
    bool sunroof;
    bool navigationSystem;

public:
    class CarBuilder;

private:
    // Private constructor: Car can only be created using CarBuilder
    Car(const CarBuilder& builder);

public:
    string getEngine() const {
        return engine;
    }

    int getWheels() const {
        return wheels;
    }

    int getSeats() const {
        return seats;
    }

    string getColor() const {
        return color;
    }

    bool hasSunroof() const {
        return sunroof;
    }

    bool hasNavigationSystem() const {
        return navigationSystem;
    }

    void display() const {
        cout << "Car [engine=" << engine
             << ", wheels=" << wheels
             << ", seats=" << seats
             << ", color=" << color
             << ", sunroof=" << (sunroof ? "true" : "false")
             << ", navigationSystem=" << (navigationSystem ? "true" : "false")
             << "]" << endl;
    }

    // Nested Builder class
    class CarBuilder {
    private:
        string engine;
        int wheels = 4;
        int seats = 5;
        string color = "Black";
        bool sunroof = false;
        bool navigationSystem = false;

        friend class Car;

    public:
        CarBuilder& setEngine(const string& engine) {
            this->engine = engine;
            return *this;
        }

        CarBuilder& setWheels(int wheels) {
            this->wheels = wheels;
            return *this;
        }

        CarBuilder& setSeats(int seats) {
            this->seats = seats;
            return *this;
        }

        CarBuilder& setColor(const string& color) {
            this->color = color;
            return *this;
        }

        CarBuilder& setSunroof(bool sunroof) {
            this->sunroof = sunroof;
            return *this;
        }

        CarBuilder& setNavigationSystem(bool navigationSystem) {
            this->navigationSystem = navigationSystem;
            return *this;
        }

        Car build() const {
            return Car(*this);
        }
    };
};

// Constructor definition
Car::Car(const CarBuilder& builder) {
    engine = builder.engine;
    wheels = builder.wheels;
    seats = builder.seats;
    color = builder.color;
    sunroof = builder.sunroof;
    navigationSystem = builder.navigationSystem;
}

// Client code
int main() {
    Car car1 = Car::CarBuilder()
                   .setEngine("V8")
                   .setColor("Red")
                   .setSeats(5)
                   .setSunroof(true)
                   .build();

    car1.display();

    Car car2 = Car::CarBuilder()
                   .setEngine("V6")
                   .setColor("Blue")
                   .setSeats(4)
                   .build();

    car2.display();

    return 0;
}