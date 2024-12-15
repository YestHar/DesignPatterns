#include <iostream>
#include <string>

class Lights {
public:
    void turnOn() {
        std::cout << "Lights are turned ON." << std::endl;
    }

    void turnOff() {
        std::cout << "Lights are turned OFF." << std::endl;
    }
};

class AirConditioning {
public:
    void setTemperature(int temp) {
        std::cout << "Air conditioning set to " << temp << " degrees." << std::endl;
    }

    void turnOn() {
        std::cout << "Air conditioning is ON." << std::endl;
    }

    void turnOff() {
        std::cout << "Air conditioning is OFF." << std::endl;
    }
};

class EntertainmentSystem {
public:
    void playMusic(const std::string& song) {
        std::cout << "Playing music: " << song << std::endl;
    }

    void turnOn() {
        std::cout << "Entertainment system is ON." << std::endl;
    }

    void turnOff() {
        std::cout << "Entertainment system is OFF." << std::endl;
    }
};

class HomeAutomationFacade {
private:
    Lights lights;
    AirConditioning airConditioning;
    EntertainmentSystem entertainment;

public:
    void activateMorningMode() {
        std::cout << "\nActivating Morning Mode:" << std::endl;
        lights.turnOn();
        airConditioning.setTemperature(22);
        entertainment.playMusic("Morning Playlist");
    }

    void activateNightMode() {
        std::cout << "\nActivating Night Mode:" << std::endl;
        lights.turnOff();
        airConditioning.setTemperature(18);
        entertainment.turnOff();
    }

    void turnEverythingOff() {
        std::cout << "\nTurning Everything Off:" << std::endl;
        lights.turnOff();
        airConditioning.turnOff();
        entertainment.turnOff();
    }
};

int main() {
    HomeAutomationFacade homeController;

    homeController.activateMorningMode();
    homeController.activateNightMode();
    homeController.turnEverythingOff();

    return 0;
}
