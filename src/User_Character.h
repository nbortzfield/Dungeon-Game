//
// Created by zacru on 4/16/2024.
//

#ifndef M4OEP_ZRUE_NBORTZFI_GGICK_TBEUCLER_USER_CHARACTER_H
#define M4OEP_ZRUE_NBORTZFI_GGICK_TBEUCLER_USER_CHARACTER_H


#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class User_Character {
protected:
    string name;
    int health;
    int gold;
    string weapon;
    int xCoordinate;
    int yCoordinate;

public:
    User_Character();

    void set_name(string pname);

    virtual string get_name();

    void set_health(int phealth);

    virtual int get_health() const;

    void sub_health(int psub);

    void set_gold(int pgold);

    virtual int get_gold() const;

    void add_gold(int addGold);

    void set_weapon(string pweapon);

    virtual string get_weapon();

    virtual int get_xCoordinate() const;

    void set_xCoordinate(int pCoordinate);

    virtual int get_yCoordinate() const;

    void set_yCoordinate(int pCoordinate);

    void set_Coordinates(int pX, int pY);
};


#endif //M4OEP_ZRUE_NBORTZFI_GGICK_TBEUCLER_USER_CHARACTER_H
