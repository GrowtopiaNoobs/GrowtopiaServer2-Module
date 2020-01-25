#include "DialogGenerator.hpp"

DialogGenerator* DialogGenerator::set_default_color(std::string color) {
	retVal += "set_default_color|" + color + "\n";
	return this;
}

DialogGenerator* DialogGenerator::add_label(std::string size, std::string text, std::string position) {
	retVal += "add_label|" + size + "|" + text + "|" + position + "|\n";
	return this;
}

DialogGenerator* DialogGenerator::add_label_with_icon(std::string size, std::string text, std::string position, int itemID) {
	retVal += "add_label_with_icon|" + size + "|" + text + "|" + position + "|" + std::to_string(itemID) + "|\n";
	return this;
}

DialogGenerator* DialogGenerator::add_smalltext(std::string text, std::string position) {
	retVal += "add_smalltext|" + text + "|" + position + "|\n";
	return this;
}

DialogGenerator* DialogGenerator::add_textbox(std::string text, std::string position) {
	retVal += "add_textbox|" + text + "|" + position + "|\n";
	return this;
}

DialogGenerator* DialogGenerator::add_text_input(std::string dataID, std::string text, std::string preSetValue, int maxLength) {
	retVal += "add_text_input|" + dataID + "|" + text + "|" + preSetValue + "|" + std::to_string(maxLength) + "|\n";
	return this;
}

DialogGenerator* DialogGenerator::add_checkbox(std::string dataID, std::string text, int preSetValue) {
	retVal += "add_checkbox|" + dataID + "|" + text + "|" + std::to_string(preSetValue) + "\n";
	return this;
}

DialogGenerator* DialogGenerator::add_player_picker(std::string dataID, std::string text) {
	retVal += "add_player_picker|" + dataID + "|" + text + "|\n";
	return this;
}

DialogGenerator* DialogGenerator::add_player_info(std::string playerName, int level, int currentXP, int nextLvlXP) {
	retVal += "add_player_info|" + playerName + "|" + std::to_string(level) + "|" + std::to_string(currentXP) + "|" + std::to_string(nextLvlXP) + "|\n";
	return this;
}

DialogGenerator* DialogGenerator::add_achieve(std::string achieveName, std::string progress, std::string position, int achieveId) {
	retVal += "add_achieve|" + achieveName + "|" + progress + "|" + position + "|" + std::to_string(achieveId) + "|\n";
	return this;
}

DialogGenerator* DialogGenerator::add_achieve_button(std::string achieveName, std::string progress, std::string position, int achieveId) {
	retVal += "add_achieve_button|" + achieveName + "|" + progress + "|" + position + "|" + std::to_string(achieveId) + "|\n";
	return this;
}

DialogGenerator* DialogGenerator::text_scaling_string(std::string scaling) {
	retVal += "text_scaling_string|" + scaling + "|\n";
	return this;
}

DialogGenerator* DialogGenerator::add_spacer(std::string size) {
	retVal += "add_spacer|" + size + "|\n";
	return this;
}

DialogGenerator* DialogGenerator::add_quick_exit() {
	retVal += "add_quick_exit|\n";
	return this;
}

DialogGenerator* DialogGenerator::add_button(std::string dataID, std::string text, std::string flags, int val1, int val2) {
	retVal += "add_button|" + dataID + "|" + text + "|" + flags + "|" + std::to_string(val1) + "|" + std::to_string(val2) + "|\n";
	return this;
}

DialogGenerator* DialogGenerator::add_button_with_icon(std::string dataID, std::string text, std::string flags, int itemID) {
	retVal += "add_button_with_icon|" + dataID + "|" + text + "|" + flags + "|" + std::to_string(itemID) + "\n";
	return this;
}

DialogGenerator* DialogGenerator::embed_data(std::string dataID, std::string value) {
	retVal += "embed_data|" + dataID + "|" + value + "\n";
	return this;
}

DialogGenerator* DialogGenerator::end_dialog(std::string dataID, std::string cancel, std::string text) {
	retVal += "end_dialog|" + dataID + "|" + cancel + "|" + text + "|\n";
	return this;
}

std::string DialogGenerator::getData() {
	return retVal;
}

DialogGenerator::DialogGenerator() {

}

DialogGenerator::~DialogGenerator() {

}
