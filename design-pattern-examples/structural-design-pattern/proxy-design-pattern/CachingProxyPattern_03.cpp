#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
using namespace std;

class DatabaseService {
    public:
        virtual ~DatabaseService() = default;
        virtual string query(const string &sqlQuery) = 0;
};

class RealDBService : public DatabaseService {
    public:
    string query(const string& sql) override {
        cout << "RealDatabase: Executing query: " << sql << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        return "Result for [" + sql + "]";
    }
};

class CachingDatabaseProxy : public DatabaseService {
    private:
        RealDBService *db;
        unordered_map<string, string> responseCache;
    public:
    CachingDatabaseProxy() {
        db = new RealDBService();
    }

    ~CachingDatabaseProxy() {
        delete db;
    }
    string query(const string& sql) override {
        auto it = responseCache.find(sql);
        if (it != responseCache.end()) {
            cout << "CachingProxy: Cache HIT for: " << sql << endl;
            return it->second;
        }
        cout << "CachingProxy: Cache MISS for: " << sql << endl;
        string result = db->query(sql);
        responseCache[sql] = result;
        return result;
    }

    void clearCache() {
        cout << "CachingProxy: Cache cleared." << endl;
        responseCache.clear();
    }
};
int main(){
    CachingDatabaseProxy db;

    cout << "--- First query (cache miss) ---" << endl;
    cout << db.query("SELECT * FROM users") << endl;

    cout << "\n--- Same query again (cache hit) ---" << endl;
    cout << db.query("SELECT * FROM users") << endl;

    cout << "\n--- Different query (cache miss) ---" << endl;
    cout << db.query("SELECT * FROM orders WHERE status = 'pending'") << endl;

    cout << "\n--- Clear cache and retry ---" << endl;
    db.clearCache();
    cout << db.query("SELECT * FROM users") << endl;

    return 0;
}