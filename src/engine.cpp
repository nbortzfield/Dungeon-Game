#include "engine.h"
#include "Dungeon.h"
#include "User_Character.h"
#include <ostream>
using namespace std;
enum state {start, play, minigameStartScreen, minigame, win, over, loss};
state screen;
// Colors
color originalFill, hoverFill, pressFill;
color lightOn, lightOff, hoverOn, hoverOff;
int currentRoomIndex;
Engine::Engine() : keys() {
    this->initWindow();
    this->initShaders();
    this->initShapes();

    screen = start;

    currentRoomIndex = 0; // Initialize globally, not inside any function

    load_dungeon(runDungeon);

    initializeCurrentRoomIndex();

    winGold = (runDungeon.get_total_treasure() * .9);


    // door and chest generation after dungeon is generated
    generateDoors();
    generateChests();

    originalFill = {1, 0, 0, 1};
    hoverFill.vec = originalFill.vec + vec4{0.5, 0.5, 0.5, 0};
    pressFill.vec = originalFill.vec - vec4{0.5, 0.5, 0.5, 0};

    // for the minigame =============================
    rectClicked.resize(rectArray.size(), false);
    lightOn = {1, 0, 0, 1};
    lightOff = {0.5, 0.5, 0.5, 1};
    hoverOn = {211, 0, 0 ,1};
    hoverOff = {0, 0, 0 ,0};
    numClicks = 0;
}
Engine::~Engine() {}
void Engine::initializeCurrentRoomIndex() {
// Setting the index of the current room
// This will change with every door click, first we check that we do not start on a boss room
    // cout << "Initial Room Index set to: " << currentRoomIndex << endl;
    /* if (runDungeon.get_vecRooms().at(1).get_type() != "Boss") {
         currentRoomIndex++;
         cout << "boss room at zero" << endl;
     }*/
}
unsigned int Engine::initWindow(bool debug) {
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);
    window = glfwCreateWindow(width, height, "engine", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }
    // OpenGL configuration
    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSwapInterval(1);
    return 0;
}

void Engine::initShaders() {
    // load shader manager
    shaderManager = make_unique<ShaderManager>();
    // Load shader into shader manager and retrieve it
    shapeShader = this->shaderManager->loadShader("../res/shaders/shape.vert", "../res/shaders/shape.frag",  nullptr, "shape");
    // Configure text shader and renderer
    textShader = shaderManager->loadShader("../res/shaders/text.vert", "../res/shaders/text.frag", nullptr, "text");
    fontRenderer = make_unique<FontRenderer>(shaderManager->getShader("text"), "../res/fonts/MxPlus_IBM_BIOS.ttf", 24);
    // Set uniforms
    textShader.setVector2f("vertex", vec4(100, 100, .5, .5));
    shapeShader.use();
    shapeShader.setMatrix4("projection", this->PROJECTION);
}

