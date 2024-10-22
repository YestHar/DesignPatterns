#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <mutex>  

class Singleton {
private:
    static Singleton* instance;
    static std::mutex mutex_;  
    std::map<std::string, std::string> settings;
    std::string configFilePath;

    Singleton() {
        configFilePath = "config.txt"; 
        loadSettingsFromFile(); 
    }

    void loadSettingsFromFile() {
        std::ifstream file(configFilePath);
        if (file.is_open()) {
            std::string key, value;
            while (file >> key >> value) {
                settings[key] = value;
            }
            file.close();
        } else {
            std::cout << "Could not open settings file, default values are used.\n";
        }
    }

    void saveSettingsToFile() {
        std::ofstream file(configFilePath);
        if (file.is_open()) {
            for (const auto& pair : settings) {
                file << pair.first << " " << pair.second << std::endl;
            }
            file.close();
        } else {
            std::cout << "Failed to save settings.\n";
        }
    }

public:
    static Singleton* getInstance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }

    std::string getSetting(const std::string& key) {
        return settings[key];
    }

    void setSetting(const std::string& key, const std::string& value) {
        settings[key] = value;
        saveSettingsToFile();  
    }

    ~Singleton() {
        saveSettingsToFile();  
    }
};

Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex_;

int main() {
    Singleton* config1 = Singleton::getInstance();
    std::cout << "Database: " << config1->getSetting("database") << std::endl;

    config1->setSetting("database", "192.168.1.100");

    Singleton* config2 = Singleton::getInstance();
    std::cout << "Updated Database: " << config2->getSetting("database") << std::endl;

    return 0;
}
