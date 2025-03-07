# M4OEP-zrue-nbortzfi-ggick-tbeucler

## Zachary Rue - Nick Bortzfield -  Fritz Gick - Thomas Beucler

### Program: 
Dungeon is a program that generates a dungeon of varying size based on user input. This project was Zac's M2OEP, and Zac, Thomas, and Fritz worked together to improve it for M3OEP. For this module, we all worked to create a screen for the user to explore the dungeon in a birds-eye view, and turn that exploration into a game. The objective of the game is to get 90% of the gold within the dungeon; the user can do this by clicking on chests that appear in rooms with treasure and they can explore the Dungeon by clicking on doors that appear as orange squares. The chests though can be trapped though so be careful! If they are trapped, a mini-game will pop up based on the lights out applied project where the user has to click on the lit-up squares to turn them off in a limited amount of time. If they fail they lose one Health. You lose if you lose all three health. 


### Module 4 Concepts used: 
GLFW, Drawing, mouse inputs, keyboard inputs, multiple screens, and graphics with C++ classes. 

### Bugs: 
Bug 1: When going through the console input section of the program, if you type your response and hit enter very quickly when confirming dungeon size, the input will not get registered and you get stuck in an endless loop. This was encountered a few times by Nick and Zac.

Bug 2: Occasionally a chest may be generated where even after clicking on it no gold is added to the user. 

Bug 3: Inconsistent hallway borders

### Future work: 
For future work, we would want to add different types of traps that require different types of mini-games and responses from the user in order to create a more complex and engaging game. We also would like to add a graphic representation of the character, and the ability for the character to hold different weapons and items in an inventory. The addition of enemies in the dungeon would also help to elevate the gameplay and create a more engaging player experience, and create more opportunities for the player to engage with the game and develop their character. We would also like to add a boss room with a boss that provides a more challenging mini-game/task for the player to complete and would drop extra gold or better items. 

### Grade:  
Main Program: 
40, I believe that our program is sufficiently complex and uses almost every concept that we talked about in module4, there is input validation for every possible input, we used GLFW, Drawing, mouse inputs, keyboard inputs, multiple screens, and graphics with C++ classes.
Interactivity of program: 20, I feel that we have an intuitive way of interacting with the program, using the mouse to move around, with clicking be to choose something. There are no minor issues that we are aware of.

#### User experience: 
20, The movement and interactions are designed to be intuitive and robust. Moving around with the mouse and clicking to interact are straightforward. 
Code organization: 20, The code is split into relevant sections. Dungeon generation and room generation and the main menu are split into their own classes and files, with the graphics being processed within the engine class, pulling from relevant methods and data in the other files, ensuring that the large program scope does not hinder the performance of the program.

#### Style and documentation: 
0, There are repost comments and lots of documentation, with clear organization.

#### Video: 
0, Video demonstrates input validation and multiple runs.

#### Lifespan of project: 
0, The lifespan of the project spans 7 days with significant contributions made on at least three separate days over 72 hours prior to the due date. 

#### Total:
100/100
