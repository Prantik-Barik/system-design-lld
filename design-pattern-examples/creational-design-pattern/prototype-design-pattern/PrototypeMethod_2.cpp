#include <iostream>
#include <string>

using namespace std;

// abstract prototype class
class EnemyPrototype {
    public:
        virtual EnemyPrototype* clone() = 0;
        virtual ~EnemyPrototype() = default;
};

class Enemy : public EnemyPrototype {
    private:
       string type;
       int health;
       double speed;
       bool armored;
       string weapon;
    
    public:
       Enemy(string type, int health, double speed, bool armored, string weapon)
           : type(type), health(health), speed(speed), armored(armored), weapon(weapon) {
            // Dynamic tracing print so you can see it working in real-time
            cout << "[System Log]: Param Constructor triggered for " << this->type << "!" << endl;
           }

        Enemy(Enemy& other) {
            this->type = other.type;
            this->health = other.health;
            this->speed = other.speed;
            this->armored = other.armored;
            this->weapon = other.weapon;
            
            // Dynamic tracing print so you can see it working in real-time
            cout << "[System Log]: Copy Constructor triggered for " << this->type << "!" << endl;
        }
    
       Enemy* clone() override {
           return new Enemy(*this);
       }
    
       void setHealth(int health) {
           this->health = health;
       }
    
       void setWeapon(string weapon) {
            this->weapon = weapon;
       }

       void setArmourStatus(bool isArmed){
        this->armored = isArmed;
       }

       void printStats() {
           cout << type << " [Health: " << health 
                << ", Speed: " << speed 
                << ", Armored: " << (armored ? "true" : "false")
                << ", Weapon: " << weapon << "]" << endl;
       }
};

int main() {
    // 1. Create and STORE the basic template pointer on the heap
    Enemy* basicGoblin = new Enemy("Goblin", 50, 5.0, false, "Wooden Club");

    // 2. Clone it to create a variant
    Enemy* goblinElite = basicGoblin->clone();
    goblinElite->setHealth(100);
    goblinElite->setArmourStatus(true);
    goblinElite->setWeapon("Iron Sword");

    // 3. Print the initial state
    cout << "Original template: ";
    basicGoblin->printStats(); // Output: Health: 50
    cout << "Cloned & Modified: ";
    goblinElite->printStats(); // Output: Health: 100

    cout << "\n--- Modifying the basic template ---\n" << endl;

    // 4. Change the "basic things" on your stored template on the fly
    basicGoblin->setHealth(75); // Buffing all future basic goblins
    basicGoblin->setWeapon("Spiked Club");

    // 5. Clone it AGAIN after the modification
    Enemy* basicGoblinV2 = basicGoblin->clone();

    // Print the results to see the change
    cout << "Updated template: ";
    basicGoblin->printStats();   // Output: Health: 75, Weapon: Spiked Club
    cout << "New Clone inherits updates: ";
    basicGoblinV2->printStats(); // Output: Health: 75, Weapon: Spiked Club

    // 6. Clean up all pointers from memory
    delete goblinElite;
    delete basicGoblinV2;
    delete basicGoblin; // Don't forget to delete your stored template!

    return 0;
}
