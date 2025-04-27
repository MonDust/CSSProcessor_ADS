#pragma once
#include "AttributeList_c.h"

///						SLIST_C							///

/* The Class consisting of: 
the singly linked Attribute list and singly linked Selector list; */
class Slist_c {
private:
	Attr_list_c attr_head;
	Select_list_c slc_head;
public:
	Slist_c() : attr_head(), slc_head() {};
	Attr_list_c* GetAttrList() { return &attr_head; }; /* Returns the head element for Attribute List */
	Select_list_c* GetSlcList() { return &slc_head; }; /* Returns the head element for Selection List */
	~Slist_c() {};
};

/* Copy the array Slist_c from oldArr to newArr; 
Copying works by changing the address that pointer is pointing to;
Needs number of elements to copy, will copy until that; 
Possible error if NumberOfElem bigger than size of Array */
void CopyArray(Slist_c * oldArr, Slist_c* newArr, size_t NumberOfElem) {
	for (size_t i = 0; i < NumberOfElem; i++) {
		newArr[i].GetAttrList()->GetHead()->next = oldArr[i].GetAttrList()->GetHead()->next;
		newArr[i].GetSlcList()->GetHead()->next = oldArr[i].GetSlcList()->GetHead()->next;
		oldArr[i].GetAttrList()->GetHead()->next = nullptr;
		oldArr[i].GetSlcList()->GetHead()->next = nullptr;
	};
};

void CopyWithoutRemoval(Slist_c* oldArr, Slist_c* newArr, size_t NumberOfElem) {
	for (size_t i = 0; i < NumberOfElem; i++) {
		newArr[i].GetAttrList()->GetHead()->next = oldArr[i].GetAttrList()->GetHead()->next;
		newArr[i].GetSlcList()->GetHead()->next = oldArr[i].GetSlcList()->GetHead()->next;
	};
};

/* Make an array of Slist_c smaller by one element; Needs a size of an old array 
Possible error if NumberOfElem bigger than size of Array */
Slist_c* DecreaseSizeOfArraybyOne(Slist_c * oldArr, size_t SizeOfOldArray) {
	if (SizeOfOldArray <= 1) {
		if(oldArr != nullptr) delete[] oldArr;
		return nullptr;
	};
	Slist_c* newArr = new Slist_c[SizeOfOldArray-1];
	CopyArray(oldArr,newArr,SizeOfOldArray-1);
	delete[] oldArr;
	return newArr;
};

/* Moving Sections - will move all elements of Array by one back by moving pointers (head->next); 
Index - starts at 0 ! */
void MoveSections(Slist_c* Arr, size_t Index, size_t SizeOfArr) {
	for (size_t i = Index; i < SizeOfArr - 1; i++) {
		Arr[i].GetAttrList()->GetHead()->next = Arr[i + 1].GetAttrList()->GetHead()->next;
		Arr[i].GetSlcList()->GetHead()->next = Arr[i + 1].GetSlcList()->GetHead()->next;
	};
	Arr[SizeOfArr - 1].GetAttrList()->GetHead()->next = nullptr;
	Arr[SizeOfArr - 1].GetSlcList()->GetHead()->next = nullptr;
};


///						DNODE						///

/* Doubly linked list Node - consists of array of Slists, numberOfLists */
class DNode {
public:
	Slist_c* arrOfAttrandSlc; /* Array of Attributes and Selectors */
	size_t numberOfLists; /* Number Of currently used spaces in the array */
	size_t sizeOfArray;
	DNode* prev;
	DNode* next;
	DNode() : numberOfLists(0), sizeOfArray(T_ARRNUMB), prev(nullptr), next(nullptr) {
		arrOfAttrandSlc = new Slist_c[T_ARRNUMB];
	};
	DNode(const DNode& otherNode) noexcept;
	DNode(DNode&& otherNode) noexcept;
	DNode& operator=(const DNode& otherNode) noexcept;
	DNode& operator=(DNode&& otherNode) noexcept;
	void Copy(const DNode& otherNode);
	void Copy(DNode&& otherNode);
	Slist_c* GetAtIndex(size_t Index);
	void MakeArraySmaller();
	bool DeletionOfElement(size_t Index);
	void RemoveArray() {
		if (arrOfAttrandSlc != nullptr) delete[] arrOfAttrandSlc;
		numberOfLists = 0; sizeOfArray = 0;
		arrOfAttrandSlc = nullptr;
	};
	~DNode() {
		if (arrOfAttrandSlc != nullptr) delete[] arrOfAttrandSlc;
	};
};

