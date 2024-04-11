/*Compilation Commands:
g++ -c main.cpp -I"Path of include folder in this directory"

g++ main.o -o main -L"Path of lib folder in this directory" -lsfml-graphics -lsfml-window -lsfml-system

*/

/*Execution Commands:

./main

*/

/* Run This line in terminal to run program(Add paths):

g++ -c main.cpp -I"Path of include folder in this directory";g++ main.o -o main -L"Path of lib folder in this directory" -lsfml-graphics -lsfml-window -lsfml-system;./main

Example:
g++ -c main.cpp -I"C:\Users\Abdul Rahman\Desktop\ColorSwitchProject\include";g++ main.o -o main -L"C:\Users\Abdul Rahman\Desktop\ColorSwitchProject\lib" -lsfml-graphics -lsfml-window -lsfml-system;./main

*/

#include <SFML\Graphics.hpp>
#include <iostream>
#include <cstring>
using namespace sf;
using namespace std;


class Button:public Sprite{
    protected:
    Texture buttontexture;
    public:

    
    Button(string texturefilepath,float offsetx,float offsety){

        buttontexture.loadFromFile(texturefilepath);
        setTexture(buttontexture);
        setPosition(196,348);
        setOrigin(29,29);
        move(offsetx,offsety);
        
    }

    void drawButton(Button &obj,RenderWindow &win){
        win.draw(obj);
    }
};

// class EasyButton:public Button{};
// class HardButton:public Button{};
// class EditButton:public Button{};



class HomePage:public Sprite{
    Texture hometexture;
    public:
    Button easybutton = Button("Sprites\\easy.png",-70,-120);
    Button hardbutton = Button("Sprites\\hard.png",50,-120);
    Button editbutton = Button("Sprites\\edit.png",-10,-60);
    // TO DO:: Add ScoreBoard Object which shows highscore and/or top three scores
    

    
    
    HomePage(){
        
        hometexture.loadFromFile("Sprites\\home.png");
        setTexture(hometexture);
    }
    void drawHome(HomePage &home,RenderWindow &win){
        win.draw(home);
        easybutton.drawButton(easybutton,win);
        hardbutton.drawButton(hardbutton,win);
        editbutton.drawButton(editbutton,win);
    }


};

class Game{};

class GameOverPage{
    //texture
    //homebutton,current score
};



int main()
{   
    //Intialising Objects
    RenderWindow window(VideoMode(392,696),"Color Switch",Style::Close | Style::Titlebar);
    HomePage home;

    // Main Loop
    while (window.isOpen())
    {
        Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == Event::Closed){
                window.close();}

            //Check if left mouse button is pressed
            if (evnt.type == Event::MouseButtonPressed && evnt.mouseButton.button == Mouse::Left) {
                Vector2i currentMousePos = Mouse::getPosition(window);
                
                
                if (home.getGlobalBounds().contains(Vector2f(currentMousePos))) {
                    
                    home.move(-5000,0);
                    home.easybutton.move(-5000,0);
                    home.editbutton.move(-5000,0);
                    home.hardbutton.move(-5000,0);
                    
                }




            }

            
        }

    window.clear(Color::Black);
    
    // Draw Functions
    home.drawHome(home,window);
    
    window.display();

    }
    

    return 0;
}