void Engine::initShapes() {
    // Base of the room aka floor centered in the middle. covers 90% of the total size (1540 x 840) * .90
    baseRoom = make_unique<Rect>(shapeShader, vec2{width/2, height/2}, vec2{1386, 756}, color{0.662, 0.662, 0.662, 1});
    // wall details
    float wallThickness = 60.0f;
    float wallLength = 1386.0f;
    leftWall = make_unique<Rect>(shapeShader, vec2{width/2 - 693, height/2}, vec2{wallThickness, 756}, color{0.45, 0.45, 0.45, 1});
    rightWall = make_unique<Rect>(shapeShader, vec2{width/2 + 693, height/2}, vec2{wallThickness, 756}, color{0.45, 0.45, 0.45, 1});
    topWall = make_unique<Rect>(shapeShader, vec2{width/2, height/2 + 378}, vec2{1386, wallThickness}, color{0.45, 0.45, 0.45, 1});
    bottomWall = make_unique<Rect>(shapeShader, vec2{width/2, height/2 - 378}, vec2{1386, wallThickness}, color{0.45, 0.45, 0.45, 1});
    openChest = make_unique<Rect>(shapeShader, vec2{width/2, height/2}, vec2{100, 50}, color{0.588, 0.294, 0.0, 1});
    closedChest = make_unique<Rect>(shapeShader, vec2{width/2, height/2}, vec2{100, 50}, color{0.588, 0.294, 0.0, 1});
    treasure = make_unique<Rect>(shapeShader, vec2{width/2, height/2}, vec2{50, 25}, color{1, 1, 1, 1});

    //Head
    boss.push_back(make_unique<Rect>(shapeShader, vec2{width/2, height/2}, vec2{100,100 }, color{1, 0, 0, 1}));
    //Body
    boss.push_back (make_unique<Rect>(shapeShader, vec2{width/4, height/2}, vec2{100,300 }, color{1, 0, 0, 1}));
    //Arms
    boss.push_back (make_unique<Rect>(shapeShader, vec2{width/8, height/2}, vec2{50,100 }, color{1, 0, 0, 1}));
    boss.push_back(make_unique<Rect>(shapeShader, vec2{width/8, height/2}, vec2{50,100 }, color{1, 0, 0, 1}));
    //Legs
    boss.push_back(make_unique<Rect>(shapeShader, vec2{width/4, height/2}, vec2{50,100 }, color{1, 0, 0, 1}));
    boss.push_back(make_unique<Rect>(shapeShader, vec2{width/4, height/2}, vec2{50,100 }, color{1, 0, 0, 1}));
    //Eyes
    boss.push_back(make_unique<Rect>(shapeShader, vec2{width/3, height/2}, vec2{20,20 }, color{0, 0, 0, 1}));
    boss.push_back(make_unique<Rect>(shapeShader, vec2{width/5, height/2}, vec2{20,20 }, color{0, 0, 0, 1}));
    bossHead = make_unique<Rect>(shapeShader, vec2{width/2, height/2}, vec2{500, 500}, color{1,0,0,1});
    bossBody = make_unique<Rect>(shapeShader, vec2{width/2, height/2}, vec2{100, 50}, color{0.588, 0.294, 0.0, 1});

    // FOR THE MINIGAME ================================
    // initialize shapes of the game
    int rows = 5;
    int cols = 5;
    int spacing = 20;
    int rectWidth = 100;
    int rectHeight = 100;
    int highligtSpacing = 10;
    int highlightWidth = 110;
    int highlightHeight = 110;
    //create the grid of rectangles (the highlight)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int x = j * (highlightWidth + highligtSpacing) + highligtSpacing + 135;
            int y = i * (highlightHeight + highligtSpacing) + highligtSpacing + 135;
            auto button3 = make_unique<Rect>(shapeShader, vec2{x, y}, vec2{highlightWidth, highlightHeight}, hoverOff);
            rectHLArray.push_back(std::move(button3));
        }
    }
    //create the grid of rectangles
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int x = j * (rectWidth + spacing) + spacing + 125;
            int y = i * (rectHeight + spacing) + spacing + 125;
            auto button2 = make_unique<Rect>(shapeShader, vec2{x, y}, vec2{rectWidth, rectHeight}, lightOn);
            rectArray.push_back(std::move(button2));
            rectClicked.push_back(false);
        }
    }
    //begin the game with a random number of "pre-clicked" squares to make the puzzle
    int numPreClicked = 3 + (rand() % 5);
    for(int i = 0; i < numPreClicked; i++){
        int numPreClickedLoc = rand() % 24;
        rectClicked[numPreClickedLoc] = !rectClicked[numPreClickedLoc];
        // switch the 2-4 adjacent squares
        if(numPreClickedLoc + 5 <= rectArray.size()){
            rectClicked[numPreClickedLoc+5] = !rectClicked[numPreClickedLoc+5];
        }
        if(numPreClickedLoc - 5 <= rectArray.size()){
            rectClicked[numPreClickedLoc-5] = !rectClicked[numPreClickedLoc-5];
        }
        if(numPreClickedLoc + 1 <= rectArray.size() && (numPreClickedLoc+1) % 5 != 0){
            rectClicked[numPreClickedLoc+1] = !rectClicked[numPreClickedLoc+1];
        }
        if(numPreClickedLoc -1 <= rectArray.size() && (numPreClickedLoc+1) % 5 != 1){
            rectClicked[numPreClickedLoc-1] = !rectClicked[numPreClickedLoc-1];
        }
    }
}