/* Copy DNode from other DNode */
void DNode::Copy(const DNode& otherNode) {
	if (&otherNode != this) {
		if (arrOfAttrandSlc) delete[] arrOfAttrandSlc;
		arrOfAttrandSlc = new Slist_c[otherNode.sizeOfArray];
		CopyWithoutRemoval(otherNode.arrOfAttrandSlc, arrOfAttrandSlc, otherNode.sizeOfArray);
		next = otherNode.next;
		prev = otherNode.prev;
		numberOfLists = otherNode.numberOfLists;
		sizeOfArray = otherNode.sizeOfArray;
	};
};

/* Copy DNode from other DNode */
void DNode::Copy(DNode&& otherNode) {
	arrOfAttrandSlc = otherNode.arrOfAttrandSlc;
	otherNode.arrOfAttrandSlc = nullptr;
	next = otherNode.next; otherNode.next = nullptr;
	prev = otherNode.prev; otherNode.prev = nullptr;
	numberOfLists = otherNode.numberOfLists;
	sizeOfArray = otherNode.sizeOfArray;
};

/* Copy Constructor */
DNode::DNode(const DNode& otherNode) noexcept {
	Copy(otherNode);
};

/* Copy Constructor */
DNode::DNode(DNode&& otherNode) noexcept {
	Copy(otherNode);
};

/* Copy DNode: DNode = DNode */
DNode& DNode::operator=(const DNode& otherNode) noexcept {
	if (&otherNode != this) {
		if (arrOfAttrandSlc) delete[] arrOfAttrandSlc;
		arrOfAttrandSlc = new Slist_c[otherNode.sizeOfArray];
		CopyWithoutRemoval(otherNode.arrOfAttrandSlc,arrOfAttrandSlc,otherNode.sizeOfArray);
		next = otherNode.next;
		prev = otherNode.prev;
		numberOfLists = otherNode.numberOfLists;
		sizeOfArray = otherNode.sizeOfArray;
	};
	return *this;
};

/* Copy DNode: DNode = DNode */
DNode& DNode::operator=(DNode&& otherNode) noexcept {
	arrOfAttrandSlc = otherNode.arrOfAttrandSlc;
	otherNode.arrOfAttrandSlc = nullptr;
	next = otherNode.next; otherNode.next = nullptr;
	prev = otherNode.prev; otherNode.prev = nullptr;
	numberOfLists = otherNode.numberOfLists;
	sizeOfArray = otherNode.sizeOfArray;
	return *this;
};

/* Return Slist_c element of index Index from the array of Attributes and Selectors;
Starting Position = 1 */
Slist_c* DNode::GetAtIndex(size_t Index) {
	return &(arrOfAttrandSlc[Index - STARTINGPOSITION]);
};

/* Make array smaller by one element;  
Will not change the numberOfLists -> implemented in DeletionOfElement */
void DNode::MakeArraySmaller() {
	arrOfAttrandSlc = DecreaseSizeOfArraybyOne(arrOfAttrandSlc,sizeOfArray);
	if (sizeOfArray != 0) sizeOfArray--;
};

