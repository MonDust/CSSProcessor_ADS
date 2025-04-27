# CSSProcessor_ADS
## Description
Project implemented for Algorithms and Data Structure course.

## Instuctions
The goal of the task is to write a simple CSS processing engine. As part of the task, you need 
to read CSS sections interleaved with command sections from standard input. CSS sections 
should be parsed and placed in the appropriate structures, and command sections should be 
parsed and executed, printing any results to standard output (after ==). 
CSS.

### Results and all information about the project
Full intstruction available in Instructions.txt. Results are available in the same file.

### Example:
Example:
```
#breadcrumb  
{ 
width: 80%; 
font-size: 9pt; 
} 
h1, body { 
min-width: 780px; 
margin: 0; 
padding: 0; 
font-family: "Trebuchet MS", "Lucida Grande", Arial; 
font-size: 85%; 
color: #666666; 
} 
h1, h2, h3, h4, h5, h6 {color: #0066CB;} 
???? 
? 
1,S,? 
1,S,1 
1,A,? 
2,A,font-family 
h1,S,? 
color,A,? 
h1,E,color 
1,A,padding 
1,D,* 
? 
2,D,color 
? 
**** 
h1, h2, h3, h4, h5, h6 {color: #0066FF;} 
???? 
?
```
Result: 
```
? == 3 
1,S,? == 1 
1,S,1 == #breadcrumb 
1,A,? == 2 
2,A,font-family == "Trebuchet MS", "Lucida Grande", Arial 
h1,S,? == 2 
color,A,? == 2 
h1,E,color == #0066CB 
1,D,* == deleted 
? == 2 
2,D, color == deleted 
? == 1 
? == 2
```

## Author
O. Paszkiewicz 2023
