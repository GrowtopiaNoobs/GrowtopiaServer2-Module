#include <iostream>
#include <map>
#include <vector>
#include <string>

namespace DialogParaser {
	std::vector<std::string> strSplit(std::string str, std::string token){
		std::vector<std::string> result;
		while(str.size()){
			int index = str.find(token);
			if(index!=std::string::npos){
				result.push_back(str.substr(0,index));
				str = str.substr(index+token.size());
				if(str.size()==0)result.push_back(str);
			}else{
				result.push_back(str);
				str = "";
			}
		}
		return result;
	}

	std::map<std::string, std::string> strMap(std::vector<std::string> parts, std::string token) {
		std::map<std::string, std::string> results;
		for (auto const& s : parts) {
			std::vector<std::string> segment = strSplit(s, token);
			if (segment.size() < 2) {
				if (segment.size() != 0 && segment[0] != "") {
					std::cout << "Not enough string parts for " + s << std::endl;
				}
				continue;
			}
			if (segment.size() > 2) {
				std::cout << "Unhandled string part for " + s << std::endl;
			}
			results[segment[0]] = segment[1];
		}
		return results;
	}
}

std::map<std::string, std::string> paraseDialog(std::string text) {
	using namespace DialogParaser;
	return strMap(strSplit(text, "\n"), "|");
}


#include "DialogParaser.cpp"
