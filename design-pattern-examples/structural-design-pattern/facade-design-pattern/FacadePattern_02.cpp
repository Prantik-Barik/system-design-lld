/* Design Smart Home Controller
Problem: Implement a SmartHomeFacade that controls lights, thermostat, and a security system. 
Provide leaveHome() and arriveHome() methods that coordinate all three subsystems.

Requirements:

leaveHome() turns off lights, sets thermostat to eco mode (18C), arms security system
arriveHome() turns on lights, sets thermostat to comfort mode (22C), disarms security system
Each subsystem prints its actions to the console */

#include <iostream>
#include <string>
using namespace std;

// Subsystem: Controls smart lights in the house
class SmartLightsSystem {
public:
    void on() {
        cout<<"Lights: Turned on"<<endl;
    }

    void off() {
        cout<<"Lights: Turned off."<<endl;
    }
};

// Subsystem: Controls the thermostat temperature and mode
class Thermostat {
    string mode;
public:
    void setTemperature(int degrees) {
        cout<<"Thermostat: Mode set to "<< this->mode<<". Temperature set to "<<degrees<<"C."<<endl;
    }

    void setMode(const string& mode) {
        this->mode = mode;
    }
};

// Subsystem: Controls the home security system
class SecuritySystem {
public:
    void arm() {
        cout<<"Security: System armed."<<endl;
    }

    void disarm() {
        cout<<"Security: System disarmed."<<endl;
    }
};

// Facade: Provides simplified methods to control all smart home subsystems
class SmartHomeFacade {
    SmartLightsSystem& lights;
    Thermostat& thermostat;
    SecuritySystem& security;

public:
    SmartHomeFacade(SmartLightsSystem& lights, Thermostat& thermostat, SecuritySystem& security)
        : lights(lights), thermostat(thermostat), security(security)
    {

    }

    void leaveHome() {
        cout<< "--- Leaving Home ---"<<endl;
        // TODO: Turn off lights, set thermostat to eco mode (18C), arm security
        lights.off();
        thermostat.setMode("eco");
        thermostat.setTemperature(18);
        security.arm();
        cout<<"--- Home secured ---"<<endl;
    }

    void arriveHome() {
        cout<<"--- Arriving Home ---"<<endl;
        // TODO: Turn on lights, set thermostat to comfort mode (22C), disarm security
        lights.on();
        thermostat.setMode("comfort");
        thermostat.setTemperature(22);
        security.disarm();
        cout<<"--- Welcome home! ---"<<endl;
    }
};

int main() {
    SmartLightsSystem lights;
    Thermostat thermostat;
    SecuritySystem security;

    SmartHomeFacade home(lights, thermostat, security);
    home.leaveHome();
    cout << endl;
    home.arriveHome();
    return 0;
}