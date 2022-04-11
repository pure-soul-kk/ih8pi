#include <fstream>
#include "config.h"

typedef std::map<std::string, std::string> config_map_t;

static std::string get_value_or_empty(const config_map_t &config, const std::string &key) {
    const auto it = config.find(key);
    if (it != config.end()) {
        return it->second;
    }
    return "";
}

Config Config::from_file(const std::string config_path) {
    Config config;
    config_map_t config_map;

    if (std::ifstream file(config_path); file.good()) {
        std::string line;

        while (std::getline(file, line)) {
            if (line[0] == '#') {
                continue;
            }

            if (const auto separator = line.find('='); separator != std::string::npos) {
                config_map[line.substr(0, separator)] = line.substr(separator + 1);
            }
        }
    }

    return Config(
        get_value_or_empty(config_map, "BUILD_FINGERPRINT"),
        get_value_or_empty(config_map, "BUILD_DESCRIPTION"),
        get_value_or_empty(config_map, "BUILD_SECURITY_PATCH_DATE"),
        get_value_or_empty(config_map, "BUILD_TAGS"),
        get_value_or_empty(config_map, "BUILD_TYPE"),
        get_value_or_empty(config_map, "BUILD_VERSION_RELEASE"),
        get_value_or_empty(config_map, "BUILD_VERSION_RELEASE_OR_CODENAME"),
        get_value_or_empty(config_map, "DEBUGGABLE"),
        get_value_or_empty(config_map, "MANUFACTURER_NAME"),
        get_value_or_empty(config_map, "PRODUCT_BRAND"),
        get_value_or_empty(config_map, "PRODUCT_DEVICE"),
        get_value_or_empty(config_map, "PRODUCT_MODEL"),
        get_value_or_empty(config_map, "PRODUCT_NAME")
    );
}
