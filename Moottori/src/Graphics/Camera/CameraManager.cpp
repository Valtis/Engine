#include "Graphics/Camera/CameraManager.h"
#include "Graphics/Camera/Camera.h"
CameraManager *CameraManager::mInstance = nullptr;


CameraManager &CameraManager::Instance()
{
	if (mInstance == nullptr)
	{
		mInstance = new CameraManager();
	}

	return *mInstance;
}

void CameraManager::Release()
{
	delete mInstance;
	mInstance = nullptr;
}

void CameraManager::AddCamera(std::unique_ptr<Camera> camera)
{
	camera->SetScreenWidth(mScreenWidth);
	camera->SetScreenHeight(mScreenHeight);

	mCameras.push_back(std::move(camera));
	if (mActiveCamera == -1) // place holder code. todo: remove magic numbers and introduce proper switching for cameras
	{
		mActiveCamera = 0;
	}

}

Camera *CameraManager::GetActiveCamera()
{
	if (mCameras.empty())
	{
		return nullptr;
	}

	return mCameras[mActiveCamera].get();
}