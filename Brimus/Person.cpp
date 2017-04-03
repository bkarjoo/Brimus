//
// Created by b.karjoo on 3/31/2017.
//

#include "Person.h"

int Person::getAge() const {
    return age;
}

void Person::setAge(int age) {
    if (this->age == age) return;
    Person::age = age;
    PropertyChanged(*this, "age");
}

Person::Person(int age) : age(age) {}
