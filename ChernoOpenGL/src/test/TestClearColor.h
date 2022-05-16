#ifndef TEST_CLEAR_COLOR_H
#define TEST_CLEAR_COLOR_H

#include"Test.h"

namespace test
{
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float colors[4];
	};
}

#endif // !TEST_CLEAR_COLOR_H

