#include <iostream>         // cout, cerr
#include <cstdlib>          // EXIT_FAILURE
#include <GL/glew.h>        // GLEW library
#include <GLFW/glfw3.h>     // GLFW library
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>      // Image loading Utility functions

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnOpengl/camera.h> // Camera class

using namespace std; // Standard namespace

/*Shader program Macro*/
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif

// Unnamed namespace
namespace
{
    const char* const WINDOW_TITLE = "Oliver Milani - 7-1 Project"; 

    // Variables for window width and height
    const int WINDOW_WIDTH = 1024;
    const int WINDOW_HEIGHT = 768;

    // Stores the GL data relative to a given mesh
    struct GLMesh
    {
        GLuint vao;         // Handle for the vertex array object
        GLuint vbo;         // Handle for the vertex buffer object
        GLuint nVertices;    // Number of indices of the mesh
    };

    // Main GLFW window
    GLFWwindow* gWindow = nullptr;
    // Triangle mesh data
    GLMesh gMeshPlane;
    GLMesh gMeshBook;
    GLMesh gMeshBook2;
    GLMesh gMeshScraper;
    GLMesh gMeshScraperStand;
    GLMesh gMeshBottle;
    GLMesh gMeshBottle2;

    // Texture
    GLuint gTextureIdPlane;
    GLuint gTextureIdBook;
    GLuint gTextureIdBook2;
    GLuint gTextureIdScraperStand;
    GLuint gTextureIdBottle;
    GLuint gTextureIdBottle2;
    glm::vec2 gUVScale(1.0f, 1.0f);
    GLint gTexWrapMode = GL_REPEAT;

    // Shader programs
    GLuint gProgramIdPlane;
    GLuint gProgramIdScraper;
    GLuint gProgramIdBook;
    GLuint gProgramIdBook2;
    GLuint gProgramIdScraperStand;
    GLuint gProgramIdBottle;
    GLuint gProgramIdBottle2;


    // camera
    Camera gCamera(glm::vec3(-3.0f, 2.0f, 7.0f));
    float gLastX = WINDOW_WIDTH / 2.0f;
    float gLastY = WINDOW_HEIGHT / 2.0f;
    bool gFirstMouse = true;

    // timing
    float gDeltaTime = 0.0f; // time between current frame and last frame
    float gLastFrame = 0.0f;

    // Subject position and scale
    glm::vec3 gPositionPlane(0.0f, 0.15f, 0.0f);     ///////////Table Position
    glm::vec3 gScalePlane(0.5f);
    glm::vec3 gRotationPlane(1.0, 0.0f, 0.0f);

    glm::vec3 gPositionBook(0.0f, 0.21f, 0.0f);
    glm::vec3 gScaleBook(2.0f);

    glm::mat4 rotationBookX = glm::rotate(0.01f, glm::vec3(1.0, 0.0f, 0.0f));
    glm::mat4 rotationBookY = glm::rotate(0.25f, glm::vec3(0.0, 1.0f, 0.0f));
    glm::mat4 rotationBookZ = glm::rotate(1.58f, glm::vec3(0.0, 0.0f, 1.0f));

    glm::mat4 rotationBook = rotationBookX * rotationBookY * rotationBookZ;

    /////////////////
    ///////
    glm::vec3 gPositionBook2(0.0f, 01.21f, 0.0f);
    glm::vec3 gScaleBook2(2.0f);

    glm::mat4 rotationBook2X = glm::rotate(0.01f, glm::vec3(1.0, 0.0f, 0.0f));
    glm::mat4 rotationBook2Y = glm::rotate(0.55f, glm::vec3(0.0, 1.0f, 0.0f));
    glm::mat4 rotationBook2Z = glm::rotate(1.58f, glm::vec3(0.0, 0.0f, 1.0f));

    glm::mat4 rotationBook2 = rotationBook2X * rotationBook2Y * rotationBook2Z;
 


    /// Scraper
   

    glm::vec3 gPositionScraperStand(-2.65f, 0.48f, -0.0f);
    glm::vec3 gScaleScraperStand(3.0f);

    glm::mat4 rotationScraperStandX = glm::rotate(-0.45f, glm::vec3(1.0, 0.0f, 0.0f));
    glm::mat4 rotationScraperStandY = glm::rotate(-0.75f, glm::vec3(0.0, 1.0f, 0.0f));
    glm::mat4 rotationScraperStandZ = glm::rotate(-0.3f, glm::vec3(0.0, 0.0f, 1.0f));

    glm::mat4 rotationScraperStand = rotationScraperStandX * rotationScraperStandY * rotationScraperStandZ;

    /// <summary>
    /// Bottle Base
    /// </summary>

    glm::vec3 gPositionBottle(-4.5f, 0.78f, 1.5f);
    glm::vec3 gScaleBottle(0.25f );

    glm::mat4 rotationBottleX = glm::rotate(0.0f, glm::vec3(1.0, 0.0f, 0.0f));
    glm::mat4 rotationBottleY = glm::rotate(0.0f, glm::vec3(0.0, 1.0f, 0.0f));
    glm::mat4 rotationBottleZ = glm::rotate(-0.0f, glm::vec3(0.0, 0.0f, 1.0f));

    glm::mat4 rotationBottle = rotationBottleX * rotationBottleY * rotationBottleZ;

    /// <summary>
    /// Bottle Top
    /// </summary>

    glm::vec3 gPositionBottle2(-4.5f, 1.75f, 1.5f);
    glm::vec3 gScaleBottle2(0.1f, 0.05f, 0.1f);

    glm::mat4 rotationBottle2X = glm::rotate(0.0f, glm::vec3(1.0, 0.0f, 0.0f));
    glm::mat4 rotationBottle2Y = glm::rotate(0.0f, glm::vec3(0.0, 1.0f, 0.0f));
    glm::mat4 rotationBottle2Z = glm::rotate(-0.0f, glm::vec3(0.0, 0.0f, 1.0f));

    glm::mat4 rotationBottle2 = rotationBottle2X * rotationBottle2Y * rotationBottle2Z;

    // Plane and light color
    //m::vec3 gObjectColor(0.6f, 0.5f, 0.75f);
    glm::vec3 gObjectColor(1.f, 0.2f, 0.0f);
    glm::vec3 gObjectColor2(1.f, 0.2f, 0.0f);
    glm::vec3 gLightColor(1.0f, 1.0f, 1.0f);

    // Light position and scale
    glm::vec3 gLightPosition(1.0f, 8.0f, 5.0f);
    glm::vec3 gLightScale(1.0f);

    // Scraper animation
    bool gIsScraperOrbiting = false;
}

/* User-defined Function prototypes to:
 * initialize the program, set the window size,
 * redraw graphics on the window when resized,
 * and render graphics on the screen
 */
bool UInitialize(int, char* [], GLFWwindow** window);
void UResizeWindow(GLFWwindow* window, int width, int height);
void UProcessInput(GLFWwindow* window);
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void UCreateMeshPlane(GLMesh& mesh);
void UCreateMeshBook(GLMesh& mesh);
void UCreateMeshBook2(GLMesh& mesh);
void UCreateMeshScraper(GLMesh& mesh);
void UCreateMeshScraperStand(GLMesh& mesh);
void UCreateMeshBottle(GLMesh& mesh);
void UCreateMeshBottle2(GLMesh& mesh);
void UDestroyMesh(GLMesh& mesh);
bool UCreateTexture(const char* filename, GLuint& textureId);
void UDestroyTexture(GLuint textureId);
void URender();
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId);
void UDestroyShaderProgram(GLuint programId);


/* Plane Vertex Shader Source Code*/
const GLchar* vertexShaderSourcePlane = GLSL(440,

    layout(location = 0) in vec3 position; // VAP position 0 for vertex position data
layout(location = 1) in vec3 normal; // VAP position 1 for normals
layout(location = 2) in vec2 textureCoordinate;

out vec3 vertexNormal; // For outgoing normals to fragment shader
out vec3 vertexFragmentPos; // For outgoing color / pixels to fragment shader
out vec2 vertexTextureCoordinate;

//Uniform / Global variables for the  transform matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates

    vertexFragmentPos = vec3(model * vec4(position, 1.0f)); // Gets fragment / pixel position in world space only (exclude view and projection)

    vertexNormal = mat3(transpose(inverse(model))) * normal; // get normal vectors in world space only and exclude normal translation properties
    vertexTextureCoordinate = textureCoordinate;
}
);


