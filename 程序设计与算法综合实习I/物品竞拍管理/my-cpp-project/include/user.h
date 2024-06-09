#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User(const std::string& name, int age);
    ~User();

    std::string getName() const;
    int getAge() const;

    void setName(const std::string& name);
    void setAge(int age);

private:
    std::string name;
    int age;
};

#endif // USER_H