void Engine::processInput() {
    bool mousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

    glfwPollEvents();
    // Set keys to true if pressed, false if released
    for (int key = 0; key < 1024; ++key) {
        if (glfwGetKey(window, key) == GLFW_PRESS)
            keys[key] = true;
        else if (glfwGetKey(window, key) == GLFW_RELEASE)
            keys[key] = false;
    }

    if (keys[GLFW_KEY_W]) {
        user.add_gold(1);
    }
    if (keys[GLFW_KEY_C]) {
        screen = play;
    }

    if (screen == start) {
        if (keys[GLFW_KEY_B]) {
            screen = play;
        }
    }

    if(screen == minigame) {
        // See if the user's mouse overlaps with the buttons
        vector<bool> overlaps;

        glfwGetCursorPos(window, &MouseX, &MouseY);
        // Changing the mouse coordinates to system coords
        MouseY = height - MouseY;

        for (int i = 0; i < rectArray.size(); i++) {
            bool buttonOverlapsMouse = rectArray[i]->isOverlapping(vec2(MouseX, MouseY));
            overlaps.push_back(buttonOverlapsMouse);
        }

        //Toggle clicked state of the block and adjacent blocks when the mouse is pressed
        if (mousePressed && !mousePressedLastFrame){
            numClicks++;
            for(int i = 0; i < rectArray.size(); i++){
                if(overlaps[i]){
                    rectClicked[i] = !rectClicked[i];
                }
            }
        }

        //TOM CODE v
        // highlight the button that the user is hovering over
        for (int i = 0; i < rectArray.size(); i++) {
            //Condition to set color if rectangle is clicked
            if (rectClicked[i]) {
                rectArray[i]->setColor(lightOn);

            } else {
                if (!overlaps[i]) {
                    rectArray[i]->setColor(lightOff);
                }
            }
        }
        for (int i = 0; i < rectArray.size(); i++) {
            //Condition to set color if rectangle is clicked
            if (overlaps[i]) {
                rectHLArray[i]->setColor(hoverOn);

            } else {
                rectHLArray[i]->setColor(hoverOff);
            }
        }

        //TOM CODE ^
        mousePressedLastFrame = mousePressed;
    }

    if (screen == play) {
        Room currentRoom = runDungeon.get_vecRooms().at(currentRoomIndex);
        ////Chest and Treasure Mechanics
        ChestInfo &chestInfo = chestStates[currentRoomIndex];
        bool mousePressedChest = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
        if (mousePressedChest && chestInfo.present) {
            double mouseX, mouseY;
            glfwGetCursorPos(window, &mouseX, &mouseY);
            // Changing the mouse coordinates to system coords
            mouseY = height - mouseY;
            //Check for mouse within chest area
            if (mouseX >= (width / 2 - 50) && mouseX <= (width / 2 + 50) && mouseY >= (height / 2 - 25) &&
                mouseY <= (height / 2 + 25)) {
                //Open chest if not opened
                if (!chestInfo.opened) {
                    chestInfo.opened = true;
                    if (chestInfo.trap) {
                        screen = minigameStartScreen;
                    }
                    user.add_gold(currentRoom.get_treasure()); //Add the gold from the currentRoom to the user
                } else if (!chestInfo.treasureTaken) {
                    //Take treasure if not taken already
                    chestInfo.treasureTaken = true;
                }
            }
        }
        //// DOOR OPENING
        //bool mousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        mouseY = height - mouseY;  // Convert mouseY to coordinate system used in rendering
        if (mousePressed && !mousePressedLastFrame) {
            Room currentRoom = runDungeon.get_vecRooms().at(currentRoomIndex);
            float doorWidth = 80;
            float doorHeight = 100;
            DoorInfo doorInfo = doorStates.at(currentRoomIndex);
            // Left door check
            if (doorInfo.left != 0 && mouseX >= (width / 2 - 693 - doorWidth / 2) &&
                mouseX <= (width / 2 - 693 + doorWidth / 2) && mouseY >= (height / 2 - doorHeight / 2) &&
                mouseY <= (height / 2 + doorHeight / 2)) {
                /// cout << "Attempting to transition to the left door" << endl;
                transitionToRoom(currentRoom.get_xCoordinate() - 1, currentRoom.get_yCoordinate());
                /// cout << "ROOM: " << currentRoomIndex << endl;
            }
            // Right door check
            if (doorInfo.right != 0 && mouseX >= (width / 2 + 693 - doorWidth / 2) &&
                mouseX <= (width / 2 + 693 + doorWidth / 2) && mouseY >= (height / 2 - doorHeight / 2) &&
                mouseY <= (height / 2 + doorHeight / 2)) {
                /// cout << "Attempting to transition to the right door" << endl;
                transitionToRoom(currentRoom.get_xCoordinate() + 1, currentRoom.get_yCoordinate());
            }
            // Top door check
            if (doorInfo.up != 0 && mouseX >= (width / 2 - doorWidth / 2) &&
                mouseX <= (width / 2 + doorWidth / 2) &&
                mouseY >= (height / 2 + 378 - doorHeight / 2) && mouseY <= (height / 2 + 378 + doorHeight / 2)) {
                /// cout << "Attempting to transition to the top door" << endl;
                transitionToRoom(currentRoom.get_xCoordinate(), currentRoom.get_yCoordinate() + 1);
            }
            /// Bottom door check
            if (doorInfo.down != 0 && mouseX >= (width / 2 - doorWidth / 2) &&
                mouseX <= (width / 2 + doorWidth / 2) &&
                mouseY >= (height / 2 - 378 - doorHeight / 2) && mouseY <= (height / 2 - 378 + doorHeight / 2)) {
                /// cout << "Attempting to transition to the bottom door." << endl;
                transitionToRoom(currentRoom.get_xCoordinate(), currentRoom.get_yCoordinate() - 1);
            }
        }
        if (user.get_gold() >= winGold) {
            screen = win;
        }
        if (user.get_health() <= 0) {
            screen = loss;
        }
        mousePressedLastFrame = mousePressed;
    }

    // Close window if escape key is pressed
    if (keys[GLFW_KEY_ESCAPE]) {
        glfwSetWindowShouldClose(window, true);
    }


    if(screen == minigameStartScreen && keys[GLFW_KEY_S]){
        screen = minigame;
    }


}
/// Save the data of the current room before moving to the next room
void Engine::saveCurrentRoomState() {
    Room currentRoom = runDungeon.get_vecRooms().at(currentRoomIndex);
    runDungeon.set_room(currentRoom,currentRoom.get_xCoordinate(), currentRoom.get_yCoordinate());
   // cout << "Current room saved" << endl;
}


