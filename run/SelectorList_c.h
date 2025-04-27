#pragma once
#include "String_c.h"

/* Node - containing a Selector: a name and a pointer to the next Selector; pointer will initialized as nullptr */
class SlcNode {
public:
	String_c name;
	SlcNode* next;
	SlcNode() : name(), next(nullptr) {};
	explicit SlcNode(String_c SlcName): name(SlcName), next(nullptr) {};
	~SlcNode() {};
};

/* Singly linked list for Selectors, containting head element of class Selector Node */
class Select_list_c {
private:
	SlcNode head;
public:
	Select_list_c() : head() {};
	void PrintAll();
	SlcNode * GetHead() { return &head; };
	size_t GetListLength();
	SlcNode* FindNodeAtIndex(size_t Index);
	SlcNode* FindNode(String_c SlcName);
	bool FindIfThereIsSelector(String_c SlcName);
	void AddNode(String_c SlcName);
	bool RemoveNodeBasedOnName(String_c n);
	static void RemoveAfter(SlcNode* Node);
	void RemoveSlcSection() {
		while (head.next) RemoveAfter(&head);
		head.next = nullptr;
	};
	~Select_list_c() {
		while (head.next) RemoveAfter(&head);
	};
};

/* Print all Selectors in a list */
void Select_list_c::PrintAll() {
	printf("SELECTOR LIST:\n");
	SlcNode* tmp = &head;
	while (tmp->next) {
		printf("%s\n", tmp->next->name.GetString());
		tmp = tmp->next;
	};
};

/* Find out if there exists a Selector named SlcName, if there is - return 1, otherwise return 0 */
bool Select_list_c::FindIfThereIsSelector(String_c SlcName) {
	SlcNode* tmp = &head;
	while (tmp->next) {
		if (tmp->next->name.CompareIfTheSame(SlcName)) return 1;
		tmp = tmp->next;
	};
	return 0;
};

/* Get the length of the list */
size_t Select_list_c::GetListLength() {
	size_t i = 0;
	SlcNode* tmp = &head;
	while (tmp->next) { 
		i++;
		tmp = tmp->next;
	};
	return i;
};

/* Find out if there exists a Selector named SlcName, if there is - return the Node containing it, otherwise return nullptr */
SlcNode* Select_list_c::FindNode(String_c SlcName) {
	SlcNode* tmp = &head;
	while (tmp->next) { 
		if (tmp->next->name.CompareIfTheSame(SlcName)) return tmp->next;
		tmp = tmp->next;
	};
	return nullptr;
};

/* Find Node at index Index; Returns the Selector Node, if not found returns nullptr; starting Position = 1 */
SlcNode* Select_list_c::FindNodeAtIndex(size_t Index) { 
	SlcNode* tmp = &head;
	size_t i = STARTINGPOSITION;
	while (tmp->next) {
		if (Index == i) return tmp->next;
		i++; tmp = tmp->next;
	};
	return nullptr;
};

/* Add new Node at the end of the list */
void Select_list_c::AddNode(String_c SlcName) {
	SlcNode* newNode = new SlcNode(SlcName);
	SlcNode* tmp = &head;
	while (tmp->next) tmp = tmp->next;
	tmp->next = newNode;
};

/* Remove Node if it has the name n, returns 1 if succesfully removed, otherwise returns 0 */
bool Select_list_c::RemoveNodeBasedOnName(String_c n) { 
	SlcNode* tmp = &head;
	while (tmp->next) {
		if (tmp->next->name.CompareIfTheSame(n)) {
			RemoveAfter(tmp);
			return 1;
		};
		tmp = tmp->next;
	};
	return 0;
};

/* Remove Node After the given Node */
void Select_list_c::RemoveAfter(SlcNode* Node) {
	SlcNode* tmp = Node->next;
	if (Node->next) {
		Node->next = Node->next->next;
		delete tmp;
	};
};