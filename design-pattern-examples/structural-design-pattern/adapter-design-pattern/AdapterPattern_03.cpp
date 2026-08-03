/*
Problem Statement:

Your application has a NotificationService that sends alerts to users through
a single unified interface, INotifier, which exposes a send(message) method.

However, the actual notification mechanisms already exist as legacy classes
with incompatible interfaces:

  - LegacyEmailClient exposes sendEmail(to, subject, body)
  - LegacySMSGateway exposes dispatchSMS(phoneNumber, text)

You cannot modify these legacy classes (assume they come from a third-party
library). Your job is to write Adapter classes that wrap each legacy class
and expose it through the INotifier interface, so NotificationService can
treat every channel uniformly.

Expected output:
    [Email] Sending to user@example.com | Subject: Alert | Body: Server CPU usage exceeded 90%
    [SMS] Dispatching to 9876543210 | Text: Server CPU usage exceeded 90%
*/

#include<iostream>
using namespace std;

class INotifier {
    public:
        virtual ~INotifier() = default;
        virtual void send(const string& message) = 0;
};

//legacy classes 
class LegacyEmailClient {
    public:
        void sendEmail(const string& to, const string& subject, const string& body){
            cout << "[Email] Sending to " << to << " | Subject: " << subject << " | Body: " << body << endl;
        };
};
    
class LegacySMSGateway {
    public:
        void dispatchSMS(const string& phoneNumber, const string& text){
            cout << "[SMS] Dispatching to " << phoneNumber << " | Text: " << text << endl;
        };
};

//Adapter
class EmailNotifierAdapter : public INotifier {
        
    LegacyEmailClient* client;
    string toAddress;
    string subject;
    public:
    EmailNotifierAdapter(LegacyEmailClient* client, const string& toAddress, const string& subject){
        this->client = client;
        this->toAddress = toAddress;
        this->subject = subject;
    };

    void send(const string& message) override {
        client->sendEmail(toAddress, subject, message);
    };
};

class SMSNotifierAdapter : public INotifier {
    private:
        LegacySMSGateway* gateway;
        string phoneNumber;
    
    public:
        SMSNotifierAdapter(LegacySMSGateway* gateway, const string& phoneNumber){
            this->gateway = gateway;
            this->phoneNumber = phoneNumber;
        };
    
        void send(const string& message) override{
            gateway->dispatchSMS(phoneNumber, message);
        };
};

int main(){
    LegacyEmailClient emailClient;
    LegacySMSGateway smsGateway;

    EmailNotifierAdapter emailAdapter(&emailClient, "user@example.com", "Alert");
    SMSNotifierAdapter smsAdapter(&smsGateway, "9876543210");

    emailAdapter.send("Hi!, migration to new architecture done, notify using send()");
    smsAdapter.send("Hi!, migration to new architecture done, notify using send()");
    return 0;
}