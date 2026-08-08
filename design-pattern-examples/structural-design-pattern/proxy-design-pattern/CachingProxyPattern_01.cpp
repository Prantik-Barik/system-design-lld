/* Caching Proxy: Defers the expensive network call until the API response is actually
   needed, then caches the response and reuses it until the TTL (time-to-live) expires. */
   #include<iostream>
   #include <string>
   #include <chrono>
   #include <thread>
   using namespace std;
   
   //abstract class
   class ApiClient {
       public:
           virtual ~ApiClient() = default;
           virtual string fetch() = 0;
           virtual string getEndpoint() = 0;
   };
   
   class RealApiClient : public ApiClient {
       string endpoint;
       public:
           RealApiClient(string url) {
               this->endpoint = url;
           }
   
           string fetch() override {
               // Performs Heavy Operation -
               cout << "[Network] Calling REST API: GET " << endpoint << "\n";
               return "{\"status\":200,\"data\":\"response for " + endpoint + "\"}";
           }
   
           string getEndpoint() override {
               return endpoint;
           }
   };
   
   // Proxy for caching with TTL - reuses cached response until it expires, then refetches
   class CachingApiProxy : public ApiClient {
       string endpoint;
       RealApiClient *apiClient;
       string cachedResponse;
       chrono::steady_clock::time_point cachedAt;
       int ttlSeconds;
       bool hasCachedResponse;
   
       public:
           CachingApiProxy(string url, int ttlSeconds) {
               this->endpoint = url;
               this->ttlSeconds = ttlSeconds;
   
               //assign null until fetch is called, as hitting the network is a heavy operation.
               this->apiClient = nullptr;
               this->hasCachedResponse = false;
   
               cout << "CachingApiProxy: Created for " << endpoint << ". API not called yet." << endl;
           }
   
           ~CachingApiProxy() {
               delete apiClient;
           }
   
           string getEndpoint() override {
               return endpoint;
           }
   
           bool isCacheExpired() {
               int elapsed = (int)chrono::duration_cast<chrono::seconds>(
                   chrono::steady_clock::now() - cachedAt
               ).count();
               return elapsed >= ttlSeconds;
           }
   
           string fetch() override {
               if (apiClient == nullptr) {
                   cout << "CachingApiProxy: fetch() requested for " << endpoint
                        << ". No client yet, creating one..." << endl;
                   apiClient = new RealApiClient(endpoint);
               }
   
               if (!hasCachedResponse || isCacheExpired()) {
                   cout << "CachingApiProxy: Cache miss/expired for " << endpoint << ". Calling API..." << endl;
                   cachedResponse = apiClient->fetch();
                   cachedAt = chrono::steady_clock::now();
                   hasCachedResponse = true;
               } else {
                   cout << "CachingApiProxy: Using cached response for " << endpoint << " (TTL not expired)" << endl;
               }
   
               return cachedResponse;
           }
   };
   
   int main(){
       cout << "Application Started. Initializing API proxies with TTL=2s..." << endl;
   
       ApiClient* endpoint1 = new CachingApiProxy("/api/users/42", 2);
       ApiClient* endpoint2 = new CachingApiProxy("/api/weather?city=Jamshedpur", 2);
   
       cout << "\nProxies initialized. No API calls made yet." << endl;
       cout << "Endpoint 1: " << endpoint1->getEndpoint() << endl;
   
       cout << "\nUser requests: " << endpoint1->getEndpoint() << endl;
       cout << "Response: " << endpoint1->fetch() << endl;
   
       cout << "\nUser requests the same endpoint again immediately." << endl;
       cout << "Response: " << endpoint1->fetch() << endl;
   
       cout << "\nWaiting 3 seconds for TTL to expire..." << endl;
       this_thread::sleep_for(chrono::seconds(3));
   
       cout << "\nUser requests the same endpoint again after TTL expiry." << endl;
       cout << "Response: " << endpoint1->fetch() << endl;
   
       cout << "\nUser requests: " << endpoint2->getEndpoint() << endl;
       cout << "Response: " << endpoint2->fetch() << endl;
   
       cout << "\nApplication finished. Note: endpoint2 was only called once, on first request." << endl;
   
       delete endpoint1;
       delete endpoint2;
       return 0;
   }