#include <iostream>
#include <memory>
#include <string>

class Building
{
private:
    std::string _wallMaterial;
    std::string _roofMaterial;
    bool _hasPool;
    int _doorCount;
    int _windowCount;
    double _gardenArea; 

public:
    void setPool(bool pool) {
        _hasPool = pool;
    }

    void setWallMaterial(const std::string& material) {
        _wallMaterial = material;
    }

    void setRoofMaterial(const std::string& material) {
        _roofMaterial = material;
    }

    void setDoorCount(int count) {
        _doorCount = count;
    }

    void setWindowCount(int count) {
        _windowCount = count;
    }

    void setGardenArea(double area) {
        _gardenArea = area;
    }

    void display() const {
        std::cout << "Building Details:\n"
                  << "Wall Material: " << _wallMaterial << "\n"
                  << "Roof Material: " << _roofMaterial << "\n"
                  << "Doors: " << _doorCount << "\n"
                  << "Windows: " << _windowCount << "\n"
                  << "Garden Area: " << _gardenArea << " m²\n"
                  << "Pool: " << (_hasPool ? "Yes" : "No") << "\n";
    }
};

class BuildingBuilder {
public:
    virtual void buildDoor() = 0;
    virtual void buildRoof() = 0;
    virtual void buildWall() = 0;
    virtual void buildPool() = 0;
    virtual void buildWindows() = 0;
    virtual void buildGardenArea() = 0;
    virtual std::unique_ptr<Building> getBuilding() = 0;
};

class TraditionalBuilding : public BuildingBuilder {
private:
    std::unique_ptr<Building> _building;

public:
    TraditionalBuilding() : _building(std::make_unique<Building>()) {}

    void buildDoor() override {
        _building->setDoorCount(1);
    }

    void buildRoof() override {
        _building->setRoofMaterial("Tile");
    }

    void buildWall() override {
        _building->setWallMaterial("Brick");
    }

    void buildPool() override {
        _building->setPool(false);
    }

    void buildWindows() override {
        _building->setWindowCount(4);
    }

    void buildGardenArea() override {
        _building->setGardenArea(50.0); 
    }

    std::unique_ptr<Building> getBuilding() override {
        return std::move(_building);
    }
};

class LuxuryVilla : public BuildingBuilder {
private:
    std::unique_ptr<Building> _building;

public:
    LuxuryVilla() : _building(std::make_unique<Building>()) {}

    void buildDoor() override {
        _building->setDoorCount(3);
    }

    void buildRoof() override {
        _building->setRoofMaterial("Wood");
    }

    void buildWall() override {
        _building->setWallMaterial("Stone");
    }

    void buildPool() override {
        _building->setPool(true);
    }

    void buildWindows() override {
        _building->setWindowCount(6);
    }

    void buildGardenArea() override {
        _building->setGardenArea(100.0); 
    }

    std::unique_ptr<Building> getBuilding() override {
        return std::move(_building);
    }
};

class ConstructionManager {
private:
    BuildingBuilder* _builder;

public:
    void setBuilder(BuildingBuilder* builder) {
        _builder = builder;
    }

    void constructBuilding() {
        _builder->buildWall();
        _builder->buildRoof();
        _builder->buildDoor();
        _builder->buildPool();
        _builder->buildWindows();
        _builder->buildGardenArea();
    }

    std::unique_ptr<Building> getBuilding() {
        return _builder->getBuilding();
    }
};

int main() {
    ConstructionManager manager;

    manager.setBuilder(new LuxuryVilla);
    manager.constructBuilding();
    std::unique_ptr<Building> villa = manager.getBuilding();
    villa->display();

    manager.setBuilder(new TraditionalBuilding);
    manager.constructBuilding();
    std::unique_ptr<Building> house = manager.getBuilding();
    house->display();

    return 0;
}
