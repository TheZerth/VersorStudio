// VersorStudio.cpp : Defines the entry point for the application.
//

#include "VersorAgent.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Gibbs.h"
#include "Versor.h"
#include <vector>
#include <implot.h>
#include <math.h>
#include <iomanip>
#include <imgui_stdlib.h>

class CustomImGui : public VersorAgent {
public:
    float inputVector[4] = {0,0,0,0};
    Versor tempVersor{0, 0, 0, 0};
    float inputVoltage = 0;
    float inputCurrent = 0;
    float inputResistance = 0;
    float* _inputCurrent = &inputCurrent;
    float* _inputVoltage = &inputVoltage;
    float* _inputResistance = &inputResistance;
    std::string versorName = "-Z";
    std::vector<Versor> worldVersors;
    std::vector<std::string> worldVersorNames;
    bool worldVersorSelected[100];
    std::string* _versorName = &versorName;


	virtual void Update() override {

		// Begin GUI
        ImGui::Begin("Versor Studio", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::InputText("Versor Name", _versorName);
        ImGui::InputFloat4("Input Versor", inputVector, "%.3f", 0);
        if (ImGui::Button("Add"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        {
            tempVersor.a = inputVector[0];                          //Assign users input values to versor to be stored
            tempVersor.x = inputVector[1];
            tempVersor.y = inputVector[2];
            tempVersor.b = inputVector[3];
            worldVersors.push_back(tempVersor);                     //Store the versor
            worldVersorNames.push_back(versorName);                 //Store the versors name
        }
        ImGui::SameLine();
        if (ImGui::Button("Remove"))                        // Buttons return true when clicked (most widgets return true when edited/activated)
        {
            worldVersors.pop_back();
        }
        if (ImPlot::BeginPlot("Plot")) {

            ImVec2 origin = ImPlot::PlotToPixels(ImPlotPoint(0,  0));
            //ImVec2 e1 = ImPlot::PlotToPixels(ImPlotPoint(1, 0));
            //ImVec2 e2 = ImPlot::PlotToPixels(ImPlotPoint(0, 1));
            ImPlot::PushPlotClipRect();
            //ImPlot::GetPlotDrawList()->AddCircleFilled(cntr,20,IM_COL32(255,255,0,255),20);
            //ImPlot::GetPlotDrawList()->AddRect(rmin, rmax, IM_COL32(128,0,255,255));
            //ImPlot::GetPlotDrawList()->AddLine(origin,e1,IM_COL32(255,0,0,255),2);

            for (int i = 0; i < worldVersors.size(); i++) {     //Iterate through all the versors in the world and draw them every frame.
                ImPlot::GetPlotDrawList()->AddLine(origin,
                                                   ImPlot::PlotToPixels(ImPlotPoint(worldVersors[i].x, worldVersors[i].y)),
                                                   IM_COL32(255, 0, 0, 255), 2);
            }
            ImPlot::PopPlotClipRect();
            ImPlot::EndPlot();
        }ImGui::End();

        if (ImGui::Begin("World Versors", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse)) {
            for (int i = 0; i < worldVersors.size(); i++) {
                ImGui::Text(worldVersorNames[i].c_str());
                ImGui::Text("A: %.3f", worldVersors[i].a);
                ImGui::Text("X: %.3f", worldVersors[i].x);
                ImGui::Text("Y: %.3f", worldVersors[i].y);
                ImGui::Text("B: %.3f", worldVersors[i].b);
                ImGui::Checkbox(worldVersorNames[i].c_str(), &worldVersorSelected[i]);
            }
        }ImGui::End();

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
	// GLFW is the service that creates and manages the window in the OS of choice.
    // It links OpenGL into this window and allows for the display of OpenGL graphics.
    //----------------
    // Initialize GLFW
    //----------------
	if (!glfwInit())
		return 1;
    // Setup window for system and versions
	const char *glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
	// Create the window using the given properties
	GLFWwindow *window = glfwCreateWindow(1280, 720, "Dear ImGui - Example", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))  // tie window context to glad's opengl funcs
		throw("Unable to context to OpenGL");
	int screen_width, screen_height;
	glfwGetFramebufferSize(window, &screen_width, &screen_height);  // Set the viewport size to the window size
	glViewport(0, 0, screen_width, screen_height);
    //****************
    //----------------
    // Pre-Loop Tests
    //----------------
    Versor testVersor{1.0f, 2.0f, 3.0f, 4.0f};
    Versor testVersor2{5.0f, 3.0f, 1.0f, 9.0f};
    std::cout << testVersor << std::endl << testVersor2 << std::endl;
    std::cout << "Versor Addition: " << (testVersor + testVersor2) << std::endl;
    std::cout << "Versor Subtraction: " << (testVersor - testVersor2) << std::endl;
    float a = 5;
    float b = 3;
    float c = a/b;
    std::cout << std::setprecision(3) << c << std::endl;
    //****************
    //----------------
    // Initialize IMGui
    //----------------
	CustomImGui myimgui;
	myimgui.Init(window, glsl_version);
    //****************
    //----------------
    // MAIN LOOP
    //----------------
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();


		glClear(GL_COLOR_BUFFER_BIT);
		myimgui.NewFrame();
		myimgui.Update();
		myimgui.Render();
		glfwSwapBuffers(window);
	}
	myimgui.Shutdown();
    //****************
	return 0;
}

void testVersors() {
    // Test Geometric Algebra
    Versor testScalar1{5.0f, 0.0f, 0.0f, 0.0f};
    Versor testScalar2{3.0f, 0.0f, 0.0f, 0.0f};
    Versor testVector1{0.0f, 2.0f, 0.0f, 0.0f};
    Versor testVector2{0.0f, 0.0f, 4.0f, 0.0f};
    Versor testBivector1{0.0f, 0.0f, 0.0f, 6.0f};
    Versor testBivector2{0.0f, 0.0f, 0.0f, 2.0f};
    std::cout << "Scalar Addition: " << (testScalar1 + testScalar2) << std::endl;
    std::cout << "Scalar Subtraction: " << (testScalar1 - testScalar2) << std::endl;
    std::cout << "Scalar Multiplication: " << (testScalar1 * testScalar2) << std::endl;
    std::cout << "Scalar Division: " << (testScalar1 / testScalar2) << std::endl;
    std::cout << "Vector Addition: " << (testVector1 + testVector2) << std::endl;
    std::cout << "Vector Subtraction: " << (testVector1 - testVector2) << std::endl;
    std::cout << "Vector Multiplication: " << (testVector1 * testVector2) << std::endl;
    std::cout << "Vector Division: " << (testVector1 / testVector2) << std::endl;
    std::cout << "Bivector Addition: " << (testBivector1 + testBivector2) << std::endl;
    std::cout << "Bivector Subtraction: " << (testBivector1 - testBivector2) << std::endl;
    std::cout << "Bivector Multiplication: " << (testBivector1 * testBivector2) << std::endl;
    std::cout << "Bivector Division: " << (testBivector1 / testBivector2) << std::endl;
    std::cout << "Scalar Vector Addition: " << (testScalar1 + testVector1) << std::endl;
    std::cout << "Scalar Vector Subtraction: " << (testScalar1 - testVector1) << std::endl;
    std::cout << "Scalar Vector Multiplication: " << (testScalar1 * testVector1) << std::endl;
    std::cout << "Scalar Vector Division: " << (testScalar1 / testVector1) << std::endl;
    std::cout << "Scalar Bivector Addition: " << (testScalar1 + testBivector1) << std::endl;
    std::cout << "Scalar Bivector Subtraction: " << (testScalar1 - testBivector1) << std::endl;
    std::cout << "Scalar Bivector Multiplication: " << (testScalar1 * testBivector1) << std::endl;
    std::cout << "Scalar Bivector Division: " << (testScalar1 / testBivector1) << std::endl;
    std::cout << "Vector Bivector Addition: " << (testVector1 + testBivector1) << std::endl;
    std::cout << "Vector Bivector Subtraction: " << (testVector1 - testBivector1) << std::endl;
    std::cout << "Vector Bivector Multiplication: " << (testVector1 * testBivector1) << std::endl;
    std::cout << "Vector Bivector Division: " << (testVector1 / testBivector1) << std::endl;
    std::cout << "Test Wedge Product: " << (testVector1 ^ testVector2) << std::endl;
    std::cout << "Test Wedge Product: " << (testVector2 ^ testVector1) << std::endl;
}