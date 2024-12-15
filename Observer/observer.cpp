#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Observer {
public:
    virtual void update(float temperature, float humidity, float pressure) = 0;
    virtual ~Observer() = default;
};

class Subject {
public:
    virtual void addObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void removeObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() = default;
};

class WeatherData : public Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;
    float temperature{};
    float humidity{};
    float pressure{};

public:
    void addObserver(std::shared_ptr<Observer> observer) override {
        observers.push_back(observer);
    }

    void removeObserver(std::shared_ptr<Observer> observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers() override {
        for (const auto& observer : observers) {
            observer->update(temperature, humidity, pressure);
        }
    }

    void setMeasurements(float temp, float hum, float pres) {
        temperature = temp;
        humidity = hum;
        pressure = pres;
        notifyObservers();
    }
};

class PhoneDisplay : public Observer {
public:
    void update(float temperature, float humidity, float pressure) override {
        std::cout << "Phone Display: Temperature = " << temperature 
                  << ", Humidity = " << humidity 
                  << ", Pressure = " << pressure << std::endl;
    }
};

class TVDisplay : public Observer {
public:
    void update(float temperature, float humidity, float pressure) override {
        std::cout << "TV Display: Temperature = " << temperature 
                  << ", Humidity = " << humidity 
                  << ", Pressure = " << pressure << std::endl;
    }
};

class WebsiteDisplay : public Observer {
public:
    void update(float temperature, float humidity, float pressure) override {
        std::cout << "Website Display: Temperature = " << temperature 
                  << ", Humidity = " << humidity 
                  << ", Pressure = " << pressure << std::endl;
    }
};

int main() {
    auto weatherData = std::make_shared<WeatherData>();

    auto phoneDisplay = std::make_shared<PhoneDisplay>();
    auto tvDisplay = std::make_shared<TVDisplay>();
    auto websiteDisplay = std::make_shared<WebsiteDisplay>();

    weatherData->addObserver(phoneDisplay);
    weatherData->addObserver(tvDisplay);
    weatherData->addObserver(websiteDisplay);

    weatherData->setMeasurements(25.0f, 65.0f, 1013.0f);
    std::cout << "-------------------" << std::endl;

    weatherData->removeObserver(tvDisplay);
    weatherData->setMeasurements(28.0f, 70.0f, 1012.5f);

    return 0;
}