/* Plane Fragment Shader Source Code*/
const GLchar* fragmentShaderSourcePlane = GLSL(440,

    in vec3 vertexNormal; // For incoming normals
in vec3 vertexFragmentPos; // For incoming fragment position
in vec2 vertexTextureCoordinate;

out vec4 fragmentColor; // For outgoing plane color to the GPU

// Uniform / Global variables for object color, light color, light position, and camera/view position
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPosition;
uniform sampler2D uTexture; // Useful when working with multiple textures
uniform vec2 uvScale;

void main()
{
    /*Phong lighting model calculations to generate ambient, diffuse, and specular components*/

    //Calculate Ambient lighting*/
    float ambientStrength = 0.1f; // Set ambient or global lighting strength
    vec3 ambient = ambientStrength * lightColor; // Generate ambient light color

    //Calculate Diffuse lighting*/
    vec3 norm = normalize(vertexNormal); // Normalize vectors to 1 unit
    vec3 lightDirection = normalize(lightPos - vertexFragmentPos); // Calculate distance (light direction) between light source and fragments/pixels on plane
    float impact = max(dot(norm, lightDirection), 0.0);// Calculate diffuse impact by generating dot product of normal and light
    vec3 diffuse = impact * lightColor; // Generate diffuse light color

    //Calculate Specular lighting*/
    float specularIntensity = 0.8f; // Set specular light strength
    float highlightSize = 16.0f; // Set specular highlight size
    vec3 viewDir = normalize(viewPosition - vertexFragmentPos); // Calculate view direction
    vec3 reflectDir = reflect(-lightDirection, norm);// Calculate reflection vector
    //Calculate specular component
    float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize);
    vec3 specular = specularIntensity * specularComponent * lightColor;

    // Texture holds the color to be used for all three components
    vec4 textureColor = texture(uTexture, vertexTextureCoordinate * uvScale);

    // Calculate phong result
    vec3 phong = (ambient + diffuse + specular) * textureColor.xyz;

    fragmentColor = vec4(phong, 1.0); // Send lighting results to GPU
}
);

////////////////////////////////////////////////////////////////////Book 1

/* Plane Vertex Shader Source Code*/
const GLchar* vertexShaderSourceBook = GLSL(440,

    layout(location = 0) in vec3 position; // VAP position 0 for vertex position data
layout(location = 1) in vec3 normal; // VAP position 1 for normals
layout(location = 2) in vec2 textureCoordinate;

out vec3 vertexNormal; // For outgoing normals to fragment shader
out vec3 vertexFragmentPos; // For outgoing color / pixels to fragment shader
out vec2 vertexTextureCoordinate;

//Uniform / Global variables for the  transform matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates

    vertexFragmentPos = vec3(model * vec4(position, 1.0f)); // Gets fragment / pixel position in world space only (exclude view and projection)

    vertexNormal = mat3(transpose(inverse(model))) * normal; // get normal vectors in world space only and exclude normal translation properties
    vertexTextureCoordinate = textureCoordinate;
}
);


/* Plane Fragment Shader Source Code*/
const GLchar* fragmentShaderSourceBook = GLSL(440,

    in vec3 vertexNormal; // For incoming normals
in vec3 vertexFragmentPos; // For incoming fragment position
in vec2 vertexTextureCoordinate;

out vec4 fragmentColor; // For outgoing plane color to the GPU

// Uniform / Global variables for object color, light color, light position, and camera/view position
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPosition;
uniform sampler2D uTexture; // Useful when working with multiple textures
uniform vec2 uvScale;

void main()
{
    /*Phong lighting model calculations to generate ambient, diffuse, and specular components*/

    //Calculate Ambient lighting*/
    float ambientStrength = 0.1f; // Set ambient or global lighting strength
    vec3 ambient = ambientStrength * lightColor; // Generate ambient light color

    //Calculate Diffuse lighting*/
    vec3 norm = normalize(vertexNormal); // Normalize vectors to 1 unit
    vec3 lightDirection = normalize(lightPos - vertexFragmentPos); // Calculate distance (light direction) between light source and fragments/pixels on plane
    float impact = max(dot(norm, lightDirection), 0.0);// Calculate diffuse impact by generating dot product of normal and light
    vec3 diffuse = impact * lightColor; // Generate diffuse light color

    //Calculate Specular lighting*/
    float specularIntensity = 0.8f; // Set specular light strength
    float highlightSize = 16.0f; // Set specular highlight size
    vec3 viewDir = normalize(viewPosition - vertexFragmentPos); // Calculate view direction
    vec3 reflectDir = reflect(-lightDirection, norm);// Calculate reflection vector
    //Calculate specular component
    float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize);
    vec3 specular = specularIntensity * specularComponent * lightColor;

    // Texture holds the color to be used for all three components
    vec4 textureColor = texture(uTexture, vertexTextureCoordinate * uvScale);

    // Calculate phong result
    vec3 phong = (ambient + diffuse + specular) * textureColor.xyz;

    fragmentColor = vec4(phong, 1.0); // Send lighting results to GPU
}
);

/////////////////////////////////////////////////////////////Book 2


/* Plane Vertex Shader Source Code*/
const GLchar* vertexShaderSourceBook2 = GLSL(440,

    layout(location = 0) in vec3 position; // VAP position 0 for vertex position data
layout(location = 1) in vec3 normal; // VAP position 1 for normals
layout(location = 2) in vec2 textureCoordinate;

out vec3 vertexNormal; // For outgoing normals to fragment shader
out vec3 vertexFragmentPos; // For outgoing color / pixels to fragment shader
out vec2 vertexTextureCoordinate;

//Uniform / Global variables for the  transform matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates

    vertexFragmentPos = vec3(model * vec4(position, 1.0f)); // Gets fragment / pixel position in world space only (exclude view and projection)

    vertexNormal = mat3(transpose(inverse(model))) * normal; // get normal vectors in world space only and exclude normal translation properties
    vertexTextureCoordinate = textureCoordinate;
}
);


/* Plane Fragment Shader Source Code*/
const GLchar* fragmentShaderSourceBook2 = GLSL(440,

    in vec3 vertexNormal; // For incoming normals
in vec3 vertexFragmentPos; // For incoming fragment position
in vec2 vertexTextureCoordinate;

out vec4 fragmentColor; // For outgoing plane color to the GPU

// Uniform / Global variables for object color, light color, light position, and camera/view position
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPosition;
uniform sampler2D uTexture; // Useful when working with multiple textures
uniform vec2 uvScale;

void main()
{
    /*Phong lighting model calculations to generate ambient, diffuse, and specular components*/

    //Calculate Ambient lighting*/
    float ambientStrength = 0.1f; // Set ambient or global lighting strength
    vec3 ambient = ambientStrength * lightColor; // Generate ambient light color

    //Calculate Diffuse lighting*/
    vec3 norm = normalize(vertexNormal); // Normalize vectors to 1 unit
    vec3 lightDirection = normalize(lightPos - vertexFragmentPos); // Calculate distance (light direction) between light source and fragments/pixels on plane
    float impact = max(dot(norm, lightDirection), 0.0);// Calculate diffuse impact by generating dot product of normal and light
    vec3 diffuse = impact * lightColor; // Generate diffuse light color

    //Calculate Specular lighting*/
    float specularIntensity = 0.8f; // Set specular light strength
    float highlightSize = 16.0f; // Set specular highlight size
    vec3 viewDir = normalize(viewPosition - vertexFragmentPos); // Calculate view direction
    vec3 reflectDir = reflect(-lightDirection, norm);// Calculate reflection vector
    //Calculate specular component
    float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize);
    vec3 specular = specularIntensity * specularComponent * lightColor;

    // Texture holds the color to be used for all three components
    vec4 textureColor = texture(uTexture, vertexTextureCoordinate * uvScale);

    // Calculate phong result
    vec3 phong = (ambient + diffuse + specular) * textureColor.xyz;

    fragmentColor = vec4(phong, 1.0); // Send lighting results to GPU
}
);

////////////////////////////////////////////Scraper

/* Scraper Shader Source Code*/
const GLchar* ScraperVertexShaderSource = GLSL(440,

    layout(location = 0) in vec3 position; // VAP position 0 for vertex position data

        //Uniform / Global variables for the  transform matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates
}
);


/* Fragment Shader Source Code*/
const GLchar* ScraperFragmentShaderSource = GLSL(440,

    out vec4 fragmentColor; // For outgoing Scraper color (smaller plane) to the GPU

void main()
{
    fragmentColor = vec4(1.0f); // Set color to white (1.0f,1.0f,1.0f) with alpha 1.0
}
);

/* Plane Vertex Shader Source Code*/
const GLchar* vertexShaderSourceScraperStand = GLSL(440,

    layout(location = 0) in vec3 position; // VAP position 0 for vertex position data
layout(location = 1) in vec3 normal; // VAP position 1 for normals
layout(location = 2) in vec2 textureCoordinate;

out vec3 vertexNormal; // For outgoing normals to fragment shader
out vec3 vertexFragmentPos; // For outgoing color / pixels to fragment shader
out vec2 vertexTextureCoordinate;

//Uniform / Global variables for the  transform matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates

    vertexFragmentPos = vec3(model * vec4(position, 1.0f)); // Gets fragment / pixel position in world space only (exclude view and projection)

    vertexNormal = mat3(transpose(inverse(model))) * normal; // get normal vectors in world space only and exclude normal translation properties
    vertexTextureCoordinate = textureCoordinate;
}
);


