#include <stack>

typedef void (*state)();

class StackFSM {
public:
	StackFSM();
	StackFSM(state initial);

	state top();

	void pop();

	void push(state next);

private:

	std::stack<state> states;
};
