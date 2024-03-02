//
// Created by dika on 29.02.2024.
//
#include <utility>

#include "../include/LogItem.hpp"

LogItem::LogItem(std::string date_time, std::string firmware, std::string owner, std::string payload) :
                 date_time(std::move(date_time)), firmware(std::move(firmware)),
                 owner(std::move(owner)), payload(std::move(payload)){

}