#include <vector>
#include <string>

struct FileIO {
	/**
	 * .txt
	 */
	static bool load_file(std::vector<std::string> &content, std::string &filepath);

	/**
	 * .txt
	 */
	static bool save_file(std::vector<std::string> &content, std::string &filepath, bool truncate);
};
