/*
 * file.h
 *
 *  Created on: Dec 12, 2023
 *      Author: pjarnot
 */

#ifndef GBSC_INCLUDE_FILE_H_
#define GBSC_INCLUDE_FILE_H_

#include <string>
#include <vector>

namespace file {
	bool is_path_exists(std::string ipath);
	std::string read_file(std::string ipath);
	void delete_files(std::string ipath_glob);
	void delete_directories(std::string ipath_glob);
	std::vector<std::string> list_directory(std::string ipath);
}


#endif /* GBSC_INCLUDE_FILE_H_ */
