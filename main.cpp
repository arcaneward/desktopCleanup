//
//  main.cpp
//  DesktopCleanup
//
//  Created on 6/11/24.
//

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <unordered_map>

std::unordered_map<std::string, std::string> folderMap = {
    {".txt", "Documents"},
    {".docx", "Documents"},
    {".pdf", "Documents"},
    {".mp3", "audio"},
    {".m4b", "audio"},
    {".png", "Pictures"},
    {".gif", "Pictures"},
    // Add + edit mappings as needed
};

void cleanupFiles(const std::string& desktopPath) {
    // std::filesystem provides cross-platform compatibility
    for (const auto& entry : std::__fs::filesystem::directory_iterator(desktopPath)) {
        if (entry.is_regular_file()) {
            std::string fileName = entry.path().filename().string();
            std::string extension = entry.path().extension().string();

            // Match folder based on extension
            auto folderIter = folderMap.find(extension);
            std::string folderName;
            if (folderIter != folderMap.end()) {
                folderName = folderIter->second;
            } else {
                // Exception handling for unmapped extensions
                std::cout << "Unmapped extension: " << extension << std::endl;
                // Logic for prompt to create a generic folder goes here
            }

            if (!folderName.empty()) {
                std::string destinationPath = desktopPath + "/" + folderName + "/" + fileName;

                // Check if folder exists
                if (!std::__fs::filesystem::exists(desktopPath + "/" + folderName)) {
                    std::__fs::filesystem::create_directory(desktopPath + "/" + folderName);
                }

                try {
                    // Move file to folder
                    std::__fs::filesystem::rename(entry.path(), destinationPath);
                    std::cout << "Moved " << fileName << " to " << folderName << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Error moving file: " << e.what() << std::endl;
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
  // Predefined desktop path (replace with your own system's path)
  std::string desktopPath = "/Users/lindseythornton/Desktop"; // Replace with your own username

  cleanupFiles(desktopPath);

  return 0;
}
