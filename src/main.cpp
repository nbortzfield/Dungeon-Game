#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <cstdlib>
#include "Room.h"
#include "Room_Hallway.h"
#include "Room_Treasure.h"
#include "Room_Boss.h"
#include "Room_Null.h"
#include "Dungeon.h"
#include "engine.h"
using namespace std;

/**
 * Requires: nothing
 * Modifies: nothing
 * Effects: Input validation for an integer value, takes in a string prompt
 */
int get_int_from_user(string prompt);

/**
 * Requires: nothing
 *
 * Modifies: nothing
 * Effects: Input validation for retrieving a string with multiple distinct words
            takes in a string prompt
 */
string get_sentence_from_user(string prompt);

/**
 * Requires: nothing
 * Modifies: nothing
 * Effects: Input validation for yes or no question
 */
string get_yes_no();

/**
 * Requires: nothing
 * Modifies: nothing
 * Effects: Input validation for any question with a single character string valid answer,
 *          takes in a vector of strings which equate to the possible answers a user can enter
 */
string get_valid_answer(vector<string> vecAnswers);

/**
 * Requires: nothing
 * Modifies: nameDungeon
 * Effects: Prompts user with the information to assign a name to a dungeon object
 */
void name_dungeon(Dungeon &nameDungeon);

/**
 * Requires: nothing
 * Modifies: genDungeon
 * Effects: Prompts user with the information to assign size and contents of a dungeon object
 */
void generate_dungeon(Dungeon &genDungeon);

/**
 * Requires: nothing
 * Modifies: dungeon
 * Effects: Writes to file with string originating from a dungeon object,
 *          with the goal of saving all information needed to reload a dungeon
 */
void save_dungeon(Dungeon &dungeon);

/**
 * Requires: nothing
 * Modifies: dungeon
 * Effects: Retrieves information From the save file and prompts the user
 *          with which save the user wants to load into a dungeon object
 */
void load_dungeon(Dungeon &dungeon);

void transfer_dungeon(Dungeon &dungeon);

/**
 * Main menu
 */
void menu_main();

// Using engine setup from Module 4 examples
int main(int argc, char *argv[]) {
    menu_main();
    //dungeon.print();

    Engine engine;

    while (!engine.shouldClose()){
        engine.processInput();
        engine.update();
        engine.render();
    }

    glfwTerminate();
    return 0;
}

