/* Design Weather Station
Build a basic weather station system. A WeatherStation subject broadcasts temperature, humidity, and pressure readings. 
Two observers respond to each update: CurrentConditionsDisplay shows the latest reading, and StatisticsDisplay tracks 
and displays the average temperature across all readings received so far.

Requirements:
Subject interface with register, remove, notify
WeatherStation with setMeasurements(temp, humidity, pressure) that notifies observers
CurrentConditionsDisplay prints the latest temperature, humidity, and pressure
StatisticsDisplay tracks all temperature readings and prints the average temperature */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>

using namespace std;

class WeatherStation;

//observer class
class WeatherObserver {
    public:
    virtual ~WeatherObserver() {}
    virtual void update(WeatherStation* station) = 0;
};

// subject class
class WeatherStation {
    double temperature = 0;
    double humidity = 0;
    double pressure = 0;
    vector<WeatherObserver*> observers;

    public:
    void registerObserver(WeatherObserver* observer) {
        observers.push_back(observer);
    }

    void removeObserver(WeatherObserver* observer) {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void setMeasurements(double temp, double h, double p){
        this->temperature = temp;
        this->humidity = h;
        this->pressure = p;
        notifyObserver();
    }

    double getTemperature() const { return temperature; }
    double getHumidity() const { return humidity; }
    double getPressure() const { return pressure; }

    private:
    void notifyObserver() {
        for(WeatherObserver* observer : observers) {
            observer->update(this);
        }
    }
};

//concrete observer
class CurrentConditionsDisplay : public WeatherObserver {
    public:
        void update(WeatherStation* station) override {
            cout<<"Current conditions are:"<<endl;
            cout<<"Temperature:"<<station->getTemperature()<<endl;
            cout<<"Humitdity:"<<station->getHumidity()<<endl;
            cout<<"Pressure:"<<station->getPressure()<<endl<<endl;
        }
};
    
 class StatisticsDisplay : public WeatherObserver {
        vector<double> readings;
    
    public:
    void update(WeatherStation* station) override {
        readings.push_back(station->getTemperature());
        cout<<"Readings: ";
        for(auto read: readings){cout<<read<<" ";}
        cout<<endl;
        double avg = accumulate(readings.begin(), readings.end(), 0.0) / readings.size();
        printf("Statistics -> Avg Temperature: %.2f\n", avg);
    }
};

int main()
{
    WeatherStation station;
    CurrentConditionsDisplay crntDisplay;
    StatisticsDisplay statDisplay;

    station.registerObserver(&crntDisplay);
    station.registerObserver(&statDisplay);

    station.setMeasurements(25.0, 65.0, 1013.0);
    station.setMeasurements(28.0, 70.0, 1012.0);
    station.setMeasurements(22.0, 90.0, 1011.0);
    return 0;
}