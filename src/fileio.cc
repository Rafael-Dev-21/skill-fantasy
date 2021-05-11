#include "fileio.hh"
#include <fstream>

bool FileIO::load_file(std::vector<std::string> &cont, std::string &path) {
	if(path == "") return false;

	std::ifstream source(path);

	if(source.eof()) return false;

	std::string line;

	while(std::getline(source, line)) {
		if(line == "") continue;
		cont.push_back(line);
	}

	if(cont.empty()) return false;

	return true;
}

bool FileIO::save_file(std::vector<std::string> &cont, std::string &path, bool trunc) {
	if(cont.empty()) return false;

	std::ios_base::openmode openflag;
	if(trunc) {
		openflag = std::ios::trunc;
	} else {
		openflag = std::ios::app;
	}

	std::ofstream target(path, openflag);

	if(!target.is_open()) return false;

	for(std::string i : cont) {
		target << i + "\n";
	}

	target.close();

	return true;
}
