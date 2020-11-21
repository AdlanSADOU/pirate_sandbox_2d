#include "game.h"
#include "client.h"

sf::RenderWindow *window = NULL;

float deltaTime;
float fps;
float speed = 0.1f;
bool up = false, down = false, left = false, right = false, shift= false, space = false;
float xAxis = 0, yAxis = 0;

void onKeyHeld(sf::Keyboard::Key key)
{
    switch (key) {
    case sf::Keyboard::Space:
        space = true;
        break;
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
        shift = true;
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
    case sf::Keyboard::Space:
        space = false;
        break;
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
    case sf::Keyboard::LShift:
        shift = false;
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
            window->close();
        onKeyHeld(e.key.code);
        break;

    case sf::Event::EventType::KeyReleased:
        onKeyUp(e.key.code);
        break;
    default:
        break;
    }
}

void update(float dt)
{
    if (up)
        yAxis -= deltaTime * speed;
    if (left)
        xAxis -= deltaTime * speed;
    if (down)
        yAxis += deltaTime * speed;
    if (right)
        xAxis += deltaTime * speed;

    gameUpdate(dt);
}

int main()
{
    sf::Clock deltaClock;
    sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;
    sf::Time t_deltaTime;

    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "SFML window");
    window->setFramerateLimit(60);

    sf::ContextSettings settings = window->getSettings();
    ImGui::SFML::Init(*window, true);

    gameInit();

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(7);

    const std::string str = "assets/background.jpg";
    sf::Texture texture;
    if (!texture.loadFromFile(str))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            onKeyCallback(event);

            if (event.type == sf::Event::Closed)
                window->close();
        }
        window->clear();
        window->draw(sprite);

        ImGui::SFML::Update(*window, deltaClock.restart());
        ImGui::Begin("Info");
        ImGui::Text("fps: %.2f, %.2fms", fps, deltaTime);

        update(deltaTime);
        gameRender(*window);

        ImGui::End();
        ImGui::SFML::Render(*window);

        window->display();

        t_deltaTime = deltaClock.getElapsedTime();

        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
        previousTime = currentTime;
        deltaTime = 1.0f / fps * 100.0f;
    }

    Client::Disconnect();
    return 0;
}
