#pragma once



#include <vector>
#include <SDL_mixer.h>
#include <string>	

class Music
{
    public:
        Music();
        virtual ~Music();

#if !defined _MSC_VER || _MSC_VER >= 1800 
		Music(const Music &) = delete;
		Music &operator=(const Music &) = delete;
#else
private:
	Music(const Music &);
	Music &operator=(const Music &);
public:
#endif

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


