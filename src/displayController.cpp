#include "displayController.h"
#include "globals.h"
#include "sdReadUtil.h"
#include <string>
#include <tuple>
#include <map>
#include <vector>

/**
 * \brief The dimensions of any button on the display in format Width, Height.
*/
const std::tuple<int, int> buttonDimensions(200, 60);

/**
 * \brief The maximum number of images allowed on the display.
*/
const int maxMessages = 7;

/**
 * \brief The current selected autonomous route.
*/
AUTON_MODE selectedMode = AUTO_DEPLOY;

/**
 * \brief All colors to use on the display.
*/
const std::map<std::string, lv_color_t> colors {
    {"red", LV_COLOR_MAKE(234, 35, 58)},
    {"blue", LV_COLOR_MAKE(41, 130, 198)},
    {"purple", LV_COLOR_MAKE(88, 36, 133)},
    {"grey", LV_COLOR_MAKE(69, 69, 69)},
    {"yellow", LV_COLOR_MAKE(255, 210, 72)},
    {"white", LV_COLOR_MAKE(255, 255, 255)}
};

/**
 * \brief All possible 
/**
 * \brief All the log messages and their respective data.
*/
std::vector<lv_obj_t*> logMessages;

/**
 * \brief Any log messages that should not be removed
*/
std::vector<lv_obj_t*> fixedMessages;

/**
 * \brief Data for the fixed messages,
*/
std::vector<FixedDebugInfo> fixedMessageData;

// Pop-up / message box style
lv_style_t mBoxStyle;

// All button styles
lv_style_t redStyle;
lv_style_t blueStyle;
lv_style_t neutralStyle;
lv_style_t logStyle;
lv_style_t warningStyle;

// Page style
lv_style_t pageStyle;

// Page themes
lv_theme_t* mainTheme;
lv_theme_t* coloredBg;
lv_theme_t* borderless;

// Page object
static lv_obj_t* scr;

// List object to store messages
lv_obj_t* messageList;

/**
 * \brief Button callback when an autonomous mode is selected.
 * @param btn The button that was clicked.
*/
static lv_res_t autonSelected(lv_obj_t* btn) {
    int autoID = lv_obj_get_free_num(btn);
    setAutonMode((AUTON_MODE) autoID);
    display.setMode(CONFIRM);

    return LV_RES_OK;
}

/**
 * \brief LVGL Button callback that does nothing.
 * @param btn The button that was clicked.
*/
static lv_res_t nullButtonCallback(lv_obj_t* btn) {
    return LV_RES_OK;
}

void setAutonMode(AUTON_MODE mode) {
    selectedMode = mode;
}

AUTON_MODE getAutonMode() {
    return selectedMode;
}

void updateFixedMessages(void* param) {
    while (true) {
        // Update the fixed messages
        for (int i = 0; i < fixedMessageData.size(); i++) {
            lv_label_set_text(lv_obj_get_child(fixedMessages[i], NULL), fixedMessageData[i].getLabel().c_str());
        }
        pros::delay(20);
    }
}

/**
 * Create a LVGL style given a list of parameters
 * @param mainColor The main color
 * @param auxColor The auxiliary color
 * @param radius The radius of the round corners
 * @param borderWidth The width of the border
 * @param borderColor The color of the border
 * @param padHorizontal The horizontal padding
 * @param padVertical The vertical padding
 * @param padInner The inner padding
 * @param shadowWidth The width of the shadow
 * @param shadowColor The color of the shadow
 * @param textColor The color of the text
*/
lv_style_t createStyle(lv_color_t mainColor, lv_color_t auxColor, int radius, int borderWidth, lv_color_t borderColor, int padHorizontal, int padVertical, int padInner, int shadowWidth, lv_color_t shadowColor, lv_color_t textColor) {
    lv_style_t tmpStyle;

    // Set up the red style
    lv_style_copy(&tmpStyle, &lv_style_plain_color);

    // Set main and aux colors
    tmpStyle.body.main_color = mainColor;
    tmpStyle.body.grad_color = auxColor;

    // Set radius
    tmpStyle.body.radius = radius;

    // Set border
    tmpStyle.body.border.width = borderWidth;
    tmpStyle.body.border.color = borderColor;

    // Set padding
    tmpStyle.body.padding.ver = padVertical;
    tmpStyle.body.padding.hor = padHorizontal;
    tmpStyle.body.padding.inner = padInner;

    // Set shadow
    tmpStyle.body.shadow.width = shadowWidth;
    tmpStyle.body.shadow.color = shadowColor;
    tmpStyle.text.color = textColor;

    return tmpStyle;
}
    

