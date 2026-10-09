# 🎵 Qt Music Player

A desktop music player developed using **C++ and Qt Framework**. This application allows users to play local audio files with playback controls, volume adjustment, song information, and a simple dark-themed user interface.

## ✨ Features

- ▶️ Play and pause music
- ⏮️ Play the previous song
- ⏭️ Play the next song
- 🔁 Automatically play the next song when the current song finishes
- 🎼 Display song title and artist metadata when available
- 🖼️ Display embedded album artwork when available, with a default image as a fallback
- ⏱️ Display current playback time and total duration
- 🎚️ Seek through a song using the progress slider
- 🔊 Adjust volume using the volume slider
- 🌙 Dark-themed interface using Qt Style Sheets (QSS)

## 🛠️ Technologies Used

- **Programming Language:** C++
- **Framework:** Qt
- **UI:** Qt Widgets and Qt Designer
- **Audio Playback:** Qt Multimedia
- **Classes:** `QMediaPlayer`, `QAudioOutput`, `QMediaMetaData`
- **IDE:** Qt Creator

## 📂 Project Structure

```text
MusicPlayer/
├── main.cpp
├── mainwindow.cpp
├── mainwindow.h
├── mainwindow.ui
├── resources.qrc
├── Music.pro
└── README.md
```

## 🎧 Supported Audio Formats

The current implementation searches for `.mp3` and `.wav` files in a configured local music folder.

Update the folder path in `MainWindow::loadSongs()` in `mainwindow.cpp` to match your computer.

## 🚀 Getting Started

### Prerequisites

- Qt Creator
- A compatible Qt kit
- Qt Widgets module
- Qt Multimedia module
- C++ compiler supported by your Qt kit

### Build and Run

1. Clone this repository:

   ```bash
   git clone YOUR_GITHUB_REPOSITORY_URL
   ```

2. Open Qt Creator.
3. Open the `Music.pro` project file.
4. Select a compatible Qt kit.
5. Check the music folder path in `mainwindow.cpp`.
6. Build and run the project.

## 🎮 How to Use

1. Launch the application.
2. Click **Play** to start playback.
3. Use **Previous** and **Next** to change songs.
4. Drag the progress slider to seek through the current song.
5. Adjust the volume slider to control the audio level.
6. View the song title, artist information, and album artwork when available.

## 🖼️ Song Metadata and Artwork

The player uses Qt Multimedia to read available audio metadata, including song title, artist, and embedded cover artwork.

- If the title is unavailable, the audio filename is displayed.
- If artist information is unavailable, `Unknown Artist` is displayed.
- If embedded artwork is unavailable, the default album image is displayed.

Metadata and artwork availability depends on the audio file and the multimedia backend.

## 🔮 Future Improvements

- File dialog to select music files
- Playlist management
- Individual artwork for songs without embedded covers
- Improved metadata support

## 👩‍💻 Author

**Dhanushree Reddy**

