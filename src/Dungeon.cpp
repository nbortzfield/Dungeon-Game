//
// Created by zacru on 2/23/2024.
//

#include "Dungeon.h"
#include <sstream>
#include <typeinfo>

Dungeon::Dungeon() {
    size = 0;
    name = "Dungeon";
    vector<Room> vecRooms;
    //TOM CODE v
    // this populates the dungeon map with null rooms
    for (int i = 0; i < maxSize; i++){
        for (int j = 0; j < maxSize; j++){
            Room_Null* nullRoom = new Room_Null;
            nullRoom->set_Coordinates(i,j);
            dungeonMap[i][j] = nullRoom;
        }
    }
    //TOM CODE ^
    height = 0;
    width = 0;
}

Dungeon::Dungeon(int psize, string pname) {
    size = psize;
    name = pname;
    generate_dungeon();
}

void Dungeon::set_size(int psize) {
    size = psize;
}

int Dungeon::get_size() const {
    return size;
}

void Dungeon::set_height(int h) {
    if (h <= maxSize){
        height = h;
    } else {
        height = maxSize;
    }
}

int Dungeon::get_height() const {
    return height;
}

void Dungeon::set_width(int w) {
    if (w <= maxSize){
        height = w;
    } else {
        height = maxSize;
    }
}

int Dungeon::get_width() const {
    return width;
}

void Dungeon::clear_dungeonMap() {
    for (int i = 0; i < maxSize; i++){
        for (int j = 0; j < maxSize; j++){
            Room_Null* nullRoom = new Room_Null;
            nullRoom->set_Coordinates(i,j);
            dungeonMap[i][j] = nullRoom;
        }
    }
}

void Dungeon::set_name(string pname) {
    name = pname;
}

string Dungeon::get_name() const {
    return name;
}

const vector<Room> &Dungeon::get_vecRooms() const {
    return vecRooms;
}

void Dungeon::set_vecRooms(const vector<Room> &pvecRooms) {
    vecRooms = pvecRooms;
    size = pvecRooms.size();
}

void Dungeon::add_to_vecRooms(Room newRoom) {
    vecRooms.push_back(newRoom);
    size = size + 1;
}

const Room &Dungeon::get_room(int pRoomNumber) const {
    return vecRooms[pRoomNumber-1];
}

const Room &Dungeon::get_room(int pX, int pY) const {
    int isRoom = 0;
    if (isRoom == 0) {
        for (const auto &room: vecRooms) {
            if (room.get_xCoordinate() == pX && room.get_yCoordinate() == pY) {
                return vecRooms[room.get_roomNumber() - 1];
            }
        }
        isRoom = 1;
    }
    static Room_Null newRoom;
    return newRoom;
}

void Dungeon::set_room(Room pRoom, int pRoomNumber) {
    vecRooms[pRoomNumber-1] = pRoom;
    Room* ptrRoom = &pRoom;
    dungeonMap[pRoom.get_yCoordinate()][pRoom.get_xCoordinate()] = ptrRoom;
}

void Dungeon::set_room(Room pRoom, int pX, int pY) {
    bool roomFound = false;
    // updating the room in the vector - if it does exist
    for (auto& room : vecRooms) {
        if (room.get_xCoordinate() == pX && room.get_yCoordinate() == pY) {
            room = pRoom;
            roomFound = true;
            cout << "Updated existing room at coordinages (" << pX << "," << pY << ")" << endl;
            break;
        }
    }
    // Updating the pointer in dungeonMap, will always point to the room in vecRooms
    for (auto& room : vecRooms){
        if (room.get_xCoordinate() == pX && room.get_yCoordinate() == pY){
            // pointing to the actual room in the vector - coords flipped because of layout
            dungeonMap[pY][pX] = &room;
            cout << "Dungeon map Updated for room at (" << pX << ", " << pY << ")" << endl;
            break;
        }
    }
}

void Dungeon::clear_vecRooms() {
    vecRooms.clear();
}

int Dungeon::get_total_treasure() const {
    int totalTreasure = 0;
    for (const auto& room : vecRooms) {
        totalTreasure += room.get_treasure();
    }
    return totalTreasure;
}

int Dungeon::get_total_traps() const {
    int totalTraps = 0;
    for (const auto& room : vecRooms) {
        if (room.get_traps() != "nothing") {
            totalTraps++;
        }
    }
    return totalTraps;
}

int Dungeon::get_total_doors() const {
    int totalDoors = 0;
    for (const auto& room : vecRooms) {
        totalDoors += room.get_doors();
    }
    return totalDoors;
}

