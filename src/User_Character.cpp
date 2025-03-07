//
// Created by zacru on 4/16/2024.
//

#include "User_Character.h"

User_Character::User_Character() {
    name = "User";
    health = 3;
    gold = 0;
    weapon = "none";
    xCoordinate = 0;
    yCoordinate = 0;
}

void User_Character::set_name(string pname) {
    name = pname;
}

string User_Character::get_name() {
    return name;
}

void User_Character::set_health(int phealth) {
    health = phealth;
}

int User_Character::get_health() const {
    return health;
}

void User_Character::sub_health(int psub) {
    health -= psub;
}

void User_Character::set_gold(int pgold) {
    gold = pgold;
}

int User_Character::get_gold() const {
    return gold;
}

void User_Character::add_gold(int addGold) {
    gold += addGold;
}

void User_Character::set_weapon(string pweapon) {
    weapon = pweapon;
}

string User_Character::get_weapon() {
    return weapon;
}

int User_Character::get_xCoordinate() const {
    return xCoordinate;
}

void User_Character::set_xCoordinate(int pCoordinate) {
    xCoordinate = pCoordinate;
}

int User_Character::get_yCoordinate() const {
    return yCoordinate;
}

void User_Character::set_yCoordinate(int pCoordinate) {
    yCoordinate = pCoordinate;
}

void User_Character::set_Coordinates(int pX, int pY) {
    xCoordinate = pX;
    yCoordinate = pY;
}