void menu_main() {
    Dungeon newDungeon;
    cout << "Welcome to the Dungeon Maker!" << endl;
    name_dungeon(newDungeon);
    generate_dungeon(newDungeon);

    /**
    Room TestRoom = newDungeon.get_room(1);
    TestRoom.set_treasure(5000);
    newDungeon.set_room(TestRoom, 1);
    */

    Room TestRoom = newDungeon.get_room(12,12);
    TestRoom.set_treasure(5000);
    newDungeon.set_room(TestRoom, 12,12);

    int inMenuMain = 0;
    int inMenuInfo = 0;
    int inMenuEdit = 0;
    int inMenuSave;
    while (inMenuMain == 0) {
        vector<string> valAnsMenu = {"i", "e", "l", "s"};
        cout << "\nMain Menu:" << endl;
        cout << "Do you want to know more info about " << newDungeon.get_name() << " (enter i)" << endl;
        cout << "Do you want to edit " << newDungeon.get_name() << " (enter e)" << endl;
        cout << "Do you want to enter the Save/Load menu (enter s)" << endl;
        cout << "Do you want to enter game mode! (enter l)\nEnter: ";
        string mainResult = get_valid_answer(valAnsMenu);
        if (mainResult == "i") {
            inMenuInfo = 0;
            while (inMenuInfo == 0) {
                vector<string> ansMenuInfo = {"b", "c", "r", "t", "p", "s", "e", "m"};
                cout << "\nInfo Menu:" << endl;
                cout << "Brief summary of " << newDungeon.get_name() << " (enter b)" << endl;
                cout << "Comprehensive summary of " << newDungeon.get_name() << " (enter c)" << endl;
                cout << "Number of rooms (enter r)\nTotal amount of treasure (enter t)\nTotal amount of traps (enter p)\nA simple map of the dungeon (enter s)"
                     << endl;
                cout << "Go back to the main menu (enter m)\nEnter: ";
                string infoResult = get_valid_answer(ansMenuInfo);
                if (infoResult == "b") {
                    newDungeon.print();
                } else if (infoResult == "c") {
                    newDungeon.printRooms();
                } else if (infoResult == "r") {
                    cout << newDungeon.get_name() << " has " << newDungeon.get_size() << " rooms\n" << endl;
                } else if (infoResult == "t") {
                    cout << newDungeon.get_name() << " has " << newDungeon.get_total_treasure() << " GP total worth in Treasure\n" << endl;
                } else if (infoResult == "p") {
                    cout << newDungeon.get_name() << " has " << newDungeon.get_total_traps() << " total number of traps\n" << endl;
                } else if (infoResult == "s") {
                    newDungeon.printDungeonMap();
                } else if (infoResult == "m") {
                    inMenuInfo = 1;
                }
            }
        } else if (mainResult == "e") {
            inMenuEdit = 0;
            while (inMenuEdit == 0) {
                vector<string> ansMenuEdit = {"m", "r", "n"};
                cout << "\nEdit Menu:" << endl;
                cout << "Regenerate the Dungeon (enter r)" << endl;
                cout << "Change the name of the " << newDungeon.get_name() << " (enter n)" << endl;
                cout << "Go back to the main menu (enter m)\nEnter: ";
                string editResult = get_valid_answer(ansMenuEdit);
                if (editResult == "m") {
                    inMenuEdit = 1;
                } else if (editResult == "r") {
                    generate_dungeon(newDungeon);
                } else if (editResult == "n") {
                    name_dungeon(newDungeon);
                }
            }
        } else if (mainResult == "s") {
            inMenuSave = 0;
            while (inMenuSave == 0) {
                vector<string> ansMenuSave = {"m", "s", "l"};
                cout << "\nSave/Load Menu:" << endl;
                cout << "Save " << newDungeon.get_name() << " (enter s)" << endl;
                cout << "Load a Save (enter l)" << endl;
                cout << "Go back to the main menu (enter m)\nEnter: ";
                string saveResult = get_valid_answer(ansMenuSave);
                if (saveResult == "m") {
                    inMenuSave = 1;
                } else if (saveResult == "s") {
                    save_dungeon(newDungeon);
                    cout << newDungeon.get_name() << " has been saved!" << endl;
                } else if (saveResult == "l") {
                    load_dungeon(newDungeon);
                }
            }
        } else if (mainResult == "l") {
            cout << "Thank You for playing!" << endl;
            inMenuMain = 1;
            transfer_dungeon(newDungeon);
        }
    }
}

void name_dungeon(Dungeon &nameDungeon) {
    string dunName;
    int correct = 0;
    if (nameDungeon.get_name() == "Dungeon") {
        cout << "Do you want to name your Dungeon? (y for yes or n for no): ";
        string makeName = get_yes_no();
        if (makeName == "y") {
            dunName = get_sentence_from_user("What would you like to name your Dungeon? ");
            while (correct == 0) {
                cout << "Is " << dunName << " the name you want? (y for yes or n for no) ";
                string valInput = get_yes_no();
                if (valInput == "y") {
                    correct = 1;
                } else {
                    dunName = get_sentence_from_user("What would you like to name your Dungeon? ");
                }
            }
            nameDungeon.set_name(dunName);
        }
    } else {
        cout << "The currect name of the Dungeon is " << nameDungeon.get_name() << endl;
        dunName = get_sentence_from_user("What would you like to change the name of your Dungeon to?\nEnter: ");
        while (correct == 0) {
            cout << "Is " << dunName << " the name you want? (y for yes or n for no) ";
            string valInput = get_yes_no();
            if (valInput == "y") {
                correct = 1;
            } else {
                dunName = get_sentence_from_user("What would you like to name your Dungeon? ");
            }
        }
        nameDungeon.set_name(dunName);
    }
}

