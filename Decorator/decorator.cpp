#include <iostream>
#include <string>
#include <memory>

class Notifier {
public:
    virtual ~Notifier() = default;
    virtual void send(const std::string& message) const = 0;
};

class SimpleNotifier : public Notifier {
public:
    void send(const std::string& message) const override {
        std::cout << "Sending basic notification: " << message << std::endl;
    }
};

class BaseDecorator : public Notifier {
protected:
    std::unique_ptr<Notifier> wrappee;
public:
    BaseDecorator(std::unique_ptr<Notifier> notifier) : wrappee(std::move(notifier)) {}

    void send(const std::string& message) const override {
        wrappee->send(message);
    }
};

class SMSDecorator : public BaseDecorator {
public:
    SMSDecorator(std::unique_ptr<Notifier> notifier) : BaseDecorator(std::move(notifier)) {}

    void send(const std::string& message) const override {
        BaseDecorator::send(message);
        std::cout << "Sending SMS: " << message << std::endl;
    }
};

class FacebookDecorator : public BaseDecorator {
public:
    FacebookDecorator(std::unique_ptr<Notifier> notifier) : BaseDecorator(std::move(notifier)) {}

    void send(const std::string& message) const override {
        BaseDecorator::send(message);
        std::cout << "Sending Facebook Message: " << message << std::endl;
    }
};

class SlackDecorator : public BaseDecorator {
public:
    SlackDecorator(std::unique_ptr<Notifier> notifier) : BaseDecorator(std::move(notifier)) {}

    void send(const std::string& message) const override {
        BaseDecorator::send(message);
        std::cout << "Sending Slack Message: " << message << std::endl;
    }
};

int main() {
    std::unique_ptr<Notifier> notifier = std::make_unique<SimpleNotifier>();

    bool facebookEnabled = true;
    bool slackEnabled = true;

    if (facebookEnabled) {
        notifier = std::make_unique<FacebookDecorator>(std::move(notifier));
    }
    if (slackEnabled) {
        notifier = std::make_unique<SlackDecorator>(std::move(notifier));
    }

    notifier->send("Ani!");
    notifier->send("Anna!");


    return 0;
}
