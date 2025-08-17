/*
 * file.cpp
 *
 *  Created on: Dec 12, 2023
 *      Author: pjarnot
 */

#include "include/file.h"

#include "assert.h"
#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <dirent.h>
#include <cstring>

using namespace std;
using namespace file;

bool file::is_path_exists(std::string ipath) {
	struct stat sb;
	return 0 == stat(ipath.c_str(), &sb);
}


std::string file::read_file(std::string ipath) {
	stringstream content;
	ifstream ifs(ipath);

	content << ifs.rdbuf();

	ifs.close();
	return content.str();
}


void file::delete_files(std::string ipath_glob) {
	stringstream command;
	command << "rm ";
	command << ipath_glob;
	system(command.str().c_str());
}

void file::delete_directories(std::string ipath_glob) {
	stringstream command;
	command << "rmdir ";
	command << ipath_glob;
	system(command.str().c_str());
}

std::vector<std::string> file::list_directory(string ipath) {
	vector<string> retval;
    DIR *dir;
    struct dirent *entry;
    stringstream entry_path;

    dir = opendir(ipath.c_str());
    if (dir == NULL) {
        perror("Error opendir()");
        return retval;
    }

    while ((entry = readdir(dir)) != NULL) {
    	if (string(".").compare(entry->d_name) != 0 && string("..").compare(entry->d_name)) {
        	entry_path.clear();
			entry_path << ipath << "/" << entry->d_name;
			retval.push_back(entry_path.str());
        }

    }
    closedir(dir);
    return retval;
}