void Dungeon::generate_dungeon() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, 4);
    uniform_int_distribution<int> distributionHW(1, 3);
    int maxTreasRoom;
    int maxBossRoom = 1;
    int currTreasRoom = 0;
    int currBossRoom = 0;
    bool postHallway = false;
    //TOM CODE v
    //Implement size declaration based on number/orientation of rooms
    height = maxSize;
    width = maxSize;
    //TOM CODE ^
    if (size <= 5) {
        maxTreasRoom = 1;
        maxBossRoom = 0;
    } else if (size <= 8) {
        maxTreasRoom = 2;
    } else if (size <= 12) {
        maxTreasRoom = 3;
    } else {
        maxTreasRoom = size / 4;
    }
    for (int i = 1; i <= size; ++i) {
        int randRoom = distribution(gen);
        int randHallChance = distributionHW(gen);
        if (randRoom == 1) {
            if (postHallway && randHallChance > 1) {
                Room_Hallway newRoom(i);
                newRoom.generate_room();
                vecRooms.push_back(newRoom);
                postHallway = true;
            } else {
                Room newRoom(i);
                newRoom.generate_room();
                vecRooms.push_back(newRoom);
                postHallway = false;
            }
        } else if (randRoom == 2) {
            Room_Hallway newRoom(i);
            newRoom.generate_room();
            vecRooms.push_back(newRoom);
            postHallway = true;
        } else if (randRoom == 3 && currTreasRoom < maxTreasRoom) {
            Room_Treasure newRoom(i);
            newRoom.generate_room();
            vecRooms.push_back(newRoom);
            postHallway = false;
            currTreasRoom++;
        } else if (currTreasRoom == maxTreasRoom) {
            i--;
        } else if (randRoom == 4 && currBossRoom < maxBossRoom) {
            Room_Boss newRoom(i);
            newRoom.generate_room();
            vecRooms.push_back(newRoom);
            postHallway = false;
            currBossRoom++;
        } else if (currBossRoom == maxBossRoom) {
            i--;
        }
    }
    clear_dungeonMap();
    generate_arrangement();
}

void Dungeon::generate_dungeon(int maxTreasNum, int maxBossNum) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, 4);
    int currTreasRoom = 0;
    int currBossRoom = 0;

    // Generates the base dungeon
    for (int i = 1; i <= size; ++i) {
        int randRoom = distribution(gen);
        if (randRoom == 1) {
            Room newRoom(i);
            newRoom.generate_room();
            vecRooms.push_back(newRoom);
        } else if (randRoom == 2) {
            Room_Hallway newRoom(i);
            newRoom.generate_room();
            vecRooms.push_back(newRoom);
        } else if (randRoom == 3 && currTreasRoom < maxTreasNum) {
            Room_Treasure newRoom(i);
            newRoom.generate_room();
            vecRooms.push_back(newRoom);
            currTreasRoom++;
        } else if (currTreasRoom == maxTreasNum) {
            i--;
        } else if (randRoom == 4 && currBossRoom < maxBossNum) {
            Room_Boss newRoom(i);
            newRoom.generate_room();
            vecRooms.push_back(newRoom);
            currBossRoom++;
        } else if (currBossRoom == maxBossNum) {
            i--;
        }
    }
    clear_dungeonMap();
    generate_arrangement();
}

