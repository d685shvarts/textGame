#include "Character.hpp"
#include "Inventory.hpp"
#include "Menu.hpp"
#include <iostream>
#include <string>
#include <limits>

using std::streamsize;
using std::cin;
using std::string;
using std::endl;
using std::cout;



Character::Character() {
    cout << "Initializing Character" << endl;
    this->health = 100;
    this->thirst = this->hunger = 0;
    this->currentLocation = nullptr;
    this->alive = true;
    this->wonGame = false;
    this->inventory = new Inventory();
}

Character::~Character() {
    delete this->inventory;
}

void Character::characterMenu() {
    cout << endl;
    int menuChoice,
        inventoryChoice;
    cout << "Please select a choice by entering the corresponding integer" << endl;
    cout << "1. Interact with location" << endl;
    cout << "2. Quit game" << endl;
    validateInt(&menuChoice, 1, 3);
    if (menuChoice == 1) {
        this->currentLocation->spaceMenu();
    }
    else {
        this->alive = false;
    }
}

bool Character::getAlive() {
    return this->alive;
}

void Character::setAlive(bool alive) {
    this->alive = alive;
}

Inventory* Character::getInventory() {
    return inventory;
}

void Character::setLocation(Space* location) {
    this->currentLocation = location;
}

void Character::printCharacterStats() {
    cout << endl;
    cout << "Your health is: " << this->health << "/100" << endl;
    cout << "You thirst is: " << this->thirst << "/100" << endl;
    cout << "You hunger is: " << this->hunger << "/100" << endl;
    cout << endl;
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
}

void Character::ageCharacter() {
    if (this->health <= 0) {
        cout << "Your health has fallen to 0 or below, you have died!" << endl;
        this->alive = false;
        return;
    }
    else {
        if (this->inventory->water > 0) {
            cout << "Consuming 1 water, you thirst is back to 0" << endl;
            this->inventory->water--;
            this->thirst = 0;
        }
        else {
            cout << "You have no water, your thirst is increased!" << endl;
            this->thirst += 25;
        }

        if (this->inventory->food > 0) {
            cout << "Consuming 1 food, you hunger is back to 0" << endl;
            this->inventory->food--;
            this->hunger = 0;
        }
        else {
            cout << "You have no food, your hunger is increased!" << endl;
            this->hunger += 20;
        }

        if (this->hunger > 100) {
            cout << "You are starving. Your health has decreased!" << endl;
            this->health -= 20;
        }

        if (this->thirst > 100) {
            cout << "You are dehydrated. Your health has decreased!" << endl;
            this->health -= 25;
        }

        if (this->hunger < 100 && this->thirst < 100) {
            if (this->health < 100) {
                cout << "You are well nourished you health is restoring slowly" << endl;
                health += 20;

            }
            if (this->health > 100) {
                this->health = 100;
            }
        }

        if (this->health <= 0) {
            cout << "Your health has fallen to 0 or below! You have died!" << endl;
            this->alive = false;
        }
    }
    

    printCharacterStats();
}

void Character::interactInventory() {
    this->inventory->printInventory();
    this->inventory->exceedCapacity();
}


bool Character::getWonGame() {
    return this->wonGame;
}

void Character::printLocation() {
    this->currentLocation->printLocation();
}