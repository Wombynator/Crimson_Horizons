#include "filemanager.h"
#include "logger.h"

#include <iostream>
#include <fstream>
#include <urlmon.h>
#include <windows.h>

#pragma comment(lib, "urlmon.lib")


void checkFileFolder(const std::string& filePath, bool isFolder, bool createIfNotExist, const std::string& downloadUrl) {
    bool exist = false;
    bool created = false;
    
    if (isFolder == false) {
        std::ifstream file(filePath);
        exist = file.good();
    }
    else {
        DWORD attributes = GetFileAttributesA(filePath.c_str());
        exist = (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
    }

    // Log if File or Folder was found
    if (exist == false && isFolder == false) {
        Log(MessageType::Error, "Filemanager", ("File: '" + filePath + "' not found."));
    }
    else if (exist == false && isFolder == true) {
        Log(MessageType::Error, "Filemanager", ("Folder: '" + filePath + "' not found."));
    }
    else if (exist == true && isFolder == false) {
        Log(MessageType::Info, "Filemanager", ("File: '" + filePath + "' found."));
    }
    else if (exist == true && isFolder == true) {
        Log(MessageType::Info, "Filemanager", ("Folder: '" + filePath + "' found."));
    }

    if (createIfNotExist == true && exist == false && isFolder == true) {
        // Create Folder
        std::wstring folderPath(filePath.begin(), filePath.end());
        if (CreateDirectoryW(folderPath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
            Log(MessageType::Info, "Filemanager", ("Folder '" + filePath + "' created successfully."));
        }
        else {
            Log(MessageType::Error, "Filemanager", "Error creating folder: " + GetLastError());
        }
    }
    else if (createIfNotExist == true && exist == false) {
        // Download File from Url
        std::wstring url(downloadUrl.begin(), downloadUrl.end());
        std::wstring destination(filePath.begin(), filePath.end());
        HRESULT hr = URLDownloadToFileW(NULL, url.c_str(), destination.c_str(), 0, NULL);
        if (SUCCEEDED(hr) == true) {
            Log(MessageType::Info, "Filemanager", ("File '" + filePath + "' downloaded successfully."));
        }
        else {
            Log(MessageType::Error, "Filemanager", "Error downloading file: " + GetLastError());
        }
    }
}