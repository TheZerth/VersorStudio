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

static void testVersors();

class CustomImGui : public VersorAgent {
public:
    float inputVector[4] = {0,0,0,0};
    Versor tempVersor{0, 0, 0, 0};
	Versor selectPlaceholder{0, 0, 0, 0};
	int selectIndex = 0;
	std::string namePlaceholder = "Select a Versor";
	std::string operationName = "Select an Operation";
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
	Versor* _selectedVersor = &selectPlaceholder;
	std::string* _selectedVersorName = &namePlaceholder;
	Versor* _operationVersor = &selectPlaceholder;
	std::string* _operationVersorName = &namePlaceholder;

	CustomImGui() : VersorAgent() {
		// Set the clear color
		glClearColor(0.0f, 0.0f, 0.0f, 1.00f);
	}

	virtual void Update() override {

		// Begin GUI
        ImGui::Begin("Versor Studio", NULL, ImGuiWindowFlags_NoCollapse);
        ImGui::InputText("Versor Name", _versorName);
        ImGui::InputFloat4("Input Versor", inputVector, "%.3f", 0);
        if (ImGui::Button("Create"))                            // Create a versor when clicked
        {
            tempVersor.a = inputVector[0];                          //Assign users input values to versor to be stored
            tempVersor.x = inputVector[1];
            tempVersor.y = inputVector[2];
            tempVersor.b = inputVector[3];
            worldVersors.push_back(tempVersor);                     //Store the versor
            worldVersorNames.push_back(versorName);                 //Store the versors name
        }ImGui::SameLine();
        if (ImGui::Button("Remove") && selectIndex >= 0 && selectIndex < worldVersors.size())                        // Remove a versor when clicked
        {
        	worldVersors.erase(worldVersors.begin() + selectIndex);
        	worldVersorNames.erase(worldVersorNames.begin() + selectIndex);
        }ImGui::SameLine();
		if (ImGui::Button("Add") && selectIndex >= 0 && selectIndex < worldVersors.size())                        // Remove a versor when clicked
		{
			operationName = "Addition";
		}ImGui::SameLine();
		if (ImGui::Button("Sub") && selectIndex >= 0 && selectIndex < worldVersors.size())                        // Remove a versor when clicked
		{
			operationName = "Subtraction";
		}ImGui::SameLine();
		if (ImGui::Button("Mul") && selectIndex >= 0 && selectIndex < worldVersors.size())                        // Remove a versor when clicked
		{
			operationName = "Geometric Product";
		}ImGui::SameLine();
		if (ImGui::Button("Ext") && selectIndex >= 0 && selectIndex < worldVersors.size())                        // Remove a versor when clicked
		{
			operationName = "Exterior Product";
		}ImGui::SameLine();
		if (ImGui::Button("Int") && selectIndex >= 0 && selectIndex < worldVersors.size())                        // Remove a versor when clicked
		{
			operationName = "Interior Product";
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

        	ImGui::Separator();
        	ImGui::Text("Selected: ");
        	ImGui::SameLine();
        	ImGui::Text(_selectedVersorName->c_str());		//Display name of selected versor
        	ImGui::Text(_selectedVersor->toString().c_str());		//Display contents of selected versor
        	ImGui::Text("Operation: ");
        	ImGui::SameLine();
        	ImGui::Text(operationName.c_str());
        }ImGui::End();

        if (ImGui::Begin("World Versors", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse)) {
            for (int i = 0; i < worldVersors.size(); i++) {
                ImGui::Text(worldVersorNames[i].c_str());
                ImGui::Text(worldVersors[i].toString().c_str());
                ImGui::SmallButton("Select");
            	if (ImGui::IsItemClicked()) {
					_selectedVersor = &worldVersors[i];
            		_selectedVersorName = &worldVersorNames[i];
            		selectIndex = i;
				}
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
    testVersors();



    //std::cout << std::setprecision(3) << c << std::endl;
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

static void testVersors() {
	try {
		//Test construction of a versor
		float a = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);;
		float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		Versor v = {a, x, y, b};
		if (v.a == a && v.x == x && v.y == y && v.b == b) {
			std::cout << "Construction Passed" << std::endl;
		} else {
			std::cout << "Construction Failed" << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cout << "Construction failed: " << e.what() << std::endl;
	}
	//System Constants
	static Versor one = {1.0f, 0.0f, 0.0f, 0.0f};
	static Versor e1 = {0.0f, 1.0f, 0.0f, 0.0f};
	static Versor e2 = {0.0f, 0.0f, 1.0f, 0.0f};
	static Versor I = {0.0f, 0.0f, 0.0f, 1.0f};			//Represents highest grade object of the algebra, in this case e1^e2
	static Versor zero = {0.0f, 0.0f, 0.0f, 0.0f};
    // Test Geometric Algebra
    Versor testScalar1{5.0f, 0.0f, 0.0f, 0.0f};
    Versor testScalar2{3.0f, 0.0f, 0.0f, 0.0f};
    Versor testVector1{0.0f, 2.0f, 0.0f, 0.0f};
    Versor testVector2{0.0f, 0.0f, 4.0f, 0.0f};
    Versor testBivector1{0.0f, 0.0f, 0.0f, 6.0f};
    Versor testBivector2{0.0f, 0.0f, 0.0f, 2.0f};
	Versor testVersor1{1.0f, 2.0f, 3.0f, 4.0f};
	Versor testVersor2{3.0, 2.0, 4.0, 1.0};
	std::cout << "----------TESTING VERSOR OPERATORS----------" << std::endl;
	std::cout << "Note this test only proves the framework is accepting and printing commands properly." << std::endl << std::endl;
	try {
		std::cout << "Scalar Addition: " << testScalar1 << " + " << testScalar2 << " = " << (testScalar1 + testScalar2) << std::endl;
		std::cout << "Vector Addition: " << testVector1 << " + " << testVector2 << " = " << (testVector1 + testVector2) << std::endl;
		std::cout << "Bivector Addition: " << testBivector1 << " + " << testBivector2 << " = " << (testBivector1 + testBivector2) << std::endl;
		std::cout << "Versor Addition: " << testVersor1 << " + " << testVersor2 << " = " << (testVersor1 + testVersor2) << std::endl << std::endl;
		std::cout << "Addition tests succesful." << std::endl << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "Addition failed: " << e.what() << std::endl;
	}

	try {
		std::cout << "Scalar Subtraction: " << testScalar1 << " - " << testScalar2 << " = " << (testScalar1 - testScalar2) << std::endl;
		std::cout << "Vector Subtraction: " << testVector1 << " - " << testVector2 << " = " << (testVector1 - testVector2) << std::endl;
		std::cout << "Bivector Subtraction: " << testBivector1 << " - " << testBivector2 << " = " << (testBivector1 - testBivector2) << std::endl;
		std::cout << "Versor Subtraction: " << testVersor1 << " - " << testVersor2 << " = " << (testVersor1 - testVersor2) << std::endl << std::endl;
		std::cout << "Subtraction tests succesful." << std::endl << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "Subtraction failed: " << e.what() << std::endl;
	}

	try {
		std::cout << "Scalar Interior Product: " << testScalar1 << " | " << testScalar2 << " = " << (testScalar1 | testScalar2) << std::endl;
		std::cout << "Vector Interior Product: " << testVector1 << " | " << testVector2 << " = " << (testVector1 | testVector2) << std::endl;
		std::cout << "Bivector Interior Product: " << testBivector1 << " | " << testBivector2 << " = " << (testBivector1 | testBivector2) << std::endl;
		std::cout << "Versor Interior Product: " << testVersor1 << " | " << testVersor2 << " = " << (testVersor1 | testVersor2) << std::endl << std::endl;
		std::cout << "Interior Product tests succesful." << std::endl << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "Interior Product failed: " << e.what() << std::endl;
	}

	try {
		std::cout << "Scalar Exterior Product: " << testScalar1 << " ^ " << testScalar2 << " = " << (testScalar1 ^ testScalar2) << std::endl;
		std::cout << "Vector Exterior Product: " << testVector1 << " ^ " << testVector2 << " = " << (testVector1 ^ testVector2) << std::endl;
		std::cout << "Bivector Exterior Product: " << testBivector1 << " ^ " << testBivector2 << " = " << (testBivector1 ^ testBivector2) << std::endl;
		std::cout << "Versor Exterior Product: " << testVersor1 << " ^ " << testVersor2 << " = " << (testVersor1 ^ testVersor2) << std::endl << std::endl;
		std::cout << "Exterior Product tests succesful." << std::endl << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "Exterior Product failed: " << e.what() << std::endl;
	}

	try {
		std::cout << "Scalar Geometric Product: " << testScalar1 << " * " << testScalar2 << " = " << (testScalar1 * testScalar2) << std::endl;
		std::cout << "Vector Geometric Product: " << testVector1 << " * " << testVector2 << " = " << (testVector1 * testVector2) << std::endl;
		std::cout << "Bivector Geometric Product: " << testBivector1 << " * " << testBivector2 << " = " << (testBivector1 * testBivector2) << std::endl;
		std::cout << "Versor Geometric Product: " << testVersor1 << " * " << testVersor2 << " = " << (testVersor1 * testVersor2) << std::endl << std::endl;
		std::cout << "Geometric Product tests succesful." << std::endl << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "Geometric Product failed: " << e.what() << std::endl;
	}
	try {
	 	std::cout << "Scalar Division: " << testScalar1 << " / " << testScalar2 << " = " << (testScalar1 / testScalar2) << std::endl;
	 	std::cout << "Vector Division: " << testVector1 << " / " << testVector2 << " = " << (testVector1 / testVector2) << std::endl;
	 	std::cout << "Bivector Division: " << testBivector1 << " / " << testBivector2 << " = " << (testBivector1 / testBivector2) << std::endl;
	 	std::cout << "Versor Division: " << testVersor1 << " / " << testVersor2 << " = " << (testVersor1 / testVersor2) << std::endl << std::endl;
	 	std::cout << "Division tests succesful." << std::endl << std::endl;
	}
	catch (const std::exception& e) {
	 	std::cout << "Division failed: " << e.what() << std::endl;
	}

	std::cout << "----------TESTING VERSOR AXIOMS----------" << std::endl;
	std::cout << "Note this test will check all operators are axiomically correct." << std::endl << std::endl;
	//Test the axiom of addition
	try {
		Versor addition1 = {1.0f, 1.0f, 1.0f, 1.0f};
		Versor addition2 = {1.0f, 1.0f, 1.0f, 1.0f};
		Versor v3 = addition1 + addition2;
		if (v3.a == 2.0f && v3.x == 2.0f && v3.y == 2.0f && v3.b == 2.0f) {
			std::cout << "Addition Axiom Passed" << std::endl;
		} else {
			std::cout << "Addition Axiom Failed" << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cout << "Addition Axiom failed: " << e.what() << std::endl;
	}

	//Test the axiom of subtraction
	try {
		Versor addition1 = {1.0f, 1.0f, 1.0f, 1.0f};
		Versor addition2 = {1.0f, 1.0f, 1.0f, 1.0f};
		Versor v3 = addition1 - addition2;
		if (v3.a == 0.0f && v3.x == 0.0f && v3.y == 0.0f && v3.b == 0.0f) {
			std::cout << "Subtraction Axiom Passed" << std::endl;
		} else {
			std::cout << "Subtraction Axiom Failed" << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cout << "Subtraction Axiom failed: " << e.what() << std::endl;
	}

	//Test the axioms of geometric product
	try {
		if ((one * one) == one &&
			(one * e1) == e1 &&
			(one * e2) == e2 &&
			(one * I) == I &&

			(e1 * one) == e1 &&
			(e1 * e1) == one &&
			(e1 * e2) == I &&
			(e1 * I) == e2 &&

			(e2 * one) == e2 &&
			(e2 * e2) == one &&
			(e2 * e1) == I.negate() &&
			(e2 * I) == e1.negate() &&

			(I * one) == I &&
			(I * I) == one.negate()	&&			//The square of the unit bivector is -1, look familiar?
			(I * e1) == e2.negate() &&
			(I * e2) == e1
				) {
			std::cout << "Geometric Product Axiom Passed" << std::endl;
		} else {
			std::cout << "Geometric Product Axiom Failed" << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cout << "Geometric Product Axiom failed: " << e.what() << std::endl;
	}

	//Test the axioms of exterior product
	try {
		if ((one ^ one) == one &&
			(one ^ e1) == e1 &&
			(one ^ e2) == e2 &&
			(one ^ I) == I &&

			(e1 ^ one) == e1 &&
			(e1 ^ e1) == zero &&	//zero due to common vectors
			(e1 ^ e2) == I &&		//The unit bivector
			(e1 ^ I) == zero &&		//Also has common vectors as I = e1^e2

			(e2 ^ one) == e2 &&
			(e2 ^ e2) == zero &&
			(e2 ^ e1) == I.negate() &&
			(e2 ^ I) == zero &&

			(I ^ one) == I &&
			(I ^ I) == zero	&&			//All have common vectors
			(I ^ e1) == zero &&
			(I ^ e2) == zero
				) {
			std::cout << "Exterior Product Axiom Passed" << std::endl;
				} else {
					std::cout << "Exterior Product Axiom Failed" << std::endl;
				}
	}
	catch (const std::exception& e) {
		std::cout << "Exterior Product Axiom failed: " << e.what() << std::endl;
	}
}