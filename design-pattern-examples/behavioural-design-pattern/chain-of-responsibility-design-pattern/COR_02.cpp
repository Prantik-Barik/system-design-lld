/* ATM Cash Withdrawal System */

#include <iostream>
using namespace std;

class ATMHandlerInterface {
    public:
        virtual void setNext(ATMHandlerInterface* next) = 0;
        virtual void handleDispenseRequest(int amount) = 0;
        virtual ~ATMHandlerInterface() = default;
};

class BaseWithdrawalHandler : public ATMHandlerInterface {
    protected:
        ATMHandlerInterface* next;
    public:
        BaseWithdrawalHandler() {
            this->next = nullptr;
        }

        void setNext(ATMHandlerInterface* next) override {
            this->next = next;
        }

        void forward(int amount) {
            if (next != nullptr) {
                next->handleDispenseRequest(amount);
            }
            else {
                cout << "Remaining amount of " << amount << " cannot be fulfilled (Insufficient fund in ATM)" << endl;
            }
        }
};

class ThousandRupeesHandler : public BaseWithdrawalHandler {
    int numOfNotes = 0;
    public:
        ThousandRupeesHandler(int notesCount) {
            this->numOfNotes = notesCount;
        }

        void handleDispenseRequest(int amount) override {
            int notesNeeded = amount / 1000;
            if (notesNeeded > numOfNotes) {
                notesNeeded = numOfNotes;
                numOfNotes = 0;
            } else {
                numOfNotes -= notesNeeded;
            }

            if (notesNeeded > 0) {
                cout << "Dispensing " << notesNeeded << " x ₹1000 notes." << endl;
            }
            int remainingAmount = amount - (notesNeeded * 1000);
            if (remainingAmount > 0) {
                forward(remainingAmount);
            }
        }
};

class FiveHundredRupeesHandler : public BaseWithdrawalHandler {
    int numOfNotes = 0;
    public:
        FiveHundredRupeesHandler(int notesCount) {
            this->numOfNotes = notesCount;
        }

        void handleDispenseRequest(int amount) override {
            int notesNeeded = amount / 500;
            if (notesNeeded > numOfNotes) {
                notesNeeded = numOfNotes;
                numOfNotes = 0;
            } else {
                numOfNotes -= notesNeeded;
            }

            if (notesNeeded > 0) {
                cout << "Dispensing " << notesNeeded << " x ₹500 notes." << endl;
            }
            int remainingAmount = amount - (notesNeeded * 500);
            if (remainingAmount > 0) {
                forward(remainingAmount);
            }
        }
};

class TwoHundredRupeesHandler : public BaseWithdrawalHandler {
    int numOfNotes = 0;
    public:
        TwoHundredRupeesHandler(int notesCount) {
            this->numOfNotes = notesCount;
        }

        void handleDispenseRequest(int amount) override {
            int notesNeeded = amount / 200;
            if (notesNeeded > numOfNotes) {
                notesNeeded = numOfNotes;
                numOfNotes = 0;
            } else {
                numOfNotes -= notesNeeded;
            }
            if (notesNeeded > 0) {
                cout << "Dispensing " << notesNeeded << " x ₹200 notes." << endl;
            }
            int remainingAmount = amount - (notesNeeded * 200);
            if (remainingAmount > 0) {
                forward(remainingAmount);
            }
        }
};

class HundredRupeesHandler : public BaseWithdrawalHandler {
    int numOfNotes = 0;
    public:
        HundredRupeesHandler(int notesCount) {
            this->numOfNotes = notesCount;
        }

        void handleDispenseRequest(int amount) override {
            int notesNeeded = amount / 100;
            if (notesNeeded > numOfNotes) {
                notesNeeded = numOfNotes;
                numOfNotes = 0;
            } else {
                numOfNotes -= notesNeeded;
            }

            if (notesNeeded > 0) {
                cout << "Dispensing " << notesNeeded << " x ₹100 notes." << endl;
            }
            int remainingAmount = amount - (notesNeeded * 100);
            if (remainingAmount > 0) {
                forward(remainingAmount);
            }   
        }
};

class FiftyRupeesHandler : public BaseWithdrawalHandler {
    int numOfNotes = 0;
    public:
        FiftyRupeesHandler(int notesCount) {
            this->numOfNotes = notesCount;
        }

        void handleDispenseRequest(int amount) override {
            int notesNeeded = amount / 50;
            if (notesNeeded > numOfNotes) {
                notesNeeded = numOfNotes;
                numOfNotes = 0;
            } else {
                numOfNotes -= notesNeeded;
            }
            if (notesNeeded > 0) {
                cout << "Dispensing " << notesNeeded << " x ₹50 notes." << endl;
            }
            int remainingAmount = amount - (notesNeeded * 50);
            if (remainingAmount > 0) {
                forward(remainingAmount);
            }
    }
};

int main() {
    ATMHandlerInterface* thousandRupeesHandler = new ThousandRupeesHandler(10);
    ATMHandlerInterface* fiveHundredRupeesHandler = new FiveHundredRupeesHandler(18);
    ATMHandlerInterface* twoHundredRupeesHandler = new TwoHundredRupeesHandler(12);
    ATMHandlerInterface* hundredRupeesHandler = new HundredRupeesHandler(5);
    ATMHandlerInterface* fiftyRupeesHandler = new FiftyRupeesHandler(20);

    //COR formation
    thousandRupeesHandler->setNext(fiveHundredRupeesHandler);
    fiveHundredRupeesHandler->setNext(twoHundredRupeesHandler);
    twoHundredRupeesHandler->setNext(hundredRupeesHandler);
    hundredRupeesHandler->setNext(fiftyRupeesHandler);

    //Request for 3700
    thousandRupeesHandler->handleDispenseRequest(133700);

    //Clean up
    delete thousandRupeesHandler;
    delete fiveHundredRupeesHandler;
    delete twoHundredRupeesHandler;
    delete hundredRupeesHandler;
    delete fiftyRupeesHandler;

    return 0;
}