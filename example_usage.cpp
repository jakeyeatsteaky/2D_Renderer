#include "Renderer.h"

Renderer renderer;

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
