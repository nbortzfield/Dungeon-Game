#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include <vector>
#include <memory>
#include <iostream>
#include <GLFW/glfw3.h>
#include <random>
#include <algorithm>
#include <fstream>
#include <ostream>

#include "shader/shaderManager.h"
#include "font/fontRenderer.h"
#include "shapes/rect.h"
#include "shapes/shape.h"
#include "Dungeon.h"
#include "User_Character.h"
#include "time.h"

using std::vector, std::unique_ptr, std::make_unique, glm::ortho, glm::mat4, glm::vec3, glm::vec4;

/**
 * @brief The Engine class.
 * @details The Engine class is responsible for initializing the GLFW window, loading shaders, and rendering the game state.
 */
class Engine {
protected:
    Dungeon runDungeon;
    User_Character user;
    int winGold;
    // Creating data structure for door info for each room
    struct DoorInfo{
        int left, right, up, down;
        // room coordinates
        int roomX, roomY;
    };
    struct ChestInfo{
        bool trap, present, opened, treasureTaken;
    };
    // Vector will store the information for each room
    vector<DoorInfo> doorStates;
    vector<ChestInfo> chestStates;

private:
    /// @brief The actual GLFW window.
    GLFWwindow* window{};
    /// M4OEP Graphics:
    glm::vec2 roomSize;
    glm::vec2 roomPosition;

    /// @brief The width and height of the window.
    const unsigned int width = 1540, height = 840; // Window dimensions

    /// @brief Keyboard state (True if pressed, false if not pressed).
    /// @details Index this array with GLFW_KEY_{key} to get the state of a key.
    bool keys[1024];

    // helper method for drawing walls and doors
    void drawWallsAndDoors(const DoorInfo& doorInfo);

    /// @brief Responsible for loading and storing all the shaders used in the project.
    /// @details Initialized in initShaders()
    unique_ptr<ShaderManager> shaderManager;

    /// @brief Responsible for rendering text on the screen.
    /// @details Initialized in initShaders()
    unique_ptr<FontRenderer> fontRenderer;

    // Shapes
    unique_ptr<Rect> spawnButton;
    unique_ptr<Rect> baseRoom;

    unique_ptr<Rect> leftWall;
    unique_ptr<Rect> rightWall;
    unique_ptr<Rect> topWall;
    unique_ptr<Rect> bottomWall;
    unique_ptr<Rect> openChest;
    unique_ptr<Rect> closedChest;
    unique_ptr<Rect> treasure;
    vector <unique_ptr<Rect>> boss;
    unique_ptr<Rect> bossHead;
    unique_ptr<Rect> bossBody;
    unique_ptr<Rect> bossArmLeft;


    vector<unique_ptr<Shape>> confetti;

    //fields for minigame
    unique_ptr<Shape> background;
    vector<unique_ptr<Shape>> button;
    vector<bool> isOn;
    unique_ptr<Rect> button1;
    unique_ptr<Rect> button2;
    unique_ptr<Rect> button3;
    unique_ptr<Rect> button4;
    unique_ptr<Rect> button5;
    vector<unique_ptr<Rect>> rectArray;
    vector<unique_ptr<Rect>> rectHLArray;
    vector<bool> rectClicked;
    // end fields for minigame
    //TOM CODE ^
    int numClicks;

    double startingTime;
    double currentTime;

    // Shaders
    Shader shapeShader;
    Shader textShader;


    double MouseX, MouseY;
    bool mousePressedLastFrame = false;




    /// @note Call glCheckError() after every OpenGL call to check for errors.
    GLenum glCheckError_(const char *file, int line);
    /// @brief Macro for glCheckError_ function. Used for debugging.
#define glCheckError() glCheckError_(__FILE__, __LINE__)

public:
    /// @brief Constructor for the Engine class.
    /// @details Initializes window and shaders.
    Engine();

    /// @brief Destructor for the Engine class.
    ~Engine();

    /// @brief Initializes the GLFW window.
    /// @return 0 if successful, -1 otherwise.
    unsigned int initWindow(bool debug = false);

    /// @brief Loads shaders from files and stores them in the shaderManager.
    /// @details Renderers are initialized here.
    void initShaders();

    /// checks if we are transitioning correctly
    void checkRoomTransitions();
    /// Sets current room prior to transferring rooms
    void saveCurrentRoomState();

    /// Creates and sets the first current room index, ensures its not a boss room
    void initializeCurrentRoomIndex();

    /// @brief Initializes the shapes to be rendered.
    void initShapes();

    /// @brief Calculates and updates door states.
    void generateDoors();
    /// @brief Calculates and updates chest states
    void generateChests();


    /// @brief Processes input from the user.
    /// @details (e.g. keyboard input, mouse input, etc.)
    void processInput();

    /// @brief Updates the game state.
    /// @details (e.g. collision detection, delta time, etc.)
    void update();

    /// @brief Renders the game state.
    /// @details Displays/renders objects on the screen.
    void render();

    /* deltaTime variables */
    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame (used to calculate deltaTime)

    // -----------------------------------
    // Getters
    // -----------------------------------

    /// @brief Returns true if the window should close.
    /// @details (Wrapper for glfwWindowShouldClose()).
    /// @return true if the window should close
    /// @return false if the window should not close
    bool shouldClose();

    /// Projection matrix used for 2D rendering (orthographic projection).
    /// We don't have to change this matrix since the screen size never changes.
    /// OpenGL uses the projection matrix to map the 3D scene to a 2D viewport.
    /// The projection matrix transforms coordinates in the camera space into normalized device coordinates (view space to clip space).
    /// @note The projection matrix is used in the vertex shader.
    // 4th quadrant
    mat4 PROJECTION = ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    // 1st quadrant
//        mat4 PROJECTION = ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));

    void load_dungeon(Dungeon &dungeon);

    void transitionToRoom(int newX, int newY);

    bool timeInitialized = false;
    int qteTime;
};

#endif //GRAPHICS_ENGINE_H