/*Design Restaurant Order System
Build a restaurant order system where a waiter (invoker) takes orders and can cancel them. 
A Kitchen receiver prepares and cancels dishes. PlaceOrderCommand tells the kitchen to prepare a dish, and CancelOrderCommand tells it to cancel. 
Both commands support undo.

Requirements:
Kitchen receiver with prepareDish(dish) and cancelDish(dish) methods
PlaceOrderCommand that calls prepareDish on execute and cancelDish on undo
CancelOrderCommand that calls cancelDish on execute and prepareDish on undo
Waiter invoker with takeOrder(command), submitOrders() (executes all queued commands), and undoLast() */

#include <iostream>
#include <string>
#include <stack>
using namespace std;

class OrderCommand {
public:
    virtual ~OrderCommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class Kitchen {
public:
    void prepareDish(const string& dish) {
        cout<< "Preparing: "<<"["<<dish<<"]"<<endl;
    }

    void cancelDish(const string& dish) {
        cout<< "Cancelling: "<<"["<<dish<<"]"<<endl;
    }
};

class PlaceOrderCommand : public OrderCommand {
    Kitchen *kitchen;
    string dish;
public:
    PlaceOrderCommand(Kitchen* kitchen, const string& dish) {
        this->kitchen = kitchen;
        this->dish = dish;
    }

    void execute() override {
        kitchen->prepareDish(dish);
    }

    void undo() override {
        kitchen->cancelDish(dish);
    }
};

class CancelOrderCommand : public OrderCommand {
    Kitchen *kitchen;
    string dish;
public:
    CancelOrderCommand(Kitchen* kitchen, const string& dish) {
        this->kitchen = kitchen;
        this->dish = dish;
    }

    void execute() override {
        kitchen->cancelDish(dish);
    }

    void undo() override {
        kitchen->prepareDish(dish);
    }
};

class Waiter {
    stack<OrderCommand*> pendingOrders;
public:
    void takeOrder(OrderCommand* command) {
        pendingOrders.push(command);
    }

    void submitOrders() {
        while(!pendingOrders.empty()){
            OrderCommand *command = pendingOrders.top();
            command->execute();
            pendingOrders.pop();
        }

        cout<<"[Waiter Says]: Order submitted to kitchen"<<endl;
    }

    void undoLast() {
        if (!pendingOrders.empty()) {
            OrderCommand* lastCommand = pendingOrders.top();
            pendingOrders.pop();
            lastCommand->undo();
        } else {
            cout << "Nothing to undo." << endl;
        }
    }
};

int main() {
    Kitchen kitchen;
    Waiter waiter;
    waiter.takeOrder(new PlaceOrderCommand(&kitchen, "Pasta"));
    waiter.takeOrder(new PlaceOrderCommand(&kitchen, "Salad"));
    waiter.submitOrders();
    waiter.takeOrder(new PlaceOrderCommand(&kitchen, "Chicken Chilli"));
    waiter.undoLast();
    waiter.submitOrders();
    waiter.undoLast();
    return 0;
}