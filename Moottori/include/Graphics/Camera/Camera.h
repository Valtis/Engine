#pragma once

class Camera
{
public:
	Camera() : mAreaWidth(0), mAreaHeight(0) { }
	Camera(int width, int height) : mAreaWidth(width), mAreaHeight(height) { }
	virtual ~Camera();

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
protected:
	int GetAreaWidth() { return mAreaWidth; }
	int GetAreaHeight() { return mAreaHeight; }

private:
	
	int mAreaWidth;
	int mAreaHeight;
};