#include "Renderer.h"

Renderer renderer;

What should this library do?
Primitives API

    Provide basic rendering functions for common shapes:
        renderRectangle(location, color, size)
        renderCircle(location, color, radius)
        renderLine(start, end, color, thickness)
    These should handle:
        Position.
        Size or dimensions.
        Color (RGBA or similar).

Textured Primitives

    Extend the primitives to support textures:
        renderRectangle(location, texture, size, uvCoords)
        renderCircle(location, texture, radius)
    Include texture handling features:
        Texture loading and binding.
        Texture atlases (optional, for efficient sprite rendering).

Batching

    Automatically batch draw calls to minimize performance overhead:
        Users call functions like renderRectangle repeatedly, and your library handles batching internally.

Shaders and Effects

    Allow for customizable shader effects:
        Example: setShaderEffect(shaderProgram), where shaderProgram is a user-defined GLSL program.
    Provide built-in effects:
        Color grading.
        Blur.
        Simple lighting (e.g., ambient, directional).

Transformations

    Support transformations for objects:
        Translation, rotation, scaling.
        API example:

        setTransformation(location, rotation, scale);
        renderRectangle(...);

Render-to-Texture

    Allow users to render to an off-screen framebuffer (e.g., for post-processing or creating custom textures).
    API example:

        startRenderToTexture(texture);
        renderRectangle(...);
        endRenderToTexture();

    Debugging Tools
        Optional but useful:
            renderBoundingBox(location, size, color).
            Visualize coordinate systems or texture UVs.

Example API
Rectangle Rendering

void renderRectangle(const glm::vec2& location, const glm::vec4& color, const glm::vec2& size);
void renderRectangle(const glm::vec2& location, const Texture& texture, const glm::vec2& size);

Circle Rendering

void renderCircle(const glm::vec2& location, const glm::vec4& color, float radius);
void renderCircle(const glm::vec2& location, const Texture& texture, float radius);

Shader Effects

void setShaderEffect(const Shader& shader);

Transformations

void pushMatrix(const glm::mat4& transformation);
void popMatrix();

Utility Functions

Texture loadTexture(const std::string& filepath);
Shader compileShader(const std::string& vertexSrc, const std::string& fragmentSrc);

Internal Design
Renderer Pipeline

    Handle rendering internally:
        Batch primitives and issue draw calls efficiently.
        Abstract the VAO/VBO management from users.

Shaders

    Provide default shaders for:
        Untextured primitives.
        Textured primitives.
    Allow users to pass custom shaders for effects.

State Management

    Manage OpenGL state (e.g., bound textures, shaders) internally to minimize user error.

Built-In Shader Effects

Provide a few built-in shader effects that users can enable easily:

    Color Blending:
        Change the color of rendered objects dynamically.
    Blur:
        Apply a Gaussian blur or similar to textures.
    Outline:
        Add an outline around objects.
    Gradient Fill:
        Allow gradients for primitives.

int main() {
    renderer.initialize();

    renderer.renderRectangle({100, 200}, {1.0f, 0.0f, 0.0f, 1.0f}, {50, 50});
    renderer.renderCircle({300, 400}, {0.0f, 0.0f, 1.0f, 1.0f}, 25);

    Texture texture = renderer.loadTexture("assets/sprite.png");
    renderer.renderRectangle({400, 300}, texture, {50, 50});

    Shader customShader = renderer.compileShader(vertexSrc, fragmentSrc);
    renderer.setShaderEffect(customShader);

    renderer.renderRectangle({100, 100}, {1.0f, 1.0f, 0.0f, 1.0f}, {50, 50});

    renderer.finalize();
    return 0;
}