/* Remove one section, Starting Position = 1; Will return 1 if deletion succeeds, otherwise returns 0 */
bool DNode::DeletionOfElement(size_t Index) {
	/* REMOVE ALL ATTRIBUTES AND SELECTORS */
	if (arrOfAttrandSlc != nullptr && Index <= sizeOfArray) {
		arrOfAttrandSlc[Index - STARTINGPOSITION].GetAttrList()->RemoveAttrSection();
		arrOfAttrandSlc[Index - STARTINGPOSITION].GetSlcList()->RemoveSlcSection();
		if(numberOfLists != 0) numberOfLists--;

		/* MOVE SECTIONS */
		MoveSections(arrOfAttrandSlc, Index - STARTINGPOSITION, sizeOfArray); /* CHECK: could make both functions into one, and possibly problematic with 0/1 elements, does it make sizeOfArray smaller? */
		MakeArraySmaller();
		return 1;
	};
	return 0;
};


///						DLIST_C							///

/* Doubly linked list of DNodes */
class Dlist_c {
private:
	DNode head;
	size_t NumberOfSections;
public:
	Dlist_c() : NumberOfSections(0) {};
	DNode* GetHead() { return &head; }; /* Returns pointer to head of doubly linked list Dlist_c */
	size_t GetListLength();
	void PrintAllSect();
	size_t GetNumberOfSections() const { return NumberOfSections; };
	Slist_c* GetSectionAtIndex(size_t IndexToFind);
	String_c FindSelector(size_t StructureNumber, size_t SlcNumber);
	String_c FindAttributeValue(size_t StructureNumber, String_c NameOfAttr);
	size_t GetSelectorNumberInBlock(size_t StructureNumber);
	size_t GetAttributeNumberInBlock(size_t StructureNumber);
	size_t GetNumberOfAttributesMatching(String_c AttrName);
	size_t GetNumberOfSelectorsMatching(String_c SlcName);
	String_c ReturnValueForASelector(String_c SelectorName, String_c AttrName);
	void AddNode();
	static void AddNodeAfter(DNode * Node);
	void AddSection();
	void AddAttribute(String_c AttrName, String_c AttrValue);
	void AddSelector(String_c SlcName);
	bool RemoveSection(size_t Index);
	bool RemoveAtrribute(size_t SectionIndex, String_c AttrName);
	static void RemoveNode(DNode* Node); 
	static void RemoveAfter(DNode* Node);
	~Dlist_c() {
		while (head.next) {
			RemoveAfter(&head);
		};
	};
};

/* Print all Structures in a list */
void Dlist_c::PrintAllSect() {
	printf("ALL:\n");
	DNode* tmp = &head;
	while (tmp->next) {
		for (size_t i = 0; i < tmp->next->numberOfLists; i++) {
			tmp->next->arrOfAttrandSlc[i].GetSlcList()->PrintAll();
			tmp->next->arrOfAttrandSlc[i].GetAttrList()->PrintAll();
			printf("\n");
		};
		tmp = tmp->next;
	};
};

/* Get Section (Slist_c) at index IndexToFind; Starting Position = 1 */
Slist_c* Dlist_c::GetSectionAtIndex(size_t IndexToFind) {
	size_t CurIndex = 0; DNode* tmp = &head; 
	while (CurIndex < IndexToFind && tmp->next) { 
		CurIndex += tmp->next->numberOfLists; 
		tmp = tmp->next;
	};
	if (CurIndex < IndexToFind) return nullptr;
	return &(tmp->arrOfAttrandSlc[IndexToFind - (CurIndex - tmp->numberOfLists) - STARTINGPOSITION]); 
};

