#include <iostream>
#include <memory>

class MachineMode {
public:
    virtual void processAction() = 0;
    virtual ~MachineMode() = default;
};

class Device {
private:
    std::unique_ptr<MachineMode> mode_;

public:
    explicit Device(std::unique_ptr<MachineMode> initialMode) : mode_(std::move(initialMode)) {}

    void switchMode(std::unique_ptr<MachineMode> newMode) {
        mode_ = std::move(newMode);
    }

    void execute() {
        mode_->processAction();
    }
};

class StandbyMode : public MachineMode {
public:
    void processAction() override {
        std::cout << "Device is in standby. Ready for further instructions." << std::endl;
    }
};

class ProcessingMode : public MachineMode {
public:
    void processAction() override {
        std::cout << "Device is processing a task." << std::endl;
    }
};

class MaintenanceMode : public MachineMode {
public:
    void processAction() override {
        std::cout << "Device is undergoing maintenance." << std::endl;
    }
};

int main() {
    Device device(std::make_unique<StandbyMode>());

    device.execute();
    std::cout << "Switching to processing mode..." << std::endl;
    device.switchMode(std::make_unique<ProcessingMode>());
    device.execute();

    std::cout << "Switching back to standby..." << std::endl;
    device.switchMode(std::make_unique<StandbyMode>());
    device.execute();

    std::cout << "Switching to maintenance mode..." << std::endl;
    device.switchMode(std::make_unique<MaintenanceMode>());
    device.execute();

    return 0;
}
