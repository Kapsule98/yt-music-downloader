# YouTube to MP3 Downloader (C++)

A fast and simple C++ command-line application to download audio from YouTube videos and convert them to MP3 format.

## Features

- ✓ Download audio from YouTube videos
- ✓ Convert to MP3 format automatically
- ✓ Simple CLI interface
- ✓ Error handling and validation
- ✓ Supports various YouTube URL formats
- ✓ Cross-platform (Linux, macOS, Windows with WSL)

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

### Example Output
```
╔════════════════════════════════════════════════════╗
║     YouTube to MP3 Downloader (C++ Edition)       ║
╚════════════════════════════════════════════════════╝

Checking dependencies...
✓ yt-dlp found
✓ ffmpeg found

========================================
YouTube to MP3 Downloader
========================================
URL: https://www.youtube.com/watch?v=dQw4w9WgXcQ
Output: song.mp3
========================================

Downloading audio from YouTube...
✓ Audio downloaded successfully
Converting to MP3 format...
✓ Conversion complete

✓ Successfully downloaded and converted to MP3!
File saved as: song.mp3
```

## Troubleshooting

### "yt-dlp not found" Error
- Install yt-dlp: `pip install --upgrade yt-dlp`
- Ensure it's in your PATH: `which yt-dlp`

### "ffmpeg not found" Error
- Install ffmpeg using your package manager (see Prerequisites section)
- Verify installation: `which ffmpeg`

### "Failed to download audio" Error
- Check your internet connection
- Verify the YouTube URL is valid and publicly accessible
- Try updating yt-dlp: `pip install --upgrade yt-dlp`

### Permission Denied Error
- Ensure you have write permissions in the output directory
- Try creating the output file in your home directory first

### Build Errors
- Ensure CMake version is 3.10 or higher: `cmake --version`
- Verify all required packages are installed
- Try cleaning and rebuilding:
  ```bash
  rm -rf build
  mkdir build
  cd build
  cmake ..
  make
  ```

## Project Structure

```
yt-downloader-cpp/
├── CMakeLists.txt              # Build configuration
├── README.md                   # This file
├── include/
│   └── youtube_downloader.h    # Header file
├── src/
│   ├── main.cpp               # CLI interface
│   └── youtube_downloader.cpp # Core implementation
└── build/                     # Build directory (created during build)
```

## Technical Details

- **Language**: C++17
- **Build System**: CMake
- **Audio Download**: yt-dlp (creates temporary files)
- **Audio Conversion**: ffmpeg with MP3 codec
- **Process Management**: Standard C++ system calls to execute external tools

## Limitations

- Requires internet connection
- YouTube URL must be publicly accessible
- Respects YouTube's terms of service (downloaded content should be for personal use only)
- Quality depends on yt-dlp's available streams and ffmpeg's conversion

## Future Enhancements

- [ ] Batch download multiple videos
- [ ] Progress bar display
- [ ] Support for different audio formats
- [ ] Playlist support
- [ ] GUI interface
- [ ] Configuration file support
- [ ] Download history

## License

This project is provided as-is for educational and personal use.

## Disclaimer

This tool is provided for educational purposes. Users are responsible for ensuring their use complies with YouTube's Terms of Service and applicable copyright laws. The developers are not responsible for any misuse of this tool.
