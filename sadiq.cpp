//To run file Change Paths and run following command

//g++ -c sadiq.cpp -I"C:\Users\Abdul Rahman\Documents\GitHub\ColourSwitchGame\include";g++ sadiq.o -o sadiq -L"C:\Users\Abdul Rahman\Documents\GitHub\ColourSwitchGame\lib" -lsfml-graphics -lsfml-window -lsfml-system;./sadiq


#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

using namespace sf;
using namespace std;
using namespace chrono;

class Pentagon : public Drawable {
private:
    ConvexShape pentagonShape;
    Color currentColor;
    Clock colorChangeClock;

public:
    Pentagon(float size) {
        pentagonShape.setPointCount(5);
        pentagonShape.setPoint(0, Vector2f(0, -size));
        pentagonShape.setPoint(1, Vector2f(size * 0.9511f, -size * 0.3090f));
        pentagonShape.setPoint(2, Vector2f(size * 0.5877f, size * 0.8090f));
        pentagonShape.setPoint(3, Vector2f(-size * 0.5877f, size * 0.8090f));
        pentagonShape.setPoint(4, Vector2f(-size * 0.9511f, -size * 0.3090f));
        pentagonShape.setFillColor(Color::Red); 
        pentagonShape.setOrigin(0, -size); 
        pentagonShape.setPosition(200, 150); 
        currentColor = Color::Red;
    }

    void updateColor() {
        if (colorChangeClock.getElapsedTime().asSeconds() >= 2.0f) {
            currentColor = Color(rand() % 256, rand() % 256, rand() % 256);
            pentagonShape.setFillColor(currentColor);
            colorChangeClock.restart(); 
        }
    }

    void draw(RenderTarget& target, RenderStates states) const override {
        target.draw(pentagonShape, states);
    }
};

class Rectangle : public Drawable {
private:
    RectangleShape rectangleShape;
    Color currentColor;
    Clock colorChangeClock;

public:
    Rectangle(float width, float height) {
        rectangleShape.setSize(Vector2f(width, height));
        rectangleShape.setFillColor(Color::Blue); 
        rectangleShape.setOrigin(width / 2.0f, height / 2.0f); 
        rectangleShape.setPosition(600, 400); 
        currentColor = Color::Blue;
    }

    void updateColor() {
        if (colorChangeClock.getElapsedTime().asSeconds() >= 2.0f) {
            currentColor = Color(rand() % 256, rand() % 256, rand() % 256);
            rectangleShape.setFillColor(currentColor);
            colorChangeClock.restart(); 
        }
    }

    void draw(RenderTarget& target, RenderStates states) const override {
        target.draw(rectangleShape, states);
    }
};

int main() {
    RenderWindow window(VideoMode(800, 600), "Shapes");

    Pentagon pentagon(50.0f);
    Rectangle rectangle(100.0f, 80.0f); 

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        pentagon.updateColor();
        rectangle.updateColor();

        window.clear(Color::Black);
        window.draw(pentagon);
        window.draw(rectangle);
        window.display();
    }

}