template <typename... Args>
std::string formatString(const std::string &format, Args... args) {
    // Calculate the size of formatted string, add one for \0
    size_t formattedSize = snprinf(nullptr, 0, format.c_str(), args...) + 1;
    if (formattedSize < 1) {
        throw std::runtime_error("Error during formatting.");
    }

    // Return the formatted string
    std::unique_ptr<char[]> buf(new char[formattedSize]);
    snprintf(buf.get(), formattedSize, format.c_str(), args...); 
    return std::string(buf.get(), buf.get() + formattedSize - 1); // Exclude \0 from string
}

FixedDebugInfo::FixedDebugInfo(const std::string& format, void* callback, char type) {
    this->format = format;
    this->callback = callback;
    this->type = type;
}

std::string FixedDebugInfo::getLabel() {
    std::string output;
    switch (this->type) {
        case 'i':
            output = std::to_string(*(int*)this->callback);
            break;
        case 'd':
            output = std::to_string(*(double*)this->callback);
            break;
        case 's':
            output = *(std::string*)this->callback;
            break;
        default:
            output = std::to_string(*(double*)this->callback);
            break;
    }
    return this->format + output;
}

bool DisplayController::initialized = false;

DisplayController::DisplayController() {
    // Don't initialize twice
    if (initialized) {
        return;
    }

    initialized = true;

    // Set up the styles
    redStyle = createStyle(colors.at("red"), colors.at("red"), 4, 2, colors.at("white"), 5, 5, 0, 0, colors.at("red"), colors.at("white"));
    blueStyle = createStyle(colors.at("blue"), colors.at("blue"), 4, 2, colors.at("white"), 5, 5, 0, 0, colors.at("red"), colors.at("white"));
    neutralStyle = createStyle(colors.at("purple"), colors.at("purple"), 4, 2, colors.at("white"), 5, 5, 0, 0, colors.at("red"), colors.at("white"));
    logStyle = createStyle(colors.at("grey"), colors.at("grey"), 4, 2, colors.at("white"), 5, 5, 0, 0, colors.at("red"), colors.at("white"));
    warningStyle = createStyle(colors.at("yellow"), colors.at("yellow"), 4, 2, colors.at("white"), 5, 5, 0, 0, colors.at("red"), colors.at("black"));
    mBoxStyle = createStyle(colors.at("white"), colors.at("white"), 4, 2, colors.at("white"), 5, 5, 0, 0, colors.at("red"), colors.at("black"));

    // Set up the theme
    coloredBg = initTheme(10, colors.at("purple"), colors.at("purple"), 0);
}

DISPLAY_MODE DisplayController::getMode() {
    return this->mode;
}

