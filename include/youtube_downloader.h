#ifndef YOUTUBE_DOWNLOADER_H
#define YOUTUBE_DOWNLOADER_H

#include <string>
#include <vector>

class YouTubeDownloader {
public:
    YouTubeDownloader();
    ~YouTubeDownloader();

    /**
     * Download MP3 from a YouTube video URL
     * @param youtube_url The URL of the YouTube video
     * @param output_file The output MP3 filename (without extension)
     * @return true if successful, false otherwise
     */
    bool downloadMP3(const std::string& youtube_url, const std::string& output_file);

    /**
     * Check if required tools (yt-dlp and ffmpeg) are installed
     * @return true if both tools are available, false otherwise
     */
    bool checkDependencies();

    /**
     * Get the last error message
     * @return Error message string
     */
    std::string getLastError() const;

private:
    std::string last_error;

    /**
     * Execute a system command and capture output
     * @param command The command to execute
     * @return The output of the command
     */
    std::string executeCommand(const std::string& command);

    /**
     * Download video audio using yt-dlp
     * @param youtube_url The URL of the YouTube video
     * @param temp_file The temporary file to store audio
     * @return true if successful, false otherwise
     */
    bool downloadAudio(const std::string& youtube_url, const std::string& temp_file);

    /**
     * Convert audio to MP3 using ffmpeg
     * @param input_file The input audio file
     * @param output_file The output MP3 file
     * @return true if successful, false otherwise
     */
    bool convertToMP3(const std::string& input_file, const std::string& output_file);

    /**
     * Check if a file exists
     * @param filename The filename to check
     * @return true if file exists, false otherwise
     */
    bool fileExists(const std::string& filename) const;

    /**
     * Find actual audio file with extension (yt-dlp adds extensions automatically)
     * @param basename The base filename without extension
     * @return The actual filename if found, empty string otherwise
     */
    std::string findAudioFile(const std::string& basename) const;
};

#endif // YOUTUBE_DOWNLOADER_H