void Engine::transitionToRoom(int newX, int newY){
    //cout << "Trying to transition to (" << newX << ", " << newY << ")" << endl;
    for (int i = 0; i < runDungeon.get_vecRooms().size(); i++){
        const Room& room = runDungeon.get_vecRooms().at(i);
        if (room.get_xCoordinate() == newX && room.get_yCoordinate() == newY){
            currentRoomIndex = i;
           // cout << "Transitioned to room #: " << room.get_roomNumber() << " at coordinates: (" << newX << ", " << newY << "). Current index: " << currentRoomIndex << endl;
            return;
        }
    }

    //cout << "Failed to find room at coordinates (" << newX << ", " << newY << ")." << endl;
}

void Engine::update() {
    // Calculate delta time
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

}


/// Function here for creating four variables for each room, by room number
// get the coordinates for room i, then check left by minus the x coordinate, for right: add 1 x, same for top and bottom.
// THis is for walls/ doors
void Engine::generateDoors() {
    doorStates.clear();  // Clear existing door states to start fresh
    auto rooms = runDungeon.get_vecRooms();  // Get all rooms from the dungeon

    for (const auto& room : rooms) {
        DoorInfo info{};
        int x = room.get_xCoordinate();
        int y = room.get_yCoordinate();

        //cout << "Room at (" << x << ", " << y << ") of type " << room.get_type() << endl;

        /// Left room check
        if (runDungeon.get_room(x - 1, y).get_type() == "Null Room"){
            info.left = 0;
            //cout << "Left room is null" << endl;
        } else if ((runDungeon.get_room(x - 1, y).get_type() == "Hallway")){
            info.left = 2;
            //cout << "left room is hallway" << endl;
        } else {
            info.left = 1;
            //cout << "left room is basic" << endl;
        }

        /// Right room check
        if (runDungeon.get_room(x + 1, y).get_type() == "Null Room"){
            info.right = 0;
            //cout << "Right room is null" << endl;
        } else if ((runDungeon.get_room(x + 1, y).get_type() == "Hallway")){
            info.right = 2;
            //cout << "Right room is hallway" << endl;
        } else {
            info.right = 1;
            //cout << "Right room is basic" << endl;
        }

        /// Above room check
        if (runDungeon.get_room(x, y + 1).get_type() == "Null Room"){
            info.up = 0;
            //cout << "up room is null" << endl;
        } else if ((runDungeon.get_room(x , y + 1).get_type() == "Hallway")){
            info.up = 2;
            //cout << "up room is hallway" << endl;
        } else {
            info.up = 1;
            //cout << "up room is basic" << endl;
        }

        /// Bottom room check
        if (runDungeon.get_room(x, y - 1).get_type() == "Null Room"){
            info.down = 0;
            //cout << "bottom room is null" << endl;
        } else if ((runDungeon.get_room(x, y - 1).get_type() == "Hallway")){
            info.down = 2;
            //cout << "bottom room is hallway" << endl;
        } else {
            info.down = 1;
            //cout << "bottom room is basic" << endl;
        }


        doorStates.push_back(info);  // Save the door information
    }
}

