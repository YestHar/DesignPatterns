#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <stack>

class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

class Light {
public:
    void turnOn() {
        std::cout << "Light is ON" << std::endl;
    }
    void turnOff() {
        std::cout << "Light is OFF" << std::endl;
    }
};

class LightOnCommand : public Command {
private:
    Light& light;

public:
    explicit LightOnCommand(Light& light) : light(light) {}
    void execute() override {
        light.turnOn();
    }
    void undo() override {
        light.turnOff();
    }
};

class LightOffCommand : public Command {
private:
    Light& light;

public:
    explicit LightOffCommand(Light& light) : light(light) {}
    void execute() override {
        light.turnOff();
    }
    void undo() override {
        light.turnOn();
    }
};

class AirConditioner {
public:
    void setTemperature(int temp) {
        std::cout << "Air Conditioner set to " << temp << " degrees." << std::endl;
    }
    void resetTemperature() {
        std::cout << "Air Conditioner temperature reset." << std::endl;
    }
};

class SetACTemperatureCommand : public Command {
private:
    AirConditioner& ac;
    int temperature;
    int previousTemperature;

public:
    explicit SetACTemperatureCommand(AirConditioner& ac, int temp)
        : ac(ac), temperature(temp), previousTemperature(24) {} // Default temp
    void execute() override {
        previousTemperature = temperature;
        ac.setTemperature(temperature);
    }
    void undo() override {
        ac.resetTemperature();
    }
};

class RemoteControl {
private:
    std::stack<std::shared_ptr<Command>> commandHistory;

public:
    void pressButton(const std::shared_ptr<Command>& command) {
        command->execute();
        commandHistory.push(command);
    }
    void pressUndo() {
        if (!commandHistory.empty()) {
            auto command = commandHistory.top();
            command->undo();
            commandHistory.pop();
        } else {
            std::cout << "No commands to undo." << std::endl;
        }
    }
};

int main() {
    Light livingRoomLight;
    AirConditioner ac;

    auto lightOn = std::make_shared<LightOnCommand>(livingRoomLight);
    auto lightOff = std::make_shared<LightOffCommand>(livingRoomLight);
    auto setACTemp = std::make_shared<SetACTemperatureCommand>(ac, 22);

    RemoteControl remote;

    remote.pressButton(lightOn);
    remote.pressUndo();
    remote.pressButton(lightOff);

    remote.pressButton(setACTemp);
    remote.pressUndo();

    return 0;
}
