.PHONY: all build clean rebuild install help

all: build

help:
	@echo "YouTube to MP3 Downloader - Build Commands"
	@echo "==========================================="
	@echo "make build    - Build the project (creates build/ directory and binary)"
	@echo "make clean    - Remove build directory and binaries"
	@echo "make rebuild  - Clean and rebuild the project"
	@echo "make install  - Install the binary to /usr/local/bin"
	@echo "make help     - Show this help message"

build:
	@echo "Building YouTube MP3 Downloader..."
	@mkdir -p build
	@cd build && cmake .. && make
	@echo "Build complete! Run with: ./build/yt-mp3"

clean:
	@echo "Cleaning build files..."
	@rm -rf build
	@echo "Clean complete!"

rebuild: clean build

install: build
	@echo "Installing yt-mp3 to /usr/local/bin..."
	@cd build && sudo make install
	@echo "Installation complete! You can now run 'yt-mp3' from anywhere"

check-deps:
	@echo "Checking for required dependencies..."
	@command -v yt-dlp >/dev/null 2>&1 || echo "✗ yt-dlp not found (install with: pip install yt-dlp)"
	@command -v ffmpeg >/dev/null 2>&1 || echo "✗ ffmpeg not found"
	@command -v cmake >/dev/null 2>&1 || echo "✗ cmake not found"
	@command -v make >/dev/null 2>&1 || echo "✗ make not found"
	@echo "Dependency check complete!"