void Engine:: generateChests(){
    //Clear states to accept new dungeon each run
    chestStates.clear();
    //Get the vector of rooms from current dungeon
    auto rooms = runDungeon.get_vecRooms();
    for(const auto& room : rooms){
        ChestInfo info;
        info.trap = false;

        //Check room type for treasure or not
        if (room.get_treasure() != 0){
            info.present = true;
            //If treasure room and treasure value is 0, chest have been opened
            if (room.get_treasure() == 0){
                info.opened = true;
                info.treasureTaken = true;
            }else{
                info.opened = false;
                info.treasureTaken = false;
            }
        }
        //Check if there is a trap
        if(room.get_traps() != "nothing"){
            info.present = true;
            info.trap = true;
        }else {
            //Set both to false if it's not a treasure room
            //info.present = false;
            info.opened = false;
        }


        //Update the chest states
        chestStates.push_back(info);
    }

}

void Engine::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);


    // Set shader to use for all shapes
    shapeShader.use();

    switch (screen) {
        case start: {
            string message = "To win collect ";
            message += to_string(winGold);
            string messageLine4 = "Press b to start";
            // (12 * message.length()) is the offset to center text.
            // 12 pixels is the width of each character scaled by 1.
            this->fontRenderer->renderText(message, width/4 - (12 * message.length()), height/2, 1, vec3{1, 1, 1});
            this->fontRenderer->renderText(messageLine4, width/4 - (12 * messageLine4.length()), height/4, 1, vec3{1, 1, 1});
            break;
        }

        case play: {
            // using .at format to use the data from the first room
            Room currentRoom = runDungeon.get_vecRooms().at(currentRoomIndex);
            //cout << "Drawing Room #: " << currentRoom.get_roomNumber() << " at Coordinates: (" << currentRoom.get_xCoordinate() << ", " << currentRoom.get_yCoordinate() << ")" << endl;

            /// Basic room floor, grey
            baseRoom->setUniforms();
            baseRoom->draw();

            // Testing message
            //string message = "Testing!";
            //this->fontRenderer->renderText(message, width/2 - (50 * message.length()), height/2 - (15* message.length()), 1, vec3{1, 1, 1});
            /// Display current room index for debugging
            //fontRenderer->renderText("Current Room: " + std::to_string(currentRoomIndex), 50, 50, 1, vec3{1.0, 1.0, 1.0});

            // center of the room
            vec2 centerRoomPos = {width/2, height/2};

            // door info at the current room
            DoorInfo doorInfo = doorStates.at(currentRoomIndex);
            //chest info for current room
            ChestInfo chestInfo = chestStates.at(currentRoomIndex);


            // not a hallway left
            if (doorInfo.left != 2) {
                leftWall->setUniforms();
                leftWall->draw();
            }
                // room on other side
            if (doorInfo.left != 0) {
                //cout << "Drawing left door at room " << currentRoomIndex << endl;
                auto door = make_unique<Rect>(shapeShader, vec2{width/2 - 693, height/2}, vec2{80, 100}, color{0.82, 0.41, 0.12, 1});
                door->setUniforms();
                door->draw();
            }

            // not a hallway right
            if (doorInfo.right != 2) {
                rightWall->setUniforms();
                rightWall->draw();
                // room on other side
            }
            if (doorInfo.right != 0) {
                // cout << "Drawing right door at room " << currentRoomIndex << endl;

                auto door = make_unique<Rect>(shapeShader, vec2{width/2 + 693, height/2}, vec2{100, 80}, color{0.82, 0.41, 0.12, 1});
                door->setUniforms();
                door->draw();
            }

            // not a hallway above
            if (doorInfo.up != 2) {
                topWall->setUniforms();
                topWall->draw();
                // room on other side
            }
            if (doorInfo.up != 0){
                //cout << "Drawing up door at room " << currentRoomIndex << endl;

                auto door = make_unique<Rect>(shapeShader, vec2{width/2, height/2 + 378}, vec2{100, 80}, color{0.82, 0.41, 0.12, 1});
                door->setUniforms();
                door->draw();
            }


            // Bottom wall, no hallway above
            if (doorInfo.down != 2) {
                bottomWall->setUniforms();
                bottomWall->draw();
            }
            if(doorInfo.down != 0){
                //cout << "Drawing down door at room " << currentRoomIndex << endl;

                auto door = make_unique<Rect>(shapeShader, vec2{width/2, height/2 - 378}, vec2{100, 80}, color{0.82, 0.41, 0.12, 1});
                door->setUniforms();
                door->draw();
            }


            //Check chest conditions and render accordingly
            if (chestInfo.present){
                if(!chestInfo.opened){
                    closedChest->setUniforms();
                    closedChest->draw();
                }else{
                    openChest->setUniforms();
                    openChest->draw();
                }if(!chestInfo.treasureTaken){
                    treasure->setUniforms();
                    treasure->draw();
                }
            }
            // temporarily get a QTE if user hits "q"
            if (keys[GLFW_KEY_Q]){
                screen = minigameStartScreen;
            }
            if (keys[GLFW_KEY_S]) {
                screen = minigame;
            }

            //Display user health and gold
            string userHealthDisplay = "Health: " + to_string(user.get_health());
            string userGoldDisplay = "Gold: " + to_string(user.get_gold());
            string roomNumber = "Room: " + to_string(currentRoom.get_roomNumber());
            this->fontRenderer->renderText(userHealthDisplay, width/20, height/10, .5, vec3{0,0,0});
            this->fontRenderer->renderText(userGoldDisplay, width/20, height/8, .5, vec3{0,0,0});
            this->fontRenderer->renderText(roomNumber, width/20, height/12, .5, vec3{0,0,0});

             //cout<< currentRoom.get_type() << endl;
            //If room entered is the boss room, generate boss
            if(currentRoom.get_type() == "Boss Room"){
                bossHead->setUniforms();
                bossHead->draw();
                for (const auto & bos : boss){
                    bos->setUniforms();
                    bos->draw();
                }
            }

            break;
        }

        case minigameStartScreen: {
            //reinitialize lights to be on
            int numPreClicked = 3 + (rand() % 5);
            for(int i = 0; i < numPreClicked; i++){
                int numPreClickedLoc = rand() % 24;
                rectClicked[numPreClickedLoc] = !rectClicked[numPreClickedLoc];
                // switch the 2-4 adjacent squares
                if(numPreClickedLoc + 5 <= rectArray.size()){
                    rectClicked[numPreClickedLoc+5] = !rectClicked[numPreClickedLoc+5];
                }
                if(numPreClickedLoc - 5 <= rectArray.size()){
                    rectClicked[numPreClickedLoc-5] = !rectClicked[numPreClickedLoc-5];
                }
                if(numPreClickedLoc + 1 <= rectArray.size() && (numPreClickedLoc+1) % 5 != 0){
                    rectClicked[numPreClickedLoc+1] = !rectClicked[numPreClickedLoc+1];
                }
                if(numPreClickedLoc -1 <= rectArray.size() && (numPreClickedLoc+1) % 5 != 1){
                    rectClicked[numPreClickedLoc-1] = !rectClicked[numPreClickedLoc-1];
                }
            }
            qteTime = rand() % 5 + 3;
            string message = "WATCH OUT!!!";
            string howMuchTime = "You have " + to_string(qteTime) + " seconds";
            string messageLine4 = "Press s to start";
            // (12 * message.length()) is the offset to center text.
            // 12 pixels is the width of each character scaled by 1.
            this->fontRenderer->renderText(message, width/4 - (12 * message.length()), height/2, 1, vec3{1, 1, 1});
            this->fontRenderer->renderText(howMuchTime, width/4 - (12 * howMuchTime.length()), height/3, 1, vec3{1, 1, 1});
            this->fontRenderer->renderText(messageLine4, width/4 - (12 * messageLine4.length()), height/4.5, 1, vec3{1, 1, 1});
            //keep reseting start time until user presses 's'
            startingTime = clock();
        }

        case minigame: {
            for (int i = 0; i < size(rectArray); i++) {
                rectHLArray[i]->setUniforms();
                rectHLArray[i]->draw();
                rectArray[i]->setUniforms();
                rectArray[i]->draw();
            }
            bool winCondition = true;
            for (int i = 0; i < size(rectArray); i++){
                if(rectClicked[i]){
                    winCondition = false;
                    break;
                }
            }
            if(winCondition){
                screen = play;
            }

            // update and display clock
            double nowTime = clock();
            int outTime1 =((nowTime - startingTime)/10);
            double outTime = (double)outTime1/100;
            currentTime = outTime;

            //check to make sure user didn't run out of time
            if (currentTime > qteTime){
                user.sub_health(1);
                screen = play;
            }
            string clockIntro = "Time: " + to_string(outTime);
            this->fontRenderer->renderText(clockIntro, width/8 - (12 * clockIntro.length()), height/22, 1, vec3{1, 1, 1});

            break;
        }

        case over: {

            break;
        }

        case win: {
            string message = "You Won!";
            string messageLine4 = "Press esc to leave game";
            // (12 * message.length()) is the offset to center text.
            // 12 pixels is the width of each character scaled by 1.
            this->fontRenderer->renderText(message, width/4 - (12 * message.length()), height/2, 1, vec3{1, 1, 1});
            this->fontRenderer->renderText(messageLine4, width/4 - (12 * messageLine4.length()), height/4, 1, vec3{1, 1, 1});
            break;
        }

        case loss: {
            string message = "You Died!";
            string messageLine4 = "Press esc to leave game";
            // (12 * message.length()) is the offset to center text.
            // 12 pixels is the width of each character scaled by 1.
            this->fontRenderer->renderText(message, width/4 - (12 * message.length()), height/2, 1, vec3{1, 1, 1});
            this->fontRenderer->renderText(messageLine4, width/4 - (12 * messageLine4.length()), height/4, 1, vec3{1, 1, 1});
            break;
        }
    }

    glfwSwapBuffers(window);
}

