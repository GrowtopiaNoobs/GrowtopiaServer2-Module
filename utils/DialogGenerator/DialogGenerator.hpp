#pragma once
#include <string>

class DialogGenerator {
protected:
	std::string retVal;

public:
	DialogGenerator* set_default_color(std::string color);

	DialogGenerator* add_label(std::string size, std::string text, std::string position);

	DialogGenerator* add_label_with_icon(std::string size, std::string text, std::string position, int itemID);

	DialogGenerator* add_smalltext(std::string text, std::string position);

	DialogGenerator* add_textbox(std::string text, std::string position);

	DialogGenerator* add_text_input(std::string dataID, std::string text, std::string preSetValue, int maxLength);

	DialogGenerator* add_checkbox(std::string dataID, std::string text, int preSetValue);

	DialogGenerator* add_player_picker(std::string dataID, std::string text);

	DialogGenerator* add_player_info(std::string playerName, int level, int currentXP, int nextLvlXP);

	DialogGenerator* add_achieve(std::string achieveName, std::string progress, std::string position, int achieveId);

	DialogGenerator* add_achieve_button(std::string achieveName, std::string progress, std::string position, int achieveId);

	DialogGenerator* text_scaling_string(std::string text);

	DialogGenerator* add_spacer(std::string size);

	DialogGenerator* add_quick_exit();

	DialogGenerator* add_button(std::string dataID, std::string text, std::string flags, int val1, int val2);

	DialogGenerator* add_button_with_icon(std::string dataID, std::string text, std::string flags, int itemID);

	DialogGenerator* embed_data(std::string dataID, std::string value);

	DialogGenerator* end_dialog(std::string dataID, std::string cancel, std::string text);

	std::string getData();
	
	DialogGenerator();

	~DialogGenerator();
};

#include "DialogGenerator.cpp"