/* Plane Fragment Shader Source Code*/
const GLchar* fragmentShaderSourceScraperStand = GLSL(440,

    in vec3 vertexNormal; // For incoming normals
in vec3 vertexFragmentPos; // For incoming fragment position
in vec2 vertexTextureCoordinate;

out vec4 fragmentColor; // For outgoing plane color to the GPU

// Uniform / Global variables for object color, light color, light position, and camera/view position
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPosition;
uniform sampler2D uTexture; // Useful when working with multiple textures
uniform vec2 uvScale;

void main()
{
    /*Phong lighting model calculations to generate ambient, diffuse, and specular components*/

    //Calculate Ambient lighting*/
    float ambientStrength = 0.1f; // Set ambient or global lighting strength
    vec3 ambient = ambientStrength * lightColor; // Generate ambient light color

    //Calculate Diffuse lighting*/
    vec3 norm = normalize(vertexNormal); // Normalize vectors to 1 unit
    vec3 lightDirection = normalize(lightPos - vertexFragmentPos); // Calculate distance (light direction) between light source and fragments/pixels on plane
    float impact = max(dot(norm, lightDirection), 0.0);// Calculate diffuse impact by generating dot product of normal and light
    vec3 diffuse = impact * lightColor; // Generate diffuse light color

    //Calculate Specular lighting*/
    float specularIntensity = 0.8f; // Set specular light strength
    float highlightSize = 16.0f; // Set specular highlight size
    vec3 viewDir = normalize(viewPosition - vertexFragmentPos); // Calculate view direction
    vec3 reflectDir = reflect(-lightDirection, norm);// Calculate reflection vector
    //Calculate specular component
    float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize);
    vec3 specular = specularIntensity * specularComponent * lightColor;

    // Texture holds the color to be used for all three components
    vec4 textureColor = texture(uTexture, vertexTextureCoordinate * uvScale);

    // Calculate phong result
    vec3 phong = (ambient + diffuse + specular) * textureColor.xyz;

    fragmentColor = vec4(phong, 1.0); // Send lighting results to GPU
}
);

/* Plane Vertex Shader Source Code*/
const GLchar* vertexShaderSourceBottle = GLSL(440,

    layout(location = 0) in vec3 position; // VAP position 0 for vertex position data
layout(location = 1) in vec3 normal; // VAP position 1 for normals
layout(location = 2) in vec2 textureCoordinate;

out vec3 vertexNormal; // For outgoing normals to fragment shader
out vec3 vertexFragmentPos; // For outgoing color / pixels to fragment shader
out vec2 vertexTextureCoordinate;

//Uniform / Global variables for the  transform matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates

    vertexFragmentPos = vec3(model * vec4(position, 1.0f)); // Gets fragment / pixel position in world space only (exclude view and projection)

    vertexNormal = mat3(transpose(inverse(model))) * normal; // get normal vectors in world space only and exclude normal translation properties
    vertexTextureCoordinate = textureCoordinate;
}
);


/* Plane Fragment Shader Source Code*/
const GLchar* fragmentShaderSourceBottle = GLSL(440,

    in vec3 vertexNormal; // For incoming normals
in vec3 vertexFragmentPos; // For incoming fragment position
in vec2 vertexTextureCoordinate;

out vec4 fragmentColor; // For outgoing plane color to the GPU

// Uniform / Global variables for object color, light color, light position, and camera/view position
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPosition;
uniform sampler2D uTexture; // Useful when working with multiple textures
uniform vec2 uvScale;

void main()
{
    /*Phong lighting model calculations to generate ambient, diffuse, and specular components*/

    //Calculate Ambient lighting*/
    float ambientStrength = 0.1f; // Set ambient or global lighting strength
    vec3 ambient = ambientStrength * lightColor; // Generate ambient light color

    //Calculate Diffuse lighting*/
    vec3 norm = normalize(vertexNormal); // Normalize vectors to 1 unit
    vec3 lightDirection = normalize(lightPos - vertexFragmentPos); // Calculate distance (light direction) between light source and fragments/pixels on plane
    float impact = max(dot(norm, lightDirection), 0.0);// Calculate diffuse impact by generating dot product of normal and light
    vec3 diffuse = impact * lightColor; // Generate diffuse light color

    //Calculate Specular lighting*/
    float specularIntensity = 0.8f; // Set specular light strength
    float highlightSize = 16.0f; // Set specular highlight size
    vec3 viewDir = normalize(viewPosition - vertexFragmentPos); // Calculate view direction
    vec3 reflectDir = reflect(-lightDirection, norm);// Calculate reflection vector
    //Calculate specular component
    float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize);
    vec3 specular = specularIntensity * specularComponent * lightColor;

    // Texture holds the color to be used for all three components
    vec4 textureColor = texture(uTexture, vertexTextureCoordinate * uvScale);

    // Calculate phong result
    vec3 phong = (ambient + diffuse + specular) * textureColor.xyz;

    fragmentColor = vec4(phong, 1.0); // Send lighting results to GPU
}
);

/* Plane Vertex Shader Source Code*/
const GLchar* vertexShaderSourceBottle2 = GLSL(440,

    layout(location = 0) in vec3 position; // VAP position 0 for vertex position data
layout(location = 1) in vec3 normal; // VAP position 1 for normals
layout(location = 2) in vec2 textureCoordinate;

out vec3 vertexNormal; // For outgoing normals to fragment shader
out vec3 vertexFragmentPos; // For outgoing color / pixels to fragment shader
out vec2 vertexTextureCoordinate;

//Uniform / Global variables for the  transform matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates

    vertexFragmentPos = vec3(model * vec4(position, 1.0f)); // Gets fragment / pixel position in world space only (exclude view and projection)

    vertexNormal = mat3(transpose(inverse(model))) * normal; // get normal vectors in world space only and exclude normal translation properties
    vertexTextureCoordinate = textureCoordinate;
}
);


/* Plane Fragment Shader Source Code*/
const GLchar* fragmentShaderSourceBottle2 = GLSL(440,

    in vec3 vertexNormal; // For incoming normals
in vec3 vertexFragmentPos; // For incoming fragment position
in vec2 vertexTextureCoordinate;

out vec4 fragmentColor; // For outgoing plane color to the GPU

// Uniform / Global variables for object color, light color, light position, and camera/view position
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPosition;
uniform sampler2D uTexture; // Useful when working with multiple textures
uniform vec2 uvScale;

void main()
{
    /*Phong lighting model calculations to generate ambient, diffuse, and specular components*/

    //Calculate Ambient lighting*/
    float ambientStrength = 0.1f; // Set ambient or global lighting strength
    vec3 ambient = ambientStrength * lightColor; // Generate ambient light color

    //Calculate Diffuse lighting*/
    vec3 norm = normalize(vertexNormal); // Normalize vectors to 1 unit
    vec3 lightDirection = normalize(lightPos - vertexFragmentPos); // Calculate distance (light direction) between light source and fragments/pixels on plane
    float impact = max(dot(norm, lightDirection), 0.0);// Calculate diffuse impact by generating dot product of normal and light
    vec3 diffuse = impact * lightColor; // Generate diffuse light color

    //Calculate Specular lighting*/
    float specularIntensity = 0.8f; // Set specular light strength
    float highlightSize = 16.0f; // Set specular highlight size
    vec3 viewDir = normalize(viewPosition - vertexFragmentPos); // Calculate view direction
    vec3 reflectDir = reflect(-lightDirection, norm);// Calculate reflection vector
    //Calculate specular component
    float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize);
    vec3 specular = specularIntensity * specularComponent * lightColor;

    // Texture holds the color to be used for all three components
    vec4 textureColor = texture(uTexture, vertexTextureCoordinate * uvScale);

    // Calculate phong result
    vec3 phong = (ambient + diffuse + specular) * textureColor.xyz;

    fragmentColor = vec4(phong, 1.0); // Send lighting results to GPU
}
);


// Images are loaded with Y axis going down, but OpenGL's Y axis goes up, so let's flip it
void flipImageVertically(unsigned char* image, int width, int height, int channels)
{
    for (int j = 0; j < height / 2; ++j)
    {
        int index1 = j * width * channels;
        int index2 = (height - 1 - j) * width * channels;

        for (int i = width * channels; i > 0; --i)
        {
            unsigned char tmp = image[index1];
            image[index1] = image[index2];
            image[index2] = tmp;
            ++index1;
            ++index2;
        }
    }
}


