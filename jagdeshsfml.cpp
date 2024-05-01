//To run file Change Paths and run following command

//g++ -c jagdeshsfml.cpp -I"C:\Users\Abdul Rahman\Documents\GitHub\ColourSwitchGame\include";g++ jagdeshsfml.o -o jagdeshsfml -L"C:\Users\Abdul Rahman\Documents\GitHub\ColourSwitchGame\lib" -lsfml-graphics -lsfml-window -lsfml-system;./jagdeshsfml

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace sf;

class ObstacleCircle {
private:
    int x;
    int y;
    int radius;
    Color colors[4];
    int position;

public:
    ObstacleCircle(int x, int y, int radius) : x(x), y(y), radius(radius), position(0) {
        colors[0] = sf::Color::Red;
        colors[1] = sf::Color::Green;
        colors[2] = sf::Color::Blue;
        colors[3] = sf::Color::Yellow;
    }

    void draw(sf::RenderWindow& window) {
        position = (position + 1) % 4;
        for (int i = 0; i < 4; ++i) {
            CircleShape shape(radius, 60);
            shape.setFillColor(colors[(i + position) % 4]);
            shape.setPosition(x - radius, y - radius);
            shape.setOutlineThickness(2);
            shape.setOutlineColor(sf::Color::Black);
            window.draw(shape);
        }
    }
};

class Ball {
private:
    int x;
    int y;
    int radius;
    sf::Color colors[4];
    int colorIndex;

public:
    Ball(int x, int y, int radius) : x(x), y(y), radius(radius), colorIndex(0) {
        colors[0] = sf::Color::Red;
        colors[1] = sf::Color::Green;
        colors[2] = sf::Color::Blue;
        colors[3] = sf::Color::Yellow;
    }

    void draw(sf::RenderWindow& window) {
        CircleShape shape(radius);
        shape.setFillColor(colors[colorIndex]);
        shape.setPosition(x - radius, y - radius);
        window.draw(shape);
    }

    void moveAbove(sf::RenderWindow& window) {
        int maxY = y - 305;
        while (y > maxY) {
            y -= 1;
            draw(window);
            window.display();
            sf::sleep(sf::milliseconds(10));
        }
    }

    inline int getColorIndex() {
        return colorIndex;
    }
};

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "GAME");

    ObstacleCircle obstacle(500, 550, 80);
    Ball ball(500, 750, 30);

    bool ballMoved = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (!ballMoved) {
            ballMoved = true;
            ball.moveAbove(window);
        }

        window.clear();
        ball.draw(window);
        obstacle.draw(window);
        window.display();
    }

    return 0;
}
