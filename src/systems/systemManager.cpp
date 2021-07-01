/**
 * Implementation for the SystemManager base class.
 * 
 * Note that all getter functions (ex. getState()) can be
 * found in the header file. 
*/

#include "systems/systemManager.h"

SystemManager::SystemManager(STATE defaultState) {
    *this = defaultState;
    this->defaultState = defaultState;
    this->lastState = defaultState;
}

void SystemManager::reset() {
    *this = this->RESET_STATE;
}

void SystemManager::enable() {
    this->lastState = DISABLED_STATE;
    this->state = this->defaultState;
    this->timeOfLastChange = pros::millis();
}

void SystemManager::disable() {
    this->lastState = this->state;
    this->state = this->DISABLED_STATE;
    this->timeOfLastChange = pros::millis();
}

void SystemManager::revertState() {
    this->changeState(this->lastState);
}

void SystemManager::fullReset() {
    this->target = 0;
    this->error = 0;
    this->position = 0;
    this->power = 0;
}

bool SystemManager::changeState(STATE newState) {
    if (this->state == DISABLED_STATE) {
        return false;
    }
    this->lastState = this->state;
    this->state = newState;
    this->timeOfLastChange = pros::millis();
    return true;
}

bool SystemManager::operator=(STATE newState) {
    return this->changeState(newState);
}

bool SystemManager::timedOut(uint32_t timeout) {
    return this->timeOfLastChange + timeout < pros::millis();
}