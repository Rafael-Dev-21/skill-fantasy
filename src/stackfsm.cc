#include "stackfsm.hh"

StackFSM::StackFSM() {}

StackFSM::StackFSM(state initial) {
	states.push(initial);
}

state StackFSM::top() {
	static state cur;
	if(cur != states.top()) {
		cur = states.top();
	}
	return cur;
}

void StackFSM::pop() {
	states.pop();
}

void StackFSM::push(state next) {
	states.push(next);
}
