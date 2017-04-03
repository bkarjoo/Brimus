//
// Created by b.karjoo on 3/31/2017.
//

#ifndef BRIMUS_PERSON_H
#define BRIMUS_PERSON_H


#include "INotifyPropertyChanged.h"

class Person : public INotifyPropertyChanged<Person> {
    int age;
    Person() {};
    ~Person() {};
public:
    Person(Person const&) = delete;
    void operator=(Person const&) = delete;
    static Person& get_instance() {
        static Person p;
        return p;
    }
    Person(int age);
    int getAge() const;
    void setAge(int age);
};


#endif //BRIMUS_PERSON_H
