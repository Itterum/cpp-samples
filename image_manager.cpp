#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>
#include <unordered_set>
#include <algorithm>

namespace fs = std::filesystem;

std::string generateRandomHash() {
    static constexpr char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    static std::random_device rd;
    static std::mt19937 rng(rd());
    static std::uniform_int_distribution<> index_dist(0, sizeof(alphanum) - 2);

    std::string result;
    result.reserve(8);
    for (int i = 0; i < 8; ++i)
        result += alphanum[index_dist(rng)];

    return result;
}

void batchRename(const fs::path &targetDir) {
    try {
        for (const auto &entry: fs::directory_iterator(targetDir)) {
            if (!entry.is_regular_file()) continue;

            const auto ext = entry.path().extension();
            std::string fileExt = ext.string();

            if (const std::pmr::unordered_set<std::string> validExtensions = {".jpg", ".jpeg", ".png", ".gif"}; !
                validExtensions.contains(ext)) continue;

            std::string newBaseName = generateRandomHash();
            fs::path newName = targetDir / (newBaseName + fileExt);

            int counter = 0;
            while (fs::exists(newName)) {
                newBaseName = generateRandomHash();
                newName = targetDir / (newBaseName + fileExt);
                if (counter++ > 10) break;
            }

            fs::rename(entry.path(), newName);
            std::cout << "Renamed: " << entry.path().filename()
                    << " -> " << newName.filename() << std::endl;
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
}

int main(const int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <directory_path>\n";
        return 1;
    }

    const std::filesystem::path imagePath = argv[1];

    if (!fs::exists(imagePath)) {
        std::cerr << "Directory does not exist!" << std::endl;
        return 1;
    }

    batchRename(imagePath);
    return 0;
}