void Dungeon::generate_arrangement() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> rNumConnectedRooms(1, 3);
    uniform_int_distribution<int> rNumNorthOrSouth(1, 2);

    //first, index into the starting location
    int currentWidth = width/2;
    int currentHeight = height/2;
    vector<Room*> vecRoomPtr;
    for (int z = 0; z < vecRooms.size(); z++) {
        Room* roomPtr = &vecRooms[z];
        vecRoomPtr.push_back(roomPtr);
    }
    dungeonMap[currentHeight][currentWidth] = vecRoomPtr[0];
    dungeonMap[currentHeight][currentWidth]->set_Coordinates(currentWidth, currentHeight);

    // here add information about this starting room

    //now begin generating the next rooms
    int i = 1;
    while (i < vecRooms.size()/2){
        int rConnections = rNumConnectedRooms(gen);
        int rNorthOrSouth = rNumNorthOrSouth(gen);
        if (rConnections == 1){
            if (dungeonMap[currentHeight][currentWidth - 1] != nullptr && dungeonMap[currentHeight][currentWidth - 1]->placedMap() != "1"){
                dungeonMap[currentHeight][currentWidth - 1] = vecRoomPtr[i];
                dungeonMap[currentHeight][currentWidth - 1]->set_Coordinates(currentWidth - 1, currentHeight);
                currentWidth = currentWidth-1;
                i++;
            }
        }
        else if (rConnections == 2){
            if (dungeonMap[currentHeight][currentWidth - 1] != nullptr && dungeonMap[currentHeight][currentWidth - 1]->placedMap() != "1"){
                dungeonMap[currentHeight][currentWidth - 1] = vecRoomPtr[i];
                dungeonMap[currentHeight][currentWidth - 1]->set_Coordinates(currentWidth - 1, currentHeight);
                currentWidth = currentWidth-1;
                i++;
            }
            if (dungeonMap[currentHeight - 1][currentWidth] != nullptr && dungeonMap[currentHeight - 1][currentWidth]->placedMap() != "1"){
                dungeonMap[currentHeight - 1][currentWidth] = vecRoomPtr[i];
                dungeonMap[currentHeight - 1][currentWidth]->set_Coordinates(currentWidth, currentHeight - 1);
                currentHeight = currentHeight - 1;
                i++;
            }
        }
        else if (rConnections == 3 && rNorthOrSouth == 1){
            if (dungeonMap[currentHeight][currentWidth - 1] != nullptr && dungeonMap[currentHeight][currentWidth - 1]->placedMap() != "1"){
                dungeonMap[currentHeight][currentWidth - 1] = vecRoomPtr[i];
                dungeonMap[currentHeight][currentWidth - 1]->set_Coordinates(currentWidth - 1, currentHeight);
                currentWidth = currentWidth-1;
                i++;
            }
            if (dungeonMap[currentHeight - 1][currentWidth] != nullptr && dungeonMap[currentHeight - 1][currentWidth]->placedMap() != "1"){
                dungeonMap[currentHeight - 1][currentWidth] = vecRoomPtr[i];
                dungeonMap[currentHeight - 1][currentWidth]->set_Coordinates(currentWidth, currentHeight - 1);
                currentHeight = currentHeight - 1;
                i++;
            }
            if (dungeonMap[currentHeight][currentWidth + 1] != nullptr && dungeonMap[currentHeight][currentWidth + 1]->placedMap() != "1"){
                dungeonMap[currentHeight][currentWidth + 1] = vecRoomPtr[i];
                dungeonMap[currentHeight][currentWidth + 1]->set_Coordinates(currentWidth + 1, currentHeight);
                currentWidth = currentWidth+1;
                i++;
            }
        }
        else if (rConnections == 3 && rNorthOrSouth == 2){
            if (dungeonMap[currentHeight][currentWidth - 1] != nullptr && dungeonMap[currentHeight][currentWidth - 1]->placedMap() != "1"){
                dungeonMap[currentHeight][currentWidth - 1] = vecRoomPtr[i];
                dungeonMap[currentHeight][currentWidth - 1]->set_Coordinates(currentWidth - 1, currentHeight);
                currentWidth = currentWidth-1;
                i++;
            }
            if (dungeonMap[currentHeight + 1][currentWidth] != nullptr && dungeonMap[currentHeight + 1][currentWidth]->placedMap() != "1"){
                dungeonMap[currentHeight + 1][currentWidth] = vecRoomPtr[i];
                dungeonMap[currentHeight + 1][currentWidth]->set_Coordinates(currentWidth, currentHeight + 1);
                currentHeight = currentHeight + 1;
                i++;
            }
            if (dungeonMap[currentHeight][currentWidth + 1] != nullptr && dungeonMap[currentHeight][currentWidth + 1]->placedMap() != "1"){
                dungeonMap[currentHeight][currentWidth + 1] = vecRoomPtr[i];
                dungeonMap[currentHeight][currentWidth + 1]->set_Coordinates(currentWidth + 1, currentHeight);
                currentWidth = currentWidth+1;
                i++;
            }
        }
        else {
            //if none of the above options work, move back to the start and move straight up to
            //to start another branch
            currentWidth = width/2;
            currentHeight = height/2;
            while (dungeonMap[currentHeight][currentWidth]->placedMap() != "0"){
                currentHeight--;
            }
            currentHeight--;
            dungeonMap[currentHeight][currentWidth] = vecRoomPtr[i];
            dungeonMap[currentHeight][currentWidth]->set_Coordinates(currentWidth, currentHeight);
            i++; //Add i++ here seemed to help not having to large dungs but I still got one that was 1 over -Zac
        }
    }
    //Now build the dungeon out from the other direction

    currentWidth = width/2;
    currentHeight = height/2;

    while (i < vecRooms.size()) {
        int rConnections = rNumConnectedRooms(gen);
        int rNorthOrSouth = rNumNorthOrSouth(gen);
        if (rConnections == 1) {
            if (dungeonMap[currentHeight][currentWidth + 1] != nullptr && dungeonMap[currentHeight][currentWidth + 1]->placedMap() != "1") {
                dungeonMap[currentHeight][currentWidth + 1] = vecRoomPtr[i];
                dungeonMap[currentHeight][currentWidth + 1]->set_Coordinates(currentWidth + 1, currentHeight);
                currentWidth = currentWidth + 1;
                i++;
            }
        } else if (rConnections == 2) {
            if (dungeonMap[currentHeight][currentWidth + 1] != nullptr && dungeonMap[currentHeight][currentWidth + 1]->placedMap() != "1") {
                dungeonMap[currentHeight][currentWidth + 1] = vecRoomPtr[i];
                dungeonMap[currentHeight][currentWidth + 1]->set_Coordinates(currentWidth + 1, currentHeight);
                currentWidth = currentWidth + 1;
                i++;
            }
            if (dungeonMap[currentHeight - 1][currentWidth] != nullptr && dungeonMap[currentHeight - 1][currentWidth]->placedMap() != "1" && i < vecRooms.size()) {
                dungeonMap[currentHeight - 1][currentWidth] = vecRoomPtr[i];
                dungeonMap[currentHeight - 1][currentWidth]->set_Coordinates(currentWidth, currentHeight - 1);
                currentHeight = currentHeight - 1;
                i++;
            }
        } else if (rConnections == 3 && rNorthOrSouth == 1) {
            if (dungeonMap[currentHeight][currentWidth + 1] != nullptr && dungeonMap[currentHeight][currentWidth + 1]->placedMap() != "1") {
                dungeonMap[currentHeight][currentWidth + 1] = vecRoomPtr[i];
                dungeonMap[currentHeight][currentWidth + 1]->set_Coordinates(currentWidth + 1, currentHeight);
                currentWidth = currentWidth + 1;
                i++;
            }
            if (dungeonMap[currentHeight - 1][currentWidth] != nullptr && dungeonMap[currentHeight - 1][currentWidth]->placedMap() != "1" && i < vecRooms.size()) {
                dungeonMap[currentHeight - 1][currentWidth] = vecRoomPtr[i];
                dungeonMap[currentHeight - 1][currentWidth]->set_Coordinates(currentWidth, currentHeight - 1);
                currentHeight = currentHeight - 1;
                i++;
            }
            if (dungeonMap[currentHeight][currentWidth - 1] != nullptr && dungeonMap[currentHeight][currentWidth - 1]->placedMap() != "1" && i < vecRooms.size()) {
                dungeonMap[currentHeight][currentWidth - 1] = vecRoomPtr[i];
                dungeonMap[currentHeight][currentWidth - 1]->set_Coordinates(currentWidth - 1, currentHeight);
                currentWidth = currentWidth - 1;
                i++;
            }
        } else if (rConnections == 3 && rNorthOrSouth == 2) {
            if (dungeonMap[currentHeight][currentWidth + 1] != nullptr && dungeonMap[currentHeight][currentWidth + 1]->placedMap() != "1") {
                dungeonMap[currentHeight][currentWidth + 1] = vecRoomPtr[i];
                dungeonMap[currentHeight][currentWidth + 1]->set_Coordinates(currentWidth + 1, currentHeight);
                currentWidth = currentWidth + 1;
                i++;
            }
            if (dungeonMap[currentHeight + 1][currentWidth] != nullptr && dungeonMap[currentHeight + 1][currentWidth]->placedMap() != "1" && i < vecRooms.size()) {
                dungeonMap[currentHeight + 1][currentWidth] = vecRoomPtr[i];
                dungeonMap[currentHeight + 1][currentWidth]->set_Coordinates(currentWidth, currentHeight + 1);
                currentHeight = currentHeight + 1;
                i++;
            }
            if (dungeonMap[currentHeight][currentWidth - 1] != nullptr && dungeonMap[currentHeight][currentWidth - 1]->placedMap() != "1" && i < vecRooms.size()) {
                dungeonMap[currentHeight][currentWidth - 1] = vecRoomPtr[i];
                dungeonMap[currentHeight][currentWidth - 1]->set_Coordinates(currentWidth - 1, currentHeight);
                currentWidth = currentWidth - 1;
                i++;
            }
        }
        else {
            //if none of the above options work, move back to the start and move straight up to
            //to start another branch
            currentWidth = width / 2;
            currentHeight = height / 2;
            while (dungeonMap[currentHeight][currentWidth]->placedMap() != "0") {
                currentHeight--;
            }
            currentHeight--;
            dungeonMap[currentHeight][currentWidth] = vecRoomPtr[i];
            dungeonMap[currentHeight][currentWidth]->set_Coordinates(currentWidth, currentHeight);
            i++; //Add i++ here seemed to help not having to large dungs but I still got one that was 1 over -Zac
        }
    }
}

