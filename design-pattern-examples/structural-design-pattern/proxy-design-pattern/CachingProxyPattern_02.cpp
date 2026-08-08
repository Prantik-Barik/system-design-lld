/* Implement Rate Limiting Proxy
Problem: Build a rate limiting proxy for an API service. The proxy allows a maximum of 3 requests within any 10-second window. Requests beyond the limit are rejected.

Requirements:

Subject interface: ApiService with request(String endpoint) returning a String
RealSubject: RealApiService that returns "Response from [endpoint]"
Proxy: RateLimitingProxy that allows at most 3 requests per 10-second window, rejecting excess requests with "Rate limit exceeded" */

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

class ApiService {
public:
    virtual string request(const string& endpoint) = 0;
    virtual ~ApiService() {}
};

class RealApiService : public ApiService {
public:
    string request(const string& endpoint) override {
        return "Response from " + endpoint;
    }
};

class RateLimitingProxy : public ApiService {
    RealApiService *apiClient;
    int requestCount = 0;
    vector<chrono::steady_clock::time_point> timestamps;
    int MAX_REQUESTS;
    int TIME_WINDOW;

public:
    RateLimitingProxy() {
        this->apiClient = new RealApiService();
        this->MAX_REQUESTS = 3;
        this->TIME_WINDOW = 10;
    }

    string request(const string& endpoint) override {
       //start the clock
       chrono::steady_clock::time_point now = chrono::steady_clock::now();

       // Remove timestamps older than TIME_WINDOW seconds
       timestamps.erase(
        remove_if(timestamps.begin(), timestamps.end(),
            [now, this](chrono::steady_clock::time_point t) {
                int age = (int)chrono::duration_cast<chrono::seconds>(now - t).count();
                return age >= TIME_WINDOW;
            }),
        timestamps.end()
    );
       if ((int)timestamps.size() >= MAX_REQUESTS) {
            return "Rate limit exceeded. Try again later.";
        }

        timestamps.push_back(now);

        return apiClient->request(endpoint);

    }
};

int main() {
    ApiService *api = new RateLimitingProxy();
    cout << api->request("/users") << endl;
    cout << api->request("/orders") << endl;
    cout << api->request("/products") << endl;
    cout << api->request("/inventory") << endl; // Should be rejected

    cout << "\nWaiting 12 seconds for TTL to expire..." << endl;
    this_thread::sleep_for(chrono::seconds(12));
    cout << api->request("/orders") << endl;
    cout << api->request("/products") << endl;
    cout << api->request("/inventory") << endl;
    cout << api->request("/orders") << endl;
    cout << api->request("/products") << endl;
    cout << api->request("/inventory") << endl;
    return 0;
}