int main(int argc, char* argv[])
{
    if (!UInitialize(argc, argv, &gWindow))
        return EXIT_FAILURE;

    // Create the mesh
    UCreateMeshPlane(gMeshPlane); // Calls the function to create the Vertex Buffer Object

    // Create the shader programs
    if (!UCreateShaderProgram(vertexShaderSourcePlane, fragmentShaderSourcePlane, gProgramIdPlane))
        return EXIT_FAILURE;

    if (!UCreateShaderProgram(ScraperVertexShaderSource, ScraperFragmentShaderSource, gProgramIdScraper))
        return EXIT_FAILURE;

    // Load texture
    const char* texFilename = "../../resources/textures/container2.png";
    if (!UCreateTexture(texFilename, gTextureIdPlane))
    {
        cout << "Failed to load texture " << texFilename << endl;
        return EXIT_FAILURE;
    }
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(gProgramIdPlane);
    // We set the texture as texture unit 0
    glUniform1i(glGetUniformLocation(gProgramIdPlane, "uTexture"), 0);

  


    UCreateMeshBook(gMeshBook); // Calls the function to create the Vertex Buffer Object

    if (!UCreateShaderProgram(vertexShaderSourceBook, fragmentShaderSourceBook, gProgramIdBook))
        return EXIT_FAILURE;


    // Load texture
    const char* texFilename2 = "../../resources/textures/booktexture.jpg";
    if (!UCreateTexture(texFilename2, gTextureIdBook))
    {
        cout << "Failed to load texture " << texFilename2 << endl;
        return EXIT_FAILURE;
    }
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(gProgramIdBook);
    // We set the texture as texture unit 0
    glUniform1i(glGetUniformLocation(gProgramIdBook, "uTexture"), 0);
    

    ////////////Book2

    UCreateMeshBook2(gMeshBook2); // Calls the function to create the Vertex Buffer Object

    if (!UCreateShaderProgram(vertexShaderSourceBook2, fragmentShaderSourceBook2, gProgramIdBook2))
        return EXIT_FAILURE;


    // Load texture
    const char* texFilename1 = "../../resources/textures/booktexture.jpg";
    if (!UCreateTexture(texFilename1, gTextureIdBook2))
    {
        cout << "Failed to load texture " << texFilename1 << endl;
        return EXIT_FAILURE;
    }
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(gProgramIdBook2);
    // We set the texture as texture unit 0
    glUniform1i(glGetUniformLocation(gProgramIdBook2, "uTexture"), 0);

    ///////////////
    // Create the mesh
    UCreateMeshScraper(gMeshScraper); // Calls the function to create the Vertex Buffer Object

    if (!UCreateShaderProgram(ScraperVertexShaderSource, ScraperFragmentShaderSource, gProgramIdScraper))
        return EXIT_FAILURE;


    UCreateMeshScraperStand(gMeshScraperStand); // Calls the function to create the Vertex Buffer Object

    if (!UCreateShaderProgram(vertexShaderSourceScraperStand, fragmentShaderSourceScraperStand, gProgramIdScraperStand))
        return EXIT_FAILURE;


    // Load texture
    const char* texFilename3 = "../../resources/textures/SteelTexture.jpg";
    if (!UCreateTexture(texFilename3, gTextureIdScraperStand))
    {
        cout << "Failed to load texture " << texFilename3 << endl;
        return EXIT_FAILURE;
    }
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(gProgramIdScraperStand);
    // We set the texture as texture unit 0
    glUniform1i(glGetUniformLocation(gProgramIdScraperStand, "uTexture"), 0);


    UCreateMeshBottle(gMeshBottle); // Calls the function to create the Vertex Buffer Object

    if (!UCreateShaderProgram(vertexShaderSourceBottle, fragmentShaderSourceBottle, gProgramIdBottle))
        return EXIT_FAILURE;


    // Load texture
    const char* texFilename4 = "../../resources/textures/SteelTexture.jpg";
    if (!UCreateTexture(texFilename4, gTextureIdBottle))
    {
        cout << "Failed to load texture " << texFilename4 << endl;
        return EXIT_FAILURE;
    }
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(gProgramIdBottle);
    // We set the texture as texture unit 0
    glUniform1i(glGetUniformLocation(gProgramIdBottle, "uTexture"), 0);

    ////////// 
    UCreateMeshBottle2(gMeshBottle2); // Calls the function to create the Vertex Buffer Object

    if (!UCreateShaderProgram(vertexShaderSourceBottle2, fragmentShaderSourceBottle2, gProgramIdBottle2))
        return EXIT_FAILURE;


    // Load texture
    const char* texFilename6 = "../../resources/textures/SteelTexture.jpg";
    if (!UCreateTexture(texFilename6, gTextureIdBottle2))
    {
        cout << "Failed to load texture " << texFilename6 << endl;
        return EXIT_FAILURE;
    }
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(gProgramIdBottle2);
    // We set the texture as texture unit 0
    glUniform1i(glGetUniformLocation(gProgramIdBottle2, "uTexture"), 0);

    // Sets the background color of the window to black (it will be implicitely used by glClear)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(gWindow))
    {
        // per-frame timing
        // --------------------
        float currentFrame = glfwGetTime();
        gDeltaTime = currentFrame - gLastFrame;
        gLastFrame = currentFrame;

        // input
        // -----
        UProcessInput(gWindow);

        // Render this frame
        URender();

        glfwPollEvents();
    }

    // Release mesh data
    UDestroyMesh(gMeshPlane);
    UDestroyMesh(gMeshBook);
    UDestroyMesh(gMeshBook2);
    UDestroyMesh(gMeshScraper);
    UDestroyMesh(gMeshScraperStand);
    UDestroyMesh(gMeshBottle);
    UDestroyMesh(gMeshBottle2);

    // Release texture
    UDestroyTexture(gTextureIdPlane);
    UDestroyTexture(gTextureIdBook);
    UDestroyTexture(gTextureIdBook2);
    UDestroyTexture(gTextureIdScraperStand);
    UDestroyTexture(gTextureIdBottle);
    UDestroyTexture(gTextureIdBottle2);

    // Release shader programs
    UDestroyShaderProgram(gProgramIdPlane);
    UDestroyShaderProgram(gProgramIdScraper);
    UDestroyShaderProgram(gProgramIdBook);
    UDestroyShaderProgram(gProgramIdBook2);
    UDestroyShaderProgram(gProgramIdScraperStand);
    UDestroyShaderProgram(gProgramIdBottle);
    UDestroyShaderProgram(gProgramIdBottle2);

    exit(EXIT_SUCCESS); // Terminates the program successfully
}


// Initialize GLFW, GLEW, and create a window
bool UInitialize(int argc, char* argv[], GLFWwindow** window)
{
    // GLFW: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW: window creation
    // ---------------------
    * window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (*window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(*window);
    glfwSetFramebufferSizeCallback(*window, UResizeWindow);
    glfwSetCursorPosCallback(*window, UMousePositionCallback);
    glfwSetScrollCallback(*window, UMouseScrollCallback);
    glfwSetMouseButtonCallback(*window, UMouseButtonCallback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // GLEW: initialize
    // ----------------
    // Note: if using GLEW version 1.13 or earlier
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();

    if (GLEW_OK != GlewInitResult)
    {
        std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
        return false;
    }

    // Displays GPU OpenGL version
    cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << endl;

    return true;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void UProcessInput(GLFWwindow* window)
{
    static const float cameraSpeed = 2.5f;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        gCamera.ProcessKeyboard(LEFT, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        gCamera.ProcessKeyboard(RIGHT, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        gCamera.ProcessKeyboard(UP, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        gCamera.ProcessKeyboard(DOWN, gDeltaTime);

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && gTexWrapMode != GL_REPEAT)
    {
        glBindTexture(GL_TEXTURE_2D, gTextureIdPlane);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glBindTexture(GL_TEXTURE_2D, 0);

        gTexWrapMode = GL_REPEAT;

        cout << "Current Texture Wrapping Mode: REPEAT" << endl;
    }
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && gTexWrapMode != GL_MIRRORED_REPEAT)
    {
        glBindTexture(GL_TEXTURE_2D, gTextureIdPlane);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glBindTexture(GL_TEXTURE_2D, 0);

        gTexWrapMode = GL_MIRRORED_REPEAT;

        cout << "Current Texture Wrapping Mode: MIRRORED REPEAT" << endl;
    }
    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && gTexWrapMode != GL_CLAMP_TO_EDGE)
    {
        glBindTexture(GL_TEXTURE_2D, gTextureIdPlane);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D, 0);

        gTexWrapMode = GL_CLAMP_TO_EDGE;

        cout << "Current Texture Wrapping Mode: CLAMP TO EDGE" << endl;
    }
    else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && gTexWrapMode != GL_CLAMP_TO_BORDER)
    {
        float color[] = { 1.0f, 0.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

        glBindTexture(GL_TEXTURE_2D, gTextureIdPlane);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glBindTexture(GL_TEXTURE_2D, 0);

        gTexWrapMode = GL_CLAMP_TO_BORDER;

        cout << "Current Texture Wrapping Mode: CLAMP TO BORDER" << endl;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)
    {
        gUVScale += 0.1f;
        cout << "Current scale (" << gUVScale[0] << ", " << gUVScale[1] << ")" << endl;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
    {
        gUVScale -= 0.1f;
        cout << "Current scale (" << gUVScale[0] << ", " << gUVScale[1] << ")" << endl;
    }

    // Pause and resume Scraper orbiting
    static bool isLKeyDown = false;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && !gIsScraperOrbiting)
        gIsScraperOrbiting = true;
    else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && gIsScraperOrbiting)
        gIsScraperOrbiting = false;

}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void UResizeWindow(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (gFirstMouse)
    {
        gLastX = xpos;
        gLastY = ypos;
        gFirstMouse = false;
    }

    float xoffset = xpos - gLastX;
    float yoffset = gLastY - ypos; // reversed since y-coordinates go from bottom to top

    gLastX = xpos;
    gLastY = ypos;

    gCamera.ProcessMouseMovement(xoffset, yoffset);
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    gCamera.ProcessMouseScroll(yoffset);
}

// glfw: handle mouse button events
// --------------------------------
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
    {
        if (action == GLFW_PRESS)
            cout << "Left mouse button pressed" << endl;
        else
            cout << "Left mouse button released" << endl;
    }
    break;

    case GLFW_MOUSE_BUTTON_MIDDLE:
    {
        if (action == GLFW_PRESS)
            cout << "Middle mouse button pressed" << endl;
        else
            cout << "Middle mouse button released" << endl;
    }
    break;

    case GLFW_MOUSE_BUTTON_RIGHT:
    {
        if (action == GLFW_PRESS)
            cout << "Right mouse button pressed" << endl;
        else
            cout << "Right mouse button released" << endl;
    }
    break;

    default:
        cout << "Unhandled mouse button event" << endl;
        break;
    }
}