/* Return Value of an Attribute named AttrName for Selector named SelectorName; 
Returns the last instance of such occurance */
String_c Dlist_c::ReturnValueForASelector(String_c SelectorName, String_c AttrName) { 
	DNode* tmp = &head; bool flag = 0;
	Slist_c* tmplistforSLC = nullptr;
	AttrNode* tmpNode = nullptr;
	while (tmp->next) {
		for (size_t i = 0; i < tmp->next->numberOfLists; i++) {
			flag = tmp->next->arrOfAttrandSlc[i].GetSlcList()->FindIfThereIsSelector(SelectorName);
			if (flag) {
				tmpNode = tmp->next->arrOfAttrandSlc[i].GetAttrList()->FindNode(AttrName);
				if (tmpNode != nullptr) {
					tmplistforSLC = &(tmp->next->arrOfAttrandSlc[i]);
				};
				flag = 0;
			}
		};
		tmp = tmp->next;
	};
	if (tmplistforSLC != nullptr) {
		tmpNode = tmplistforSLC->GetAttrList()->FindNode(AttrName);
		if (tmpNode != nullptr) return tmpNode->value;
	};
	String_c StrEmpty;
	return StrEmpty;
};

/* Function tha returns number of occurence of Selector named SlcName in the whole structure */ 
size_t Dlist_c::GetNumberOfSelectorsMatching(String_c SlcName) { 
	DNode* tmp = &head;	size_t numberSlc = 0;
	while (tmp->next) {
		for (size_t i = 0; i < tmp->next->numberOfLists; i++) {
			numberSlc += tmp->next->arrOfAttrandSlc[i].GetSlcList()->FindIfThereIsSelector(SlcName);
		};
		tmp = tmp->next;
	};
	return numberSlc;
};

/* Function tha returns number of occurence of Attributes named AttrName in the whole structure */ 
size_t Dlist_c::GetNumberOfAttributesMatching(String_c AttrName) { 
	DNode* tmp = &head;	size_t numberAttr = 0;
	while (tmp->next) {
		for (size_t i = 0; i < tmp->next->numberOfLists; i++) {
			numberAttr += tmp->next->arrOfAttrandSlc[i].GetAttrList()->FindIfThereIsAttributes(AttrName); /* could be exchange for: withRemoval */
		};
		tmp = tmp->next;
	};
	return numberAttr;
};

/* Remove Attribute name AttrName in Section of index SectionIndex, if the Section becomes empty, remove Section; 
If operation is succesfull return 1, otherwise return 0; Starting Position = 1  */
bool Dlist_c::RemoveAtrribute(size_t SectionIndex, String_c AttrName) { 
	Slist_c* tmpSection = GetSectionAtIndex(SectionIndex);
	if (tmpSection != nullptr) {
		bool Removed = tmpSection->GetAttrList()->RemoveNodeBasedOnName(AttrName);
		if (Removed) {
			if (tmpSection->GetAttrList()->GetListLength() == 0) {
				RemoveSection(SectionIndex);
			};
			return 1;
		};
	};
	return 0;
};

/* Find Selector of index SlcNumber in Node StructureNumber;
Returns a name of the Selector, if not found returns empty string */
String_c Dlist_c::FindSelector(size_t StructureNumber, size_t SlcNumber) {
	Slist_c* tmpSection = GetSectionAtIndex(StructureNumber);
	if (tmpSection != nullptr) {
		SlcNode* tmpNode = tmpSection->GetSlcList()->FindNodeAtIndex(SlcNumber);
		if (tmpNode != nullptr) return tmpNode->name;
	};
	String_c StrEmpty;
	return StrEmpty;
};

/* Find Attribute value of Attribute named NameOfAttr in Node StructureNumber;
Returns a value of Attribute, if not found returns empty string */
String_c Dlist_c::FindAttributeValue(size_t StructureNumber, String_c NameOfAttr) {
	Slist_c* tmpSection = GetSectionAtIndex(StructureNumber);
	if (tmpSection != nullptr) {
		AttrNode* tmpNode = tmpSection->GetAttrList()->FindNode(NameOfAttr);
		if (tmpNode != nullptr) return tmpNode->value;
	};
	String_c StrEmpty;
	return StrEmpty;
};

/* Returns number of Selectors in the Structure of index StructureNumber */
size_t Dlist_c::GetSelectorNumberInBlock(size_t StructureNumber) {
	Slist_c* tmpSection = GetSectionAtIndex(StructureNumber);
	if(tmpSection != nullptr) return tmpSection->GetSlcList()->GetListLength();
	return 0;
};

