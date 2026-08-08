/* Protection Proxy: Performs permission checks before allowing access to certain operations. */

#include <cstddef>
#include<iostream>
using namespace std;

// User class with membership status
class User {
    public:
        string name;
        bool premiumMembership;
        
        User(string name, bool isPremium) {
            this->name = name;
            this->premiumMembership = isPremium;
        }

        bool isPremiumMember(){
            return premiumMembership;
        }
};

class DocumentReader {
    public:
        virtual ~DocumentReader() = default;
        virtual void unlockPDF(string filePath, string password) = 0;

};

class RealDocumentReader : public DocumentReader {
    public:
        RealDocumentReader(){
            cout<<"[RealDocumentReader] Reader created to read!\n";
        }
        void unlockPDF(string filePath, string password) override {
            cout << "[RealDocumentReader] Unlocking PDF at: " << filePath << "\n";
            cout << "[RealDocumentReader] PDF unlocked successfully with password: " << password << "\n";
            cout << "[RealDocumentReader] Displaying PDF content...\n";
        }
};

class SecureDocumentReaderProxy : public DocumentReader {
    User *user;
    RealDocumentReader *doc;
    public:
        SecureDocumentReaderProxy(User *user){
            this->user = user;
            this->doc = nullptr;
        }

        ~SecureDocumentReaderProxy() { delete doc; }

        void unlockPDF(string filePath, string password) override {
            if (!user->isPremiumMember()) {
                cout << "[DocumentProxy] Access denied. Only premium members can unlock PDFs.\n";
                return;
            }
            
            if(doc == nullptr)  doc = new RealDocumentReader();
            // Forwarding the request to the real reader
            doc->unlockPDF(filePath, password);
        }
};


int main(){
    User* user1 = new User("Rohan", false);  // Non Premium User
    User* user2 = new User("Rashmi", true);  // premium user

    cout << "== Rohan (Non-Premium) tries to unlock PDF ==\n";
    DocumentReader* docReader = new SecureDocumentReaderProxy(user1);
    docReader->unlockPDF("protected_document.pdf", "secret123");
    delete docReader;

    cout << "\n== Rashmi (Premium) unlocks PDF ==\n";
    docReader = new SecureDocumentReaderProxy(user2);
    docReader->unlockPDF("protected_document.pdf", "secret123");
    docReader->unlockPDF("protected_document_1.pdf", "secret123");
    delete docReader;

    return 0;
}