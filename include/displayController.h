/**
 * \file displayController.h
 * 
 * \brief This file contains the implementation of the DisplayController class.
*/

#pragma once
#include "main.h"

/**
 * \brief Enum representing all possible autonomous modes.
*/
enum AUTON_MODE {
    AUTO_RED_1,
    AUTO_RED_2,
    AUTO_BLUE_1,
    AUTO_BLUE_2,
    AUTO_SIMPLE,
    AUTO_DEPLOY,
    NONE
};

/**
 * \brief Enum representing all possible log levels.
*/
enum LOGGING_LEVEL {
    LOG,
    WARNING,
    ERROR
};

/**
 * \brief Enum representing all possible display modes.
*/
enum DISPLAY_MODE {
    SELECTOR, // The autonomous selector
    CONFIRM, // Shows the autonomous selected
    MATCH, // The mode to display during a match
    DEBUG // The debug mode
};

/**
 * \brief Sets the current autonomous mode.
 * @param mode The new autonomous mode.
*/
void setAutonMode(AUTON_MODE mode);

/**
 * \brief Get the current autonomous mode.
*/
AUTON_MODE getAutonMode();

/**
 * \brief PROS task to update the fixed messages on the display.
*/
void updateFixedMessages(void* param);

/**
 * \brief Safely formats a string similarly to printf, accepting varriables
 * @param format The format of the string.
 * @param args The variables to substitute in the format string.
 * @return The final formatted string with the variables subsituted.
*/
template <typename... Args>
std::string formatString(const std::string &format, Args... args);

/**
 * \brief Fixed format to retain debug info.
*/
class FixedDebugInfo {
    public:
        /**
         * \brief Constructor for fixed_debug_info.
         * @param format The format string.
         * @param callback The callback function.
         * @param type The type of callback.
        */
        FixedDebugInfo(const std::string& format, void* callback, char type);

        /**
         * \brief Convert the type to a string.
         * @return The type as a string.
        */
        std::string getLabel();

        std::string format;
        void* callback;
        char type;
};

/**
 * \brief The display controller class, which manages the V5 display. 
*/
class DisplayController {
    public:
        /**
         * \brief Constructor for the DisplayController class.
        */
        DisplayController();

        /**
         * \brief Gets the current display mode.
        */
        DISPLAY_MODE getMode();

        /**
         * \brief Changes the current display mode.
         * @param newMode The new display mode.
        */
        void setMode(DISPLAY_MODE newMode);

        /**
         * \brief Start debug mode, which prints statements to the console.
        */
        void startDebugMode();

        /**
         * \brief Log a message.
         * @param message The message to log.
         * @param level The logging level, which defaults to LOG.
        */
        void logMessage(std::string message, LOGGING_LEVEL level = LOG);

        /**
         * \brief Clear all logs.
        */
        void clearLogs();

        /**
         * \brief Prints a fixed format debug message.
         * @param format The format string.
         * @param type The type of callback.
         * @param callback The callback function.
        */
        void addFixedMessage(std::string format, char type, void* callback);
    
    private:
        static bool initialized;
        DISPLAY_MODE mode;

        /**
         * \brief Render a button on the display.
         * @param x The x coordinate of the button.
         * @param y The y coordinate of the button.
         * @param width The width of the button.
         * @param height The height of the button.
         * @param text The text to display on the button.
         * @param action The action when the button is pressed.
         * @param relStyle The style of the button when released.
         * @param host The host object of the button.
         * @return A pointer to the button.
        */
        lv_obj_t* renderButton(
            int id, 
            int x, 
            int y, 
            int width, 
            int height, 
            std::string text, 
            lv_action_t action, 
            lv_style_t *relStyle, 
            lv_obj_t *host
        );
        
        /**
         * \brief Render a text label on the display.
         * @param x The x coordinate of the label.
         * @param y The y coordinate of the label.
         * @param text The text to display on the label.
         * @param style The style of the label.
         * @param host The host object of the label..
         * @return A pointer to the label.
        */
        lv_obj_t* renderLabel(
            std::string text,
            int x,
            int y,
            lv_obj_t* host
        );

        /**
         * \brief Render a warning on the display.
         * @param message The message to display as the warning.
        */
        void renderWarning(std::string message);

        /**
         * \brief Render a error message on the display.
         * @param message The message to display as the error message.
        */
        void renderError(std::string message);

        /**
         * \brief Render a debug message on the display.
         * @param message The message to display as the debug message.
        */
        void renderDebug(std::string message);

        /**
         * \brief Initialize the style of the display.
         * @param hue The hue of the style.
         * @param borderColor The border color of the style.
         * @param mainColor The main color of the style.
         * @param borderWidth The border width of the style.
         * @return A pointer to the style of the display.
        */
        lv_theme_t* initTheme(int hue, lv_color_t borderColor, lv_color_t mainColor, int borderWidth);
};