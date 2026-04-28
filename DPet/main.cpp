#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glad.c"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "windows.h"
#include "shellapi.h"

#include "thread"
#include "chrono"
#include "vector"
#include "string"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

extern "C" {
	__declspec(dllexport) DWORD NvOptimusEnablement = 0;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0;
}

#define SLEEP(n) std::this_thread::sleep_for(std::chrono::milliseconds(n))

class CoreSystem {
	HANDLE processCheck{ nullptr };
public:
	CoreSystem() {
		processCheck = CreateMutex(NULL, TRUE, L"6B7BSnowDropProgram");
		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			if (processCheck) CloseHandle(processCheck);
			exit(-1);
		}

		if (!glfwInit()) exit(-1);
	}
	~CoreSystem() {
		glfwTerminate();
		CloseHandle(processCheck);
	}
};

int main() { CoreSystem run; }