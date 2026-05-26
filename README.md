# YouTube to MP3 Downloader (C++)

A fast and simple C++ command-line application to download audio from YouTube videos and convert them to MP3 format.

## Features

- Download audio from YouTube videos
- Convert to MP3 format automatically
- Simple CLI interface
- Error handling and validation
- Supports various YouTube URL formats
- Cross-platform (Linux, macOS, Windows with WSL)

## Prerequisites

Before building and running the application, ensure you have the following installed:

### Required Tools

1. **yt-dlp** - For downloading YouTube videos
   ```bash
   # Install via pip
   pip install yt-dlp
   
   # Or via package manager
   # Ubuntu/Debian
   sudo apt install yt-dlp
   
   # macOS
   brew install yt-dlp
   ```

2. **ffmpeg** - For audio conversion
   ```bash
   # Ubuntu/Debian
   sudo apt-get install ffmpeg
   
   # macOS
   brew install ffmpeg
   
   # CentOS/RHEL
   sudo yum install ffmpeg
   
   # Windows (WSL)
   sudo apt-get install ffmpeg
   ```

3. **Build Tools**
   ```bash
   # Ubuntu/Debian
   sudo apt-get install build-essential cmake git
   
   # macOS
   xcode-select --install
   brew install cmake
   
   # CentOS/RHEL
   sudo yum install gcc g++ cmake make
   ```

4. **libcurl** (for future enhancements)
   ```bash
   # Ubuntu/Debian
   sudo apt-get install libcurl4-openssl-dev
   
   # macOS
   brew install curl
   ```

## Building

1. **Clone or navigate to the project directory:**
   ```bash
   cd /path/to/yt-downloader-cpp
   ```

2. **Create a build directory:**
   ```bash
   mkdir build
   cd build
   ```

3. **Generate build files with CMake:**
   ```bash
   cmake ..
   ```

4. **Build the project:**
   ```bash
   make
   ```

5. **Optional: Install the binary:**
   ```bash
   sudo make install
   ```
   This installs the `yt-mp3` binary to `/usr/local/bin`

## Usage

### Basic Usage
```bash
./yt-mp3 "<YouTube_URL>" "<output_filename>"
```

### Examples
```bash
# Download and save as "song.mp3"
./yt-mp3 "https://www.youtube.com/watch?v=dQw4w9WgXcQ" "song"

# Using short YouTube URL
./yt-mp3 "https://youtu.be/dQw4w9WgXcQ" "my-music"

# With path (output directory must exist)
./yt-mp3 "https://www.youtube.com/watch?v=dQw4w9WgXcQ" "./downloads/song"
```

### Help
```bash
./yt-mp3 -h
./yt-mp3 --help
```

## Output

The application will:
1. Check for required dependencies (yt-dlp and ffmpeg)
2. Download the audio from the YouTube video
3. Convert the audio to MP3 format
4. Save the final MP3 file as `<output_filename>.mp3`
5. Display progress and status messages