void generate_dungeon(Dungeon &genDungeon) {
    random_device rd;
    mt19937 gen(rd());

    genDungeon.clear_vecRooms();

    vector<string> valAnsSize = {"s", "m", "l", "c"};
    cout << "What size of dungeon do you want to make? \ns for small\nm for medium\nl for large\nc for custom number\nEnter: ";
    string sizeResult = get_valid_answer(valAnsSize);
    int correct = 0;
    while (correct == 0) {
        if (sizeResult == "s") {
            cout << "is small the size you want? Enter (y for yes or n for no): ";
        } else if (sizeResult == "m") {
            cout << "is medium the size you want? Enter (y for yes or n for no): ";
        } else if (sizeResult == "l") {
            cout << "is large the size you want? Enter (y for yes or n for no): ";
        } else if (sizeResult == "c") {
            cout << "Do you want to enter a custom the size? Enter (y for yes or n for no): ";
        }
        string valInput = get_yes_no();
        if (valInput == "y") {
            correct = 1;
        } else {
            cout << "What size of dungeon do you want to make? \ns for small\nm for medium\nl for large\nc for custom number\nEnter: ";
            sizeResult = get_valid_answer(valAnsSize);
        }
    }
    int roomNumber;
    if (sizeResult == "s") {
        uniform_int_distribution<int> distribution(3, 5);
        roomNumber = distribution(gen);
    } else if (sizeResult == "m") {
        uniform_int_distribution<int> distribution(6, 11);
        roomNumber = distribution(gen);
    } else if (sizeResult == "l") {
        uniform_int_distribution<int> distribution(12, 20);
        roomNumber = distribution(gen);
    } else if (sizeResult == "c") {
        roomNumber = get_int_from_user("How many rooms do you want in your dungeon: ");
        correct = 0;
        while (correct == 0) {
            cout << "is " << roomNumber << " the number of rooms you want? Enter (y for yes or n for no): ";
            string valInput = get_yes_no();
            if (valInput == "y") {
                correct = 1;
            } else {
                roomNumber = get_int_from_user("How many rooms do you want in your dungeon: ");
            }
        }
    }
    genDungeon.set_size(roomNumber);
    genDungeon.generate_dungeon();
    cout << genDungeon.get_name() << " has been generated" << endl;

    //TOM CODE v

    //TOM CODE ^
}

void save_dungeon(Dungeon &dungeon) {
    vector<string> saveData = dungeon.get_save_dungeon_data();
    ofstream outFile("../src/DungeonSaves.csv", ios::app);
    if (outFile.is_open()) {
        for (const auto &part : saveData) {
            outFile << part << ",";
        }
        outFile << endl;
        outFile.close();
    } else {
        cout << "Unable to open save file" << endl;
    }
}

void load_dungeon(Dungeon &dungeon) {
    vector<string> fileData;
    ifstream inFile("../src/DungeonSaves.csv");
    if (inFile.is_open()) {
        string saveLine;
        while (getline(inFile, saveLine)) {
            fileData.push_back(saveLine);
        }
        inFile.close();
    } else {
        cout << "Unable to open save file" << endl;
    }
    vector<vector<string>> allFileData;
    vector<string> saveData;
    for (string save : fileData) {
        saveData = dungeon.split_string(save, ',');
        allFileData.push_back(saveData);
    }
    vector<string> valAnsLoad;
    cout << "Currect Saves:" << endl;
    int i = 0;
    for (vector<string> save : allFileData) {
        cout << "Name: " << save[0] << " Size: " << save[1] << " (enter " << i << ")" << endl;
        valAnsLoad.push_back(to_string(i));
        i++;
    }
    valAnsLoad.push_back("s");
    cout << "If you want to return to the Save/Load Menu (enter s)\nEnter: ";
    string loadResult = get_valid_answer(valAnsLoad);
    if (loadResult == "s") {
        return;
    }
    for (int x = 0; x < valAnsLoad.size(); x++) {
        if (loadResult == valAnsLoad[x]) {
            dungeon.load_dungeon_data(allFileData[x]);
            cout << dungeon.get_name() << " is loaded in!" << endl;
            break;
        }
    }
}

