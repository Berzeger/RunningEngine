#pragma once

#include "Running/Window.h"
#include <GLFW/glfw3.h>
#include "Running/Renderer/GraphicsContext.h"

namespace Running
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned GetWidth() const override { return _data.Width; }
		inline unsigned GetHeight() const override { return _data.Height; }

		// Window properties
		inline void SetEventCallback(const EventCallbackFn& callback) override { _data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void* GetNativeWindow() const override { return (void*)_window; };

	private:
		virtual void Init(const WindowProperties& props);
		virtual void Shutdown();
	private:
		GLFWwindow* _window;
		GraphicsContext* _context;

		struct WindowData
		{
			std::string Title;
			unsigned Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData _data;
	};
}
