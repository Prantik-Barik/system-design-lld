#include <iostream>
#include <string>

using namespace std;

//abstract class 
class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual bool pay(double amount) = 0;
};

class CreditCardPayment : public PaymentStrategy {
private:
    string cardNumber;
    string expiryDate;
    string cvv;

public:
    CreditCardPayment(const string& card, const string& expiry, const string&cvvNumber)
        : cardNumber(card), expiryDate(expiry), cvv(cvvNumber) {}

    bool pay(double amount) override {
        cout << "Charging $" << amount << " to credit card ending in "
             << cardNumber.substr(cardNumber.length() - 4) << endl;
        return true;
    }
};

class PayPalPayment : public PaymentStrategy {
private:
    string email;

public:
    PayPalPayment(const string& e) : email(e) {}

    bool pay(double amount) override {
        cout << "Sending $" << amount << " via PayPal to " << email << endl;
        return true;
    }
};

class CryptoPayment : public PaymentStrategy {
private:
    string walletAddress;

public:
    CryptoPayment(const string& wallet) : walletAddress(wallet) {}

    bool pay(double amount) override {
        cout << "Transferring $" << amount << " in crypto to " << walletAddress << endl;
        return true;
    }
};

class CheckoutService {
private:
    PaymentStrategy* paymentStrategy;

public:
    CheckoutService(PaymentStrategy* strategy) : paymentStrategy(strategy) {}

    void setPaymentStrategy(PaymentStrategy* strategy) {
        paymentStrategy = strategy;
    }

    bool checkout(double amount) {
        return paymentStrategy->pay(amount);
    }
};

// Usage
int main() {
    CheckoutService* checkout = nullptr;
    PaymentStrategy* currentStrategy = nullptr;
    
    double totalAmount = 150.00;
    int choice = 0;

    cout << "--- Welcome to Checkout ---" << endl;
    cout << "Total Amount Due: $" << totalAmount << endl;
    cout << "Select Payment Method:\n1. Credit Card\n2. PayPal\n3. Crypto\n4. Cancel" << endl;
    cout << "Enter choice (1-4): ";
    cin >> choice;

    // Dynamically instantiate the selected strategy at runtime
    switch (choice) {
        case 1:
            currentStrategy = new CreditCardPayment("4111111111111111", "12/26", "1234");
            break;
        case 2:
            currentStrategy = new PayPalPayment("user@example.com");
            break;
        case 3:
            currentStrategy = new CryptoPayment("0xABC123...");
            break;
        case 4:
            cout << "Checkout cancelled." << endl;
            return 0;
        default:
            cout << "Invalid choice. Exiting." << endl;
            return 1;
    }

    // Initialize checkout with the dynamically selected strategy
    checkout = new CheckoutService(currentStrategy);
    checkout->checkout(totalAmount);

    // --- Dynamic Strategy Swap Demo ---
    // Simulating a scenario where a user changes their mind or the primary method fails
    char changeMind;
    cout << "\nWould you like to switch payment methods to Crypto for a 5% discount? (y/n): ";
    cin >> changeMind;

    if ((changeMind == 'y' || changeMind == 'Y') && choice != 3) {
        cout << "Switching payment strategy dynamically..." << endl;
        
        // Dynamically change strategy object ownership and update context
        currentStrategy = new CryptoPayment("0xABC123...");
        checkout->setPaymentStrategy(currentStrategy);
        
        // Execute checkout with the updated runtime strategy
        checkout->checkout(totalAmount * 0.95); 
    }

    delete checkout;
    return 0;
}
