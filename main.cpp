#include "Camera.h"
#include "Shader.h"
#include "Model.h"

int main(int argc, char **argv)
{

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    sf::Event event;

    glewExperimental=true;
    GLenum initialisationGLEW( glewInit() );
    if(initialisationGLEW != GLEW_OK)
    {
        // On affiche l'erreur grla fonction : glewGetErrorString(GLenum code)
        std::cout << "Glew Initialisation Error : " << glewGetErrorString(initialisationGLEW) << std::endl;
    }
    else
        std::cout << "Glew Initialisation Successful" << std::endl;

    glm::mat4 view;
    glm::mat4 projection;
    projection = glm::perspective(70.0, (double) 800 / 600, 0.1, 1000.0);
    //std::cout << glGetString(GL_VERSION) << std::endl;
    /*

        //*/
    Core::Shader shader("Shaders/texture.vert", "Shaders/texture.frag");
    Core::Camera camera(&window, glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), 0.01, 0.5);
    Textureloader textload("images/");
    Model test("test" ,"SFML.png", &textload, shader);
    //shaderBasique.charger();
    int translate = 0b0;
    window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width/2)-400,(sf::VideoMode::getDesktopMode().height/2)-300));
    sf::Mouse::setPosition(sf::Vector2i(400,300) , window);
    bool a(true);
    //glUseProgram(shaderBasique.getProgramID());
    sf::Mouse::setPosition(sf::Vector2i(window.getSize().x/2, window.getSize().y/2), window);
    while(window.isOpen())
    {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);
        if(a && sf::Mouse::getPosition(window).x != 400)
        {
            a = false;
            sf::Mouse::setPosition(sf::Vector2i(400,300) , window);
        }
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        case sf::Keyboard::Z:
                            translate += 0b1;
                            break;
                        case sf::Keyboard::S:
                            translate += 0b10;
                            break;
                        case sf::Keyboard::Q:
                            translate += 0b100;
                            break;
                        case sf::Keyboard::D:
                            translate += 0b1000;
                            break;
                        case sf::Keyboard::P:
                            sf::Mouse::setPosition(sf::Vector2i(400, 300), window);
                            break;
                        default:
                            break;
                    }
                    break;
                case sf::Event::KeyReleased:
                    switch(event.key.code)
                    {
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        if(window.isOpen())
        {
            glClearColor(0.0f, 0.6f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            view = camera.update(sf::Vector2f(window.getSize().x/2, window.getSize().y/2));
            translate = 0b0;
            //sf::Mouse::setPosition(sf::Vector2i(400,300) , window);
            glUseProgram(shader.getProgramID());
                test.update(projection, view);
            glUseProgram(0);
            window.display();
        }
    }
    /**/
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    //*/
	glDeleteProgram(shader.getProgramID());
    return 0;
}
