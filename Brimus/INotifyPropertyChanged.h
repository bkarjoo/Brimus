//
// Created by b.karjoo on 3/31/2017.
//
#pragma once

#include <boost/signals2.hpp>
#include <string>

template <typename T>
class INotifyPropertyChanged {
public:
    virtual ~INotifyPropertyChanged() = default;
    boost::signals2::signal<void(T&, const std::string&)> PropertyChanged;
};



