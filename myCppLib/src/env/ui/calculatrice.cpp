// #include "imgui.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"
// #include <GLFW/glfw3.h>
// #include <string>
// #include <sstream>
// #include <iomanip>
//
// class CalculatorLogic {
// private:
//     std::string currentNumber;
//     std::string operation;
//     double firstOperand;
//     bool newNumber;
//
// public:
//     CalculatorLogic() : currentNumber(""), operation(""),
//                         firstOperand(0), newNumber(true) {}
//
//     std::string handleInput(const std::string& input) {
//         if (input >= "0" && input <= "9") {
//             if (newNumber) {
//                 currentNumber = input;
//                 newNumber = false;
//             } else {
//                 currentNumber += input;
//             }
//             return currentNumber;
//         }
//         else if (input == ".") {
//             if (currentNumber.find('.') == std::string::npos) {
//                 if (currentNumber.empty()) currentNumber = "0";
//                 currentNumber += ".";
//                 newNumber = false;
//             }
//             return currentNumber;
//         }
//         else if (input == "C") {
//             currentNumber = "";
//             operation = "";
//             firstOperand = 0;
//             newNumber = true;
//             return "0";
//         }
//         else if (input == "+" || input == "-" || input == "*" || input == "/") {
//             if (!currentNumber.empty()) {
//                 firstOperand = std::stod(currentNumber);
//             }
//             operation = input;
//             newNumber = true;
//             currentNumber = "";
//             return std::to_string(firstOperand);
//         }
//         else if (input == "=") {
//             if (!operation.empty() && !currentNumber.empty()) {
//                 double secondOperand = std::stod(currentNumber);
//                 double result = 0;
//
//                 if (operation == "+") result = firstOperand + secondOperand;
//                 else if (operation == "-") result = firstOperand - secondOperand;
//                 else if (operation == "*") result = firstOperand * secondOperand;
//                 else if (operation == "/") {
//                     if (secondOperand != 0) result = firstOperand / secondOperand;
//                     else return "Error";
//                 }
//
//                 std::ostringstream oss;
//                 oss << std::fixed << std::setprecision(2) << result;
//                 std::string display = oss.str();
//
//                 // Supprimer les zéros inutiles
//                 display.erase(display.find_last_not_of('0') + 1);
//                 if (display.back() == '.') display.pop_back();
//
//                 currentNumber = display;
//                 operation = "";
//                 newNumber = true;
//
//                 return display;
//             }
//         }
//
//         return currentNumber.empty() ? "0" : currentNumber;
//     }
// };
//
// int main() {
//     // Initialiser GLFW
//     if (!glfwInit())
//         return -1;
//
//     // GL 3.0 + GLSL 130
//     const char* glsl_version = "#version 130";
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//
//     // Créer la fenêtre
//     GLFWwindow* window = glfwCreateWindow(400, 550, "Calculatrice ImGui", NULL, NULL);
//     if (window == NULL)
//         return -1;
//
//     glfwMakeContextCurrent(window);
//     glfwSwapInterval(1); // Enable vsync
//
//     // Setup Dear ImGui
//     IMGUI_CHECKVERSION();
//     ImGui::CreateContext();
//     ImGuiIO& io = ImGui::GetIO();
//     io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
//
//     // Setup style
//     ImGui::StyleColorsDark();
//
//     // Setup Platform/Renderer backends
//     ImGui_ImplGlfw_InitForOpenGL(window, true);
//     ImGui_ImplOpenGL3_Init(glsl_version);
//
//     CalculatorLogic calc;
//     std::string display = "0";
//
//     // Main loop
//     while (!glfwWindowShouldClose(window)) {
//         glfwPollEvents();
//
//         // Start ImGui frame
//         ImGui_ImplOpenGL3_NewFrame();
//         ImGui_ImplGlfw_NewFrame();
//         ImGui::NewFrame();
//
//         // Calculatrice window
//         ImGui::SetNextWindowPos(ImVec2(0, 0));
//         ImGui::SetNextWindowSize(ImVec2(400, 550));
//         ImGui::Begin("Calculatrice", nullptr,
//             ImGuiWindowFlags_NoResize |
//             ImGuiWindowFlags_NoMove |
//             ImGuiWindowFlags_NoCollapse |
//             ImGuiWindowFlags_NoTitleBar);
//
//         // Affichage
//         ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.95f, 0.95f, 0.95f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
//         ImGui::PushFont(io.Fonts->Fonts[0]);
//
//         char displayBuffer[64];
//         strncpy(displayBuffer, display.c_str(), sizeof(displayBuffer));
//         ImGui::InputText("##display", displayBuffer, sizeof(displayBuffer),
//             ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_CharsDecimal);
//
//         ImGui::PopFont();
//         ImGui::PopStyleColor(2);
//
//         ImGui::Spacing();
//
//         // Boutons
//         float buttonSize = 85.0f;
//         ImVec2 btnSize(buttonSize, buttonSize);
//
//         // Style pour les boutons numériques
//         ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.86f, 0.86f, 0.86f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.76f, 0.76f, 0.76f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.66f, 0.66f, 0.66f, 1.0f));
//
//         // Ligne 1
//         if (ImGui::Button("7", btnSize)) display = calc.handleInput("7");
//         ImGui::SameLine();
//         if (ImGui::Button("8", btnSize)) display = calc.handleInput("8");
//         ImGui::SameLine();
//         if (ImGui::Button("9", btnSize)) display = calc.handleInput("9");
//         ImGui::SameLine();
//
//         ImGui::PopStyleColor(3);
//         ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.8f, 0.8f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.7f, 0.7f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.9f, 0.6f, 0.6f, 1.0f));
//         if (ImGui::Button("/", btnSize)) display = calc.handleInput("/");
//         ImGui::PopStyleColor(3);
//
//         // Ligne 2
//         ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.86f, 0.86f, 0.86f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.76f, 0.76f, 0.76f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.66f, 0.66f, 0.66f, 1.0f));
//
//         if (ImGui::Button("4", btnSize)) display = calc.handleInput("4");
//         ImGui::SameLine();
//         if (ImGui::Button("5", btnSize)) display = calc.handleInput("5");
//         ImGui::SameLine();
//         if (ImGui::Button("6", btnSize)) display = calc.handleInput("6");
//         ImGui::SameLine();
//
//         ImGui::PopStyleColor(3);
//         ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.8f, 0.8f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.7f, 0.7f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.9f, 0.6f, 0.6f, 1.0f));
//         if (ImGui::Button("*", btnSize)) display = calc.handleInput("*");
//         ImGui::PopStyleColor(3);
//
//         // Ligne 3
//         ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.86f, 0.86f, 0.86f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.76f, 0.76f, 0.76f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.66f, 0.66f, 0.66f, 1.0f));
//
//         if (ImGui::Button("1", btnSize)) display = calc.handleInput("1");
//         ImGui::SameLine();
//         if (ImGui::Button("2", btnSize)) display = calc.handleInput("2");
//         ImGui::SameLine();
//         if (ImGui::Button("3", btnSize)) display = calc.handleInput("3");
//         ImGui::SameLine();
//
//         ImGui::PopStyleColor(3);
//         ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.8f, 0.8f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.7f, 0.7f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.9f, 0.6f, 0.6f, 1.0f));
//         if (ImGui::Button("-", btnSize)) display = calc.handleInput("-");
//         ImGui::PopStyleColor(3);
//
//         // Ligne 4
//         ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.86f, 0.86f, 0.86f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.76f, 0.76f, 0.76f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.66f, 0.66f, 0.66f, 1.0f));
//
//         if (ImGui::Button("0", btnSize)) display = calc.handleInput("0");
//         ImGui::SameLine();
//         if (ImGui::Button(".", btnSize)) display = calc.handleInput(".");
//         ImGui::SameLine();
//
//         ImGui::PopStyleColor(3);
//         ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 1.0f, 0.8f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 1.0f, 0.7f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.9f, 0.6f, 1.0f));
//         if (ImGui::Button("=", btnSize)) display = calc.handleInput("=");
//         ImGui::SameLine();
//         ImGui::PopStyleColor(3);
//
//         ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.8f, 0.8f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.7f, 0.7f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.9f, 0.6f, 0.6f, 1.0f));
//         if (ImGui::Button("+", btnSize)) display = calc.handleInput("+");
//         ImGui::PopStyleColor(3);
//
//         // Ligne 5 - Clear
//         ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.87f, 0.67f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.77f, 0.57f, 1.0f));
//         ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.9f, 0.67f, 0.47f, 1.0f));
//         if (ImGui::Button("C", ImVec2(360, buttonSize))) display = calc.handleInput("C");
//         ImGui::PopStyleColor(3);
//
//         ImGui::End();
//
//         // Rendering
//         ImGui::Render();
//         int display_w, display_h;
//         glfwGetFramebufferSize(window, &display_w, &display_h);
//         glViewport(0, 0, display_w, display_h);
//         glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
//         glClear(GL_COLOR_BUFFER_BIT);
//         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//         glfwSwapBuffers(window);
//     }
//
//     // Cleanup
//     ImGui_ImplOpenGL3_Shutdown();
//     ImGui_ImplGlfw_Shutdown();
//     ImGui::DestroyContext();
//
//     glfwDestroyWindow(window);
//     glfwTerminate();
//
//     return 0;
// }