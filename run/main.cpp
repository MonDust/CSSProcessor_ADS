#pragma once
#include "DStructure_c.h"

/* Check If an array of chars is a digif, return 0 if it is not, return 1 if it is; Will return that it is a digit for an Empty array */
bool IsDigit(char* Arr) { /* Does not ommit spaces */
    while (*Arr != ENDOFSTRING) {
        if (!((*Arr >= '0') && (*Arr <= '9'))) return 0;
        Arr++;
    };
    return 1;
};

/* Read Input until a certain character, to read to the endline - pass the ENDLINE, will stop after no stdin */
String_c ReadInput(char UntilChar) {
    String_c Str; String_c EmptyStr;
    char Character;
    char BufferArr[BUFFERSTRING] = { };
    bool flag = 0, j_flagMakeSmaller = 0;

    if (scanf("%c", &Character) == EOF || feof(stdin)) return EmptyStr; 

    while (!(Character == ENDLINE || Character == UntilChar)) {
        for (size_t j = 0; j < BUFFERSTRING - SPACEFORENDCHAR; j++) {
            if (j_flagMakeSmaller) { j--; j_flagMakeSmaller = 0; };
            if (Character == ENDLINE || Character == UntilChar) {
                flag = 1;   BufferArr[j] = ENDOFSTRING;
                break;
            };

            if (Character < SPACE) /* Take the Index back - skip all chars smaller than SPACE */
            {
                if (j != 0) j--;
                else j_flagMakeSmaller = 1;
            }
            else {
                BufferArr[j] = Character;
                BufferArr[j + 1] = ENDOFSTRING;
            };
            if (scanf("%c", &Character) == EOF || feof(stdin)) { flag = 1;  break; };
        };
        Str.AddStr(BufferArr);
        if (flag) break;
    };
    return Str;
};

/* Instruction: Digit + S */
size_t DigitSelectorInstruction(Dlist_c* Structure, size_t FirstNumber) {
    String_c String = ReadInput(ENDLINE);
    size_t End = String.FindInString(RESUME_READING);
    if (End != 0) return End;
    size_t NumberOfSections = Structure->GetNumberOfSections();
    if (FirstNumber < NumberOfSections) {
        if (String.CompareIfTheSame(NUMB_OF_SECTION_CH)) /* THE INSTRUCTION: DIGIT,S,? */
        {
            size_t NumberOfSelectors = Structure->GetSelectorNumberInBlock(FirstNumber);
            printf("%zu,S,? == %zu\n", FirstNumber, NumberOfSelectors);
        }
        else if (IsDigit(String.GetString())) /* THE INSTRUCTION: DIGIT,S,DIGIT */
        {
            if (String.GetString()[0] != ENDOFSTRING) {
                size_t SecondNumber;    sscanf_s(String.GetString(), "%zu", &SecondNumber);
                String_c FoundSelector;
                FoundSelector = Structure->FindSelector(FirstNumber, SecondNumber); /* FirstNumber - section, SecondNumber - selector */
                if (FoundSelector.GetString()[0] != ENDOFSTRING) printf("%zu,S,%zu == %s\n", FirstNumber, SecondNumber, FoundSelector.GetString());
            };
        };
    };
    return End;
};

/* Instruction: Digit + A */
size_t DigitAttributeInstruction(Dlist_c* Structure, size_t Number) {
    String_c String = ReadInput(ENDLINE);
    size_t End = String.FindInString(RESUME_READING);
    if (End != 0) return End;
    size_t NumberOfSections = Structure->GetNumberOfSections();
    if (Number < NumberOfSections) {
        if (String.CompareIfTheSame(NUMB_OF_SECTION_CH))  /* THE INSTRUCTION: DIGIT,A,? */
        {
            size_t NumberOfAttributes = Structure->GetAttributeNumberInBlock(Number);
            printf("%zu,A,? == %zu\n", Number, NumberOfAttributes);
        }
        else if (String.GetString()[0] != ENDOFSTRING) /* THE INSTRUCTION: DIGIT,A,STRING */
        {
            String_c FoundValue = Structure->FindAttributeValue(Number, String);
            if (FoundValue.GetString()[0] != ENDOFSTRING) printf("%zu,A,%s == %s\n", Number, String.GetString(), FoundValue.GetString());
        };
    };
    return End;
};

