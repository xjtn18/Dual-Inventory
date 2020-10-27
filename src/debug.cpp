#include "debug.h"



namespace mystd {

	void shclear(){
		if (kRefresh){
			system(CLEAR_SHELL_COMMAND);
		}
	}



	void catfile(std::string filename){
		shclear();
		std::ifstream f;
		f.open(filename);
		std::cout << f.rdbuf();
		f.close();
	}



	std::vector<std::string> splitOnSpace(std::string s){
		// split function like the one python has
		std::vector<std::string> tVec; // token vector
		size_t pos = s.find(" ");
		std::string token;

		if (pos == std::string::npos){
			tVec.push_back(s);
		}

		while (pos != std::string::npos){
			if (isspace(s[0])) {
				s.erase(0, 1);
				continue;
			}
			pos = s.find(" "); // TODO: what if there another type of whitespace after the word?
			token = s.substr(0, pos);
			tVec.push_back(token);
			s.erase(0, pos + 1); // 1 being the length of a single space
		}

		return tVec;
	}
}




