#include <iostream>

class Collaborator {
public:
    virtual int GetFirstNumber() = 0;
    virtual int GetSecondNumber() = 0;
};

class SystemUnderTest {
public:
    SystemUnderTest(Collaborator* collaborator) : collaborator_(collaborator) {}

    int SumOfTwoNumbers() {
        int first = collaborator_->GetFirstNumber();
        int second = collaborator_->GetSecondNumber();
        return first + second;
    }

private:
    Collaborator* collaborator_;
};
