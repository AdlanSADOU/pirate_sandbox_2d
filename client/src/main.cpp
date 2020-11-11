#include "game.h"
#include "client.h"

sf::RenderWindow *gWindow = NULL;

float deltaTime;
float fps;
float speed = 0.1f;

void onKeyHeld(sf::Keyboard::Key key)
{
    switch (key) {
    case sf::Keyboard::Z:
        playerClass.up = true;
        break;
    case sf::Keyboard::Q:
        playerClass.left = true;
        break;
    case sf::Keyboard::S :
        playerClass.down = true;
        break;
    case sf::Keyboard::D:
        playerClass.right = true;
        break;
    case sf::Keyboard::LShift:
        playerClass.shift = true;
        if (yAxis > -0.16 && yAxis < 0.01)
            yAxis = 0;
        else
            yAxis -= yAxis / 10 * deltaTime;
        if (xAxis > -0.16 && xAxis < 0.01)
            xAxis = 0;
        else
            xAxis -= xAxis / 10 * deltaTime;
        break;
    default:
        break;
    }
}

void onKeyUp(sf::Keyboard::Key key)
{
    switch (key) {
    case sf::Keyboard::Z:
        playerClass.up = false;
        break;
    case sf::Keyboard::Q:
        playerClass.left = false;
        break;
    case sf::Keyboard::S :
        playerClass.down = false;
        break;
    case sf::Keyboard::D:
        playerClass.right = false;
        break;
    case sf::Keyboard::LShift:
        playerClass.shift = false;
        break;
    default:
        break;
    }
}

void onKeyCallback(sf::Event e)
{   
    gameInput(e);
 
    switch (e.type)
    {
    case sf::Event::EventType::KeyPressed:
        if (e.key.code == sf::Keyboard::Escape)
            gWindow->close();
        onKeyHeld(e.key.code);
        break;

    case sf::Event::EventType::KeyReleased:
        onKeyUp(e.key.code);
        break;
    default:
        break;
    }
}

void update()
{
    if (playerClass.up)
        yAxis -= deltaTime * speed;
    if (playerClass.left)
        xAxis -= deltaTime * speed;
    if (playerClass.down)
        yAxis += deltaTime * speed;
    if (playerClass.right)
        xAxis += deltaTime * speed;

    gameUpdate();
}

int main()
{
    sf::Clock deltaClock;
    sf::Clock clock = sf::Clock::Clock();
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;
    sf::Time t_deltaTime;

    int test = 0;

    gWindow = new sf::RenderWindow(sf::VideoMode(1280, 720), "SFML window");
    gWindow->setFramerateLimit(60);

    sf::ContextSettings settings = gWindow->getSettings();
    ImGui::SFML::Init(*gWindow, true);
    
    clientStart();
    gameInit();

    GLuint vertexBuffer;
    

    const std::string str = "assets/background.jpg";
    sf::Texture texture;
    if (!texture.loadFromFile(str))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    while (gWindow->isOpen()) {
        sf::Event event;
        while (gWindow->pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            onKeyCallback(event);

            if (event.type == sf::Event::Closed)
                gWindow->close();
        }
        gWindow->clear();
        gWindow->draw(sprite);

        ImGui::SFML::Update(*gWindow, deltaClock.restart());
        ImGui::Begin("Info");
        ImGui::Text("fps: %.2f, %.2fms", fps, deltaTime);

        update();
        gameRender();

        ImGui::End();
        ImGui::SFML::Render(*gWindow);

        gWindow->display();
    
        

        t_deltaTime = deltaClock.getElapsedTime();

        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
        previousTime = currentTime;
        deltaTime = 1.0f / fps * 100.0f;
    }

    clientDisconnect();
    return 0;
}
