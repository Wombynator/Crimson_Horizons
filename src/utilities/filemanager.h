#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

void checkFileFolder(const std::string& filePath, bool isFolder, bool createIfNotExist, const std::string& downloadUrl);

#endif