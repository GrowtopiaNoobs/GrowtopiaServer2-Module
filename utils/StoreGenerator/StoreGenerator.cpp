#include "StoreGenerator.hpp"

StoreGenerator* StoreGenerator::set_description_text(std::string text) {
	retVal += "set_description_text|" + text + "\n";
	return this;
}


StoreGenerator* StoreGenerator::add_button(std::string dataID, std::string name, std::string texture, std::string description, int textureX, int textureY, int price, int price2, std::string text2) {
	retVal += "add_button|" + dataID + "|" + name + "|" + texture + "|" + description + "|" + std::to_string(textureX) + "|" + std::to_string(textureY) + "|" + std::to_string(price) + "|" + std::to_string(price2) + "|" + text2 + "|\n";
	return this;
}

StoreGenerator* StoreGenerator::set_back_target(std::string target) {
	retVal += "set_back_target|" + target + "\n";
	return this;
}

std::string StoreGenerator::getData() {
	return retVal;
}

StoreGenerator::StoreGenerator() {

}

StoreGenerator::~StoreGenerator() {

}