void transfer_dungeon(Dungeon &dungeon) {
    vector<string> saveData = dungeon.get_save_dungeon_data();
    ofstream outFile("../src/DungeonTransfer.csv");
    if (outFile.is_open()) {
        for (const auto &part : saveData) {
            outFile << part << ",";
        }
        outFile << endl;
        outFile.close();
    } else {
        cout << "Unable to open save file" << endl;
    }
}

string get_yes_no() {
    string input_char;
    // correct variable used to ensure that the while loop still runs until a correct input has been entered
    int correct = 0;
    while (correct == 0) {
        // Getting the input from the user
        getline(cin, input_char);
        if (input_char.size() > 1) { // If the size of the input is greater than 1 then will reprompt the user
            cout << "Invalid input. Enter a single character (y or n): ";
        } else if (input_char != "y" && input_char != "n") {
            cout << "Invalid input. Enter a single character (y or n): ";
        } else if (input_char == "" || input_char == " ") { // If the input is white space or nothing then will reprompt the user
            cout << "No input. Enter a single character (y or n): ";
        } else { // Marking as the input being within the correct parameters the loop then exits
            correct = 1;
        }
    }
    return input_char;
}

string get_valid_answer(vector<string> vecAnswers) {
    string strAnswer;
    for (const auto& str : vecAnswers) {
        strAnswer += str;
        strAnswer += ", ";
    }

    string inputChar;
    // correct variable used to ensure that the while loop still runs until a correct input has been entered
    int correct = 0;
    while (correct == 0) {
        // Getting the input from the user
        getline(cin, inputChar);
        auto inputVal = find(vecAnswers.begin(), vecAnswers.end(), inputChar);
        if (inputChar.size() > 1) { // If the size of the input is greater than 1 then will reprompt the user
            cout << "Invalid input. Enter " << strAnswer << "\n Enter: ";
        } else if (inputVal == vecAnswers.end()) {
            cout << "Invalid input. Enter " << strAnswer << "\n Enter: ";
        } else if (inputChar == "" || inputChar == " ") { // If the input is white space or nothing then will reprompt the user
            cout << "No input. Enter " << strAnswer << "\n Enter: ";
        } else { // Marking as the input being within the correct parameters the loop then exits
            correct = 1;
        }
    }
    return inputChar;
}

int get_int_from_user(string prompt) {
    stringstream ss;
    cout << prompt;
    string input_int;
    // Using a Boolean to declare if the input is an integer
    bool int_true = true;
    // correct variable used to ensure that the while loop still runs until a correct input has been entered
    int correct = 0;
    while (correct == 0) {
        // Getting the input from the user
        getline(cin, input_int);
        for (char ch : input_int) { // Progressing through the input character by character and checking if each character is a digit and or a dash. If so stops the for Loop and sets int_true as false
            if (!(isdigit(ch)) && (ch != '-')) {
                int_true = false;
                break;
            }
        }
        if (int_true == false) { // If int_true is false then reprompts the user and resets int_true
            cout << "Invalid input. Enter a number:";
            int_true = true;
        } else if (input_int == "" || input_int == " ") { // If the input is white space or nothing then will reprompt the user
            cout << "No input. Enter a number: ";
        } else {
            correct = 1;
        }
    }
    int result;
    // Converts input into an integer
    ss << input_int;
    ss >> result;
    return result;
}

string get_sentence_from_user(string prompt) {
    // NOTE: a sentence does NOT need punctuation or syntax validation
    cout << prompt;
    string input_sentence;
    // correct variable used to ensure that the while loop still runs until a correct input has been entered
    int correct = 0;
    while (correct == 0) {
        // Getting the input from the user
        getline(cin, input_sentence);
        if (input_sentence == "" || input_sentence == " ") { // If the input is just white space or nothing then will reprompt the user
            cout << "No input. Enter a sentence: ";
        } else {
            correct = 1;
        }
    }
    return input_sentence;
}