/* Instruction: Digit + D */
size_t DeletionInstruction(Dlist_c* Structure, size_t Number) {
    String_c String = ReadInput(ENDLINE);
    size_t End = String.FindInString(RESUME_READING);
    if (End != 0) return End;

    size_t NumberOfSections = Structure->GetNumberOfSections();
    if (Number < NumberOfSections) {
        bool Removed = 0;
        if (String.CompareIfTheSame(SELECT_ALL_CH))  /* THE INSTRUCTION: DIGIT,D,* */
        {
            Removed = Structure->RemoveSection(Number);
            if (Removed) printf("%zu,D,* == deleted\n", Number);
        }
        else if (String.GetString()[0] != ENDOFSTRING) /* THE INSTRUCTION: DIGIT,D,STRING (ATTRIBUTE NAME) */
        {
            Removed = Structure->RemoveAtrribute(Number, String);
            if (Removed) printf("%zu,D,%s == deleted\n", Number, String.GetString());
        };
    };
    return End;
};

/* Function for when Instruction starts with DIGIT */
size_t TheInstructionStartsWithDIGIT(Dlist_c* Structure, size_t FirstNumber) {
    String_c Instruction = ReadInput(COMMA);
    size_t End = Instruction.FindInString(RESUME_READING);
    if (End != 0) return End;
    if (Instruction.CompareIfTheSame(S_SELECTOR_CH)) /* S - SELECTOR */
    {
        End = DigitSelectorInstruction(Structure, FirstNumber);
    }
    else if (Instruction.CompareIfTheSame(A_ATTRIBUTE_CH)) /* A - ATTRIBUTE */
    {
        End = DigitAttributeInstruction(Structure, FirstNumber);
    }
    else if (Instruction.CompareIfTheSame(D_REMOVE_CH)) { /* D - DELETE/REMOVE */
        End = DeletionInstruction(Structure, FirstNumber);
    }
    else {
        Instruction = ReadInput(ENDLINE);
    }
    return End;
};

/* Function for when Instruction starts with STRING */
size_t TheInstructionStartsWithSTRING(Dlist_c* Structure, String_c FirstString) {
    String_c Instruction = ReadInput(COMMA);
    size_t End = Instruction.FindInString(RESUME_READING);
    if (End != 0) return End;
    if (Instruction.CompareIfTheSame(S_SELECTOR_CH)) /* S - SELECTOR */
    {
        Instruction = ReadInput(ENDLINE);
        if (Instruction.CompareIfTheSame(NUMB_OF_SECTION_CH)) /* THE INSTRUCTION: STRING,S,? */
        {
            size_t NumberOfSelectors = Structure->GetNumberOfSelectorsMatching(FirstString);
            printf("%s,S,? == %zu\n", FirstString.GetString(), NumberOfSelectors);
        };
    }
    else if (Instruction.CompareIfTheSame(A_ATTRIBUTE_CH)) /* A - ATTRIBUTE */
    {
        Instruction = ReadInput(ENDLINE);
        if (Instruction.CompareIfTheSame(NUMB_OF_SECTION_CH)) /* STRING,A,? */
        {
            size_t NumberOfAttributes = Structure->GetNumberOfAttributesMatching(FirstString);
            printf("%s,A,? == %zu\n", FirstString.GetString(), NumberOfAttributes);
        };
    }
    else if (Instruction.CompareIfTheSame(E_FIND_CH)) /* E - EVERYTHING/FIND */
    {
        Instruction = ReadInput(ENDLINE);
        if (Instruction.GetString()[0] != ENDOFSTRING) {
            String_c ReturningValue = Structure->ReturnValueForASelector(FirstString, Instruction);
            if (ReturningValue.GetString()[0] != ENDOFSTRING) printf("%s,E,%s == %s\n", FirstString.GetString(), Instruction.GetString(), ReturningValue.GetString());
        };
    }
    else {
        Instruction = ReadInput(ENDLINE);
    };
    End = Instruction.FindInString(RESUME_READING);
    return End;
};

/* Function Processing Instructions in CSS Processor;
Takes the structure being processed as an argument */
void DoInstructions(Dlist_c* Structure) {
    String_c Instruction;   size_t End = 0;
    Instruction = ReadInput(COMMA);
    End = Instruction.FindInString(RESUME_READING); /* End - will search for "****" */

    while (End == 0) {
        if (Instruction.CompareIfTheSame(NUMB_OF_SECTION_CH)) /* THE INSTRUCTION: ? */
        {
            size_t NumberOfSections = Structure->GetNumberOfSections();
            if (NumberOfSections != 0) NumberOfSections--;
            printf("? == %zu\n", NumberOfSections); /* The code adds the Strucute, before it is filled */
        }
        else if (IsDigit(Instruction.GetString())) /* THE INSTRUCTION STARTS WITH: DIGIT */
        {
            if (Instruction.GetString()[0] != ENDOFSTRING) {
                size_t FirstNumber;     sscanf_s(Instruction.GetString(), "%zu", &FirstNumber);
                End = TheInstructionStartsWithDIGIT(Structure, FirstNumber);
            };
        }
        else /* THE INSTRUCTION STARTS WITH: STRING */
        {
            End = TheInstructionStartsWithSTRING(Structure, Instruction);
        };
        if (feof(stdin) || End != 0) break;
        Instruction = ReadInput(COMMA);
        End = Instruction.FindInString(RESUME_READING); /* CHECK: Is there End in the same line as instruction? */
    };
};

