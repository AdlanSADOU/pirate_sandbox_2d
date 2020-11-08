
#include "game.h"
// S2D_Window *gWindow = NULL;

sf::RenderWindow *gWindow = NULL;

// S2D_Text *fps;

float speed = 0.1f;

void onKeyHeld(sf::Keyboard::Key key)
{
    switch (key) {
    case sf::Keyboard::W:
        (yAxis) -=  speed;
        break;
    case sf::Keyboard::A:
        (xAxis) -=  speed;
        break;
    case sf::Keyboard::S :
        (yAxis) +=  speed;
        break;
    case sf::Keyboard::D:
        (xAxis) +=  speed;
        break;
    case sf::Keyboard::LShift:
        if (yAxis > -0.16 && yAxis < 0.01) yAxis = 0;
        else (yAxis > 0) ? ((yAxis) -=  speed) : ((yAxis) +=  speed);
        if (xAxis > -0.16 && xAxis < 0.01) xAxis = 0;
        else (xAxis > 0) ? ((xAxis) -=  speed) : ((xAxis) +=  speed);
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

    // case S2D_KEY_HELD:
    //     break;

    case sf::Event::EventType::KeyReleased:
        break;
    default:
        break;
    }
}

void update(void *args)
{
    update_args *a_args = (update_args *)(args);

    // S2D_SetText(fps, "FPS:  %.2f  -  deltaTime:  %.2f", gWindow->fps,)

    gameUpdate(a_args);
}

void render()
{
    gameRender();
    // S2D_DrawText(fps);
}


int main()
{
    update_args u_args;
    // gWindow = S2D_CreateWindow("Awesome Sample", 1920, 1080, update, render, S2D_RESIZABLE | S2D_HIGHDPI);
    // gWindow->background = {.12f, .10f, .10f, 0.1f};
    // gWindow->on_UpdateArgs = (&u_args);
    // gWindow->viewport.mode = S2D_EXPAND;
    // gWindow->on_key = onKeyCallback;
    // gWindow->fps_cap = 60;
    // gWindow->vsync = true;
    //  1;
    gWindow = new sf::RenderWindow(sf::VideoMode(1280, 720), "SFML window");

    
    // Load a sprite to display
    const std::string str = "assets/background.jpg";
    sf::Texture texture;
    if (!texture.loadFromFile(str))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(sf::String("assets/fonts/space_invaders.ttf")))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);
    // Load a music to play
    sf::Music music;
    // if (!music.openFromFile("nice_music.ogg"))
    //     return EXIT_FAILURE;
    // // Play the music
    // music.play();
    // Start the game loop
    while (gWindow->isOpen())
    {
        // Process events
        sf::Event event;
        while (gWindow->pollEvent(event))
        {
            onKeyCallback(event);
            // Close gWindow-> exit
            if (event.type == sf::Event::Closed)
                gWindow->close();
        }
        // Clear screen
        gWindow->clear();
        // Draw the sprite
        gWindow->draw(sprite);

        update(&u_args);
        render();
        // Draw the string
        gWindow->draw(text);
        // Update the 
        gWindow->display();
    }

    // fps = S2D_CreateText("assets/fonts/space_invaders.ttf", "Hello Space!", 20);
    // gameInit();
    // S2D_Show(gWindow);
    return 0;
}
