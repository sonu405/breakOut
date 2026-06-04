# Code Organization
We define a spriteRenderer class that takes in a sprite (a texture) and loads it into a rectangle by defining its VBO, VAO, VBO etc required.
It takes in a shader object so, we can define different shaders for different sprites.

# Some things to remember
We define our projection matrix (view space -> clip space) like this for our game where we need orthographic projection. 
`glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);`

parameters: (left, right, bottom, top);

This means, x -> (left, right)
            y -> (600, 0)

(0,0) -------------------- (800,0)
   |                        |
   |                        |
   |                        |
(0,600) ------------------ (800,600)


Ortho maps  => (0 -- 800) -> (-1, +1) NDC
            => (600 -- 0) -> (-1, +1) NDC

We flip the y to increase downward because this is the convension most 2D games follow.

# NOTE
Breakout is a 2D one scene game so we don't use the camera/view matrix instead directly transform the 
world coordinates to the normalized device coordinates. This is the reason for such ranges in the orthographic 
projection matrix we defined above.
(Remember that we get world coordiantes from the local space using the model matrix)



