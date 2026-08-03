/* Design Temperature Converter Adapter
Problem: You have a Thermometer interface that returns temperature in Celsius. 
A third-party weather sensor library provides readings in Fahrenheit through a different interface. 
Write an adapter so your application can use the Fahrenheit sensor as if it were a Celsius thermometer.

Requirements:

Target interface: Thermometer with getTemperature() returning Celsius (double)
Adaptee: FahrenheitSensor with readFahrenheit() returning Fahrenheit (double)
Adapter: converts Fahrenheit to Celsius using (F - 32) * 5/9 */

#include<iostream>
using namespace std;

class Thermometer {
    public:
        virtual double getTemperature(double temp) = 0;  // Returns Celsius
        virtual ~Thermometer() {}
};

class CelsiusSensor : public Thermometer {
    public:
        double getTemperature(double temperature) override { 
            cout<<"[Celsious Temperature]: "<<temperature<<" degC"<<endl; 
            return temperature;
        }
 };

 class FahrenheitSensor {
    public:
        double readFahrenheit(double temp) {
            double convertedToCelsius = (temp - 32) * 5/9;
            cout<<"Converted to Celsius: "<<convertedToCelsius<<endl;
            return convertedToCelsius;
        }
};

class FahrenheitSensorAdapter : public Thermometer {
    private:
        FahrenheitSensor *fSensor;
    public:
    FahrenheitSensorAdapter(FahrenheitSensor *sensor) {
        this->fSensor = sensor;
    }
    double getTemperature(double temperature) override { 

        cout<<"[Fahrenheit Temperature]: "<<temperature<<" degF"<<endl; 
        return fSensor->readFahrenheit(temperature);
    }
};


int main(){

    CelsiusSensor celsius;
    celsius.getTemperature(28);

    // TODO: Uncomment the lines below after implementing the adapter
    FahrenheitSensor sensor;
    FahrenheitSensorAdapter adapted(&sensor);
    printf("Fahrenheit sensor (adapted): %.1f C\n", adapted.getTemperature(97.6));
    
    return 0;
}