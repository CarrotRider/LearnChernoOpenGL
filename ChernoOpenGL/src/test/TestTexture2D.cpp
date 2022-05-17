#include "TestTexture2D.h"
#include <imgui.h>


namespace test
{
	TestTexture2D::TestTexture2D()
	{
		float positions[]
		{
			 - 100.0f, -100.0f, 0.0f, 0.0f,
			  100.0f, -100.0f, 1.0f, 0.0f,
			  100.0f,  100.0f, 1.0f, 1.0f,
			 -100.0f,  100.0f, 0.0f, 1.0f
		};
		unsigned int index[]
		{
			0, 1, 2,
			2, 3, 0
		};

		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		m_Layout = std::make_unique<VertexBufferLayout>();
		m_Layout->Push<float>(2);
		m_Layout->Push<float>(2);
		m_VertexArray->AddBuffer(*m_VertexBuffer, *m_Layout);
		m_VertexArray->UnBind();

		m_IndexBuffer = std::make_unique<IndexBuffer>(index, 6);
		m_Shader = std::make_unique<Shader>("res/shaders/basic.shader");
		m_Shader->Bind();

		m_Porj = glm::ortho(0.0f, 1080.0f, 0.0f, 960.0f, -1.0f, 1.0f);

		m_Texture = std::make_unique<Texture>("res/textures/carrot.png");
		m_Texture->Bind();

		m_transA = glm::vec3(200, 200, 0);
		m_transB = glm::vec3(100, 100, 0);

	}
	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}

	void TestTexture2D::OnRender()
	{
		Renderer renderer;
		renderer.Clear(0.2f, 0.3f, 0.3f, 1.0f);
		{
			m_Shader->Bind();
			glm::mat4x4 model = glm::translate(glm::mat4(1.0f), m_transA);
			glm::mat4 mvp = m_Porj * model;
			m_Shader->SetUniform("u_MVP", mvp);
			m_Shader->SetUniform("uTex", 0);
			renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
		}
		{
			m_Shader->Bind();
			glm::mat4x4 model = glm::translate(glm::mat4(1.0f), m_transB);
			glm::mat4 mvp = m_Porj * model;
			m_Shader->SetUniform("u_MVP", mvp);
			m_Shader->SetUniform("uTex", 0);
			renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
		}
	}
	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("TranslationA", &m_transA.x, -500.0f, 500.0f);
		ImGui::SliderFloat3("TranslationB", &m_transB.x, -500.0f, 500.0f);
	}
}