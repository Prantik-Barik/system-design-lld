#include<iostream>

using namespace std;

class Light;
class Fan;
class Thermostat;

//Command abstract class
class Command {
    public:
        virtual ~Command() = default;
        virtual void execute() = 0;
        virtual void undo() = 0;
};

// reciever class
class Light {
    public:
        void on()  { 
            cout << "Light is ON" << endl; 
        }
        void off() { 
            cout << "Light is OFF" << endl;
        }
};

class Fan {
    public:
    void on()  { 
        cout << "Fan is ON" << endl; 
    }
    void off() { 
        cout << "Fan is OFF" << endl;
    }
};

class Thermostat {
    private:
        double temp = 20;
    public:
        double getTemperature() {
            return this->temp;
        }

        void setTemperature(double &temperature) {
            this->temp = temperature;
            cout << "Thermostat set to " << temp << "C" << endl;
        }
};

//Command concrete classes
class LightCommand : public Command {
    private:
        Light *light;
    public:
        LightCommand(Light *l){
            light = l;
        }
        void execute() override { 
            light->on(); 
        }
    
        void undo() override { 
            light->off(); 
        }

};

class FanCommand : public Command {
    private:
        Fan* fan;
    
    public:
        FanCommand(Fan* f) { 
            fan = f; 
        }
        void execute() override { 
            fan->on(); 
        }
        void undo() override { 
            fan->off(); 
        }
    };

class ThermoStatCommand: public Command {
    private:
        Thermostat* thermostat;
        double prevTemp;
        double newTemp;
    
    public:
        ThermoStatCommand(Thermostat* t, double temperature) { 
            thermostat = t; 
            prevTemp = 0.0;
            newTemp = temperature;
        }
        void execute() override { 
            prevTemp = thermostat->getTemperature();
            thermostat->setTemperature(this->newTemp); 
        }
        void undo() override {
            thermostat->setTemperature(prevTemp);
        }
};

class RemoteControl {
    private:
        stack<Command*> history;
    
    public:
        void executeCommand(Command* command) {
            command->execute();
            history.push(command);
        }
    
        void undoLast() {
            if (!history.empty()) {
                Command* lastCommand = history.top();
                history.pop();
                lastCommand->undo();
            } else {
                cout << "Nothing to undo." << endl;
            }
        }
};

int main() {
    Light light;
    Fan fan;
    Thermostat thermostat;

    LightCommand lightComm(&light);
    FanCommand fanComm(&fan);
    ThermoStatCommand setTemp(&thermostat, 25);

    RemoteControl remote;

    cout << "--- Executing Commands ---" << endl;
    remote.executeCommand(&lightComm);
    remote.executeCommand(&setTemp);
    remote.executeCommand(&fanComm);

    cout << "\n--- Undoing Commands ---" << endl;
    remote.undoLast();
    remote.undoLast();
    remote.undoLast();
    remote.undoLast();

    return 0;
}