// Functioned called to render a frame
void URender()
{
    // Scraper orbits around the origin
    const float angularVelocity = glm::radians(45.0f);
    if (gIsScraperOrbiting)
    {
        glm::vec4 newPosition = glm::rotate(angularVelocity * gDeltaTime, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(gLightPosition, 1.0f);
        gLightPosition.x = newPosition.x;
        gLightPosition.y = newPosition.y;
        gLightPosition.z = newPosition.z;
    }

    // Enable z-depth
    glEnable(GL_DEPTH_TEST);

    // Clear the frame and z buffers
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    

    // PLANE: draw plane
    //----------------
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 model = glm::translate(gPositionPlane) * glm::scale(gScalePlane) * glm::rotate(-1.57f, glm::vec3(1.0, 0.0f, 0.0f));

    // camera/view transformation
    glm::mat4 view = gCamera.GetViewMatrix();

    // Creates a perspective projection
    glm::mat4 projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);

    // Set the shader to be used
    glUseProgram(gProgramIdPlane);

    // Retrieves and passes transform matrices to the Shader program
    GLint modelLoc = glGetUniformLocation(gProgramIdPlane, "model");
    GLint viewLoc = glGetUniformLocation(gProgramIdPlane, "view");
    GLint projLoc = glGetUniformLocation(gProgramIdPlane, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Reference matrix uniforms from the Plane Shader program for the cub color, light color, light position, and camera position
    GLint objectColorLoc = glGetUniformLocation(gProgramIdPlane, "objectColor");
    GLint lightColorLoc = glGetUniformLocation(gProgramIdPlane, "lightColor");
    GLint lightPositionLoc = glGetUniformLocation(gProgramIdPlane, "lightPos");
    GLint viewPositionLoc = glGetUniformLocation(gProgramIdPlane, "viewPosition");

    // Pass color, light, and camera data to the Plane Shader program's corresponding uniforms
    glUniform3f(objectColorLoc, gObjectColor.r, gObjectColor.g, gObjectColor.b);
    glUniform3f(lightColorLoc, gLightColor.r, gLightColor.g, gLightColor.b);
    glUniform3f(lightPositionLoc, gLightPosition.x, gLightPosition.y, gLightPosition.z);
    const glm::vec3 cameraPosition = gCamera.Position;
    glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);

    GLint UVScaleLoc = glGetUniformLocation(gProgramIdPlane, "uvScale");
    glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

    // Activate the plane VAO (used by plane and Scraper)
    glBindVertexArray(gMeshPlane.vao);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTextureIdPlane);

    // Draws the triangles
    glDrawArrays(GL_TRIANGLES, 0, gMeshPlane.nVertices);



    // Book: draw Book
    //----------------
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 modelBook = glm::translate(gPositionBook) * glm::scale(gScaleBook) * rotationBook;

    // Set the shader to be used
    glUseProgram(gProgramIdBook);

    // Retrieves and passes transform matrices to the Shader program
    GLint modelLocBook = glGetUniformLocation(gProgramIdBook, "model");
    GLint viewLocBook = glGetUniformLocation(gProgramIdBook, "view");
    GLint projLocBook = glGetUniformLocation(gProgramIdBook, "projection");

    glUniformMatrix4fv(modelLocBook, 1, GL_FALSE, glm::value_ptr(modelBook));
    glUniformMatrix4fv(viewLocBook, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLocBook, 1, GL_FALSE, glm::value_ptr(projection));

    // Reference matrix uniforms from the Plane Shader program for the cub color, light color, light position, and camera position
    GLint objectColorLocBook = glGetUniformLocation(gProgramIdPlane, "objectColor");
    GLint lightColorLocBook = glGetUniformLocation(gProgramIdPlane, "lightColor");
    GLint lightPositionLocBook = glGetUniformLocation(gProgramIdPlane, "lightPos");
    GLint viewPositionLocBook = glGetUniformLocation(gProgramIdPlane, "viewPosition");

    // Pass color, light, and camera data to the Plane Shader program's corresponding uniforms
    glUniform3f(objectColorLocBook, gObjectColor.r, gObjectColor.g, gObjectColor.b);
    glUniform3f(lightColorLocBook, gLightColor.r, gLightColor.g, gLightColor.b);
    glUniform3f(lightPositionLocBook, gLightPosition.x, gLightPosition.y, gLightPosition.z);
    const glm::vec3 cameraPositionBook = gCamera.Position;
    glUniform3f(viewPositionLocBook, cameraPositionBook.x, cameraPositionBook.y, cameraPositionBook.z);

    GLint UVScaleLocBook = glGetUniformLocation(gProgramIdPlane, "uvScale");
    glUniform2fv(UVScaleLocBook, 1, glm::value_ptr(gUVScale));

    // Activate the plane VAO (used by plane and Scraper)
    glBindVertexArray(gMeshBook.vao);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTextureIdBook);

    // Draws the triangles
    glDrawArrays(GL_TRIANGLES, 0, gMeshBook.nVertices);


    // Book2: draw Book2
   //----------------
   // Model matrix: transformations are applied right-to-left order
    glm::mat4 modelBook2 = glm::translate(gPositionBook2) * glm::scale(gScaleBook2) * rotationBook2;

    // Set the shader to be used
    glUseProgram(gProgramIdBook2);

    // Retrieves and passes transform matrices to the Shader program
    GLint modelLocBook2 = glGetUniformLocation(gProgramIdBook2, "model");
    GLint viewLocBook2 = glGetUniformLocation(gProgramIdBook2, "view");
    GLint projLocBook2 = glGetUniformLocation(gProgramIdBook2, "projection");

    glUniformMatrix4fv(modelLocBook2, 1, GL_FALSE, glm::value_ptr(modelBook2));
    glUniformMatrix4fv(viewLocBook2, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLocBook2, 1, GL_FALSE, glm::value_ptr(projection));

    // Reference matrix uniforms from the Plane Shader program for the cub color, light color, light position, and camera position
    GLint objectColorLocBook2 = glGetUniformLocation(gProgramIdPlane, "objectColor");
    GLint lightColorLocBook2 = glGetUniformLocation(gProgramIdPlane, "lightColor");
    GLint lightPositionLocBook2 = glGetUniformLocation(gProgramIdPlane, "lightPos");
    GLint viewPositionLocBook2 = glGetUniformLocation(gProgramIdPlane, "viewPosition");

    // Pass color, light, and camera data to the Plane Shader program's corresponding uniforms
    glUniform3f(objectColorLocBook2, gObjectColor.r, gObjectColor.g, gObjectColor.b);
    glUniform3f(lightColorLocBook2, gLightColor.r, gLightColor.g, gLightColor.b);
    glUniform3f(lightPositionLocBook2, gLightPosition.x, gLightPosition.y, gLightPosition.z);
    const glm::vec3 cameraPositionBook2 = gCamera.Position;
    glUniform3f(viewPositionLocBook2, cameraPositionBook2.x, cameraPositionBook2.y, cameraPositionBook2.z);

    GLint UVScaleLocBook2 = glGetUniformLocation(gProgramIdPlane, "uvScale");
    glUniform2fv(UVScaleLocBook2, 1, glm::value_ptr(gUVScale));

    // Activate the plane VAO (used by plane and Scraper)
    glBindVertexArray(gMeshBook2.vao);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTextureIdBook2);

    // Draws the triangles
    glDrawArrays(GL_TRIANGLES, 0, gMeshBook2.nVertices);




    // Scraper: draw Scraper
    //----------------
    glUseProgram(gProgramIdScraper);

    //Transform the smaller plane used as a visual que for the light source
    glm::mat4 modelScraper = glm::translate(gLightPosition) * glm::scale(gLightScale) * glm::rotate(-1.57f, glm::vec3(1.0, 0.0f, 0.0f));

    // Reference matrix uniforms from the Scraper Shader program
    GLint modelLocScraper = glGetUniformLocation(gProgramIdScraper, "model");
    GLint viewLocScraper = glGetUniformLocation(gProgramIdScraper, "view");
    GLint projLocScraper = glGetUniformLocation(gProgramIdScraper, "projection");

    // Pass matrix data to the Scraper Shader program's matrix uniforms
    glUniformMatrix4fv(modelLocScraper, 1, GL_FALSE, glm::value_ptr(modelScraper));
    glUniformMatrix4fv(viewLocScraper, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLocScraper, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(gMeshScraper.vao);

    glDrawArrays(GL_TRIANGLES, 0, gMeshScraper.nVertices);



    // ScraperStand: draw ScraperStand
    //----------------
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 modelScraperStand = glm::translate(gPositionScraperStand) * glm::scale(gScaleScraperStand) * rotationScraperStand;

    // Set the shader to be used
    glUseProgram(gProgramIdScraperStand);

    // Retrieves and passes transform matrices to the Shader program
    GLint modelLocScraperStand = glGetUniformLocation(gProgramIdScraperStand, "model");
    GLint viewLocScraperStand = glGetUniformLocation(gProgramIdScraperStand, "view");
    GLint projLocScraperStand = glGetUniformLocation(gProgramIdScraperStand, "projection");

    glUniformMatrix4fv(modelLocScraperStand, 1, GL_FALSE, glm::value_ptr(modelScraperStand));
    glUniformMatrix4fv(viewLocScraperStand, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLocScraperStand, 1, GL_FALSE, glm::value_ptr(projection));

    // Reference matrix uniforms from the Plane Shader program for the cub color, light color, light position, and camera position
    GLint objectColorLocScraperStand = glGetUniformLocation(gProgramIdPlane, "objectColor");
    GLint lightColorLocScraperStand = glGetUniformLocation(gProgramIdPlane, "lightColor");
    GLint lightPositionLocScraperStand = glGetUniformLocation(gProgramIdPlane, "lightPos");
    GLint viewPositionLocScraperStand = glGetUniformLocation(gProgramIdPlane, "viewPosition");

    // Pass color, light, and camera data to the Plane Shader program's corresponding uniforms
    glUniform3f(objectColorLocScraperStand, gObjectColor.r, gObjectColor.g, gObjectColor.b);
    glUniform3f(lightColorLocScraperStand, gLightColor.r, gLightColor.g, gLightColor.b);
    glUniform3f(lightPositionLocScraperStand, gLightPosition.x, gLightPosition.y, gLightPosition.z);
    const glm::vec3 cameraPositionScraperStand = gCamera.Position;
    glUniform3f(viewPositionLocScraperStand, cameraPositionScraperStand.x, cameraPositionScraperStand.y, cameraPositionScraperStand.z);

    GLint UVScaleLocScraperStand = glGetUniformLocation(gProgramIdPlane, "uvScale");
    glUniform2fv(UVScaleLocScraperStand, 1, glm::value_ptr(gUVScale));

    // Activate the plane VAO (used by plane and Scraper)
    glBindVertexArray(gMeshScraperStand.vao);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTextureIdScraperStand);

    // Draws the triangles
    glDrawArrays(GL_TRIANGLES, 0, gMeshScraperStand.nVertices);



    // Bottle: draw Bottle
    //----------------
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 modelBottle = glm::translate(gPositionBottle) * glm::scale(gScaleBottle) * rotationBottle;

    // Set the shader to be used
    glUseProgram(gProgramIdBottle);

    // Retrieves and passes transform matrices to the Shader program
    GLint modelLocBottle = glGetUniformLocation(gProgramIdBottle, "model");
    GLint viewLocBottle = glGetUniformLocation(gProgramIdBottle, "view");
    GLint projLocBottle = glGetUniformLocation(gProgramIdBottle, "projection");

    glUniformMatrix4fv(modelLocBottle, 1, GL_FALSE, glm::value_ptr(modelBottle));
    glUniformMatrix4fv(viewLocBottle, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLocBottle, 1, GL_FALSE, glm::value_ptr(projection));

    // Reference matrix uniforms from the Plane Shader program for the cub color, light color, light position, and camera position
    GLint objectColorLocBottle = glGetUniformLocation(gProgramIdPlane, "objectColor");
    GLint lightColorLocBottle = glGetUniformLocation(gProgramIdPlane, "lightColor");
    GLint lightPositionLocBottle = glGetUniformLocation(gProgramIdPlane, "lightPos");
    GLint viewPositionLocBottle = glGetUniformLocation(gProgramIdPlane, "viewPosition");

    // Pass color, light, and camera data to the Plane Shader program's corresponding uniforms
    glUniform3f(objectColorLocBottle, gObjectColor.r, gObjectColor.g, gObjectColor.b);
    glUniform3f(lightColorLocBottle, gLightColor.r, gLightColor.g, gLightColor.b);
    glUniform3f(lightPositionLocBottle, gLightPosition.x, gLightPosition.y, gLightPosition.z);
    const glm::vec3 cameraPositionBottle = gCamera.Position;
    glUniform3f(viewPositionLocBottle, cameraPositionBottle.x, cameraPositionBottle.y, cameraPositionBottle.z);

    GLint UVScaleLocBottle = glGetUniformLocation(gProgramIdPlane, "uvScale");
    glUniform2fv(UVScaleLocBottle, 1, glm::value_ptr(gUVScale));

    // Activate the plane VAO (used by plane and Scraper)
    glBindVertexArray(gMeshBottle.vao);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTextureIdBottle);

    // Draws the triangles
    glDrawArrays(GL_TRIANGLES, 0, gMeshBottle.nVertices);

    // Bottle2: draw Bottle2
    //----------------
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 modelBottle2 = glm::translate(gPositionBottle2) * glm::scale(gScaleBottle2) * rotationBottle2;

    // Set the shader to be used
    glUseProgram(gProgramIdBottle2);

    // Retrieves and passes transform matrices to the Shader program
    GLint modelLocBottle2 = glGetUniformLocation(gProgramIdBottle2, "model");
    GLint viewLocBottle2 = glGetUniformLocation(gProgramIdBottle2, "view");
    GLint projLocBottle2 = glGetUniformLocation(gProgramIdBottle2, "projection");

    glUniformMatrix4fv(modelLocBottle2, 1, GL_FALSE, glm::value_ptr(modelBottle2));
    glUniformMatrix4fv(viewLocBottle2, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLocBottle2, 1, GL_FALSE, glm::value_ptr(projection));

    // Reference matrix uniforms from the Plane Shader program for the cub color, light color, light position, and camera position
    GLint objectColorLocBottle2 = glGetUniformLocation(gProgramIdPlane, "objectColor");
    GLint lightColorLocBottle2 = glGetUniformLocation(gProgramIdPlane, "lightColor");
    GLint lightPositionLocBottle2 = glGetUniformLocation(gProgramIdPlane, "lightPos");
    GLint viewPositionLocBottle2 = glGetUniformLocation(gProgramIdPlane, "viewPosition");

    // Pass color, light, and camera data to the Plane Shader program's corresponding uniforms
    glUniform3f(objectColorLocBottle2, gObjectColor.r, gObjectColor.g, gObjectColor.b);
    glUniform3f(lightColorLocBottle2, gLightColor.r, gLightColor.g, gLightColor.b);
    glUniform3f(lightPositionLocBottle2, gLightPosition.x, gLightPosition.y, gLightPosition.z);
    const glm::vec3 cameraPositionBottle2 = gCamera.Position;
    glUniform3f(viewPositionLocBottle2, cameraPositionBottle2.x, cameraPositionBottle2.y, cameraPositionBottle2.z);

    GLint UVScaleLocBottle2 = glGetUniformLocation(gProgramIdPlane, "uvScale");
    glUniform2fv(UVScaleLocBottle2, 1, glm::value_ptr(gUVScale));

    // Activate the plane VAO (used by plane and Scraper)
    glBindVertexArray(gMeshBottle2.vao);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTextureIdBottle2);

    // Draws the triangles
    glDrawArrays(GL_TRIANGLES, 0, gMeshBottle2.nVertices);



    // Deactivate the Vertex Array Object and shader program
    glBindVertexArray(0);
    glUseProgram(0);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(gWindow);    // Flips the the back buffer with the front buffer every frame.
}