bool Engine::shouldClose() {
    return glfwWindowShouldClose(window);
}

GLenum Engine::glCheckError_(const char *file, int line) {
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        string error;
        switch (errorCode) {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        cout << error << " | " << file << " (" << line << ")" << endl;
    }
    return errorCode;
}

void Engine::load_dungeon(Dungeon &dungeon) {
    ifstream inFile("../src/DungeonTransfer.csv");
    if (!inFile.is_open()) {
        cerr << "Unable to open save file" << endl;
        return;
    }

    string line;
    getline(inFile, line);  // Assuming there's only one line per CSV
    inFile.close();

    auto roomDataStart = line.find('|') + 1;  // Find the first '|' and skip it
    string roomData = line.substr(roomDataStart);  // Get the substring after the first '|'

    istringstream roomStream(roomData);
    string roomDetail;

    dungeon.clear_vecRooms();  // Clear existing rooms

    while (getline(roomStream, roomDetail, '|')) {
        if (roomDetail.empty()) continue;

        istringstream detailStream(roomDetail);
        string part;
        vector<string> parts;

        while (getline(detailStream, part, '-')) {
            parts.push_back(part);
        }

        if (parts.size() == 8) {  // Assuming all parts are present
            int roomNumber = stoi(parts[0]);
            string type = parts[1];
            double threatLevel = stod(parts[2]);
            int treasure = stoi(parts[3]);
            string traps = parts[4];
            int doors = stoi(parts[5]);
            int xCoordinate = stoi(parts[6]);
            int yCoordinate = stoi(parts[7]);

            Room room(roomNumber, type, threatLevel, treasure, traps, doors, xCoordinate, yCoordinate);
            dungeon.add_to_vecRooms(room);
        }
    }

    //cout << "Loaded dungeon with " << dungeon.get_vecRooms().size() << " rooms." << endl;
}