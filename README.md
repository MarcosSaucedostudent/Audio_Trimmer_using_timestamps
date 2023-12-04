# Macro_repos / Audio Trimmer using Timestamps

![Language](https://img.shields.io/badge/language-C++-yellow.svg?style=flat-square)

Repository for projects

Prerequisites:

Need GNU compiler C++

C++ IDE of your choice
- - - - - - - - - - - 
This code will separate and/or trim a WAV file you provide using a txt file of timestamps you also provide.

Example: (timestamps for song Colour My World - Chicago)

\- \- \- \- \- \- \- \- \-

0:00 piano solo      

0:59 vocal solo  

1:55 flute solo      
\- \- \- \- \- \- \- \- \- 

\+

Colour My World.wav 

=

piano solo.wav | vocal solo.wav | flute solo.wav

How to use:
+ Download trimmer.h, trimmer.cpp, and AudioFile.h
+ Open trimmer.cpp with C++ IDE of your choice.
+ Put your txt file name and wav file name in the code.
+ Open a terminal in the directory containing the wav file and txt file and compile using command: g++ -std=c++23 trimmer.cpp -o trim
+ Run the executable with command ./trim

How to trim:

If you do not want a certain portion of audio write down "delete" as the song name in the txt file. Like this: 

\- \- \- \- \- \- \- \- \-

0:00 piano solo      

0:59 delete  

1:55 flute solo      
\- \- \- \- \- \- \- \- \- 

With this txt file, you will not get vocal solo.wav like the previous example.
