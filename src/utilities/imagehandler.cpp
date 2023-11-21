#include "imagehandler.h"
#include "filemanager.h"
#include "logger.h"

sf::Image checkerboard;

void generateCheckerboardPattern() {
    checkerboard.create(512, 512, sf::Color::White); // Initialize the image with white pixels

    sf::Color colorBlack(0, 0, 0);
    sf::Color colorMagenta(248, 0, 248);

    for (int i = 0; i < 512; i++) {
        for (int j = 0; j < 512; j++) {
            if ((i / (512 / 8)) % 2 == (j / (512 / 8)) % 2) {
                checkerboard.setPixel(j, i, colorBlack);
            } else {
                checkerboard.setPixel(j, i, colorMagenta);
            }
        }
    }
}

sf::Image getFile(const std::string& imagePath, const std::string& downloadUrl) {
    // Load the input image from a file
    if (!downloadUrl.empty()) {
        checkFileFolder(imagePath, false, true, downloadUrl);
    } else {
        checkFileFolder(imagePath, false, false, downloadUrl);
    }

    sf::Image img;
    if (!img.loadFromFile(imagePath)) {
        Log(MessageType::Error, "Image Handler", "Could not open or load '" + imagePath + "'.");
        return checkerboard;
    } else {
        Log(MessageType::Info, "Image Handler", ("Image '" + imagePath + "' loaded successfully."));
        return img;
    }
}