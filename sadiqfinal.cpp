#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
//g++ -c sadiqfinal.cpp -I"C:\Users\Abdul Rahman\Documents\GitHub\ColourSwitchGame\include";g++ main-combined.o -o main-combined -L"C:\Users\Abdul Rahman\Documents\GitHub\ColourSwitchGame\lib" -lsfml-graphics -lsfml-window -lsfml-system
using namespace sf;
using namespace std;

const float colorChangeTime = 2.0f; 
 Color colors[5] = {Color(255,0,0),Color(0,255,0),Color(0,0,255),Color(255,255,0),Color(255,0,255)};

class Object {
public:
    virtual void changeInitialPosition(float posx, float posy) = 0;
    virtual Vector2f GetPosition() const = 0;
};

class Rectangle : virtual public Drawable, public Object {
private:
    RectangleShape rectangleShape;
    Color currentColor;
    Clock colorChangeClock;

public:
    Rectangle(float width, float height, float initialX, float initialY) {
        rectangleShape.setSize(Vector2f(width, height));
        rectangleShape.setFillColor(Color::Transparent);
        rectangleShape.setOutlineThickness(2.0f);
        rectangleShape.setOutlineColor(Color::Red);
        rectangleShape.setOrigin(width / 2.0f, height / 2.0f);
        rectangleShape.setPosition(initialX, initialY);
        currentColor = Color::Blue;
    }

    void updateColor() {
        if (colorChangeClock.getElapsedTime().asSeconds() >= colorChangeTime) {
            currentColor = Color(colors[rand()%5]);
            rectangleShape.setOutlineColor(currentColor);
            colorChangeClock.restart();
        }
    }

    void draw(RenderTarget& target, RenderStates states) const override {
        target.draw(rectangleShape, states);
    }

    void changeInitialPosition(float posx, float posy) override {
        rectangleShape.setPosition(posx, posy);
    }

    Vector2f GetPosition() const override { return rectangleShape.getPosition(); }
};

class Pentagon : virtual public Drawable, public Object {
private:
    ConvexShape pentagonShape;
    Color currentColor;
    Clock colorChangeClock;

public:
    Pentagon(float size, float initialX, float initialY) {
        pentagonShape.setPointCount(5);
        pentagonShape.setPoint(0, Vector2f(0, -size));
        pentagonShape.setPoint(1, Vector2f(size * 0.9511f, -size * 0.3090f));
        pentagonShape.setPoint(2, Vector2f(size * 0.5877f, size * 0.8090f));
        pentagonShape.setPoint(3, Vector2f(-size * 0.5877f, size * 0.8090f));
        pentagonShape.setPoint(4, Vector2f(-size * 0.9511f, -size * 0.3090f));
        pentagonShape.setFillColor(Color::Transparent);
        pentagonShape.setOutlineThickness(2.0f);
        pentagonShape.setOutlineColor(Color::Green);
        Vector2f center((pentagonShape.getPoint(0).x + pentagonShape.getPoint(2).x) / 2.0f,
                        (pentagonShape.getPoint(1).y + pentagonShape.getPoint(3).y) / 2.0f);
        pentagonShape.setOrigin(center);
        pentagonShape.setPosition(initialX, initialY);
        currentColor = Color::Yellow;
    }

    void updateColor() {
        if (colorChangeClock.getElapsedTime().asSeconds() >= colorChangeTime) {
            currentColor = Color(colors[rand()%5]);
            pentagonShape.setOutlineColor(currentColor);
            colorChangeClock.restart();
        }
    }

    void draw(RenderTarget& target, RenderStates states) const override {
        target.draw(pentagonShape, states);
    }

    void changeInitialPosition(float posx, float posy) override {
        pentagonShape.setPosition(posx, posy);
    }

    Vector2f GetPosition() const override { return pentagonShape.getPosition(); }
};

class ColoredCircle : virtual public Sprite {
private:
    CircleShape circleShape;
    Color currentColor;
    Clock colorChangeClock;

public:
    ColoredCircle(float radius, const Vector2f& position) {
        circleShape.setRadius(radius);
        circleShape.setFillColor(Color::Transparent);
        circleShape.setOutlineThickness(2.0f);
        circleShape.setOutlineColor(Color::Red);
        circleShape.setOrigin(radius, radius);
        circleShape.setPosition(position);
        currentColor = Color::Blue;
    }

    void updateColor() {
        if (colorChangeClock.getElapsedTime().asSeconds() >= colorChangeTime) {
            currentColor = Color(colors[rand()%5]);
            circleShape.setOutlineColor(currentColor);
            colorChangeClock.restart();
        }
    }

    void draw(RenderTarget& target, RenderStates states) const override {
        target.draw(circleShape, states);
    }

    void setPosition(const Vector2f& position) {
        circleShape.setPosition(position);
    }
};

class Score {
private:
    int currentScore;
    int highestScore;

public:
    Score() : currentScore(0), highestScore(0) {}

    void increaseScore() {
        currentScore++;
    }

    int getCurrentScore() const { return currentScore; }

    int getHighestScore() const { return highestScore; }

    void updateHighestScore() {
        if (currentScore > highestScore) {
            highestScore = currentScore;
        }
    }

    void resetScore() { currentScore = 0; }

    void displayScore(RenderWindow& window, Font& font) {
        Text scoreText("Score: " + to_string(currentScore), font, 24);
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(10, 10);
        window.draw(scoreText);

        Text highestScoreText("Highest Score: " + to_string(highestScore), font, 24);
        highestScoreText.setFillColor(Color::White);
        highestScoreText.setPosition(10, 40);
        window.draw(highestScoreText);
    }

    void saveHighestScoreToFile(const string& filename) {
        ofstream outputFile(filename);
        if (outputFile.is_open()) {
            outputFile << highestScore;
            outputFile.close();
        } else {
            cerr << "Error: Unable to open file for writing." << endl;
        }
    }

    void loadHighestScoreFromFile(const string& filename) {
        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            inputFile >> highestScore;
            inputFile.close();
        } else {
            cerr << "Error: Unable to open file for reading." << endl;
        }
    }
};

int main() {
    srand(time(0)); 

    RenderWindow window(VideoMode(800, 600), "SFML Game");

    Score score;
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Failed to load font file!" << endl;
        return EXIT_FAILURE;
    }

    Rectangle rectangle(100.0f, 50.0f, 200.0f, 300.0f);
    Pentagon pentagon(80.0f, 500.0f, 400.0f);
    ColoredCircle coloredCircle(50.0f, Vector2f(400.0f, 300.0f));

    Clock clock;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        if (clock.getElapsedTime().asSeconds() >= 0.1f) {
            coloredCircle.updateColor();
            rectangle.updateColor();
            pentagon.updateColor();
            clock.restart();
        }

        window.clear(Color::Black);

        rectangle.draw(window, RenderStates::Default);
        pentagon.draw(window, RenderStates::Default);
        coloredCircle.draw(window, RenderStates::Default);

        
        score.displayScore(window, font);

        window.display();
    }

    return 0;
}
