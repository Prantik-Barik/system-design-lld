/* Request goes through various stages -
Authentication: Is the user properly authenticated via a token or session?
Authorization: Is the authenticated user allowed to perform this action?
Rate Limiting: Has the user exceeded their allowed number of requests?
Data Validation: Is the request payload well-formed and valid? */

#include <iostream>
using namespace std;

class Request {
    public:
        string username;
        string role;
        int requestCount;
        string payload;

        Request(string username, string role, int requestCount, string payload){
            this->username = username;
            this->role = role;
            this->requestCount = requestCount;
            this->payload = payload;
        }
};

class RequestHandlerInterface {
    public:
        virtual void setNext(RequestHandlerInterface* next) = 0;
        virtual void handle(Request request) = 0;
        virtual ~RequestHandlerInterface() {}
};

class BaseHandler : public RequestHandlerInterface {
    protected:
       RequestHandlerInterface* next;

    public:
       BaseHandler() {
        this->next = nullptr;
       }

       void setNext(RequestHandlerInterface* next) override {
           this->next = next;
       }

    protected:
       void forward(Request request) {
           if (next != nullptr) {
               next->handle(request);
           }
       }
};

class AuthHandler : public BaseHandler {
    public:
        void handle(Request request) override {
            if (request.username.empty()) {
                cout << "AuthHandler: User not authenticated." << endl;
                return;
            }
            cout << "AuthHandler: Authenticated." << endl;
            forward(request);
        }
};

class AuthorizationHandler : public BaseHandler {
    public:
        void handle(Request request) override {
            if (request.role != "ADMIN") {
                cout << "AuthorizationHandler: Access denied." << endl;
                return;
            }
            cout << "AuthorizationHandler: Authorized." << endl;
            forward(request);
        }
};

class RateLimitHandler : public BaseHandler {
    public:
        void handle(Request request) override {
            if (request.requestCount >= 100) {
                cout << "RateLimitHandler: Rate limit exceeded." << endl;
                return;
            }
            cout << "RateLimitHandler: Within rate limit." << endl;
            forward(request);
        }
};

class ValidationHandler : public BaseHandler {
    public:
        void handle(Request request) override {
            if (request.payload.empty()) {
                cout << "ValidationHandler: Invalid payload." << endl;
                return;
            }
            cout << "ValidationHandler: Payload valid." << endl;
            forward(request);
        }
};

class BusinessLogicHandler : public BaseHandler {
    public:
        void handle(Request request) override {
            cout << "BusinessLogicHandler: Processing request for " << request.username << "..." << endl;
        }
};

int main() {
    // Create handlers
    RequestHandlerInterface* auth = new AuthHandler();
    RequestHandlerInterface* authorization = new AuthorizationHandler();
    RequestHandlerInterface* rateLimit = new RateLimitHandler();
    RequestHandlerInterface* validation = new ValidationHandler();
    RequestHandlerInterface* businessLogic = new BusinessLogicHandler();

    // Build the chain
    auth->setNext(authorization);
    authorization->setNext(rateLimit);
    rateLimit->setNext(validation);
    validation->setNext(businessLogic);

    // Send a request through the chain
    Request request("john", "ADMIN", 10, "{ \"data\": \"valid\" }");
    auth->handle(request);

    cout << "\n--- Trying an invalid request ---" << endl;
    Request badRequest("", "USER", 150, "");
    auth->handle(badRequest);

    // Clean up
    delete auth;
    delete authorization;
    delete rateLimit;
    delete validation;
    delete businessLogic;

    return 0;
}