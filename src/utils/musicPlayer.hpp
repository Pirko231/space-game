#pragma once
#include <SFML/Audio.hpp>
#include <array>
#include "configLoader.hpp"

namespace util
{

class MusicPlayer
{
public:
    MusicPlayer(MusicPlayer&) = delete;
    MusicPlayer& operator=(MusicPlayer&) = delete;

    static MusicPlayer& get()
    {
        static MusicPlayer mPlayer;
        return mPlayer;
    }
    void play()
    {
        if (music.getStatus() == sf::Music::Status::Stopped)
        {
            if (currentSong < (int)songs.size() - 1)
                currentSong++;
            else
                currentSong = 0;
            music.openFromFile(songs[currentSong]);
        }

        
        if (music.getStatus() != sf::Music::Status::Playing)
        {
            music.play();
        }
    }

private:
    MusicPlayer()
    {
        songs[0] = "resources/music/soundtrack/OutThere.ogg";
        songs[1] = "resources/music/soundtrack/through space.ogg";
        songs[2] = "resources/music/soundtrack/Szymat - Echo (game).mp3";
        music.setVolume(util::ConfigLoader::get().musicVolume);
    }
    sf::Music music;
    std::array<std::filesystem::path, 3> songs;
    int currentSong{0};
};

};