/* The TreeType interface defines the flyweight contract with a single render method that accepts extrinsic coordinates. 
ConcreteTreeType stores the heavy intrinsic data (name, color, texture) and implements rendering. 
The TreeTypeFactory maintains a cache of flyweights, creating new ones only when a species combination has not been seen before.

Each Tree object is lightweight, holding just a reference to its shared TreeType plus its own x and y position.
Finally, the Forest class ties everything together, using the factory to plant trees and delegating rendering to each tree. */

#include<iostream>
using namespace std;

// Flyweight - Stores INTRINSIC state only
class TreeFlyweight{
    private:
    // Intrinsic properties (shared among trees of same type)
    string name;
    string color;
    string texture;

    public:
    TreeFlyweight(string name, string col, string tex) {
        this->name = name;
        this->color = col;
        this->texture = tex;
    }

    void render(int posX, int posY) {
        cout << "Rendering " << name << " tree [color=" << color
             << ", texture=" << texture << "] at (" << posX << "," << posY << ")" << endl;
    }
};

// Flyweight Context - Stores EXTRINSIC state only
class TreeContext {
    private:
        TreeFlyweight* flyweight;
        int posX, posY;
    public:
        TreeContext(TreeFlyweight* tree, int x, int y){
            this->flyweight = tree;
            this->posX = x;
            this->posY = y;
        }

        void render() {
            flyweight->render(posX, posY);
        }
};

//Flyweight Factory
class TreeFactory {
    private:
    static unordered_map<string, TreeFlyweight*> flyweights;
    public:
    static TreeFlyweight* getTreeType(string name, string color, string texture) {
        string key = name + "_" + color + "_" + texture;

        if (flyweights.find(key) == flyweights.end()) {
            flyweights[key] = new TreeFlyweight(name, color, texture);
        }

        return flyweights[key];
    }
    static int getFlyweightCount() {
        return flyweights.size();
    }

    static void cleanup() {
        flyweights.clear();
    }
};

unordered_map<string, TreeFlyweight*> TreeFactory::flyweights;

//Client class
class Forest {
    private:
    vector<TreeContext*> trees;

    public:
        void plantTree(int x, int y, string name, string color, string texture) {
            //intrinsic props
            TreeFlyweight* flyweight = TreeFactory::getTreeType(name, color, texture);

            // actual memoised tree created at posX and posY
            trees.push_back(new TreeContext(flyweight, x, y));
        }

        void render() {
            for (int i = 0; i < (int)trees.size(); i++) {
                trees[i]->render();
            }

            cout << "\nTotal trees planted: " << trees.size() << endl;
            cout << "Unique tree types created: " << TreeFactory::getFlyweightCount() << endl;
        }
};

int main(){
    Forest* forest = new Forest();

    forest->plantTree(10, 20, "Oak", "dark green", "rough bark");
    forest->plantTree(50, 80, "Pine", "green", "needle texture");
    forest->plantTree(30, 60, "Oak", "dark green", "rough bark");
    forest->plantTree(70, 40, "Birch", "light green", "white bark");
    forest->plantTree(90, 10, "Pine", "green", "needle texture");

    //duplicate trees
    forest->plantTree(10, 20, "Oak", "dark green", "rough bark");
    forest->plantTree(50, 80, "Pine", "green", "needle texture");
    forest->plantTree(30, 60, "Oak", "dark green", "rough bark");
    forest->plantTree(70, 40, "Birch", "light green", "white bark");
    forest->plantTree(90, 10, "Pine", "green", "needle texture");

    forest->render();

    return 0;
}

/* Five trees in the forest, but only three TreeType flyweight objects in memory. The two Oak trees share one flyweight, and the two Pine trees share another. In a real game with 10,000 trees and 15 species, you would have 10,000 Tree objects (each holding just a reference and two coordinates) but only 15 ConcreteTreeType objects storing the heavy texture and color data.*/