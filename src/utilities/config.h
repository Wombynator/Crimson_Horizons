#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>

class Config {
public:
    static Config& getInstance();
    std::string getValue(const std::string& section, const std::string& key);
    void setValue(const std::string& section, const std::string& key, const std::string& value);
    void saveToFile();

private:
    Config(); // Constructor is private
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;
    void parseLine(const std::string& line, std::string& currentSection);

    // Disallow copy and assignment
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
};

#endif