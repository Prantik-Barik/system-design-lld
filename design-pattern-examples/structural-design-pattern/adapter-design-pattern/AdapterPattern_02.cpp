/* Practical Example: Media Player Adapter
Lets say you are building a media player that natively plays MP3 files. 
The product team wants to add support for VLC (can play both MP4 and AVI) and MP4 formats. 
Rather than rewriting the player, you will use adapters to integrate external codec libraries. */

#include<iostream>
using namespace std;

class MusicPlayer{
    public:
    virtual ~MusicPlayer() = default;
    virtual void playMusic(string fileName) = 0; 
};

class Mp3Player : public MusicPlayer {
    public:
    void playMusic(string filename) override {
        cout << "MP3 Player: Playing " << filename << endl;
    }
};

//Adaptee
class Mp4Codec {
    public:
    void playMp4(string filename) {
        cout << "MP4 Codec: Decoding and playing " << filename << endl;
    }
};

class AviCodec {
    public:
    void playAvi(string filename) {
        cout << "AVI Codec: Decoding and playing " << filename << endl;
    }
};

//Adapters
class Mp4MusicAdapter : public MusicPlayer {
    private:
        Mp4Codec* codec;
    public:
        Mp4MusicAdapter(Mp4Codec* codec){
            this->codec = codec;
        }
        void playMusic(string filename) override {
            codec->playMp4(filename);
        }
};

class AviMusicAdapter : public MusicPlayer {
    private:
        AviCodec* codec;
    public:
        AviMusicAdapter(AviCodec* codec){
            this->codec = codec;
        }
        void playMusic(string filename) override {
            codec->playAvi(filename);
        }
};

//client code
class AudioPlayer {
    public: 
        void play(string filename){
            string ext = filename.substr(filename.rfind('.') + 1);
            transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            if(ext == "mp3"){
                Mp3Player player;
                player.playMusic(filename);
            }
            else if(ext == "mp4"){
                Mp4Codec mp4Codec;
                Mp4MusicAdapter mp4Player(&mp4Codec);
                mp4Player.playMusic(filename);
            }
            else if(ext == "avi"){
                AviCodec aviCodec;
                AviMusicAdapter aviPlayer(&aviCodec);
                aviPlayer.playMusic(filename);
            }
            else{
                cout<<"[Unsupported extension]: Cannot play music with ext: ."<<ext<<endl;
            }
        }
};

int main(){
    AudioPlayer player;
    player.play("song.mp3");
    player.play("movie.mp4");
    player.play("documentary.vlc");
    player.play("documentary.avi");
    player.play("image.png");
    return 0;
}