#ifndef _FILEIO_H_
#define _FILEIO_H_

#include <vector>
#include <string>

struct FileIO {
	static bool load_file(std::vector<std::string> &container, std::string &filepath);

	static bool save_file(std::vector<std::string> &container, std::string &filepath, bool trunc);
};

#endif
