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
	unsigned int LoadPNG(const char* path) {
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		stbi_set_flip_vertically_on_load(true);

		int width, height, channels;
		unsigned char* data = stbi_load(path, &width, &height, &channels, 4);

		if (data) {
			GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			return 0;
		}

		stbi_image_free(data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		return texture;
	}
private:
	class Charactor {
	private:
		GLFWwindow* window{ nullptr };
		HWND hwnd{ nullptr };

		const enum class CharactorState {
			IDLE,
			GRAB,
			DROP,
			COUNT
		};

		unsigned int texture[USHORT(CharactorState::COUNT)][10]{ NULL };
		bool animation_end = false;

		void CheckAnimationEnd(const short* num) {

		}
	public:
		void Render() {

		}

		Charactor() {

		}
		~Charactor() {

		}
	};
	// ----------------------------------------------------------
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

		Menu() {

		}
		~Menu() {

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