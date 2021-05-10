#include "fileio.hh"
#include <fstream>

bool FileIO::load_file(std::vector<std::string> &content, std::string &filepath) {
	std::ifstream myfile(filepath);

	std::string line;

	while(std::getline(myfile, line)) {
		content.push_back(line);
	}

	myfile.close();
	return content.empty();
}

bool FileIO::save_file(std::vector<std::string> &content, std::string &filepath, bool truncate) {
	std::ios_base::open_mode file_flag;
	if(truncate) {
		file_flag = std::ios::trunc;
	} else {
		file_flag = std::ios::app;
	}

	std::ofstream myfile(filepath, file_flag);
	for(std::string line : content) {
		myfile << line + "\n";
	}
		
	myfile.close();
	return true;
}

