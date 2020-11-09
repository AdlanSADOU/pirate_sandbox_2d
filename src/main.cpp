
#include "game.h"
// S2D_Window *gWindow = NULL;

sf::RenderWindow *gWindow = NULL;

// S2D_Text *fps;

float deltaTime;
float fps;
float speed = 0.1f;

bool up, down, left, right = false;

void onKeyHeld(sf::Keyboard::Key key)
{
    switch (key) {
    case sf::Keyboard::Z:
        up = true;
        break;
    case sf::Keyboard::Q:
        left = true;
        break;
    case sf::Keyboard::S :
        down = true;
        break;
    case sf::Keyboard::D:
        right = true;
        break;
    case sf::Keyboard::LShift:
        if (yAxis > -0.16 && yAxis < 0.01) yAxis = 0;
        else yAxis -= yAxis / 10 * deltaTime;
        if (xAxis > -0.16 && xAxis < 0.01) xAxis = 0;
        else xAxis -= xAxis / 10 * deltaTime;
        break;
    default:
        break;
    }
}

void onKeyUp(sf::Keyboard::Key key)
{

    switch (key) {
    case sf::Keyboard::Z:
        up = false;
        break;
    case sf::Keyboard::Q:
        left = false;
        break;
    case sf::Keyboard::S :
        down = false;
        break;
    case sf::Keyboard::D:
        right = false;
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
        if (up) yAxis -= deltaTime * speed;
        if (left) xAxis -= deltaTime * speed;
        if (down) yAxis += deltaTime * speed;
        if (right) xAxis += deltaTime * speed;

    gameUpdate();
}

void render()
{
    gameRender();
    // S2D_DrawText(fps);
}


int main()
{
    sf::Clock deltaClock;

    sf::Clock clock = sf::Clock::Clock();
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;

    gWindow = new sf::RenderWindow(sf::VideoMode(1280, 720), "SFML window");
    gWindow->setFramerateLimit(60);

    gameInit();

    const std::string str = "assets/background.jpg";
    sf::Texture texture;
    if (!texture.loadFromFile(str))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    while (gWindow->isOpen()) {
        // Process events
        sf::Event event;
        while (gWindow->pollEvent(event)) {
            onKeyCallback(event);

            if (event.type == sf::Event::Closed)
                gWindow->close();
        }

        gWindow->clear();

        gWindow->draw(sprite);

        update();
        render();

        gWindow->display();

        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
        previousTime = currentTime;

        deltaTime = 1.0f / fps * 100.0f;
        // printf("fps = %f\n", (deltaTime));
    }

    return 0;
}