/* Append the Attribute List of the current Node (the last Node) */
void AppendStructure_Attr(String_c Str, Dlist_c* Structure) {
    String_c name, value, value_2;   bool Added = 1;
    size_t PositionSemicolon = 0, PositionEnd = 0;

    if (Str.GetString()[0] == CURLY_BRACKETS2) return; /* Find if there is a possibility of {}; CHECK: Is { } possible? */

    while (Str.GetString()[0] != ENDOFSTRING) {
        if (Str.GetString()[0] == CURLY_BRACKETS2) break;
        size_t PositionColon = Str.FindInString(COLON);

        if (PositionColon != 0) {
            Added = 0;
            name = Str.ReturnStringUntil(PositionColon);
            PositionSemicolon = Str.FindInString(SEMICOLON);
            PositionEnd = Str.FindInString(CURLY_BRACKETS2);
            if (PositionSemicolon != 0) {
                Added = 1;
                value = Str.ReturnStringUntil(PositionSemicolon);
                Structure->AddAttribute(name, value);
            }
            else if (PositionEnd != 0) {
                Added = 1;
                value = Str.ReturnStringUntil(PositionEnd);
                Structure->AddAttribute(name, value);   break;
            }
            else break;
        }
        else break;
    };
    while (PositionEnd == 0) {
        if (Added) name = ReadInput(COLON);
        if (name.GetString()[0] != ENDOFSTRING) {
            if (name.FindInString(CURLY_BRACKETS2)) PositionEnd = 1;
            else {
                value = ReadInput(SEMICOLON);
                if (value.GetString()[0] != ENDOFSTRING) {
                    PositionEnd = value.FindInString(CURLY_BRACKETS2);
                    if (PositionEnd > 1) {
                        value_2 = value.ReturnStringUntil(PositionEnd);
                        Structure->AddAttribute(name, value_2);
                        Added = 1;
                    }
                    else {
                        Structure->AddAttribute(name, value);
                        Added = 1;
                    }; }; }; };
    };
    Structure->AddSection();
};

/* Append the Structure List of the current Node (the last Node) */
void AppendStructure_Slc(String_c Str, Dlist_c* Structure, size_t whereCurly) {
    String_c Name;  size_t Position;
    if (whereCurly == 1) {
        Name = Str.ReturnStringUntil(whereCurly);
        AppendStructure_Attr(Str, Structure);
    }
    else if (whereCurly == 0) {
        if (Str.GetString()[0] == ENDOFSTRING) return;
        Position = Str.FindInString(COMMA);
        while (Position > 1) {
            Name = Str.ReturnStringUntil(Position);
            Structure->AddSelector(Name);
            Position = Str.FindInString(COMMA);
        };
        if (Str.GetString()[0] != ENDOFSTRING) Structure->AddSelector(Str);
    }
    else {
        Position = Str.FindInString(COMMA);
        while (Position > 1) {
            if (whereCurly < Position) break;
            Name = Str.ReturnStringUntil(Position);
            Structure->AddSelector(Name);
            Position = Str.FindInString(COMMA);
            whereCurly = Str.FindInString(CURLY_BRACKETS1);
        };
        Name = Str.ReturnStringUntil(whereCurly);
        Structure->AddSelector(Name);
        AppendStructure_Attr(Str, Structure);
    };
};

/* Check to what category goes the Input */
void CheckTheInput(String_c Str, Dlist_c* Structure) {
    size_t Position = 0;
    Position = Str.FindInString(START_OF_INSTR);
    if (Position != 0) {
        DoInstructions(Structure);
    }
    else {
        Position = Str.FindInString(CURLY_BRACKETS1);
        AppendStructure_Slc(Str, Structure, Position);
    };
};



int main() {
    String_c Str;   Dlist_c Structure;
    Structure.AddSection();

    Str = ReadInput(ENDLINE);
    while (!feof(stdin)) {
        CheckTheInput(Str, &Structure);
        Str = ReadInput(ENDLINE);
    };
    return 0;
};