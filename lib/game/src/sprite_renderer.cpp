#include "sprite_renderer.h"
#include <glm/glm.hpp>

void SpriteRenderer::initRenderData() {
    // configure VAO/VBO
    unsigned int VBO;

    float vertices[] = {
        // pos // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // GL_STATIC_DRAW: vertex data will be set once and used many times for drawing
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

    
    glBindVertexArray(quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);

    // unbinding our VBO and quadVAO from the openGL state machine
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(const Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color){
    // apply all the options to our shader so we must first select it.
    shader.Use();

    // When transforming objects, 
    // we must first scale, rotate and then translate by convension. we code in
    // reverse order because matrix multiplication 
    // is done from right.
    

    // Note that we have 0,0 at the top left. So, in order to rotate, we must first go to the origin and rotate from there. 
    // quad: (0,0) → (1,1) => in local space
    // size = (2,2)
    // center = (1,1)

    // Take a local vertex: (0.5, 0.5)
    // Scale => (1, 1)  : quad is in size space
    // We translate by -0.5 * size = (-1, -1). hence, v = (1,1) + (-1, -1) = (0,0). Thus, the vertex is at origin.

    // we rotate it at origin. 
    // Move the pivot back by translating with (0.5 * size) = (1,1). 
    // Thus, v = (1,1);

    // If the world pos is (10, 10);
    // Move to world so v = (11, 11)

    // IN CONCLUSION: The origin is at the top left of the object. So, we move the object in such a way that the object's centre is at the origin. 
    //                Origin stays there, the object moves. 

    //                After rotating, we move the object back to its place.

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5*size.y, 0.0f));

    // in a 2D game, rotating across the z axis.
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); 

    model = glm::translate(model, glm::vec3(-0.5*size.x, -0.5*size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));


    // in our shader, set the model and spriteColor uniforms 
    shader.SetMatrix4("model", model); // in vertex shader
    shader.SetVector3f("spriteColor", color); // in fragment shader
    
    // GPU has fixed number of texture slots. 
    // Telll, GPU that i am using texture 0.  
    // so, anything that binds goes onto texture 0. 
    glActiveTexture(GL_TEXTURE0); 

    // thus, Texture Unit 0 → our texture
    texture.Bind();               

    // tell to use the quadVAO for drawing.
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0); // unbind the quadVAO
}
    