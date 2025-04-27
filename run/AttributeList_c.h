#pragma once
#include "SelectorList_c.h"

/* Node - containing an Attribute: a name, a value and a pointer to the next Attribute */
class AttrNode {
public:
	String_c name;
	String_c value;
	AttrNode* next;
	AttrNode() : name(), value(), next(nullptr) { };
	AttrNode(String_c AttrName, String_c AttrValue): name(AttrName), value(AttrValue), next(nullptr) {}; /* CHANGED */
	void ChangeValue(String_c AttrValue) {
		value = AttrValue;
	};
	~AttrNode() {};
};

/* Singly linked list for Attributes, containting head element of class Attribute Node */
class Attr_list_c {
private:
	AttrNode head;
public:
	Attr_list_c() : head() {};
	void PrintAll();
	AttrNode * GetHead() { return &head; };
	size_t GetListLength();
	AttrNode* FindNodeAtIndex(size_t Index);
	AttrNode* FindNode(String_c AttrName);
	bool FindIfThereIsAttributes(String_c AttrName);
	bool FindIfThereIsAttributes_Removal(String_c AttrName);
	void AddNode(String_c AttrName, String_c AttrValue);
	void AddNodeCheckIfExists(String_c AttrName, String_c AttrValue);
	bool RemoveNodeBasedOnName(String_c n);
	static void RemoveAfter(AttrNode* Node);
	void RemoveAttrSection() {
		while (head.next) RemoveAfter(&head);
		head.next = nullptr;
	};
	~Attr_list_c() {
		while (head.next) RemoveAfter(&head);
	};
};

/* Print all Attributes in a list */
void Attr_list_c::PrintAll() {
	printf("ATTRIBUTE LIST:\n");
	AttrNode* tmp = &head;
	while (tmp->next) {
		printf("name: %s | value: %s\n", tmp->next->name.GetString(), tmp->next->value.GetString());
		tmp = tmp->next;
	};
};

/* Find out if there exists an Attribute named AttrName, if there is - return 1, otherwise return 0; + removal of attributes with reapiting names */
bool Attr_list_c::FindIfThereIsAttributes_Removal(String_c AttrName) { 
	AttrNode* tmp = &head;
	size_t NumberOfMatchingAttributes = 0;
	while (tmp->next) {
		if (tmp->next->name.CompareIfTheSame(AttrName)) {
			NumberOfMatchingAttributes++;
		};
	};
	tmp = &head;
	while (NumberOfMatchingAttributes > 1) {
		while (tmp->next) {
			if (tmp->next->name.CompareIfTheSame(AttrName)) {
				RemoveAfter(tmp);
				NumberOfMatchingAttributes--;
			}; };
	};
	if (NumberOfMatchingAttributes >= 1) return 1;
	else return 0;
};

/* Find out if there exists an Attribute named AttrName, if there is - return 1, otherwise return 0 */
bool Attr_list_c::FindIfThereIsAttributes(String_c AttrName) { 
	AttrNode* tmp = &head;
	while (tmp->next) {
		if (tmp->next->name.CompareIfTheSame(AttrName)) return 1;
		tmp = tmp->next;
	};
	return 0;
};

/* Get the length of the list */
size_t Attr_list_c::GetListLength() {
	size_t i = 0;
	AttrNode* tmp = &head;
	while (tmp->next) {
		i++;
		tmp = tmp->next;
	};
	return i;
};

/* Find out if there exists an Attribute named AttrName, if there is - return the Node containing it, otherwise return nullptr */
AttrNode* Attr_list_c::FindNode(String_c AttrName) {
	AttrNode* tmp = &head;
	while (tmp->next) {
		if (tmp->next->name.CompareIfTheSame(AttrName)) return tmp->next;
		tmp = tmp->next;
	};
	return nullptr;
};

/* Find Node at index Index; starting Position = 1 */
AttrNode* Attr_list_c::FindNodeAtIndex(size_t Index) {
	AttrNode* tmp = &head;
	size_t i = 0;
	while (tmp) {
		if (Index == i) return tmp;
		i++; tmp = tmp->next;
	};
	return nullptr;
};

/* Add new Node if doesn't exist, else update value of the Attribute */
void Attr_list_c::AddNodeCheckIfExists(String_c AttrName, String_c AttrValue) {
	AttrNode* tmpNode = FindNode(AttrName);
	if (tmpNode != nullptr) tmpNode->ChangeValue(AttrValue);
	else AddNode(AttrName, AttrValue);
};

/* Add new Node at the end of the list */
void Attr_list_c::AddNode(String_c AttrName, String_c AttrValue) {
	AttrNode* newNode = new AttrNode(AttrName, AttrValue);
	AttrNode* tmp = &head;
	while (tmp->next) tmp = tmp->next;
	tmp->next = newNode;
};

/* Remove Node if it has the name n, returns 1 if succesfully removed, otherwise returns 0 */
bool Attr_list_c::RemoveNodeBasedOnName(String_c n) { 
	AttrNode* tmp = &head;
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
void Attr_list_c::RemoveAfter(AttrNode* Node) {
	AttrNode* tmp = Node->next;
	if (Node->next) {
		Node->next = Node->next->next;
		delete tmp;
	};
};