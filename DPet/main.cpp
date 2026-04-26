#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "windows.h"
#include "shellapi.h"

#include "thread"
#include "chrono"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#define UCHAR(n) static_cast<unsigned char>(n)
#define USHORT(n) static_cast<unsigned short>(n)
#define SLEEP(n) std::this_thread::sleep_for(std::chrono::milliseconds(n))

class CoreSystem {
public:
	struct Frame {

	}; static Frame* frame;
private:
	class Charactor {
	private:
		GLFWwindow* window{ nullptr };
		HWND hwnd{ nullptr };
	public:
		void Render() {

		}
	};
	class Menu {
	private:
		GLFWwindow* window{ nullptr };
		HWND hwnd{ nullptr };

		bool run = true;
	public:
		bool ProgramRun() {
			return run;
		}
		void Render() {

		}
	};

	HANDLE process_check{ nullptr };

	Charactor* charactor{ nullptr };
	Menu* menu{ nullptr };
public:
	CoreSystem() {
		process_check = CreateMutex(NULL, TRUE, L"6B7BSnowDropProgram");
		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			if (process_check) CloseHandle(process_check);
			exit(-1);
		}

		if (!glfwInit()) exit(-1);

		charactor = new Charactor;
		menu = new Menu;
		
		while (menu->ProgramRun()) {
			glfwPollEvents();

			charactor->Render();
			menu->Render();

			SLEEP(25);
		}
	}
	~CoreSystem() {
		if (charactor != nullptr) delete charactor;
		if (menu != nullptr) delete menu;

		glfwTerminate();
		if (process_check) CloseHandle(process_check);
	}
};

int main() { CoreSystem run; }