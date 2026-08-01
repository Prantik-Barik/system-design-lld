/* Practice Problem: Order Processing System (State Design Pattern)
Build an order processing system where an Order moves through a workflow
of states, each with different rules for what actions are allowed.
In Placed state, the order can be paid for, or cancelled.
In Paid state, the order can be shipped, or cancelled before shipping.
In Shipped state, the order can be delivered. It can no longer be cancelled.
In Delivered state, the order is complete. No further actions are allowed.
In Cancelled state, the order was cancelled before shipping. No further actions are allowed. */

#include<iostream>
using namespace std;

class Order;

class OrderState {
    public:
        virtual ~OrderState() = default;
        virtual void pay(Order* order) = 0;
        virtual void ship(Order* order) = 0;
        virtual void deliver(Order* order) = 0;
        virtual void cancel(Order* order) = 0;
        
        virtual void refund(Order* order) = 0;
};

class PlacedOrderState: public OrderState {
    void pay(Order* order) override;
    void ship(Order* order) override {
        cout << "Cannot ship order in Placed state." << endl;
    }
    void deliver(Order* order) override {
        cout << "Cannot deliver order in Placed state." << endl;
    }
    void cancel(Order* order) override;
    void refund(Order* order) override {
        cout<<"Cannot refund money unitl paid and order is cancelled"<<endl;
    }
};

class PaidOrderState: public OrderState {
    void pay(Order* order) override{
        cout<<"Order is already paid"<<endl;
    }
    void ship(Order* order) override;
    void deliver(Order* order) override {
        cout << "Cannot deliver order in Paid state." << endl;
    }
    void cancel(Order* order) override;
    void refund(Order* order) override {
        cout<<"Cannot refund money unitl paid and order is cancelled"<<endl;
    }
};

class ShippedOrderState: public OrderState {
    void pay(Order* order) override {
        cout << "Cannot pay for order in Shipped state." << endl;
    }
    void ship(Order* order) override {
        cout << "Order is already shipped." << endl;
    }
    void deliver(Order* order) override;
    void cancel(Order* order) override {
        cout << "Cannot cancel order in Shipped state." << endl;
    }
    void refund(Order* order) override {
        cout<<"Cannot refund money unitl paid and order is cancelled"<<endl;
    }
};

class DeliveredOrderState: public OrderState {
    void pay(Order* order) override {
        cout << "Cannot pay for order in Delivered state." << endl;
    }
    void ship(Order* order) override {
        cout << "Cannot ship order in Delivered state." << endl;
    }
    void deliver(Order* order) override {
        cout << "Order is already delivered." << endl;
    }
    void cancel(Order* order) override {
        cout << "Cannot cancel order in Delivered state." << endl;
    }
    void refund(Order* order) override {
        cout << "Cannot refund order in Delivered state." << endl;
    }
};

class CancelledOrderState: public OrderState {
    void pay(Order* order) override {
        cout << "Cannot pay for order in Cancelled state." << endl;
    }
    void ship(Order* order) override {
        cout << "Cannot ship order in Cancelled state." << endl;
    }
    void deliver(Order* order) override {
        cout << "Cannot deliver order in Cancelled state." << endl;
    }
    void cancel(Order* order) override {
        cout << "Order is already cancelled." << endl;
    }
    void refund(Order* order) override;
};

class RefundedState : public OrderState {
    public:
        void pay(Order* order) override {
            cout << "Cannot pay for order in Refunded state." << endl;
        }
        void ship(Order* order) override {
            cout << "Cannot ship order in Refunded state." << endl;
        }
        void deliver(Order* order) override {
            cout << "Cannot deliver order in Refunded state." << endl;
        }
        void cancel(Order* order) override {
            cout << "Cannot cancel order in Refunded state." << endl;
        }
        void refund(Order* order) override {
            cout << "Order is already refunded." << endl;
        }
};

class Order {
    string orderId;
    OrderState* currentState;

    public:
        Order(string id){
            orderId = id;
            cout<<"Order Placed with id: "<<orderId<<endl;
            currentState = new PlacedOrderState();
        }

        ~Order(){
            delete currentState;
        }

        void setCurrentState(OrderState *updatedState) {
            delete currentState;
            currentState = updatedState;
        }
        OrderState* getCurrentState(){
            return currentState;
        }

        void pay() { currentState->pay(this); }
        void ship() { currentState->ship(this); }
        void deliver() { currentState->deliver(this); }
        void cancel() { currentState->cancel(this); }
        void refund() { currentState->refund(this); }
};

void PlacedOrderState :: pay(Order *order) {
    cout << "Order paid." << endl;
    order->setCurrentState(new PaidOrderState());
}

void PlacedOrderState::cancel(Order* order) {
    cout << "Order cancelled." << endl;
    order->setCurrentState(new CancelledOrderState());
}

void PaidOrderState::ship(Order* order) {
    cout << "Order shipped." << endl;
    order->setCurrentState(new ShippedOrderState());
}

void PaidOrderState::cancel(Order* order) {
    cout << "Order cancelled." << endl;
    order->setCurrentState(new CancelledOrderState());
}

void ShippedOrderState::deliver(Order* order) {
    cout << "Order delivered." << endl;
    order->setCurrentState(new DeliveredOrderState());
}

void CancelledOrderState::refund(Order* order) {
    cout << "Order refunded." << endl;
    order->setCurrentState(new RefundedState());
}

int main() {
    Order order("ORD-1001");

    order.refund();   // Cannot refund - not cancelled yet
    order.pay();      // Placed -> Paid
    order.cancel();   // Paid -> Cancelled
    order.refund();
    order.ship();     // Cannot ship - already cancelled
    order.refund();   // Cancelled -> Refunded
    order.refund();   // Already refunded
    order.pay();      // Cannot pay - already refunded
    return 0;
}