#include <iostream>
#include <memory>

class Transport {
public:
    virtual void deliver() const = 0;
    virtual ~Transport() = default;
};

class Truck : public Transport {
public:
    void deliver() const override {
        std::cout << "Delivering by truck" << std::endl;
    }
};

class Ship : public Transport {
public:
    void deliver() const override {
        std::cout << "Delivering by ship" << std::endl;
    }
};

class TransportFactory {
public:
    static std::unique_ptr<Transport> createTransport(const std::string& type) {
        if (type == "truck") {
            return std::make_unique<Truck>();
        } else if (type == "ship") {
            return std::make_unique<Ship>();
        }
        return nullptr;
    }
};

int main() {
    std::unique_ptr<Transport> transport = TransportFactory::createTransport("truck");
    if (transport) {
        transport->deliver();
    }

    transport = TransportFactory::createTransport("ship");
    if (transport) {
        transport->deliver();
    }

    return 0;
}
