#ifndef ENGINE_KEY_INPUT_H
#define ENGINE_KEY_INPUT_H


namespace Input
{
	class InputKeyMapper;
	class _declspec (dllexport) KeyInput
	{
		InputKeyMapper* map;
		int maxActionValue;
		int actionsRequested;
		//start singleton pattern
		KeyInput(){} //defined a function it is implicitly inlined
		KeyInput(const KeyInput&); //copy constructor
		KeyInput& operator=(const KeyInput&); //assignment operator
		static KeyInput instance; //define a memmory for singleton
		//end singleton pattern
	public:
		bool initialize(InputKeyMapper* map, int maxActionValue);
		bool shutdown();
		void update();
		int actionsThisFrame() const;
		bool actionsHotThisFrame(int action) const;
		static KeyInput& getInstance();
	};

	#define input Input::KeyInput::getInstance()

}
#endif