/* Returns number of Attributes in the Structure of index StructureNumber */
size_t Dlist_c::GetAttributeNumberInBlock(size_t StructureNumber) { /* Possibly problematic for repeatition */
	Slist_c* tmpSection = GetSectionAtIndex(StructureNumber);
	if(tmpSection != nullptr) return tmpSection->GetAttrList()->GetListLength();
	return 0;
};

/* Add new Section */
void Dlist_c::AddSection() {
	DNode* tmp = &head;
	if (tmp->next) {
		while (tmp->next) tmp = tmp->next;
		if (tmp->numberOfLists < tmp->sizeOfArray) { tmp->numberOfLists++; NumberOfSections++; }
		else {
			AddNodeAfter(tmp);
			if (tmp->next) { tmp->next->numberOfLists++; NumberOfSections++; };
		};
	}
	else {
		AddNodeAfter(tmp);
		if (tmp->next) { tmp->next->numberOfLists++; NumberOfSections++; };
	};
};

/* Add new attribute to current Section (last existing Section) */
void Dlist_c::AddAttribute(String_c AttrName, String_c AttrValue) {
	DNode* tmp = &head;
	while (tmp->next) tmp = tmp->next;
	tmp->arrOfAttrandSlc[tmp->numberOfLists - STARTINGPOSITION].GetAttrList()->AddNodeCheckIfExists(AttrName, AttrValue);
};

/* Add new Selector to current Section (last existing Section) */
void Dlist_c::AddSelector(String_c SlcName) {
	DNode* tmp = &head;
	while (tmp->next) tmp = tmp->next;
	tmp->arrOfAttrandSlc[tmp->numberOfLists - STARTINGPOSITION].GetSlcList()->AddNode(SlcName); /* CHECK - is there a need to skip duplicate Selectors ? */
};

/* Remove Section at index Index, if opperation succeeds return 1, otherwise return 0; Starting Position = 1 */
bool Dlist_c::RemoveSection(size_t Index) {
	size_t CurIndex = 0; DNode* tmp = &head; bool Removed = 1;
	if (Index > NumberOfSections) return 0;
	while (CurIndex < Index && tmp->next) {	
		CurIndex += tmp->next->numberOfLists;	
		tmp = tmp->next;	
	};
	if (CurIndex < Index) return 0;
	Removed = tmp->DeletionOfElement(Index - (CurIndex - tmp->numberOfLists));
	if (Removed) {
		if (tmp->sizeOfArray == 0) RemoveNode(tmp);
		if(NumberOfSections != 0 ) NumberOfSections--;
		return 1;
	};
	return 0;
};

/* Get the length of Doubly linked list */
size_t Dlist_c::GetListLength() {
	size_t i = 0;
	DNode* tmp = &head;
	while (tmp->next) {
		i++;
		tmp = tmp->next;
	};
	return i;
};

/* Adding a New Node */
void Dlist_c::AddNode() {
	DNode* newNode = new DNode();
	DNode* tmp = &head;
	while (tmp->next) tmp = tmp->next;
	tmp->next = newNode;
	newNode->prev = tmp;
};

/* Adding new Node after the Node */
void Dlist_c::AddNodeAfter(DNode* Node) {
	DNode* newNode = new DNode();
	Node->next = newNode;
	newNode->prev = Node;

};

/* Remove the argument Node */
void Dlist_c::RemoveNode(DNode* Node) {
	DNode* tmp = Node;
	if (Node) {
		if (Node->next) Node->next->prev = Node->prev;
		if (Node->prev) Node->prev->next = Node->next;
		delete tmp;
	};
};

/* Remove the Node after the argument Node */
void Dlist_c::RemoveAfter(DNode* Node) {
	DNode* tmp = Node->next;
	if (Node->next) {
		if (Node->next->next) Node->next->next->prev = Node->next->prev;
		Node->next = Node->next->next;
		delete tmp;
	};
};