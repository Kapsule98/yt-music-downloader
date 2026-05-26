#include "youtube_downloader.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <sys/wait.h>
#include <unistd.h>

YouTubeDownloader::YouTubeDownloader() : last_error("") {}

YouTubeDownloader::~YouTubeDownloader() {}

std::string YouTubeDownloader::executeCommand(const std::string& command) {
    std::stringstream output;
    FILE* pipe = popen(command.c_str(), "r");
    
    if (!pipe) {
        last_error = "Failed to execute command: " + command;
        return "";
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        output << buffer;
    }

    int status = pclose(pipe);
    if (status != 0 && status != -1) {
        last_error = "Command failed with status: " + std::to_string(WEXITSTATUS(status));
    }

    return output.str();
}

bool YouTubeDownloader::fileExists(const std::string& filename) const {
    return std::filesystem::exists(filename);
}

std::string YouTubeDownloader::findAudioFile(const std::string& basename) const {
    if (fileExists(basename)) {
        return basename;
    }

    std::vector<std::string> extensions = {".m4a", ".opus", ".webm", ".wav", ".mp4", ".mkv", ".aac", ".flac", ".wma"};
    for (const auto& ext : extensions) {
        std::string full_path = basename + ext;
        if (fileExists(full_path)) {
            return full_path;
        }
    }

    return ""; 
}

bool YouTubeDownloader::checkDependencies() {
    std::cout << "Checking dependencies..." << std::endl;
    
    // Check for yt-dlp
    std::string result = executeCommand("which yt-dlp");
    if (result.empty()) {
        last_error = "yt-dlp not found. Please install it: pip install yt-dlp";
        std::cerr << "Error: " << last_error << std::endl;
        return false;
    }
    std::cout << "✓ yt-dlp found" << std::endl;

    result = executeCommand("which ffmpeg");
    if (result.empty()) {
        last_error = "ffmpeg not found. Please install it using your package manager (apt, brew, etc.)";
        std::cerr << "Error: " << last_error << std::endl;
        return false;
    }
    std::cout << "✓ ffmpeg found" << std::endl;

    return true;
}

bool YouTubeDownloader::downloadAudio(const std::string& youtube_url, const std::string& temp_file) {
    std::cout << "Downloading audio from YouTube..." << std::endl;
    
    std::string command = "yt-dlp -f 'ba' -x -o \"" + temp_file + "\" \"" + youtube_url + "\" 2>&1";
    
    std::string result = executeCommand(command);
    
    std::string actual_file = findAudioFile(temp_file);
    
    if (actual_file.empty()) {
        last_error = "Failed to download audio from YouTube URL: " + youtube_url;
        if (!result.empty()) {
            last_error += "\nDetails: " + result;
        }
        return false;
    }

    std::cout << "✓ Audio downloaded successfully (" << std::filesystem::path(actual_file).filename().string() << ")" << std::endl;
    return true;
}

bool YouTubeDownloader::convertToMP3(const std::string& input_file, const std::string& output_file) {
    std::cout << "Converting to MP3 format..." << std::endl;
    
    std::string actual_input = findAudioFile(input_file);
    if (actual_input.empty()) {
        last_error = "Input audio file not found: " + input_file;
        return false;
    }
    
    std::string mp3_output = output_file + ".mp3";
    std::string command = "ffmpeg -i \"" + actual_input + "\" -q:a 0 -map a \"" + mp3_output + "\" -y 2>&1";
    
    std::string result = executeCommand(command);
    
    if (!fileExists(mp3_output)) {
        last_error = "Failed to convert audio to MP3";
        if (!result.empty()) {
            last_error += "\nDetails: " + result;
        }
        return false;
    }

    if (fileExists(actual_input)) {
        std::remove(actual_input.c_str());
    }

    std::cout << "✓ Conversion complete" << std::endl;
    return true;
}

bool YouTubeDownloader::downloadMP3(const std::string& youtube_url, const std::string& output_file) {
    std::cout << "\n========================================" << std::endl;
    std::cout << "YouTube to MP3 Downloader" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "URL: " << youtube_url << std::endl;
    std::cout << "Output: " << output_file << ".mp3" << std::endl;
    std::cout << "========================================\n" << std::endl;

    if (youtube_url.empty()) {
        last_error = "YouTube URL cannot be empty";
        return false;
    }

    std::string temp_file = output_file + "_temp";

    if (!downloadAudio(youtube_url, temp_file)) {
        return false;
    }

    if (!convertToMP3(temp_file, output_file)) {
        return false;
    }

    std::cout << "\n✓ Successfully downloaded and converted to MP3!" << std::endl;
    std::cout << "File saved as: " << output_file << ".mp3" << std::endl;
    
    return true;
}

std::string YouTubeDownloader::getLastError() const {
    return last_error;
}