void DisplayController::setMode(DISPLAY_MODE mode) {
    this->mode = mode;

    // Clean the screen
    lv_obj_clean(scr);

    // Create and load a new page
    scr = lv_page_create(NULL, NULL);
    lv_scr_load(scr);
    lv_page_set_sb_mode(scr, LV_SB_MODE_OFF);

    // Set the theme
    lv_theme_set_current(coloredBg);

    // Display the correct page based on the mode variable
    switch (mode) {
        // Display mode: Autonomous selection
        case SELECTOR: {
            // Render all of the buttons for each autonomous mode, to future readers: change this to reflect your respective auton routines
            // TODO: Make this generate itself from a data struct?

            // Autonomous Red 1
            renderButton(
                AUTO_RED_1, 
                LV_HOR_RES / 2, 
                0, 
                std::get<0>(buttonDimensions),
                std::get<1>(buttonDimensions),
                "Protected Zone\n(5-point)",
                autonSelected,
                &redStyle,
                scr
            );

            // Autonomous Red 2
            renderButton(
                AUTO_RED_2, 
                0, 
                20, 
                std::get<0>(buttonDimensions),
                std::get<1>(buttonDimensions),
                "Unprotected Zone\n(5-point)",
                autonSelected,
                &redStyle,
                scr
            );

            // Autonomous Blue 1
            renderButton(
                AUTO_BLUE_1, 
                0, 
                LV_VER_RES - 80, 
                std::get<0>(buttonDimensions),
                std::get<1>(buttonDimensions),
                "Unprotected Zone\n(5-point)",
                autonSelected,
                &blueStyle,
                scr
            );

            // Autonomous Blue 2
            renderButton(
                AUTO_BLUE_2, 
                LV_HOR_RES / 2, 
                LV_VER_RES - 80, 
                std::get<0>(buttonDimensions),
                std::get<1>(buttonDimensions),
                "Protected Zone\n(5-point)",
                autonSelected,
                &blueStyle,
                scr
            );

            // Autonomous Blue 2
            renderButton(
                AUTO_BLUE_2, 
                LV_HOR_RES / 2, 
                LV_VER_RES - 80, 
                std::get<0>(buttonDimensions),
                std::get<1>(buttonDimensions),
                "Protected Zone\n(5-point)",
                autonSelected,
                &blueStyle,
                scr
            );

            // Simple autonomous (one ball)
            renderButton(
                AUTO_SIMPLE, 
                LV_HOR_RES / 2, 
                LV_VER_RES / 2 - 30, 
                std::get<0>(buttonDimensions),
                std::get<1>(buttonDimensions),
                "One Ball",
                autonSelected,
                &neutralStyle,
                scr
            );

            // Deploy the routine
            renderButton(
                AUTO_DEPLOY, 
                0, 
                LV_VER_RES / 2 - 30, 
                std::get<0>(buttonDimensions),
                std::get<1>(buttonDimensions),
                "Deploy",
                autonSelected,
                &neutralStyle,
                scr
            );

            break;
        }

        // Display mode: Show the autonomous mode selected
        case CONFIRM: {
            AUTON_MODE autoID = getAutonMode();
            std::string autoName;

            // Get the current autonomous name based on the ID
            switch (autoID) {
                case (AUTO_RED_1):
                    autoName = "Red Protected Routine";
                    break;
                case (AUTO_RED_2):
                    autoName = "Red Unprotected Routine";
                    break;
                case (AUTO_BLUE_1):
                    autoName = "Blue Protected Routine";
                    break;
                case (AUTO_BLUE_2):
                    autoName = "Blue Unprotected Routine";
                    break;
                case (AUTO_SIMPLE):
                    autoName = "One Cube Routine";
                    break;
                case (AUTO_DEPLOY):
                    autoName = "Deploy Routine";
                    break;
                default:
                    autoName = "Unknown Routine Selected";
                    break;
            }

            // Render the text on the screen
            renderButton(-1, 80, 50, 150, 300, autoName, nullButtonCallback, &neutralStyle, scr);
            break;
        }

        // Display mode: Show the royals logo during the match
        case MATCH: {
            // Setup the read driver
            lv_fs_drv_t pcfs_drv;
            memset(&pcfs_drv, 0, sizeof(lv_fs_drv_t));

            // Set the driver callback functions
            pcfs_drv.file_size = sizeof(SDReadUtil::pc_file_t);
            pcfs_drv.letter = 'S';
            pcfs_drv.open = SDReadUtil::pcfs_open;
            pcfs_drv.close = SDReadUtil::pcfs_close;
            pcfs_drv.read = SDReadUtil::pcfs_read;
            pcfs_drv.seek = SDReadUtil::pcfs_seek;
            pcfs_drv.tell = SDReadUtil::pcfs_tell;
            lv_fs_add_drv(&pcfs_drv);

            // Get the image from the SD card and display it
            lv_obj_t *img_var = lv_img_create(lv_scr_act(), NULL);
            lv_img_set_src(img_var, "S:/usd/royals_logo.bin");
            lv_obj_set_size(img_var, LV_HOR_RES, LV_VER_RES);
            lv_obj_set_pos(img_var, 0, -10);

            // Display the messagel list
            messageList = lv_list_create(lv_scr_act(), NULL);
            lv_obj_set_width(messageList, LV_HOR_RES - 40);
            break;
        }

        // Debug mode: First and only mode to be run
        case DEBUG: {
            // Create the message list
            messageList = lv_list_create(lv_scr_act(), NULL);
            lv_obj_set_width(messageList, LV_HOR_RES - 40);

            // Display each message
            for (int i = 0; i < fixedMessageData.size(); i++) {
                fixedMessages.push_back(lv_list_add(messageList, NULL, fixedMessageData[i].getLabel().c_str(), nullButtonCallback));
                this->logMessage(std::to_string(lv_obj_count_children(fixedMessages[i])), ERROR);
                lv_obj_set_style(fixedMessages[i], &logStyle);
            }

            // Create a task to continuously update the messages
            pros::Task updateMessages(updateFixedMessages, (void*) "PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Updating Messages");
            break;
        }
    }
}

