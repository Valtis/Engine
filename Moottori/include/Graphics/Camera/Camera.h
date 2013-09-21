#pragma once

class Camera
{
public:
	Camera() : mScreenWidth(0), mScreenHeight(0) { }
	Camera(int width, int height) : mScreenWidth(width), mScreenHeight(height) { }
	virtual ~Camera() { }

#if !defined _MSC_VER || _MSC_VER >= 1800 
	Camera(const Camera &) = delete;
	Camera &operator=(const Camera &) = delete;
#else
private:
	Camera(const Camera &);
	Camera &operator=(const Camera &);
public:
#endif

	virtual int GetX() const = 0; 
	virtual int GetY() const = 0;

	void SetScreenWidth(int w) { mScreenWidth = w; }
	void SetScreenHeight(int h)  { mScreenHeight = h; }

	int GetScreenWidth() const { return mScreenWidth; }
	int GetScreenHeight() const { return mScreenHeight; }



protected:

	int GetLevelWidth() const { return mLevelWidth; }
	void SetLevelWidth(int width) { mLevelWidth = width; }

	
	int GetLevelHeight() const { return mLevelHeight; }
	void SetLevelHeight(int width) { mLevelHeight = width; }

private:
	
	int mScreenWidth;
	int mScreenHeight;

	int mLevelWidth;
	int mLevelHeight;
};