void Dungeon::generate_doors() {
    for (const auto& room : vecRooms) {
        for (const auto& roomNext : vecRooms) {
            //if (room.get_xCoordinate() == roomNext.get_xCoordinate() + 1 &&)
        }
    }
}

void Dungeon::print() const {
    int totalTreasure = get_total_treasure();
    int totalTraps = get_total_traps();
    cout << endl;
    cout << name << " has " << size << " rooms" << endl;
    cout << name << " has " << totalTreasure << " GP total worth in Treasure" << endl;
    cout << name << " has " << totalTraps << " traps" << endl;
}

void Dungeon::printRooms() const {
    for (const auto& room : vecRooms) {
        room.print();
        cout << endl;
    }
}

void Dungeon::printDungeonMap() const {
    cout << "Dungeon Map: " << endl;
    for (int i = 0; i < width; i++){
        for (int k = 0; k < height; k++){
            cout << dungeonMap[i][k]->placedMap() << " ";
        }
        cout << endl;
    }
    cout << "Height: " << height << " Width: " << width << endl;
}

void Dungeon::load_dungeon_data(vector<string> saveData) {
    clear_vecRooms();
    name = saveData[0];
    size = stoi(saveData[1]);
    string strRooms = saveData[2];
    vector<string> allRoomData = split_string(strRooms, '|');
    vector<string> roomData;
    for (const auto& room : allRoomData) {
        if (room != "") {
            roomData = split_string(room, '-');
            Room newRoom(stoi(roomData[0]), roomData[1], stod(roomData[2]), stoi(roomData[3]), roomData[4], stoi(roomData[5]), stoi(roomData[6]), stoi(roomData[7]) );
            vecRooms.push_back(newRoom);
        }
    }
    if (vecRooms[0].get_xCoordinate() != 0) {
        load_dungeon_arrangement();
    }
}

