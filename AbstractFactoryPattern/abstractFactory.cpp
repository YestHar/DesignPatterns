#include <iostream>
#include <memory>

class Chair {
public:
    virtual void sitOn() const = 0;
    virtual ~Chair() = default;
};

class Sofa {
public:
    virtual void lieOn() const = 0;
    virtual ~Sofa() = default;
};

class CoffeeTable {
public:
    virtual void placeItems() const = 0;
    virtual ~CoffeeTable() = default;
};

class ModernChair : public Chair {
public:
    void sitOn() const override {
        std::cout << "Sitting on a modern chair." << std::endl;
    }
};

class ModernSofa : public Sofa {
public:
    void lieOn() const override {
        std::cout << "Lying on a modern sofa." << std::endl;
    }
};

class ModernCoffeeTable : public CoffeeTable {
public:
    void placeItems() const override {
        std::cout << "Placing items on a modern coffee table." << std::endl;
    }
};

class VictorianChair : public Chair {
public:
    void sitOn() const override {
        std::cout << "Sitting on a Victorian chair." << std::endl;
    }
};

class VictorianSofa : public Sofa {
public:
    void lieOn() const override {
        std::cout << "Lying on a Victorian sofa." << std::endl;
    }
};

class VictorianCoffeeTable : public CoffeeTable {
public:
    void placeItems() const override {
        std::cout << "Placing items on a Victorian coffee table." << std::endl;
    }
};

class ArtDecoChair : public Chair {
public:
    void sitOn() const override {
        std::cout << "Sitting on an Art Deco chair." << std::endl;
    }
};

class ArtDecoSofa : public Sofa {
public:
    void lieOn() const override {
        std::cout << "Lying on an Art Deco sofa." << std::endl;
    }
};

class ArtDecoCoffeeTable : public CoffeeTable {
public:
    void placeItems() const override {
        std::cout << "Placing items on an Art Deco coffee table." << std::endl;
    }
};

class FurnitureFactory {
public:
    virtual std::unique_ptr<Chair> createChair() const = 0;
    virtual std::unique_ptr<Sofa> createSofa() const = 0;
    virtual std::unique_ptr<CoffeeTable> createCoffeeTable() const = 0;
    virtual ~FurnitureFactory() = default;
};

class ModernFurnitureFactory : public FurnitureFactory {
public:
    std::unique_ptr<Chair> createChair() const override {
        return std::make_unique<ModernChair>();
    }

    std::unique_ptr<Sofa> createSofa() const override {
        return std::make_unique<ModernSofa>();
    }

    std::unique_ptr<CoffeeTable> createCoffeeTable() const override {
        return std::make_unique<ModernCoffeeTable>();
    }
};

class VictorianFurnitureFactory : public FurnitureFactory {
public:
    std::unique_ptr<Chair> createChair() const override {
        return std::make_unique<VictorianChair>();
    }

    std::unique_ptr<Sofa> createSofa() const override {
        return std::make_unique<VictorianSofa>();
    }

    std::unique_ptr<CoffeeTable> createCoffeeTable() const override {
        return std::make_unique<VictorianCoffeeTable>();
    }
};

class ArtDecoFurnitureFactory : public FurnitureFactory {
public:
    std::unique_ptr<Chair> createChair() const override {
        return std::make_unique<ArtDecoChair>();
    }

    std::unique_ptr<Sofa> createSofa() const override {
        return std::make_unique<ArtDecoSofa>();
    }

    std::unique_ptr<CoffeeTable> createCoffeeTable() const override {
        return std::make_unique<ArtDecoCoffeeTable>();
    }
};

class FurnitureShowroom {
private:
    std::unique_ptr<FurnitureFactory> factory;

public:
    FurnitureShowroom(std::unique_ptr<FurnitureFactory> f) : factory(std::move(f)) {}

    void displayFurniture() {
        auto chair = factory->createChair();
        auto sofa = factory->createSofa();
        auto coffeeTable = factory->createCoffeeTable();
        
        chair->sitOn();
        sofa->lieOn();
        coffeeTable->placeItems();
    }
};

int main() {
    std::unique_ptr<FurnitureFactory> factory;

    std::string style = "Modern"; 
    if (style == "Modern") {
        factory = std::make_unique<ModernFurnitureFactory>();
    } else if (style == "Victorian") {
        factory = std::make_unique<VictorianFurnitureFactory>();
    } else if (style == "ArtDeco") {
        factory = std::make_unique<ArtDecoFurnitureFactory>();
    }

    FurnitureShowroom showroom(std::move(factory));
    showroom.displayFurniture();

    return 0;
}
