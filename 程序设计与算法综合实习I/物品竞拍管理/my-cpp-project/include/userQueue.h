#ifndef USERQUEUE_H
#define USERQUEUE_H

#include "user.h"

class UserQueue {
public:
    UserQueue();
    ~UserQueue();

    void enqueue(User* user);
    User* dequeue();
    bool isEmpty() const;
    int size() const;

private:
    struct Node {
        User* user;
        Node* next;
    };

    Node* front;
    Node* rear;
    int count;
};

#endif // USERQUEUE_H