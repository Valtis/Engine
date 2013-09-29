#pragma once



#include <vector>
class Mix_Music;
class Music
{
    public:
        Music();
        virtual ~Music();

        Music(const Music&) = delete;
        Music &operator=(const Music &) = delete;
        void Initialize();

		void ParseLine( std::string &line );

		void Uninitialize();

        void Play();
        void Pause();
        void Resume();
        void Stop();

		void Next();
		void Previous();
		bool IsPlaying();
		bool MusicFinished();

    protected:
    private:
        std::vector<Mix_Music *> mMusic;
		int mCurrentSong;
		bool mIsPlaying;
};


