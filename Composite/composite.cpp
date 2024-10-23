#include <iostream>
#include <vector>
#include <memory>

class Item {
public:
    virtual double getPrice() const = 0;  
    virtual ~Item() = default;
};

class Product : public Item {
private:
    double price;
public:
    Product(double p) : price(p) {}

    double getPrice() const override {
        return price;  
    }
};

class Box : public Item {
private:
    std::vector<std::shared_ptr<Item>> items;  
    double packagingCost;  
public:
    Box(double cost) : packagingCost(cost) {}

    void add(const std::shared_ptr<Item>& item) {
        items.push_back(item);
    }

    double getPrice() const override {
        double total = packagingCost; 
        for (const auto& item : items) {
            total += item->getPrice();  
        }
        return total;
    }
};

int main() {
    auto product1 = std::make_shared<Product>(100); 
    auto product2 = std::make_shared<Product>(50);   

    auto box1 = std::make_shared<Box>(10); 
    box1->add(product1);
    box1->add(product2);

    auto box2 = std::make_shared<Box>(5); 
    box2->add(box1);

    auto product3 = std::make_shared<Product>(75);  
    box2->add(product3);

    std::cout << "Total price:" << box2->getPrice() << " dram" << std::endl;  

    return 0;
}
