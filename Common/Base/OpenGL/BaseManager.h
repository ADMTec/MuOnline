/*!
	@file
	@author		Albert Semenov
	@date		08/2008
*/

#ifndef __BASE_MANAGER_H__
#define __BASE_MANAGER_H__

#include <MyGUI.h>
#include <MyGUI_OpenGLPlatform.h>

#include "InputManager.h"
#include "PointerManager.h"

#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
#	include <windows.h>
#	include <winuser.h>
#endif

namespace base
{

	class BaseManager :
		public input::InputManager,
		public input::PointerManager,
		public MyGUI::OpenGLImageLoader
	{
	public:
		BaseManager();
		virtual ~BaseManager();

		virtual void prepare();
		bool create(int _width = 1024, int _height = 768);
		void destroy();
		void run();
		void quit();

		void setWindowCaption(const std::wstring& _text);
		void makeScreenShot() { }

		const std::string& getRootMedia();
		void setResourceFilename(const std::string& _flename);
		void addResourceLocation(const std::string& _name, bool _recursive = false);

		size_t getWindowHandle();

		MyGUI::MapString getStatistic() { return MyGUI::MapString(); }

	/*internal:*/
		void _windowResized();
		virtual void* loadImage(int& _width, int& _height, MyGUI::PixelFormat& _format, const std::string& _filename);
		virtual void saveImage(int _width, int _height, MyGUI::PixelFormat _format, void* _texture, const std::string& _filename);

	protected:
		virtual void createScene() { }
		virtual void destroyScene() { }

		virtual void setupResources();

		virtual void injectMouseMove(int _absx, int _absy, int _absz);
		virtual void injectMousePress(int _absx, int _absy, MyGUI::MouseButton _id);
		virtual void injectMouseRelease(int _absx, int _absy, MyGUI::MouseButton _id);
		virtual void injectKeyPress(MyGUI::KeyCode _key, MyGUI::Char _text);
		virtual void injectKeyRelease(MyGUI::KeyCode _key);

		virtual void createGui();
		virtual void destroyGui();

	private:
		void windowAdjustSettings(HWND hWnd, int width, int height, bool fullScreen);

		void resizeRender(int _width, int _height);
		bool createRender(int _width, int _height, bool _windowed);
		void drawOneFrame();
		void destroyRender();

	private:
		MyGUI::Gui* mGUI;
		MyGUI::OpenGLPlatform* mPlatform;

		HWND hWnd;
		HDC hDC;
		HGLRC hRC;
		HINSTANCE hInstance;

		bool mExit;

		std::string mRootMedia;
		std::string mResourceFileName;
	};

} // namespace base

#endif // __BASE_MANAGER_H__