void Dungeon::load_dungeon_arrangement() {
    vector<Room*> vecRoomPtr;
    for (int z = 0; z < vecRooms.size(); z++) {
        Room* roomPtr = &vecRooms[z];
        vecRoomPtr.push_back(roomPtr);
    }
    clear_dungeonMap();
    int i = 0;
    for (const auto& room : vecRooms) {
        dungeonMap[room.get_yCoordinate()][room.get_xCoordinate()] = vecRoomPtr[i];
        i++;
    }
}

vector<string> Dungeon::get_save_dungeon_data() const {
    vector<string> saveData;
    saveData.push_back(name);
    saveData.push_back(to_string(size));
    ostringstream roomData;
    for (Room room : vecRooms) {
        roomData << "|"
                 << room.get_roomNumber() << "-"
                 << room.get_type() << "-"
                 << room.get_threatLevel() << "-"
                 << room.get_treasure() << "-"
                 << room.get_traps() << "-"
                 << room.get_doors() << "-"
                 << room.get_xCoordinate() << "-"
                 << room.get_yCoordinate();
    }
    saveData.push_back(roomData.str());

    return saveData;
}

vector<string> Dungeon::split_string(const string &input, char del) {
    vector<string> result;
    istringstream stream(input);
    string token;

    while (getline(stream, token, del)) {
        result.push_back(token);
    }

    return result;
}

// Needed for finding the surrounding room types
int Dungeon::checkRoomType(int x, int y){
// Checking bounds
    if (x < 0 || y < 0 || x >= maxSize || y >= maxSize) {
        // No room can be out of bounds
        return 0;
    }

    // Accessing the room by coordinates
    Room* room = dungeonMap[y][x];

    // checking if the pointer is null, if it is, there is no room
    if (typeid(*room) == typeid(Room_Null)){
        cout << "null type room neighbor" << endl;
        return 0;
    // checking if the pointer is 2, meaning a hallway
    } else if (typeid(*room) == typeid(Room_Hallway)){
        cout << "hallway type room neighbor" << endl;
        return 2;
    // all others must be rooms
    } else {
        cout << "normal room type neighbor" << endl;
        return 1;
    }
}