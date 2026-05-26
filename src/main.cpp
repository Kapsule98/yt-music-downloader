#include "youtube_downloader.h"
#include <iostream>
#include <string>
#include <algorithm>

void printUsage(const std::string& program_name) {
    std::cout << "Usage: " << program_name << " <YouTube_URL> <output_filename>" << std::endl;
    std::cout << "\nExamples:" << std::endl;
    std::cout << "  " << program_name << " \"https://www.youtube.com/watch?v=dQw4w9WgXcQ\" \"song\"" << std::endl;
    std::cout << "  " << program_name << " \"https://youtu.be/dQw4w9WgXcQ\" \"my-music\"" << std::endl;
    std::cout << "\nThe output will be saved as: <output_filename>.mp3" << std::endl;
}

void printWelcome() {
    std::cout << "\n╔════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║     YouTube to MP3 Downloader (C++ Edition)       ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════╝\n" << std::endl;
}

bool isValidYouTubeURL(const std::string& url) {
    return (url.find("youtube.com") != std::string::npos || 
            url.find("youtu.be") != std::string::npos);
}

int main(int argc, char* argv[]) {
    printWelcome();

    if (argc < 3) {
        if (argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")) {
            printUsage(argv[0]);
            return 0;
        }

        std::cerr << "Error: Missing arguments\n" << std::endl;
        printUsage(argv[0]);
        return 1;
    }

    std::string youtube_url = argv[1];
    std::string output_file = argv[2];

    if (!isValidYouTubeURL(youtube_url)) {
        std::cerr << "Error: Invalid YouTube URL. Please provide a valid YouTube link." << std::endl;
        return 1;
    }

    YouTubeDownloader downloader;

    if (!downloader.checkDependencies()) {
        std::cerr << "Error: " << downloader.getLastError() << std::endl;
        return 1;
    }

    if (!downloader.downloadMP3(youtube_url, output_file)) {
        std::cerr << "\nError: " << downloader.getLastError() << std::endl;
        return 1;
    }

    return 0;
}
