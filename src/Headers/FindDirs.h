//
// Created by pixel on 2/22/2026.
//

#ifndef FIND_DIRECTORYS_H
#define FIND_DIRECTORYS_H
#include <string>
#include <algorithm>

namespace fileSystem = std::filesystem;

std::string findDirectory(const std::string& folderDir, auto fileDir) {
    fileSystem::path parentDir = fileSystem::current_path().parent_path();
    std::string combinedDir;

    for (const auto& entry : fileSystem::recursive_directory_iterator(parentDir)) {
        if (fileSystem::is_directory(entry.path())) {
            if (entry.path().filename() == folderDir) {
                combinedDir = entry.path().string() + "\\" + fileDir;

            }
        }

    }


    return combinedDir;
}

#endif //FIND_DIRECTORYS_H