void DisplayController::logMessage(std::string message, LOGGING_LEVEL level) {
    if (this->mode != DEBUG && level != ERROR) {
        // Don't log the error if it's not critical and we're not in debug mode
        return;
    }

    lv_obj_t* newMsg = lv_list_add(messageList, NULL, message.c_str(), nullButtonCallback);

    lv_style_t messageStyle;
    switch (level) {
        case WARNING: {
            lv_btn_set_style(newMsg, LV_BTN_STYLE_REL, &warningStyle);
            break;
        }
        case ERROR: {
            lv_btn_set_style(newMsg, LV_BTN_STYLE_REL, &redStyle);
            break;
        }
        default: {
            lv_btn_set_style(newMsg, LV_BTN_STYLE_REL, &logStyle);
            break;
        }
    }

    logMessages.push_back(newMsg);

    if (logMessages.size() + fixedMessages.size() > maxMessages) {
        lv_obj_del(logMessages[0]);
    }
}

void DisplayController::clearLogs() {
    for (lv_obj_t* i : logMessages) {
        lv_obj_del(i);
    }
}

void DisplayController::addFixedMessage(std::string format, char type, void* callback) {
    fixedMessageData.push_back(FixedDebugInfo(format, callback, type));
}

lv_obj_t* DisplayController::renderButton(int id, int x, int y, int width, int height, std::string text, lv_action_t action, lv_style_t *relStyle, lv_obj_t *host) {
    lv_cont_set_fit(host, false, false); // Disable all fits
    lv_obj_t* button = lv_btn_create(host, NULL);

    // Set the size and position
    lv_obj_set_size(button, width, height);
    lv_obj_set_pos(button, x, y);

    // Set the ID, style, and callback
    lv_obj_set_free_num(button, id);
    lv_btn_set_style(button, LV_BTN_STYLE_REL, relStyle);
    lv_btn_set_action(button, LV_BTN_ACTION_CLICK, action);

    // Set the label for the button
    lv_obj_t* buttonLabel = renderLabel(text, 0, 0, button);
    lv_obj_align(buttonLabel, button, LV_ALIGN_CENTER, 0, 0);

    return button;
}

lv_obj_t* DisplayController::renderLabel(std::string text, int x, int y, lv_obj_t* host) {
    lv_obj_t* label = lv_label_create(host, NULL);
    lv_obj_align(label, host, LV_LABEL_ALIGN_CENTER, x, y); // Align to the center of the parent
    lv_label_set_text(label, text.c_str()); // Set the text

    return label;
}

lv_theme_t* DisplayController::initTheme(int hue, lv_color_t borderColor, lv_color_t mainColor, int borderWidth) {
    lv_theme_t* theme = lv_theme_alien_init(hue, NULL);

    theme->win.bg->body.border.color = LV_COLOR_WHITE;
    theme->win.bg->body.border.width = borderWidth;
    theme->win.bg->body.border.color = borderColor;
    theme->win.bg->body.main_color = mainColor;
    theme->win.bg->body.grad_color = mainColor;

    return theme;
}