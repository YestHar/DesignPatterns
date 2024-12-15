#include <iostream>
#include <memory>

class LensBase {
public:
    virtual void printDetails() const = 0;
    virtual ~LensBase() = default;
};

class Polarized : public LensBase {
public:
    void printDetails() const override {
        std::cout << "Polarized Lens Applied" << std::endl;
    }
};

class AntiReflective : public LensBase {
public:
    void printDetails() const override {
        std::cout << "Anti-Reflective Lens Applied" << std::endl;
    }
};

class Tinted : public LensBase {
public:
    void printDetails() const override {
        std::cout << "Tinted Lens Applied" << std::endl;
    }
};

class GlassesBase {
protected:
    std::shared_ptr<LensBase> lens_;

public:
    explicit GlassesBase(std::shared_ptr<LensBase> lens) : lens_(std::move(lens)) {}
    virtual void showDescription() const = 0;
    virtual ~GlassesBase() = default;
};

class CasualWear : public GlassesBase {
public:
    explicit CasualWear(std::shared_ptr<LensBase> lens) : GlassesBase(std::move(lens)) {}
    void showDescription() const override {
        std::cout << "Casual Glasses with ";
        lens_->printDetails();
    }
};

class ProfessionalWear : public GlassesBase {
public:
    explicit ProfessionalWear(std::shared_ptr<LensBase> lens) : GlassesBase(std::move(lens)) {}
    void showDescription() const override {
        std::cout << "Professional Glasses with ";
        lens_->printDetails();
    }
};

class AthleticWear : public GlassesBase {
public:
    explicit AthleticWear(std::shared_ptr<LensBase> lens) : GlassesBase(std::move(lens)) {}
    void showDescription() const override {
        std::cout << "Athletic Glasses with ";
        lens_->printDetails();
    }
};

int main() {
    auto polarized = std::make_shared<Polarized>();
    auto antiReflective = std::make_shared<AntiReflective>();
    auto tinted = std::make_shared<Tinted>();

    CasualWear casual(polarized);
    ProfessionalWear professional(antiReflective);
    AthleticWear athletic(tinted);

    casual.showDescription();
    professional.showDescription();
    athletic.showDescription();

    return 0;
}
