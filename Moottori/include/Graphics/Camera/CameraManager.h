#pragma once
#include <memory>
#include <vector>
class Camera;

class CameraManager
{
public:
	static CameraManager &Instance();
	static void Release();

	void AddCamera(std::unique_ptr<Camera> camera);
	Camera *GetActiveCamera();

	void SetScreenWidth(int width) { mScreenWidth = width; }
	void SetScreenHeight(int height) { mScreenHeight = height; }

private:
	CameraManager() : mActiveCamera(-1) { }
	
	static CameraManager *mInstance;
	int mActiveCamera;
	std::vector<std::unique_ptr<Camera>> mCameras;
	int mScreenWidth;
	int mScreenHeight;
};