QUESTION 3 EXPLANATION
----------------------

This file is made to go along with my question 3 program solution. I built the program using visual studio 2015 in C++. The entire visual studio project is contained within  the file ConsoleApplication1 with the source code being in Question3Solution.cpp

Implementation)

I implemented the solution using data structures (structs) in C++. I created a data structure of my own that creates the grid as well as other helping structures for iterating through the grid structure and for analyzing it for printing. The functions are all separated appropriately and passed so that it follows the DRY Principle of programming. The process basically works by picking the upper left portion of the grid and following down a path until it leads to 9. Once a path is completed the algorithm drops back by one node and makes a new path to see if any other nodes besides the one already taken lead to 9. It works in this way for each node until the entire grid is analyzed. Afterwords it deletes duplicates and prints

Larger Grid/Scalability) 

Basically, the algorithm portion of my program can be scaled to any grid size (as well as I can tell). This is because I attempted to make the algorithm that scans the grid unknowing of the underlying structure; each node just scans what is around it without knowing the size of the grid. The primary problem with my program is grid creation. I manually inputed the grid structure to be 3x3 so any larger structure at this point would have to be manually put together if you look closely at the code. I'm sure that an algorithm could be used to create the grid too but I did not implement this because of time constraints (I barely learned of this project a few weeks ago) and because unlike any nxn grid where n > 3 each node in a 3x3 grid does not have the same characteristics to any other node in the structure. So, regretably, hardcoding the grid was not the most scalable option but the best choice at the time. 

Hopefully if any actual reading of my program occurs it is highly readable and all decisions are perfectly understandable. Thanks!