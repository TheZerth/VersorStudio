// VersorStudio.cpp : Defines the entry point for the application.
//

#include "UseImGui.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Versor.h"
#include <vector>

class CustomImGui : public UseImGui {
public:
    float inputVector[3] = {0,0,0};
    Versor tempVersor{0,0,0};
    float inputVoltage = 0;
    float inputCurrent = 0;
    float inputResistance = 0;
    float* _inputCurrent = &inputCurrent;
    float* _inputVoltage = &inputVoltage;
    float* _inputResistance = &inputResistance;
    std::vector<Versor> worldVersors;
	virtual void Update() override {

		// Begin GUI
        int counter = 0;

        // Ohm's Law Screen
        if (ImGui::Begin("Ohm's Law", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
        {
            ImGui::InputFloat("I", _inputCurrent,0.0f,0.0f, "%.3f", 0);
            ImGui::InputFloat("V", _inputVoltage,0.0f,0.0f, "%.3f", 0);
            ImGui::InputFloat("R", _inputResistance,0.0f,0.0f, "%.3f", 0);
            if (ImGui::Button("Solve"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            {
                if (inputCurrent == 0.0f)
                {
                    inputCurrent = inputVoltage / inputResistance;
                    std::cout << "The current is: " << inputCurrent << " Amperes" << std::endl;
                }
                else if (inputVoltage == 0.0f)
                {
                    inputVoltage = inputCurrent * inputResistance;
                    std::cout << "The voltage is: " << inputVoltage << " Volts" << std::endl;
                }
                else if (inputResistance == 0.0f)
                {
                    inputResistance = inputVoltage / inputCurrent;
                    std::cout << "The resistance is: " << inputResistance << " Ohms" << std::endl;
                }
                else
                {
                    std::cout << "No value to solve." << std::endl;
                }
            }
        }ImGui::End();

        // Versor Screen
        if (ImGui::Begin("Versor Studio", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
        {
            ImGui::InputFloat3("Vector", inputVector, "%.3f", 0);
            if (ImGui::Button("Add"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            {
                tempVersor.x(inputVector[0]);
                tempVersor.y(inputVector[1]);
                tempVersor.z(inputVector[2]);
                worldVersors.push_back(tempVersor);
                std::cout << "Added Versor: [" << tempVersor.x() << "e1, " << tempVersor.y() << "e2, " << tempVersor.z() << "e3]" << std::endl;
            }
        }ImGui::End();

        // Info Screen
        ImGui::SetNextWindowSize(ImVec2(360,80));
		if (ImGui::Begin("Info", NULL, ImGuiWindowFlags_NoResize)) {
            // Color Change and FPS
            bool clear_color_changed = ImGui::ColorEdit3("clear color",
                                                         (float *) clear_color); // Edit 3 floats representing a color

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            if (clear_color_changed) {
                change_clear_color(clear_color[0], clear_color[1], clear_color[2]);
            }
        }ImGui::End();


	}

private:
	float clear_color[3] = { .0f, .0f, .0f };
	void change_clear_color(float r, float g, float b) {
		glClearColor(r, g, b, 1.00f);
	}
};

int main()
{
	// Setup GLFW window
	if (!glfwInit())
		return 1;

	// GL 3.0 + GLSL 130
	const char *glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

	// Create window with graphics context
	GLFWwindow *window = glfwCreateWindow(1280, 720, "Dear ImGui - Example", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))  // tie window context to glad's opengl funcs
		throw("Unable to context to OpenGL");

	int screen_width, screen_height;
	glfwGetFramebufferSize(window, &screen_width, &screen_height);
	glViewport(0, 0, screen_width, screen_height);

    // Create IMGui manager and initialize GUI
	CustomImGui myimgui;
	myimgui.Init(window, glsl_version);

    //--- MAIN LOOP ---
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();


		glClear(GL_COLOR_BUFFER_BIT);
		myimgui.NewFrame();
		myimgui.Update();
		myimgui.Render();
		glfwSwapBuffers(window);
	}
	myimgui.Shutdown();

	return 0;
}
