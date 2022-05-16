#include "TestClearColor.h"
#include <Renderer.h>
#include <glad/glad.h>
#include <imgui.h>
namespace test
{
	TestClearColor::TestClearColor()
	{
	}
	TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::OnUpdate(float deltaTime) 
	{
	}
	void TestClearColor::OnRender() 
	{
		GLCall(glClearColor(colors[0], colors[1], colors[2], colors[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

	}
	void TestClearColor::OnImGuiRender() 
	{
		ImGui::ColorEdit4("ClearColor", colors);
	}
}