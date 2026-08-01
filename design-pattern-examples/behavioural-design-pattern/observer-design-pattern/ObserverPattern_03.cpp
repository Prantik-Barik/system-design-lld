/*
Problem: Design a File Watcher System
 
Build a basic file watcher system using the Observer design pattern.
 
A FileWatcher subject monitors a file and notifies observers whenever the
file changes (e.g. content modified, size changed). Two observers respond
to each change:
 
- LoggerDisplay: prints the latest file name, event type (e.g. "MODIFIED",
  "CREATED", "DELETED"), and file size whenever a change occurs.
- ChangeStatsDisplay: tracks every file size seen across all change events
  and prints the average file size so far.
 
Requirements:
- A WeatherObserver-style interface (FileObserver) with a pure virtual
  update(FileWatcher* watcher) method.
- FileWatcher (the subject) holds fileName, fileSizeBytes, and eventType,
  along with a list of registered observers.
- registerObserver / removeObserver to manage the observer list.
- notifyChange(fileName, fileSizeBytes, eventType) updates the subject's
  state and notifies all observers.
- LoggerDisplay prints: "Logger -> File: X, Event: Y, Size: Z bytes"
- ChangeStatsDisplay prints: "Stats -> Files Watched: N, Avg Size: X bytes"
 
Fill in the TODOs below to complete the implementation.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>

using namespace std;

class FileWatcher;

//observer class
class FileObserver {
    public:
    virtual ~FileObserver() {};
    virtual void update(FileWatcher* watcher) = 0;
};

//subject class 
class FileWatcher {
    string fileName;
    long fileSizeBytes = 0;
    string eventType; // "CREATED", "MODIFIED", "DELETED"
    vector<FileObserver*> observers;

    public:
    void registerObserver(FileObserver* observer) {
        observers.push_back(observer);
        cout<<"Observer Subscribed!"<<endl;
    }
 
    void removeObserver(FileObserver* observer) {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
        cout<<"Observer un-subscribed!"<<endl;
    }
 
    void notifyChange(string fileName, long fileSizeBytes, string eventType) {
        this->fileName = fileName;
        this->fileSizeBytes = fileSizeBytes;
        this->eventType = eventType;
        notifyObservers();
    }
    string getFileName() {return this->fileName;}
    string getEventName() {return this->eventType;}
    long getFileSize () {return this->fileSizeBytes;} 

    private:
    void notifyObservers() {
        for(FileObserver* ob : observers){
            ob->update(this);
        }
    }
};

// observer concrete classes
class LoggerDisplay : public FileObserver {
    public:
    void update(FileWatcher *watcher) override {
        cout<< "Logger -> File: "<< watcher->getFileName()<<", Event: "<<watcher->getEventName()<<", Size: "<<watcher->getFileSize()<<" bytes"<<endl;
    }
};

class ChangeStatsDisplay : public FileObserver {
    vector<double> fileSize;
    public:
    void update(FileWatcher *watcher) override {
        fileSize.push_back(watcher->getFileSize());
        double averageFileSize = accumulate(fileSize.begin(), fileSize.end(), 0.0) / fileSize.size();
        cout<<"Stats -> Files Watched: "<<fileSize.size()<<", Avg Size: "<<averageFileSize<<" bytes"<<endl;
    }
};

int main() {
    FileWatcher watcher;
    LoggerDisplay logger;
    ChangeStatsDisplay stats;

    watcher.registerObserver(&logger);
    watcher.registerObserver(&stats);

    watcher.notifyChange("config.yaml", 1024, "CREATED");
    watcher.notifyChange("config.yaml", 2048, "MODIFIED");
    watcher.notifyChange("data.csv", 500000, "MODIFIED");
    watcher.removeObserver(&logger);
    watcher.notifyChange("data.csv", 480000, "DELETED");

    return 0;
}
