#include <iostream>

void SendSms(const std::string& number, const std::string& message) {
    std::cout << "Send '" << message << "' to number " << number << std::endl;
}

void SendEmail(const std::string& email, const std::string& message) {
    std::cout << "Send '" << message << "' to e-mail "  << email << std::endl;
}

class NotifierBase {
private:
public:
    NotifierBase() = default;

    virtual void Notify(const std::string&) const = 0;

    virtual ~NotifierBase() = default;
};

class EmailNotifier : public NotifierBase {
private:
    const std::string email;
public:
    EmailNotifier(std::string email):
        email(email){}
    
    void Notify(const std::string& message) const override {
        SendEmail(email, message);
    }

    ~EmailNotifier() = default;
};

class SmsNotifier : public NotifierBase {
private:
    const std::string number;
public:
    SmsNotifier(std::string number):
        number(number){}
    
    void Notify(const std::string& message) const override {
        SendSms(number, message);
    }

    ~SmsNotifier() = default;
};

void Notify(const NotifierBase& notifier, const std::string& message) {
    notifier.Notify(message);
}

int main() {
    SmsNotifier sms("+7-495-777-77-77");
    EmailNotifier email("na-derevnyu@dedushke.ru");

    Notify(sms, "Hello! How are you?");
    Notify(email, "Let's learn C++!");
    return 0;
}