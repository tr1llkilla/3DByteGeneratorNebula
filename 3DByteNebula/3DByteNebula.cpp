/**
 * main.cpp - 3D Byte Universe Simulation with Advanced Physics
 *
 * Author: Cadell Richard Anderson
 * Co-author: Gemini
 * Date: October 18, 2025
 * Environment: C++17, Visual Studio 2022/2026
 # ElevenValueBoolean

**Author:** Cadell Richard Anderson  
**License:** Custom License: ElevenValueBoolean Attribution License (EAL) v1.0
**Version:** 0.2  
**Date:** July 2025
 *
 * --- DESCRIPTION OF ENHANCEMENTS (V5) ---
 * This version introduces a parallel simulation layer for subatomic particle physics,
 * creating a multi-scale model of the universe from quantum fields to cosmic structures.
 *
 * Key New Features:
 * - Subatomic Simulation Layer: A new set of particles ("protons", "neutrons", "quarks")
 * now exist in a parallel simulation. Their interactions, governed by approximations of
 * strong, weak, and electromagnetic forces, are logged to the console.
 * - Quantum & Nuclear Events: The simulation now logs events like beta decay,
 * deuterium synthesis (p+n fusion), and electron-positron annihilation, providing a
 * window into the quantum-level physics.
 * - Refined Quantum Entanglement: The logic for creating and rendering the "Flux Web" has been
 * enhanced for more stable and visually appealing results, with more detailed event logging.
 * - Doppler Relativity Overlay: Particle colors are still tinted red or blue based on their
 * velocity relative to the camera (redshift/blueshift).
 * - Advanced Thermodynamics & MHD: The cosmological simulation continues to be governed by
 * thermal conduction, radiative cooling, shock heating, and magnetic fields, driving the
 * formation of protostars and galaxies.
 *
 * --- HOW TO COMPILE ---
 * This is a single-file project, but it depends on three external libraries:
 * 1. GLFW: For window and input management. (https://www.glfw.org/)
 * 2. GLAD: To load modern OpenGL functions. (https://glad.dav1d.de/)
 * 3. GLM: For OpenGL mathematics (vectors, matrices). (https://glm.g-truc.net/)
 *
 * Setup Instructions for Visual Studio with vcpkg:
 * 1. Run 'vcpkg integrate install'.
 * 2. Install packages: 'vcpkg install glad glfw3 glm'.
 * 3. Create a new C++ Console App project.
 * 4. Add the glad.c file (if needed by your setup) to your project's source files.
 * 5. Copy the entire content of this file into your `main.cpp`.
 * 6. Compile and run.
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream> // Required for std::stringstream
#include <cmath>
#include <random>
#include <iomanip>
#include <algorithm>
#include <unordered_map>
#include <numeric>

 // OpenGL Loader (GLAD)
#include <glad/glad.h>
// Windowing and Input (GLFW)
#include <GLFW/glfw3.h>

// Mathematics for OpenGL (GLM)
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtx/norm.hpp>

// --- ElevenValueBoolean Class (As provided and integrated) ---
class ElevenValueBoolean {
public:
    enum State : unsigned char {
        AbsoluteUncertainty = 0, HighlyUnlikely = 1, Unlikely = 2, SomewhatFalse = 3, ModeratelyFalse = 4,
        Neutral = 5, ModeratelyTrue = 6, SomewhatTrue = 7, Likely = 8, HighlyLikely = 9, AbsoluteCertainty = 10
    };
private:
    State current_state;
    double applyChaoticInfluence(double value) const {
        const double r = 3.99;
        double normalized_value = value / 10.0;
        double transformed_value = r * normalized_value * (1.0 - normalized_value);
        return std::round(transformed_value * 10.0);
    }
    State clampState(double value) const {
        return static_cast<State>(std::clamp(static_cast<int>(std::round(value)), 0, 10));
    }
public:
    ElevenValueBoolean(State initial_state = AbsoluteUncertainty) : current_state(initial_state) {}
    ElevenValueBoolean(int initial_value) : current_state(clampState(static_cast<double>(initial_value))) {}

    State getState() const { return current_state; }
    void setState(State new_state) { current_state = new_state; }

    ElevenValueBoolean operator!() const {
        double inverted_value = 10.0 - static_cast<double>(current_state);
        double influenced_value = applyChaoticInfluence(inverted_value);
        return ElevenValueBoolean(clampState(influenced_value));
    }
    std::string toString() const {
        const char* names[] = { "AbsUncertainty", "HighlyUnlikely", "Unlikely", "SomewhatFalse", "ModeratelyFalse",
                                "Neutral", "ModeratelyTrue", "SomewhatTrue", "Likely", "HighlyLikely", "AbsCertainty" };
        return names[current_state] + std::string(" (") + std::to_string(current_state) + std::string(")");
    }
};

// --- Simulation Constants and Structures ---
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// Grid dimensions
const int GRID_DIM = 32;
float UNIVERSE_SIZE = 150.0f;

// Camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, UNIVERSE_SIZE * 0.9f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true;
bool mouseDragging = false;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = SCR_WIDTH / 2.0;
float lastY = SCR_HEIGHT / 2.0;
float fov = 55.0f;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float timeScale = 1.0f;

// --- V5: SUBATOMIC STRUCTURES ---
struct SubatomicParticle {
    std::string name;         // "proton", "neutron", "quark_up", "gluon"
    float mass;               // MeV/c^2
    float charge;             // e
    float spin;               // intrinsic spin
    glm::vec3 pos, vel;       // position/velocity in a conceptual space
};

struct ParticleDefinition {
    std::string name;
    float mass;
    float charge;
    float spin;
};

// --- COSMOLOGICAL STRUCTURES ---
struct ByteParticle {
    glm::vec3 pos{ 0.0f };
    glm::vec3 vel{ 0.0f };
    int atomic_number = 0;
    bool isAnti = false;
    ElevenValueBoolean evbState;
    float lifespan = 0.0f;
    float temperature = 0.0f;
    float dopplerShift = 0.0f;
    float relativisticEnergy = 0.0f;
};

struct GridCell {
    std::vector<int> particleIndices;
    glm::mat3 pressureTensor{ 0.0f };
    glm::vec3 avgVelocity{ 0.0f };
    float temperature = 0.0f;
    float density = 0.0f;
    float entropy = 0.0f;
};

struct EntangledLink {
    size_t a, b;
    float coherence;
    float maxCoherence;
    glm::vec3 color;
};

// Global simulation state
std::vector<ByteParticle> particles;
std::vector<GridCell> grid;
std::vector<glm::vec4> particleRenderData;
std::vector<float> dopplerRenderData;
std::vector<EntangledLink> entangledLinks;
std::vector<SubatomicParticle> fieldParticles; // V5: Subatomic field
std::mt19937 rng(std::random_device{}());
int currentEpochIndex = 0;

// --- V5: STANDARD MODEL DATA ---
const float MASS_PROTON = 938.27f;
const float MASS_NEUTRON = 939.56f;
const float MASS_ELECTRON = 0.511f;
const float MASS_POSITRON = 0.511f;
const float MASS_UP_QUARK = 2.2f;
const float MASS_DOWN_QUARK = 4.7f;
const float MASS_GLUON = 0.0f;
const float MASS_PHOTON = 0.0f;
const float MASS_HIGGS = 125090.0f; // MeV

std::vector<ParticleDefinition> standardModel = {
    {"up_quark", MASS_UP_QUARK, +2.0f / 3.0f, 0.5f},
    {"down_quark", MASS_DOWN_QUARK, -1.0f / 3.0f, 0.5f},
    {"gluon", MASS_GLUON, 0.0f, 1.0f},
    {"photon", MASS_PHOTON, 0.0f, 1.0f},
    {"electron", MASS_ELECTRON, -1.0f, 0.5f},
    {"positron", MASS_POSITRON, +1.0f, 0.5f},
    {"neutrino", 0.0f, 0.0f, 0.5f},
    {"proton", MASS_PROTON, +1.0f, 0.5f},
    {"neutron", MASS_NEUTRON, 0.0f, 0.5f},
    {"higgs_boson", MASS_HIGGS, 0.0f, 0.0f},
};


// --- Forward Declarations ---
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void initSimulation();
void updateSimulation(float dt);
void triggerSupernova(int grid_idx);
void triggerKilonova(int grid_idx1, int grid_idx2);
void diffuseTemperature(float dt);
void applyRadiativeCooling(float dt);
void applyShockHeating(float dt);
void particleCollisions();
void updateIonization(float dt);
void applyMagneticForces(float dt);
glm::vec3 computeGridPressureForce(int idx, const glm::vec3& pos);
void applyDopplerRelativity(float dt);
void applyQuantumEntanglement(float dt);
void renderEntanglementFluxWeb(unsigned int shader, const glm::mat4& view, const glm::mat4& projection);
static int getGridIndex(const glm::vec3& pos);
static glm::vec3 getMagneticField(const glm::vec3& pos);
// V5: New Subatomic Layer Declarations
void applyQuantumFieldInteractions(float dt);
void handleNuclearFusion(float dt);
void handleHighEnergyEvents(float dt);
float randFloat();


// --- Shader Source ---
const char* vertexShaderSource = R"glsl(#version 330 core
    layout (location = 0) in vec4 posAndType;
    layout (location = 1) in float dopplerShiftIn;
    uniform mat4 model; uniform mat4 view; uniform mat4 projection;
    out vec4 particleColor;
    out float dopplerShift;
    vec4 getColorForAtom(float num) {
        if (num < 1.5) return vec4(0.9, 0.9, 1.0, 0.7);
        if (num < 2.5) return vec4(0.6, 0.8, 1.0, 0.75);
        if (num < 6.5) return vec4(0.5, 0.5, 0.5, 0.8);
        if (num < 8.5) return vec4(1.0, 0.2, 0.2, 0.85);
        if (num < 26.5) return vec4(0.6, 0.4, 0.2, 0.9);
        if (num < 79.5) return vec4(0.7, 0.3, 0.9, 0.95);
        if (num >= 79.5) return vec4(1.0, 0.85, 0.0, 1.0);
        return vec4(0.2, 0.8, 0.3, 0.8);
    }
    void main() {
        gl_Position = projection * view * model * vec4(posAndType.xyz, 1.0);
        float type = posAndType.w;
        if (type == 0.0) particleColor = vec4(1.0, 1.0, 0.9, 1.0);
        else if (type < 0.0) particleColor = getColorForAtom(-type) * vec4(1.0, 0.5, 0.5, 1.0);
        else particleColor = getColorForAtom(type);
        gl_PointSize = 1.0 + (particleColor.a * 2.5);
        dopplerShift = dopplerShiftIn;
    })glsl";

const char* fragmentShaderSource = R"glsl(#version 330 core
    in vec4 particleColor;
    in float dopplerShift;
    out vec4 FragColor;

    vec4 applyDopplerOverlay(vec4 baseColor, float shift) {
        vec3 tint = vec3(1.0);
        if (shift > 0.0) tint = vec3(1.0, 0.6, 0.4);   // redshift
        else if (shift < 0.0) tint = vec3(0.6, 0.8, 1.0); // blueshift
        float intensity = clamp(abs(shift) * 5.0, 0.0, 0.5);
        baseColor.rgb = mix(baseColor.rgb, tint, intensity);
        return baseColor;
    }

    void main() {
        float dist = length(gl_PointCoord - vec2(0.5));
        float alpha = 1.0 - smoothstep(0.4, 0.5, dist);
        vec4 finalColor = applyDopplerOverlay(particleColor, dopplerShift);
        FragColor = vec4(finalColor.rgb, finalColor.a * alpha);
    })glsl";

const char* lineVertexShaderSource = R"glsl(#version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec4 aColor;
    uniform mat4 projection;
    uniform mat4 view;
    out vec4 lineColor;
    void main() {
        gl_Position = projection * view * vec4(aPos, 1.0);
        lineColor = aColor;
    })glsl";

const char* lineFragmentShaderSource = R"glsl(#version 330 core
    in vec4 lineColor;
    out vec4 FragColor;
    void main() {
        FragColor = lineColor;
    })glsl";


// --- Main Application ---
int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Byte Universe", NULL, NULL);
    if (!window) { std::cout << "Failed to create GLFW window" << std::endl; glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { std::cout << "Failed to initialize GLAD" << std::endl; return -1; }

    // Particle Shader
    unsigned int particleShaderProgram;
    {
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        particleShaderProgram = glCreateProgram();
        glAttachShader(particleShaderProgram, vertexShader);
        glAttachShader(particleShaderProgram, fragmentShader);
        glLinkProgram(particleShaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    // Line Shader
    unsigned int lineShaderProgram;
    {
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &lineVertexShaderSource, NULL);
        glCompileShader(vertexShader);
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &lineFragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        lineShaderProgram = glCreateProgram();
        glAttachShader(lineShaderProgram, vertexShader);
        glAttachShader(lineShaderProgram, fragmentShader);
        glLinkProgram(lineShaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    unsigned int particleVAO, particleVBO, dopplerVBO;
    glGenVertexArrays(1, &particleVAO);
    glGenBuffers(1, &particleVBO);
    glGenBuffers(1, &dopplerVBO);
    glBindVertexArray(particleVAO);
    glBindBuffer(GL_ARRAY_BUFFER, particleVBO);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, dopplerVBO);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);

    initSimulation();

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        updateSimulation(deltaTime);

        std::stringstream ss;
        ss << "Byte Universe | Particles: " << particles.size() << " | Time: " << std::fixed << std::setprecision(2) << timeScale << "x";
        glfwSetWindowTitle(window, ss.str().c_str());

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, UNIVERSE_SIZE * 2.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 model = glm::mat4(1.0f);

        // Draw Particles
        glUseProgram(particleShaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(particleShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(particleShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(particleShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

        if (!particleRenderData.empty()) {
            glBindBuffer(GL_ARRAY_BUFFER, particleVBO);
            glBufferData(GL_ARRAY_BUFFER, particleRenderData.size() * sizeof(glm::vec4), particleRenderData.data(), GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, dopplerVBO);
            glBufferData(GL_ARRAY_BUFFER, dopplerRenderData.size() * sizeof(float), dopplerRenderData.data(), GL_DYNAMIC_DRAW);
        }

        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glBindVertexArray(particleVAO);
        glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(particleRenderData.size()));

        // Draw Flux Web
        renderEntanglementFluxWeb(lineShaderProgram, view, projection);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &particleVAO);
    glDeleteBuffers(1, &particleVBO);
    glDeleteBuffers(1, &dopplerVBO);
    glDeleteProgram(particleShaderProgram);
    glDeleteProgram(lineShaderProgram);
    glfwTerminate();
    return 0;
}

static int getGridIndex(const glm::vec3& pos) {
    int ix = static_cast<int>((pos.x / UNIVERSE_SIZE + 0.5f) * GRID_DIM);
    int iy = static_cast<int>((pos.y / UNIVERSE_SIZE + 0.5f) * GRID_DIM);
    int iz = static_cast<int>((pos.z / UNIVERSE_SIZE + 0.5f) * GRID_DIM);
    ix = std::clamp(ix, 0, GRID_DIM - 1);
    iy = std::clamp(iy, 0, GRID_DIM - 1);
    iz = std::clamp(iz, 0, GRID_DIM - 1);
    return ix * GRID_DIM * GRID_DIM + iy * GRID_DIM + iz;
}

// V5: Helper for random floats
float randFloat() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

void initSimulation() {
    // Cosmological simulation
    const int NUM_PARTICLES = 100000;
    particles.clear();
    particles.resize(NUM_PARTICLES);
    std::uniform_real_distribution<float> pos_dist(-1.0f, 1.0f);

    for (int i = 0; i < NUM_PARTICLES; ++i) {
        glm::vec3 pos = glm::vec3(pos_dist(rng), pos_dist(rng) * 0.5f, pos_dist(rng)) * (UNIVERSE_SIZE * 0.4f);
        particles[i].pos = pos;
        particles[i].vel = glm::cross(pos, glm::vec3(0.0f, 1.0f, 0.0f)) * 0.05f;
        particles[i].atomic_number = 1;
        particles[i].isAnti = (rng() % 100 < 2);
        particles[i].evbState = ElevenValueBoolean::AbsoluteUncertainty;
        particles[i].lifespan = 0.0f;
        particles[i].temperature = 1.0f + randFloat() * 2.0f;
    }
    grid.assign(GRID_DIM * GRID_DIM * GRID_DIM, GridCell());
    entangledLinks.clear();
    currentEpochIndex = 0;

    // V5: Subatomic simulation
    const int NUM_FIELD_PARTICLES = 200;
    fieldParticles.clear();
    fieldParticles.reserve(NUM_FIELD_PARTICLES);
    for (int i = 0; i < NUM_FIELD_PARTICLES; ++i) {
        SubatomicParticle p;
        int type = rng() % 4;
        ParticleDefinition def;
        if (type == 0) def = standardModel[7]; // proton
        else if (type == 1) def = standardModel[8]; // neutron
        else if (type == 2) def = standardModel[4]; // electron
        else def = standardModel[5]; // positron

        p.name = def.name;
        p.mass = def.mass;
        p.charge = def.charge;
        p.spin = def.spin;
        p.pos = glm::ballRand(5.0f); // smaller conceptual space
        p.vel = glm::vec3(0.0f);
        fieldParticles.push_back(p);
    }
}

void updateSimulation(float real_dt) {
    if (real_dt > 0.017f) real_dt = 0.017f;

    float dt = real_dt * timeScale;

    // --- V5: SUBATOMIC SIMULATION UPDATE ---
    // This runs in parallel and only logs to console, not affecting the main visualization
    applyQuantumFieldInteractions(dt);
    handleNuclearFusion(dt);
    handleHighEnergyEvents(dt);
    // --- END SUBATOMIC ---

    // Grid Binning
    for (auto& cell : grid) {
        cell.particleIndices.clear();
        cell.temperature = 0.0f;
        cell.density = 0.0f;
        cell.avgVelocity = glm::vec3(0.0f);
        cell.entropy = 0.0f;
    }
    for (size_t i = 0; i < particles.size(); ++i) {
        if (particles[i].lifespan <= 0.0f) {
            grid[getGridIndex(particles[i].pos)].particleIndices.push_back(static_cast<int>(i));
        }
    }

    // Grid Property Calculation
    for (auto& cell : grid) {
        if (cell.particleIndices.empty()) continue;
        cell.density = (float)cell.particleIndices.size();
        for (int p_idx : cell.particleIndices) {
            cell.temperature += particles[p_idx].temperature;
            cell.avgVelocity += particles[p_idx].vel;
        }
        cell.temperature /= cell.density;
        cell.avgVelocity /= cell.density;
        cell.entropy = logf(cell.density + 1.0f) + 0.01f * cell.temperature;
    }

    // Physics Layers
    applyRadiativeCooling(dt);
    diffuseTemperature(dt);
    applyShockHeating(dt);
    particleCollisions();
    applyMagneticForces(dt);
    updateIonization(dt);
    applyDopplerRelativity(dt);
    applyQuantumEntanglement(dt);

    // Nucleosynthesis
    for (size_t i = 0; i < grid.size(); ++i) {
        if (grid[i].particleIndices.size() < 2) continue;
        if (grid[i].density > 20.0f && grid[i].temperature > 25.0f) {
            if (particles[grid[i].particleIndices[0]].atomic_number < 26 && particles[grid[i].particleIndices[1]].atomic_number < 26) {
                particles[grid[i].particleIndices[0]].atomic_number += particles[grid[i].particleIndices[1]].atomic_number;
                particles[grid[i].particleIndices[0]].temperature += 25.0f;
                particles[grid[i].particleIndices[1]].lifespan = 0.01f;
            }
        }
        if (grid[i].density > 50.0f && grid[i].temperature > 100.0f) triggerSupernova(static_cast<int>(i));
        if (i < grid.size() - 1 && grid[i].density > 45.f && grid[i + 1].density > 45.f && glm::length2(grid[i].avgVelocity - grid[i + 1].avgVelocity) > 2.0f) {
            triggerKilonova(static_cast<int>(i), static_cast<int>(i + 1));
        }
    }

    // Integration
    for (size_t i = 0; i < particles.size(); ++i) {
        ByteParticle& p = particles[i];
        if (p.lifespan > 0.0f) { p.lifespan -= dt; continue; }
        glm::vec3 force(0.0f);
        if (glm::length(p.pos) > 0.1f) {
            force += -glm::normalize(p.pos) * 1.5f * ((float)p.atomic_number * 0.1f + 1.0f);
        }
        force += computeGridPressureForce(getGridIndex(p.pos), p.pos);
        p.vel += force * dt;
        p.pos += p.vel * dt;
        if (glm::length2(p.pos) > (UNIVERSE_SIZE / 2.0f * UNIVERSE_SIZE / 2.0f)) {
            p.pos = glm::normalize(p.pos) * (UNIVERSE_SIZE / 2.0f - 0.1f);
            p.vel = -p.vel * 0.1f;
        }
    }

    // Cleanup & Build Render Data
    particleRenderData.clear();
    dopplerRenderData.clear();
    std::vector<ByteParticle> next_particles;
    next_particles.reserve(particles.size());
    for (const auto& p : particles) {
        if (p.lifespan <= 0.0f) next_particles.push_back(p);
        particleRenderData.push_back(glm::vec4(p.pos, p.isAnti ? -static_cast<float>(p.atomic_number) : static_cast<float>(p.atomic_number)));
        dopplerRenderData.push_back(p.dopplerShift);
    }
    particles = next_particles;
}

// --- V5: SUBATOMIC PHYSICS IMPLEMENTATIONS ---
void applyQuantumFieldInteractions(float dt) {
    for (size_t i = 0; i < fieldParticles.size(); ++i) {
        for (size_t j = i + 1; j < fieldParticles.size(); ++j) {
            auto& a = fieldParticles[i];
            auto& b = fieldParticles[j];
            glm::vec3 r = b.pos - a.pos;
            float dist = glm::length(r);
            if (dist < 1e-3f) continue;

            glm::vec3 dir = r / dist;

            // Electromagnetic force
            float EM_force = (a.charge * b.charge) / (dist * dist);
            a.vel += dir * EM_force * dt * 0.001f; // Scaled for stability
            b.vel -= dir * EM_force * dt * 0.001f;

            // Strong QCD-like attraction at small scales (gluon binding)
            if (dist < 1.0f) {
                float strongForce = -expf(-dist) * 5.0f; // pseudo QCD potential
                a.vel += dir * strongForce * dt * 0.001f;
                b.vel -= dir * strongForce * dt * 0.001f;
            }

            // Weak decay example (beta decay trigger)
            if (a.name == "neutron" && dist < 0.1f && randFloat() < 1e-6f) {
                std::cout << "[EVENT: DECAY] Neutron -> Proton + Electron + Antineutrino\n";
                // In a real sim, you'd replace the neutron with the products
            }
        }
    }
    // Simple integration for subatomic particles
    for (auto& p : fieldParticles) {
        p.pos += p.vel * dt;
    }
}

void handleNuclearFusion(float dt) {
    for (auto& a : fieldParticles) {
        for (auto& b : fieldParticles) {
            if (&a == &b) continue;
            float dist = glm::length(a.pos - b.pos);
            if (dist < 0.05f && a.name == "proton" && b.name == "neutron") {
                if (randFloat() < 0.001f) // Low probability event
                    std::cout << "[EVENT: SYNTHESIS] Deuterium nucleus formed (p+n)\n";
            }
        }
    }
}

void handleHighEnergyEvents(float dt) {
    for (auto& p : fieldParticles) {
        if (p.name == "electron") {
            for (auto& q : fieldParticles) {
                if (q.name == "positron" && glm::distance(p.pos, q.pos) < 0.01f) {
                    if (randFloat() < 0.01f) // Low probability event
                        std::cout << "[EVENT: ANNIHILATION] e- + e+ -> gamma + gamma (511 keV photons)\n";
                }
            }
        }
    }
}


// --- Physics Implementations ---
void diffuseTemperature(float dt) {
    auto oldGrid = grid;
    for (int x = 1; x < GRID_DIM - 1; ++x) for (int y = 1; y < GRID_DIM - 1; ++y) for (int z = 1; z < GRID_DIM - 1; ++z) {
        int idx = x * GRID_DIM * GRID_DIM + y * GRID_DIM + z;
        if (oldGrid[idx].density == 0) continue;
        float neighbor_temp = (oldGrid[idx - 1].temperature + oldGrid[idx + 1].temperature + oldGrid[idx - GRID_DIM].temperature + oldGrid[idx + GRID_DIM].temperature + oldGrid[idx - GRID_DIM * GRID_DIM].temperature + oldGrid[idx + GRID_DIM * GRID_DIM].temperature) / 6.0f;
        grid[idx].temperature += 20.0f * (neighbor_temp - oldGrid[idx].temperature) * dt;
    }
}

void applyRadiativeCooling(float dt) {
    for (auto& cell : grid) {
        if (cell.temperature > 0.0f) {
            cell.temperature -= 1e-8f * powf(cell.temperature, 4) * dt;
            cell.temperature = std::max(0.0f, cell.temperature);
        }
    }
}

glm::vec3 computeGridPressureForce(int idx, const glm::vec3& pos) {
    const float k_B = 0.5f;
    float p_neg_x = k_B * grid[std::max(0, idx - 1)].density * grid[std::max(0, idx - 1)].temperature;
    float p_pos_x = k_B * grid[std::min((int)grid.size() - 1, idx + 1)].density * grid[std::min((int)grid.size() - 1, idx + 1)].temperature;
    float p_neg_y = k_B * grid[std::max(0, idx - GRID_DIM)].density * grid[std::max(0, idx - GRID_DIM)].temperature;
    float p_pos_y = k_B * grid[std::min((int)grid.size() - 1, idx + GRID_DIM)].density * grid[std::min((int)grid.size() - 1, idx + GRID_DIM)].temperature;
    float p_neg_z = k_B * grid[std::max(0, idx - GRID_DIM * GRID_DIM)].density * grid[std::max(0, idx - GRID_DIM * GRID_DIM)].temperature;
    float p_pos_z = k_B * grid[std::min((int)grid.size() - 1, idx + GRID_DIM * GRID_DIM)].density * grid[std::min((int)grid.size() - 1, idx + GRID_DIM * GRID_DIM)].temperature;
    return glm::vec3(-(p_pos_x - p_neg_x), -(p_pos_y - p_neg_y), -(p_pos_z - p_neg_z));
}

void applyShockHeating(float dt) {
    for (const auto& cell : grid) {
        if (cell.density < 2.0f) continue;
        for (int p_idx : cell.particleIndices) {
            particles[p_idx].temperature += 0.05f * glm::length2(particles[p_idx].vel - cell.avgVelocity) * dt;
        }
    }
}

void particleCollisions() {
    for (const auto& cell : grid) {
        if (cell.particleIndices.size() < 2) continue;
        for (size_t i = 0; i < cell.particleIndices.size() - 1; ++i) {
            for (size_t j = i + 1; j < cell.particleIndices.size(); ++j) {
                ByteParticle& p1 = particles[cell.particleIndices[i]];
                ByteParticle& p2 = particles[cell.particleIndices[j]];
                if (glm::distance2(p1.pos, p2.pos) < 0.5f) {
                    glm::vec3 v_rel = p1.vel - p2.vel, x_rel = p1.pos - p2.pos;
                    if (glm::length2(x_rel) > 0.001f) {
                        glm::vec3 impulse = glm::dot(v_rel, x_rel) / glm::length2(x_rel) * x_rel;
                        p1.vel -= impulse; p2.vel += impulse;
                    }
                    float avgTemp = (p1.temperature + p2.temperature) * 0.5f;
                    p1.temperature = p1.temperature * 0.9f + avgTemp * 0.1f;
                    p2.temperature = p2.temperature * 0.9f + avgTemp * 0.1f;
                }
            }
        }
    }
}

static glm::vec3 getMagneticField(const glm::vec3& pos) {
    return glm::vec3(-pos.y, pos.x, 0.0f) * (0.5f / (1.0f + glm::length(pos) * 0.1f));
}

void applyMagneticForces(float dt) {
    for (auto& p : particles) {
        if (p.lifespan <= 0.0f) {
            p.vel += glm::cross((float)p.atomic_number * p.vel * 0.1f, getMagneticField(p.pos)) * dt;
        }
    }
}

void updateIonization(float dt) {
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);
    for (auto& p : particles) {
        if (p.temperature > 80.0f && p.atomic_number < 26 && chance(rng) < 0.1f) {
            p.atomic_number++; p.temperature -= 10.0f;
        }
        else if (p.temperature < 10.0f && p.atomic_number > 1 && chance(rng) < 0.1f) {
            p.atomic_number--; p.temperature += 2.0f;
        }
    }
}

void applyDopplerRelativity(float dt) {
    const float C_LIGHT = 150.0f;
    const float DOPPLER_THRESHOLD = 0.25f;
    const float DOPPLER_LOG_INTERVAL = 5.0f;
    static float logTimer = 0.0f;
    logTimer += dt;

    for (auto& p : particles) {
        glm::vec3 viewDir = glm::normalize(p.pos - cameraPos);
        float vr = glm::dot(p.vel, viewDir);
        p.dopplerShift = vr / C_LIGHT;
        p.relativisticEnergy = p.temperature * (1.0f + 0.05f * p.dopplerShift);

        if (fabs(p.dopplerShift) > DOPPLER_THRESHOLD && logTimer > DOPPLER_LOG_INTERVAL) {
            if (p.dopplerShift > 0)
                std::cout << "[EVENT: RELATIVITY] Local redshift zone detected (v_r = +" << vr << ")\n";
            else
                std::cout << "[EVENT: RELATIVITY] Local blueshift zone detected (v_r = " << vr << ")\n";
        }
    }
    if (logTimer > DOPPLER_LOG_INTERVAL)
        logTimer = 0.0f;
}

// REPLACEMENT for applyQuantumEntanglement
void applyQuantumEntanglement(float dt) {
    const float L_COHERENCE = 15.0f;
    const float T_DECOH = 60.0f;
    const float ENTANGLE_RATE = 0.002f;
    const float ENTANGLE_EVENT_PROB = 0.001f;
    static std::uniform_real_distribution<float> chance(0.0f, 1.0f);

    if (particles.size() > 60) {
        for (size_t i = 0; i < particles.size(); i += 30) {
            ByteParticle& p1 = particles[i];
            size_t j = (i + rng() % (particles.size() - 30)) % particles.size();
            ByteParticle& p2 = particles[j];

            float r = glm::distance(p1.pos, p2.pos);
            float C_ent = expf(-r / L_COHERENCE) * expf(-p1.temperature / T_DECOH);

            if (chance(rng) < C_ent * ENTANGLE_RATE) {
                auto newState = static_cast<ElevenValueBoolean::State>(
                    (p1.evbState.getState() + p2.evbState.getState()) / 2);
                p1.evbState.setState(newState);
                p2.evbState.setState(newState);

                glm::vec3 meanVel = (p1.vel + p2.vel) * 0.5f;
                p1.vel = glm::mix(p1.vel, meanVel, 0.01f);
                p2.vel = glm::mix(p2.vel, meanVel, 0.01f);

                glm::vec3 color = glm::vec3(0.3f + 0.7f * C_ent,
                    0.5f + 0.5f * C_ent,
                    1.0f);
                entangledLinks.push_back({ i, j, C_ent, C_ent, color });

                if (chance(rng) < ENTANGLE_EVENT_PROB)
                    std::cout << "[EVENT: QUANTUM] Entanglement formed between "
                    << i << " and " << j << " (C=" << C_ent << ")\n";
            }
        }
    }

    // Gradual decoherence of links
    for (auto& link : entangledLinks) {
        link.coherence -= dt * 0.05f;
        if (link.coherence < 0.0f) link.coherence = 0.0f;
    }

    // Remove broken links
    entangledLinks.erase(
        std::remove_if(entangledLinks.begin(), entangledLinks.end(),
            [](const EntangledLink& l) { return l.coherence <= 0.0f; }),
        entangledLinks.end());
}

// REPLACEMENT for renderEntanglementFluxWeb
void renderEntanglementFluxWeb(unsigned int shader, const glm::mat4& view, const glm::mat4& projection) {
    if (entangledLinks.empty()) return;

    glUseProgram(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));

    std::vector<glm::vec3> lineVertices;
    std::vector<glm::vec4> lineColors;

    for (const auto& link : entangledLinks) {
        if (link.a >= particles.size() || link.b >= particles.size()) continue;
        const ByteParticle& p1 = particles[link.a];
        const ByteParticle& p2 = particles[link.b];

        float alpha = glm::clamp(link.coherence / link.maxCoherence, 0.0f, 1.0f);
        glm::vec4 c(link.color * alpha, alpha);

        lineVertices.push_back(p1.pos);
        lineVertices.push_back(p2.pos);
        lineColors.push_back(c);
        lineColors.push_back(c);
    }

    if (lineVertices.empty()) return;

    unsigned int VAO, VBOv, VBOc;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBOv);
    glGenBuffers(1, &VBOc);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBOv);
    glBufferData(GL_ARRAY_BUFFER, lineVertices.size() * sizeof(glm::vec3), lineVertices.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBOc);
    glBufferData(GL_ARRAY_BUFFER, lineColors.size() * sizeof(glm::vec4), lineColors.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
    glEnableVertexAttribArray(1);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glLineWidth(1.5f);
    glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(lineVertices.size()));

    glDeleteBuffers(1, &VBOv);
    glDeleteBuffers(1, &VBOc);
    glDeleteVertexArrays(1, &VAO);
}


// --- Nucleosynthesis Events ---
void triggerSupernova(int grid_idx) {
    GridCell& cell = grid[grid_idx];
    if (cell.density == 0) return;
    glm::vec3 center_pos(0.0f);
    for (int p_idx : cell.particleIndices) { center_pos += particles[p_idx].pos; }
    center_pos /= cell.density;
    std::cout << "EVENT: Core-Collapse Supernova!" << std::endl;
    std::uniform_int_distribution<int> element_dist(8, 30);
    for (int p_idx : cell.particleIndices) {
        particles[p_idx].atomic_number = element_dist(rng);
        particles[p_idx].vel += glm::normalize(particles[p_idx].pos - center_pos + 0.01f) * 20.0f;
        particles[p_idx].temperature += 100.0f;
    }
}
void triggerKilonova(int grid_idx1, int grid_idx2) {
    std::cout << "EVENT: KILONOVA!" << std::endl;
    std::vector<int> combined_indices = grid[grid_idx1].particleIndices;
    combined_indices.insert(combined_indices.end(), grid[grid_idx2].particleIndices.begin(), grid[grid_idx2].particleIndices.end());
    std::uniform_int_distribution<int> heavy_element_dist(31, 80);
    for (size_t i = 0; i < combined_indices.size(); ++i) {
        int p_idx = combined_indices[i];
        if (i % 4 == 0) particles[p_idx].atomic_number = heavy_element_dist(rng);
        particles[p_idx].vel *= -1.2f;
        particles[p_idx].vel += glm::sphericalRand(25.0f);
        particles[p_idx].temperature += 200.0f;
    }
}

// --- GLFW Callbacks and Input ---
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        initSimulation();

    bool shift_pressed = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);
    bool ctrl_pressed = (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS);

    float timeAdjustmentFactor = 1.02f;
    if (shift_pressed) timeAdjustmentFactor = 1.005f;
    else if (ctrl_pressed) timeAdjustmentFactor = 1.1f;

    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) timeScale *= timeAdjustmentFactor;
    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) timeScale /= timeAdjustmentFactor;
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) timeScale = 1.0f;
    timeScale = std::max(0.001f, timeScale);


    float cameraSpeed = static_cast<float>(40.0 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) cameraPos += cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && !ctrl_pressed) cameraPos -= cameraSpeed * cameraUp;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            mouseDragging = true; firstMouse = true;
        }
        else if (action == GLFW_RELEASE) {
            mouseDragging = false;
        }
    }
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    if (!mouseDragging) return;

    float xpos = static_cast<float>(xposIn), ypos = static_cast<float>(yposIn);
    if (firstMouse) { lastX = xpos; lastY = ypos; firstMouse = false; }
    float xoffset = xpos - lastX, yoffset = lastY - ypos;
    lastX = xpos; lastY = ypos;
    float sensitivity = 0.1f;
    xoffset *= sensitivity; yoffset *= sensitivity;
    yaw += xoffset; pitch += yoffset;
    if (pitch > 89.0f) pitch = 89.0f; if (pitch < -89.0f) pitch = -89.0f;
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    fov -= (float)yoffset;
    if (fov < 1.0f) fov = 1.0f;
    if (fov > 75.0f) fov = 75.0f;
}