// Implements the UCreateMesh function
void UCreateMeshScraper(GLMesh& mesh)
{
    // Position and Color data
    GLfloat verts[] = {
        //Positions          //Texture Coordinates
        0.5f,  0.5f, 0.0f,   0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
       -0.5f,  0.5f, 0.0f,   0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.0f,  0.0f, 1.0f,   0.0f,  1.0f,  0.0f,  0.0f, 0.0f,

        0.0f,  0.0f, 1.0f,   1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f, 0.0f,   1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, 0.0f,   1.0f,  0.0f,  0.0f,  0.0f, 0.0f,


        0.0f,  0.0f, 1.0f,   -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
       -0.5f, -0.5f, 0.0f,   -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
       -0.5f,  0.5f, 0.0f,   -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,

        0.0f,  0.0f, 1.0f,   0.0f,  -1.0f,  0.0f,  1.0f, 1.0f,
       -0.5f, -0.5f, 0.0f,   0.0f,  -1.0f,  0.0f,  0.0f, 1.0f,
       0.5f, -0.5f, 0.0f,    0.0f,  -1.0f,  0.0f,  0.0f, 0.0f,


        0.5f,  0.5f, 0.0f,   0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       -0.5f, -0.5f, 0.0f,   0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
       -0.5f,  0.5f, 0.0f,   0.0f,  0.0f, -1.0f,  1.0f, 0.0f,

        0.5f,  0.5f, 0.0f,   0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       -0.5f, -0.5f, 0.0f,   0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,   0.0f,  0.0f, -1.0f,  0.0f, 1.0f
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    mesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

void UCreateMeshPlane(GLMesh& mesh)
{
    // Vertex data
    GLfloat verts[] = {
        25.0f,    25.0f, 0.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
        25.0f,   -25.0f, 0.0f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
        -25.0f,  -25.0f, 0.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,   // Triangle 1

        -25.0f,  -25.0f, 0.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
        -25.0f,   25.0f, 0.0f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
        25.0f,    25.0f, 0.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f   // Triangle 2
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    mesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

void UCreateMeshBook(GLMesh& mesh)
{
    // Vertex data
    GLfloat verts[] = {


        -0.0f, -1.5f, -0.75f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -1.5f, -0.75f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  1.5f, -0.75f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  1.5f, -0.75f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       -0.0f,  1.5f, -0.75f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
       -0.0f, -1.5f, -0.75f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

       //back Face         //Positive Z Normal
      -0.0f, -01.5f,  0.75f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
       0.5f, -01.5f,  0.75f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
       0.5f,  01.5f,  0.75f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
       0.5f,  01.5f,  0.75f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
      -0.0f,  01.5f,  0.75f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
      -0.0f, -01.5f,  0.75f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

      //bottom Face          //Negative X Normal
     -0.0f,  01.5f,  0.75f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     -0.0f,  01.5f, -0.75f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     -0.0f, -01.5f, -0.75f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     -0.0f, -01.5f, -0.75f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     -0.0f, -01.5f,  0.75f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     -0.0f,  01.5f,  0.75f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     //Top Face         //Positive X Normal
     0.5f,  01.5f,  0.75f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  01.5f, -0.75f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -01.5f, -0.75f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -01.5f, -0.75f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -01.5f,  0.75f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  01.5f,  0.75f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     //R Face        //Negative Y Normal
    -0.0f, -01.5f, -0.75f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -01.5f, -0.75f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -01.5f,  0.75f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -01.5f,  0.75f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.0f, -01.5f,  0.75f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.0f, -01.5f, -0.75f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    //L Face           //Positive Y Normal
   -0.0f,  1.5f, -0.75f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
    0.5f,  01.5f, -0.75f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
    0.5f,  01.5f,  0.75f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    0.5f,  01.5f,  0.75f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
   -0.0f,  01.5f,  0.75f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
   -0.0f,  01.5f, -0.75f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f

   ////////////////////////////////////////////////////////////////////////////////////////


      
      
    };
    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    mesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

void UCreateMeshBook2(GLMesh& mesh)
{
    // Vertex data
    GLfloat verts[] = {


        -0.0f, -1.5f, -0.75f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -1.5f, -0.75f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  1.5f, -0.75f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  1.5f, -0.75f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       -0.0f,  1.5f, -0.75f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
       -0.0f, -1.5f, -0.75f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

       //back Face         //Positive Z Normal
      -0.0f, -01.5f,  0.75f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
       0.5f, -01.5f,  0.75f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
       0.5f,  01.5f,  0.75f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
       0.5f,  01.5f,  0.75f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
      -0.0f,  01.5f,  0.75f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
      -0.0f, -01.5f,  0.75f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

      //bottom Face          //Negative X Normal
     -0.0f,  01.5f,  0.75f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     -0.0f,  01.5f, -0.75f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     -0.0f, -01.5f, -0.75f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     -0.0f, -01.5f, -0.75f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     -0.0f, -01.5f,  0.75f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     -0.0f,  01.5f,  0.75f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     //Top Face         //Positive X Normal
     0.5f,  01.5f,  0.75f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  01.5f, -0.75f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -01.5f, -0.75f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -01.5f, -0.75f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -01.5f,  0.75f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  01.5f,  0.75f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     //R Face        //Negative Y Normal
    -0.0f, -01.5f, -0.75f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -01.5f, -0.75f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -01.5f,  0.75f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -01.5f,  0.75f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.0f, -01.5f,  0.75f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.0f, -01.5f, -0.75f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    //L Face           //Positive Y Normal
   -0.0f,  1.5f, -0.75f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
    0.5f,  01.5f, -0.75f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
    0.5f,  01.5f,  0.75f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    0.5f,  01.5f,  0.75f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
   -0.0f,  01.5f,  0.75f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
   -0.0f,  01.5f, -0.75f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f

   ////////////////////////////////////////////////////////////////////////////////////////




    };
    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    mesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}
void UCreateMeshScraperStand(GLMesh& mesh)
{
    // Vertex data  Paint Scraper
    GLfloat verts[] = {
        //Positions          //Normals
        // ------------------------------------------------------
        //Back Face          //Negative Z Normal  Texture Coords. handle
        0.03f, 0.20f, 0.51f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, //bl
        0.22f, 0.20f, 0.51f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, //br
        0.226f,  0.65f, 0.51f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, //TR
        0.226f,  0.65f, 0.51f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,//r
        0.024f,  0.65f, 0.51f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,//TL
        0.03f, 0.20f, 0.51f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,//BL

       //Front Face         //Positive Z Normal plane/////////////
       -0.05f, -0.0f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  //Bottom Bottom Left
       0.3f, -0.0f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, // bottom Bottom right
       0.222f,  0.20f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,// bottom top right
       0.222f,  0.20f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, //right
       0.0275f,  0.2f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, //top left
      -0.05f, -0.0f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, //bottom left

      //Left Face          //Negative X Normal handle
        0.03f, 0.20f, 0.49f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, //bl
        0.22f, 0.20f, 0.49f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, //br
        0.226f,  0.65f, 0.49f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, //TR
        0.226f,  0.65f, 0.49f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,//r
        0.024f,  0.65f, 0.49f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,//TL
        0.03f, 0.20f, 0.49f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,//BL

      //Right Face         //Positive X Normal plane 2
      -0.10f, -0.3f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  
       0.35f, -0.3f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 
       0.3f,  0.0f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
       0.3f,  0.0f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
      -0.05f,  0.0f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, 
      -0.10f, -0.3f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 

     //L        //Negative Y Normal
     0.024f,  0.65f,  0.49f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.024f,  0.65f, 0.51f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.03f,  0.2f, 0.51f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.03f, 0.2f, 0.51f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.03f, 0.2f,  0.49f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.024f,  0.65f,  0.49f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    //R       //Positive Y Normal
     0.226f,  0.65f,  0.49f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.226f,  0.65f, 0.51f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.22f,  0.2f, 0.51f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.22f, 0.2f, 0.51f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.22f, 0.2f,  0.49f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.226f,  0.65f,  0.49f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     // handle top
     0.024f, 0.65f, 0.49f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.226f, 0.65f, 0.49f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.226f, 0.65f,  0.51f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.226f, 0.65f,  0.51f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.024f, 0.65f, 0.51f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
     0.024, 0.65f, 0.49f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

     // Handle Bottom
      0.03f, 0.2f, 0.49f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.22f, 0.2f, 0.49f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.22f, 0.2f,  0.51f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.22f, 0.2f,  0.51f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.03f, 0.2f, 0.51f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
     0.03, 0.2f, 0.49f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
    };
    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    mesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

void UCreateMeshBottle(GLMesh& mesh)
{
    // Vertex data
    GLfloat verts[] = {
        //Positions          //Normals
        // ------------------------------------------------------
        //Back Face          //Negative Z Normal  Texture Coords.
       -0.5f, -02.5f, -01.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -02.5f, -01.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  03.5f, -01.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  03.5f, -01.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       -0.5f,  03.5f, -01.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
       -0.5f, -02.5f, -01.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

       //Back Face   L       //Negative Z Normal  Texture Coords.
       -1.5f, -02.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
       -0.5f, -02.5f, -01.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
       -0.5f,  03.5f, -01.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       -0.5f,  03.5f, -01.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       -1.5f,  03.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
       -1.5f, -02.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

       //Back Face   R     //Negative Z Normal  Texture Coords.
       0.5f, -02.5f, -01.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
       1.5f, -02.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
       1.5f,  03.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       1.5f,  03.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       0.5f,  03.5f, -01.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
       0.5f, -02.5f, -01.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,




/////////
       //Front Face         //Positive Z Normal
      -0.5f, -02.5f,  01.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, //1
       0.5f, -02.5f,  01.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, //2
       0.5f,  03.5f,  01.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, //3
       0.5f,  03.5f,  01.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, //4
      -0.5f,  03.5f,  01.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, //5
      -0.5f, -02.5f,  01.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, //6
      
      /// Front Right
    
       0.5f, -02.5f,  01.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, //1
       1.5f, -02.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, //2
       1.5f,  03.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, //3
       1.5f,  03.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, //4
       0.5f,  03.5f,  01.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, //5
       0.5f, -02.5f,  01.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, //6

     
/////////
// 
//
      //Left Face          //Negative X Normal
     -01.5f,  03.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     -01.5f,  03.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     -01.5f, -02.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     -01.5f, -02.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     -01.5f, -02.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     -01.5f,  03.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     
    //Left Right         //Negative X Normal
    -0.5f,  03.5f,  01.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     -01.5f,  03.5f, 0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     -01.5f, -02.5f, 0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     -01.5f, -02.5f, 0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     -0.5f, -02.5f,  01.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     -0.5f,  03.5f,  01.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,




     ////////
     //Right Face         //Positive X Normal
    01.5f,  03.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     01.5f,  03.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     01.5f, -02.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     01.5f, -02.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     01.5f, -02.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     01.5f,  03.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     //Bottom Face        //Negative Y Normal
    -1.5f, -02.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     1.5f, -02.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     1.5f, -02.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     1.5f, -02.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -1.5f, -02.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -1.5f, -02.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
    //
    -0.5f, -02.5f, -1.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -02.5f, -1.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -02.5f,  1.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -02.5f,  1.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -02.5f,  1.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -02.5f, -1.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
    //
 
     -01.5f, -02.5f, 0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, //1
     0.5f, -02.5f, -01.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     01.5f, -02.5f,  -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     01.5f, -02.5f,  -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -02.5f,  01.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, //5
    -01.5f, -02.5f, 0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, // 6
     // 
    -0.5f, -02.5f, -1.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, //1
     01.5f, -02.5f, 0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, //2
     0.5f, -2.5f,  01.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, //3
     0.5f, -02.5f,  01.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, //4
    -01.5f, -02.5f,  -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, //5
    -0.5f, -02.5f, -1.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, //6
    
 
  //Top Face        //Negative Y Normal
           -1.5f, 3.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
           1.5f, 3.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
           1.5f, 3.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
           1.5f, 3.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
           -1.5f, 3.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
           -1.5f, 3.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
           //
           -0.5f, 3.5f, -1.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
           0.5f, 3.5f, -1.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
           0.5f, 3.5f, 1.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
           0.5f, 3.5f, 1.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
           -0.5f, 3.5f, 1.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
           -0.5f, 3.5f, -1.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
           //

           -01.5f, 3.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, //1
           0.5f, 3.5f, -01.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
           01.5f, 3.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
           01.5f, 3.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
           -0.5f, 3.5f, 01.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, //5
           -01.5f, 3.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // 6
            // 
           -0.5f, 3.5f, -1.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, //1
           01.5f, 3.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, //2
           0.5f, 3.5f, 01.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, //3
           0.5f, 3.5f, 01.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, //4
           -01.5f, 3.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, //5
           -0.5f, 3.5f, -1.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, //6
    };
    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    mesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

void UCreateMeshBottle2(GLMesh& mesh)
{
    // Vertex data
    GLfloat verts[] = {
        //Positions          //Normals
        // ------------------------------------------------------
        //Back Face          //Negative Z Normal  Texture Coords.
       -0.5f, -02.5f, -01.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -02.5f, -01.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  03.5f, -01.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  03.5f, -01.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       -0.5f,  03.5f, -01.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
       -0.5f, -02.5f, -01.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

       //Back Face   L       //Negative Z Normal  Texture Coords.
       -1.5f, -02.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
       -0.5f, -02.5f, -01.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
       -0.5f,  03.5f, -01.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       -0.5f,  03.5f, -01.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       -1.5f,  03.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
       -1.5f, -02.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

       //Back Face   R     //Negative Z Normal  Texture Coords.
       0.5f, -02.5f, -01.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
       1.5f, -02.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
       1.5f,  03.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       1.5f,  03.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       0.5f,  03.5f, -01.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
       0.5f, -02.5f, -01.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,




       /////////
              //Front Face         //Positive Z Normal
             -0.5f, -02.5f,  01.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, //1
              0.5f, -02.5f,  01.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, //2
              0.5f,  03.5f,  01.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, //3
              0.5f,  03.5f,  01.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, //4
             -0.5f,  03.5f,  01.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, //5
             -0.5f, -02.5f,  01.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, //6

             /// Front Right

              0.5f, -02.5f,  01.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, //1
              1.5f, -02.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, //2
              1.5f,  03.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, //3
              1.5f,  03.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, //4
              0.5f,  03.5f,  01.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, //5
              0.5f, -02.5f,  01.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, //6


       /////////
       // 
       //
             //Left Face          //Negative X Normal
            -01.5f,  03.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -01.5f,  03.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -01.5f, -02.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -01.5f, -02.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -01.5f, -02.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -01.5f,  03.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,


            //Left Right         //Negative X Normal
            -0.5f,  03.5f,  01.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
             -01.5f,  03.5f, 0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
             -01.5f, -02.5f, 0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             -01.5f, -02.5f, 0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             -0.5f, -02.5f,  01.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
             -0.5f,  03.5f,  01.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,




             ////////
             //Right Face         //Positive X Normal
            01.5f,  03.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
             01.5f,  03.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
             01.5f, -02.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             01.5f, -02.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             01.5f, -02.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
             01.5f,  03.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

             //Bottom Face        //Negative Y Normal
            -1.5f, -02.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
             1.5f, -02.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
             1.5f, -02.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
             1.5f, -02.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -1.5f, -02.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -1.5f, -02.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
            //
            -0.5f, -02.5f, -1.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -02.5f, -1.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -02.5f,  1.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
             0.5f, -02.5f,  1.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -02.5f,  1.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -02.5f, -1.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
            //

             -01.5f, -02.5f, 0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, //1
             0.5f, -02.5f, -01.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
             01.5f, -02.5f,  -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
             01.5f, -02.5f,  -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -02.5f,  01.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, //5
            -01.5f, -02.5f, 0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, // 6
             // 
            -0.5f, -02.5f, -1.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, //1
             01.5f, -02.5f, 0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, //2
             0.5f, -2.5f,  01.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, //3
             0.5f, -02.5f,  01.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, //4
            -01.5f, -02.5f,  -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, //5
            -0.5f, -02.5f, -1.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, //6


               //Top Face        //Negative Y Normal
           -1.5f, 3.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
           1.5f, 3.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
           1.5f, 3.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
           1.5f, 3.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
           -1.5f, 3.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
           -1.5f, 3.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
           //
           -0.5f, 3.5f, -1.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
           0.5f, 3.5f, -1.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
           0.5f, 3.5f, 1.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
           0.5f, 3.5f, 1.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
           -0.5f, 3.5f, 1.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
           -0.5f, 3.5f, -1.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
           //

           -01.5f, 3.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, //1
           0.5f, 3.5f, -01.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
           01.5f, 3.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
           01.5f, 3.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
           -0.5f, 3.5f, 01.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, //5
           -01.5f, 3.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // 6
            // 
           -0.5f, 3.5f, -1.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, //1
           01.5f, 3.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, //2
           0.5f, 3.5f, 01.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, //3
           0.5f, 3.5f, 01.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, //4
           -01.5f, 3.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, //5
           -0.5f, 3.5f, -1.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, //6


         
    };
    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    mesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}


void UDestroyMesh(GLMesh& mesh)
{
    glDeleteVertexArrays(1, &mesh.vao);
    glDeleteBuffers(1, &mesh.vbo);
}


/*Generate and load the texture*/
bool UCreateTexture(const char* filename, GLuint& textureId)
{
    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
    if (image)
    {
        flipImageVertically(image, width, height, channels);

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (channels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        else if (channels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        else
        {
            cout << "Not implemented to handle image with " << channels << " channels" << endl;
            return false;
        }

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(image);
        glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

        return true;
    }

    // Error loading the image
    return false;
}


void UDestroyTexture(GLuint textureId)
{
    glGenTextures(1, &textureId);
}


// Implements the UCreateShaders function
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId)
{
    // Compilation and linkage error reporting
    int success = 0;
    char infoLog[512];

    // Create a Shader program object.
    programId = glCreateProgram();

    // Create the vertex and fragment shader objects
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // Retrive the shader source
    glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
    glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

    // Compile the vertex shader, and print compilation errors (if any)
    glCompileShader(vertexShaderId); // compile the vertex shader
    // check for shader compile errors
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glCompileShader(fragmentShaderId); // compile the fragment shader
    // check for shader compile errors
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    // Attached compiled shaders to the shader program
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

    glLinkProgram(programId);   // links the shader program
    // check for linking errors
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glUseProgram(programId);    // Uses the shader program

    return true;
}


void UDestroyShaderProgram(GLuint programId)
{
    glDeleteProgram(programId);
}
