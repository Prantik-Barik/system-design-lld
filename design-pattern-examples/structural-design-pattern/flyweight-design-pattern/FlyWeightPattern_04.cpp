/*Implement Browser Tab Icon Cache
Problem: A web browser keeps many tabs open, and each tab shows a favicon (site icon).
Loading and decoding the same icon image data for every tab wastes memory, especially
when dozens of tabs point to the same site (e.g. 20 Gmail tabs). Build an icon cache
where identical favicons share one underlying IconFlyweight object. Each IconFlyweight
stores the site domain, the image file path, and the pixel dimensions (width, height).
The tab position (tabIndex) and the current page title are extrinsic state that vary
per tab even when the favicon is identical.

Requirements:

Flyweight: IconFlyweight storing domain (String), imagePath (String), width (int), height (int)
Factory: IconFactory with getIcon(domain, imagePath, width, height) and getIconCount()
Context: BrowserTab storing the shared IconFlyweight plus tabIndex and pageTitle
Client code opens multiple tabs sharing icons, then renders the tab bar */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

// Flyweight - Stores INTRINSIC state only
class IconFlyweight {
private:
    // Intrinsic properties (shared among tabs pointing to the same favicon)
    string domain;
    string imagePath;
    int width;
    int height;

public:
    IconFlyweight(string dom, string path, int w, int h) {
        this->domain = dom;
        this->imagePath = path;
        this->width = w;
        this->height = h;
    }

    void render(int tabIndex, string pageTitle) {
        cout << "Tab " << tabIndex << ": [" << domain << " icon "
             << width << "x" << height << " from " << imagePath
             << "] " << pageTitle << endl;
    }
};

// Flyweight Factory
class IconFactory {
private:
    static unordered_map<string, IconFlyweight*> flyweights;

public:
    static IconFlyweight* getIcon(string domain, string imagePath, int width, int height) {

        string key = domain + "_" + imagePath + "_" +
                    to_string(width) + "_" + to_string(height);

        if (flyweights.find(key) == flyweights.end()) {
            flyweights[key] = new IconFlyweight(domain, imagePath, width, height);
        }

        return flyweights[key];
    }

    static int getIconCount() {
        return flyweights.size();
    }

    static void cleanup() {
        flyweights.clear();
    }
};

// Static member definition
unordered_map<string, IconFlyweight*> IconFactory::flyweights;


// Context - Stores EXTRINSIC state only
class BrowserTabContext {
private:
    IconFlyweight* icon;
    int tabIndex;
    string pageTitle;

public:
    BrowserTabContext(IconFlyweight* icon, int tabIndex, string pageTitle) {
        this->icon = icon;
        this->tabIndex = tabIndex;
        this->pageTitle = pageTitle;
    }

    void render() {
        icon->render(tabIndex, pageTitle);
    }
};

class Browser {
private:
    vector<BrowserTabContext*> tabs;

public:
    void openTab(string pageTitle, string domain, string imagePath, int width, int height) {

        IconFlyweight* icon = IconFactory::getIcon(domain, imagePath, width, height);

        int tabIndex = tabs.size() + 1;
        tabs.push_back(new BrowserTabContext(icon, tabIndex, pageTitle));
    }

    void render() {
        for (int i = 0; i < (int)tabs.size(); i++) {
            tabs[i]->render();
        }

        cout << "\nTotal tabs open: " << tabs.size() << endl;
        cout << "Unique icons cached: " << IconFactory::getIconCount() << endl;
    }
};

int main() {
    Browser* browser = new Browser();

    browser->openTab("Inbox (12)", "gmail.com", "/icons/gmail.png", 16, 16);
    browser->openTab("Drafts", "gmail.com", "/icons/gmail.png", 16, 16);
    browser->openTab("Sent Mail", "gmail.com", "/icons/gmail.png", 16, 16);

    browser->openTab("anthropic/claude", "github.com", "/icons/github.png", 16, 16);
    browser->openTab("pull requests", "github.com", "/icons/github.png", 16, 16);

    browser->openTab("Search results", "google.com", "/icons/google.png", 16, 16);


    browser->openTab("anthropic/claude", "github.com", "/icons/github.png", 16, 16);
    browser->openTab("pull requests", "github.com", "/icons/github.png", 16, 16);

    browser->openTab("Search results", "google.com", "/icons/google_new.png", 16, 16);

    browser->render();

    return 0;
}