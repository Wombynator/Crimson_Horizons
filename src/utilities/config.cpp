#include "Config.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <iostream>

std::unordered_map<std::string, int> keys = {
    {"key.unknown", 0},

    {"key.mouse.left", 20},
    {"key.mouse.right", 21},
    {"key.mouse.middle", 22},
    {"key.mouse.4", 23},
    {"key.mouse.5", 24},
    {"key.mouse.6", 25},
    {"key.mouse.7", 26},

    {"key.keyboard.0", 148},
    {"key.keyboard.1", 149},
    {"key.keyboard.2", 150},
    {"key.keyboard.3", 151},
    {"key.keyboard.4", 152},
    {"key.keyboard.5", 153},
    {"key.keyboard.6", 154},
    {"key.keyboard.7", 155},
    {"key.keyboard.8", 156},
    {"key.keyboard.9", 157},

    {"key.keyboard.a", 165},
    {"key.keyboard.b", 166},
    {"key.keyboard.c", 167},
    {"key.keyboard.d", 168},
    {"key.keyboard.e", 169},
    {"key.keyboard.f", 170},
    {"key.keyboard.g", 171},
    {"key.keyboard.h", 172},
    {"key.keyboard.i", 173},
    {"key.keyboard.j", 174},
    {"key.keyboard.k", 175},
    {"key.keyboard.l", 176},
    {"key.keyboard.m", 177},
    {"key.keyboard.n", 178},
    {"key.keyboard.o", 179},
    {"key.keyboard.p", 180},
    {"key.keyboard.q", 181},
    {"key.keyboard.r", 182},
    {"key.keyboard.s", 183},
    {"key.keyboard.t", 184},
    {"key.keyboard.u", 185},
    {"key.keyboard.v", 186},
    {"key.keyboard.w", 187},
    {"key.keyboard.x", 188},
    {"key.keyboard.y", 189},
    {"key.keyboard.z", 190},

    {"key.keyboard.f1", 1290},
    {"key.keyboard.f2", 1291},
    {"key.keyboard.f3", 1292},
    {"key.keyboard.f4", 1293},
    {"key.keyboard.f5", 1294},
    {"key.keyboard.f6", 1295},
    {"key.keyboard.f7", 1296},
    {"key.keyboard.f8", 1297},
    {"key.keyboard.f9", 1298},
    {"key.keyboard.f10", 1299},
    {"key.keyboard.f11", 1300},
    {"key.keyboard.f12", 1301},

    {"key.keyboard.num.lock", 1282},
    {"key.keyboard.keypad.0", 1320},
    {"key.keyboard.keypad.1", 1321},
    {"key.keyboard.keypad.2", 1322},
    {"key.keyboard.keypad.3", 1323},
    {"key.keyboard.keypad.4", 1324},
    {"key.keyboard.keypad.5", 1325},
    {"key.keyboard.keypad.6", 1326},
    {"key.keyboard.keypad.7", 1327},
    {"key.keyboard.keypad.8", 1328},
    {"key.keyboard.keypad.9", 1329},
    {"key.keyboard.keypad.decimal", 1330},
    {"key.keyboard.keypad.divide", 1331},
    {"key.keyboard.keypad.multiply", 1332},
    {"key.keyboard.keypad.subtract", 1333},
    {"key.keyboard.keypad.add", 1334},
    {"key.keyboard.keypad.enter", 1335},
    {"key.keyboard.keypad.equal", 1336},

    {"key.keyboard.right", 1262},
    {"key.keyboard.left", 1263},
    {"key.keyboard.down", 1264},
    {"key.keyboard.up", 1265},
    {"key.keyboard.apostrophe", 139},
    {"key.keyboard.backslash", 192},
    {"key.keyboard.comma", 144},
    {"key.keyboard.equal", 161},
    {"key.keyboard.grave.accent", 196},
    {"key.keyboard.left.bracket", 191},
    {"key.keyboard.right.bracket", 193},
    {"key.keyboard.minus", 145},
    {"key.keyboard.period", 146},
    {"key.keyboard.slash", 147},
    {"key.keyboard.semicolon", 159},
    
    {"key.keyboard.space", 132},
    {"key.keyboard.tab", 1258},
    {"key.keyboard.left.alt", 1342},
    {"key.keyboard.left.control", 1341},
    {"key.keyboard.left.shift", 1340},
    {"key.keyboard.left.super", 1343},
    {"key.keyboard.right.alt", 1346},
    {"key.keyboard.right.control", 1345},
    {"key.keyboard.right.shift", 1344},
    {"key.keyboard.right.super", 1347},
    {"key.keyboard.enter", 1257},
    {"key.keyboard.escape", 1256},
    {"key.keyboard.backspace", 1259},
    {"key.keyboard.delete", 1261},
    {"key.keyboard.end", 1269},
    {"key.keyboard.home", 1268},
    {"key.keyboard.insert", 1260},
    {"key.keyboard.page.up", 1266},
    {"key.keyboard.page.down", 1267},
    {"key.keyboard.caps.lock", 1280},
    {"key.keyboard.pause", 1284},
    {"key.keyboard.scroll.lock", 1281},
    {"key.keyboard.menu", 1283},
    {"key.keyboard.print.screen", 1348},

    {"key.gamepad.left.face.up", 31},
    {"key.gamepad.left.face.right", 32},
    {"key.gamepad.left.face.down", 33},
    {"key.gamepad.left.face.left", 34},
    {"key.gamepad.right.face.up", 35},
    {"key.gamepad.right.face.right", 36},
    {"key.gamepad.right.face.down", 37},
    {"key.gamepad.right.face.left", 38},
    {"key.gamepad.left.trigger.1", 39},
    {"key.gamepad.left.trigger.2", 310},
    {"key.gamepad.right.trigger.1", 311},
    {"key.gamepad.right.trigger.2", 312},
    {"key.gamepad.middle.left", 313},
    {"key.gamepad.middle", 314},
    {"key.gamepad.middle.right", 315},
    {"key.gamepad.left.thumb", 316},
    {"key.gamepad.right.thumb", 317}
};

Config::Config() {
    std::string filename = "../config.ini"; // Hardcoded file path
    std::ifstream file(filename);
    std::string line;
    std::string currentSection;

    while (getline(file, line)) {
        parseLine(line, currentSection);
    }
}

Config& Config::getInstance() {
    static Config instance; // Instantiated on first use and guaranteed to be destroyed
    return instance;
}

void Config::parseLine(const std::string& line, std::string& currentSection) {
    if (line.empty() || line[0] == '#') return; // Skip empty lines and comments

    if (line[0] == '[') {
        currentSection = line.substr(1, line.find(']') - 1);
    } else {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '=')) {
            std::string value;
            if (std::getline(is_line, value)) {
                data[currentSection][key] = value;
            }
        }
    }
}

std::string Config::getValue(const std::string& section, const std::string& key) {
    return data[section][key];
}

void Config::setValue(const std::string& section, const std::string& key, const std::string& value) {
    data[section][key] = value;
}

void Config::saveToFile() {
    std::string filename = "path_to_your_config_file.txt"; // Hardcoded file path
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for writing");
    }

    for (const auto& section : data) {
        file << "[" << section.first << "]\n";
        for (const auto& kv : section.second) {
            file << kv.first << " = " << kv.second << "\n";
        }
        file << "\n";
    }
}