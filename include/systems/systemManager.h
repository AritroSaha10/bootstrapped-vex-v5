/**
 * \file systemManager.h
 * 
 * \brief Contains headers for the SystemManager abstract class.
*/

#pragma once
#include "main.h"

/**
 * \brief Base class for a system manager. 
*/
class SystemManager {
    public:
        /**
         * All possible states for the system.
        */
        enum STATE {
            DISABLED_STATE = (uint8_t) 0x00,
            RESET_STATE = (uint8_t) 0x01,
            OPERATOR_OVERRIDE = (uint8_t) 0x20
        };

        /**
         * Constructor for the SystemManager class
         * @param defaultState The default state for the system.
        */
        SystemManager(STATE defaultState);
        
        /**
         * Gets the current target value.
         * @return The current target value.
        */
        double getTarget() { return this->target; };

        /**
         * Gets the current error value from the target.
         * @return The current error value.
        */
        double getError() { return this->error; };

        /**
         * Gets the current position of the system.
         * @return The current position.
        */
        double getPosition() { return this->position; };

        /**
         * Gets the amount of power provided to the system.
         * @return The current amount of power provided.
        */
        double getPower() { return this->power; };

        /**
         * Gets the current state of the system.
         * @return The current state.
        */
        STATE getState() { return this->state; };

        /**
         * Returns whether the system is enabled or not.
         * @return Whether the state is enabled or not.
        */
        bool enabled() { return this->state != DISABLED_STATE; };

        /**
         * Toggle the state of the system to RESET.
        */
        void reset();

        /**
         * Enable the machine, allowing for the current state to be changed.
        */
        void enable();

        /**
         * Disable the machine, prohibiting the current state to be changed.
        */
        void disable();

        /**
         * Revert the state to what it previously was.
        */
        void revertState();

        /**
         * The control loop for the system. This should be run every loop.
        */
        virtual void update();

        /**
         * Run a full reset of the system and its variables and state.
        */
        virtual void fullReset();

    protected:
        /**
         * The current target of the system.
        */
        double target;

        /**
         * The current error of the system from the desired target.
        */
        double error;

        /**
         * The current position of the system.
        */
        double position;

        /**
         * The current amount of power being provided of the system.
        */
        double power;

        /**
         * The last time that a change was made to the state of the system.
        */
        uint32_t timeOfLastChange = 0;

        /**
         * The previous state of the system.
        */
        STATE lastState = DISABLED_STATE;

        /**
         * The current state of the system.
        */
        STATE state = DISABLED_STATE;

        /**
         * The default state of the system.
        */
        STATE defaultState;

        /**
         * Sets the state of the system.
         * @param newState The new state of the system.
         * @return True if the system was enabled, and false if it was disabled.
        */
        virtual bool changeState(STATE newState);

        /**
         * Sets the state of the system, alias to changeState()
         * @param newState The new state of the system.
         * @return True if the system was enabled, and false if it was disabled.
        */
        bool operator=(STATE newState);

        /**
         * Checks whether the last change of state was made during a specific period of time.
         * @param timeout The amount of milliseconds after the last state change.
         * @return True if the system state was changed before the time period, False if not.
        */
        bool timedOut(uint32_t timeout);
};