#pragma once
#include <string>

class StoreGenerator {
protected:
	std::string retVal;

public:
	StoreGenerator* set_description_text(std::string text);

	// if price is negative, then in growtokens
	// price 2 is in video credits
	StoreGenerator* add_button(std::string dataID, std::string name, std::string texture, std::string description, int textureX, int textureY, int price, int price2, std::string text2);

	StoreGenerator* set_back_target(std::string target);

	std::string getData();
	
	StoreGenerator();

	~StoreGenerator();
};

#include "StoreGenerator.cpp"
