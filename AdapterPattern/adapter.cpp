#include <iostream>
#include <string>
#include <memory>

class MediaPlayer {
public:
    virtual void play(const std::string& audioType, const std::string& fileName) = 0;
    virtual ~MediaPlayer() = default;
};

class AdvancedMediaPlayer {
public:
    virtual void playVideo(const std::string& fileName) = 0;
    virtual ~AdvancedMediaPlayer() = default;
};

class VideoPlayer : public AdvancedMediaPlayer {
public:
    void playVideo(const std::string& fileName) override {
        std::cout << "Playing video: " << fileName << std::endl;
    }
};

class MediaAdapter : public MediaPlayer {
private:
    std::unique_ptr<AdvancedMediaPlayer> advancedPlayer;
public:
    MediaAdapter(const std::string& audioType) {
        if (audioType == "video") {
            advancedPlayer = std::make_unique<VideoPlayer>();
        }
    }

    void play(const std::string& audioType, const std::string& fileName) override {
        if (audioType == "video") {
            advancedPlayer->playVideo(fileName);
        }
    }
};

class AudioPlayer : public MediaPlayer {
public:
    void play(const std::string& audioType, const std::string& fileName) override {
        if (audioType == "audio") {
            std::cout << "Playing audio: " << fileName << std::endl;
        } else if (audioType == "video") {
            MediaAdapter adapter("video");
            adapter.play(audioType, fileName);
        } else {
            std::cout << "Invalid media type" << std::endl;
        }
    }
};

int main() {
    AudioPlayer audioPlayer;
    audioPlayer.play("audio", "song.mp3");
    audioPlayer.play("video", "movie.mp4");

    return 0;
}
