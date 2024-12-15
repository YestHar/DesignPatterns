#include <iostream>
#include <memory>
#include <string>

class IssueHandler {
protected:
    std::shared_ptr<IssueHandler> successor_;

public:
    void setSuccessor(std::shared_ptr<IssueHandler> handler) {
        successor_ = handler;
    }

    virtual void resolveIssue(const std::string& issueType) = 0;
    virtual ~IssueHandler() = default;
};

class JuniorDeveloper : public IssueHandler {
public:
    void resolveIssue(const std::string& issueType) override {
        if (issueType == "Simple") {
            std::cout << "Junior Developer resolved the issue." << std::endl;
        } else if (successor_) {
            std::cout << "Passing issue to the Senior Developer." << std::endl;
            successor_->resolveIssue(issueType);
        } else {
            std::cout << "Issue remains unresolved." << std::endl;
        }
    }
};

class SeniorDeveloper : public IssueHandler {
public:
    void resolveIssue(const std::string& issueType) override {
        if (issueType == "Moderate") {
            std::cout << "Senior Developer resolved the issue." << std::endl;
        } else if (successor_) {
            std::cout << "Passing issue to the Project Manager." << std::endl;
            successor_->resolveIssue(issueType);
        } else {
            std::cout << "Issue remains unresolved." << std::endl;
        }
    }
};

class ProjectManager : public IssueHandler {
public:
    void resolveIssue(const std::string& issueType) override {
        if (issueType == "Challenging") {
            std::cout << "Project Manager resolved the issue." << std::endl;
        } else if (successor_) {
            std::cout << "Passing issue to the Director." << std::endl;
            successor_->resolveIssue(issueType);
        } else {
            std::cout << "Issue remains unresolved." << std::endl;
        }
    }
};

class Director : public IssueHandler {
public:
    void resolveIssue(const std::string& issueType) override {
        if (issueType == "Critical") {
            std::cout << "Director resolved the issue." << std::endl;
        } else {
            std::cout << "Issue remains unresolved." << std::endl;
        }
    }
};

int main() {
    auto junior = std::make_shared<JuniorDeveloper>();
    auto senior = std::make_shared<SeniorDeveloper>();
    auto manager = std::make_shared<ProjectManager>();
    auto director = std::make_shared<Director>();

    junior->setSuccessor(senior);
    senior->setSuccessor(manager);
    manager->setSuccessor(director);

    junior->resolveIssue("Simple");
    junior->resolveIssue("Moderate");
    junior->resolveIssue("Challenging");
    junior->resolveIssue("Critical");
    junior->resolveIssue("Unresolvable");

    return 0;
}
