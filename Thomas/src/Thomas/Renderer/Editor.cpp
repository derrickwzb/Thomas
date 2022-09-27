#include "thpch.h"
//
//#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
//#include "imgui.h"
//#include "Editor.h"
//
//#include "backends/imgui_impl_opengl3.cpp"
//#include "backends/imgui_impl_glfw.cpp"
//
//
//void Editor::init() {
//    GLFWwindow* r_Window;
//    r_Window = glfwGetCurrentContext();
//	ImGui::CreateContext();
//    ImGui_ImplGlfw_InitForOpenGL(r_Window, true);
//	ImGui::StyleColorsDark();
//}
//
//void Editor::update() {
//    ImGui_ImplGlfw_NewFrame();
//    ImGui::NewFrame();
//    buttons();
//    obj_property();
//    texture_property();
//    colliderobj_property();
//}
//
//void Editor::draw() {
//	ImGui::Render();
//    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//}
//
//void Editor::cleanup() {
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//}
//
//void Editor::buttons() {
//    if (ImGui::Button("Square")) {
//        if (Render::obj_shape != 0)
//            Render::obj_shape = 0;
//        Render::Add_Obj();
//    }
//    ImGui::SameLine();
//    if (ImGui::Button("Cirlce")) {
//        if (Render::obj_shape != 1)
//            Render::obj_shape = 1;
//        Render::Add_Obj();
//    }
//    ImGui::SameLine();
//    if (ImGui::Button("BB")) {
//        if (Render::mdl_obj[Render::sel].BBtog != 1)
//            Render::mdl_obj[Render::sel].BBtog = 1;
//        else
//            Render::mdl_obj[Render::sel].BBtog = 0;
//    }
//    ImGui::SameLine();
//    if (ImGui::Button("Delete")) {
//        Render::mdl_obj.erase(Render::mdl_obj.begin() + Render::sel);
//        Render::collider_obj.erase(Render::collider_obj.begin() + Render::sel);
//    }
//}
//
//void Editor::obj_property() {
//    if (ImGui::BeginCombo("Object", "Properties", 0)) {
//        ImGui::SliderFloat("Scale X", &Render::mdl_obj[Render::sel].scaling.x, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
//        ImGui::SliderFloat("Scale Y", &Render::mdl_obj[Render::sel].scaling.y, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
//        ImGui::SliderFloat("Rotation", &Render::mdl_obj[Render::sel].rotation, -360.f, 360.f);
//        ImGui::SliderFloat("Translate X", &Render::mdl_obj[Render::sel].translation.x, -1, 1);
//        ImGui::SliderFloat("Translate Y", &Render::mdl_obj[Render::sel].translation.y, 1, -1);
//    }
//}
//
//void Editor::texture_property() {
//    if (ImGui::BeginCombo("", "Textures", 0)) {
//        if (ImGui::Button("Big Boss")) {
//            if (Render::mdl_obj[Render::sel].text_file != 1)
//                Render::mdl_obj[Render::sel].text_file = 1;
//            else
//                Render::mdl_obj[Render::sel].text_file = 0;
//        }
//        if (ImGui::Button("Background")) {
//            if (Render::mdl_obj[Render::sel].text_file != 2)
//                Render::mdl_obj[Render::sel].text_file = 2;
//            else
//                Render::mdl_obj[Render::sel].text_file = 0;
//        }
//        if (ImGui::Button("Display")) {
//            if (Render::mdl_obj[Render::sel].text_file != 3)
//                Render::mdl_obj[Render::sel].text_file = 3;
//            else
//                Render::mdl_obj[Render::sel].text_file = 0;
//        }
//        if (ImGui::Button("Animation")) {
//            if (Render::mdl_obj[Render::sel].animation_but != 1)
//                Render::mdl_obj[Render::sel].animation_but = 1;
//            else
//                Render::mdl_obj[Render::sel].animation_but = 0;
//        }
//    }
//}
//
//void Editor::colliderobj_property(){
//    if (ImGui::BeginCombo("Collider", "Properties", 0)) {
//        ImGui::SliderFloat("Scale X", &Render::collider_obj[Render::sel].scaling.x, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
//        ImGui::SliderFloat("Scale Y", &Render::collider_obj[Render::sel].scaling.y, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
//        ImGui::SliderFloat("Translate X", &Render::collider_obj[Render::sel].translation.x, -1, 1);
//        ImGui::SliderFloat("Translate Y", &Render::collider_obj[Render::sel].translation.y, 1, -1);
//        if (ImGui::Button("Reset"))
//            Render::collider_obj[Render::sel].reset_but = 1;
//    }
//}
