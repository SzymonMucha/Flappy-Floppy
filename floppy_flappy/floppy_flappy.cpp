#include "object.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "Flappy_floppy", sf::Style::Titlebar | sf::Style::Close);
    sf::Image icon;
    icon.loadFromFile("assets/byrb.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setFramerateLimit(60);

    //music
    sf::Music bcg_music;
    bcg_music.openFromFile("assets/zorba.wav");
    bcg_music.play();
    bcg_music.setLoop(true);
    bcg_music.setVolume(50);

    //objects
    Player player("assets/byrb.png", 0.25f, 280, 350, 6.f, 3.f);
    Object ob("assets/Rura.png", 0.25f, 600, 230);

    //threads
    thread physics_handler(physics, &ob, &player);
    thread inputs_handler(inputs, &player);

    sf::Font font;
    font.loadFromFile("assets/videotype.ttf");

    score_txt.setString(string("Present score: ") + string("0"));
    score_txt.setPosition(15, 350);
    score_txt.setCharacterSize(15);
    score_txt.setFont(font);

    ifstream highscore_filein;
    highscore_filein.open("highscore.txt", ios::in);
    string h_fromfile;

    if (getline(highscore_filein, h_fromfile))
    {
        highscore.setString(string("High score: ") + h_fromfile);
    }
    else
    {
        highscore.setString(string("High score: ") + string("0"));
    }

    highscore_filein.close();
    
    highscore.setPosition(15, 375);
    highscore.setCharacterSize(15);
    highscore.setFont(font);
    
    sf::Event event;

    //game loop
    while (isPlaying)
    {

        //close window handler
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                if ((h_fromfile != "") ? score > stoi(h_fromfile) : true)
                {
                    ofstream highscore_fileout;
                    highscore_fileout.open("highscore.txt", ios::trunc);
                    highscore_fileout << to_string(score);
                    highscore_fileout.close();
                    bcg_music.stop();
                }
                isPlaying = false;
                window.close();
            }
        }
        //move objects
        ob.sprite.move(-ob.speed, 0.0f);
        player.sprite.move(static_cast<float>(static_cast<int>(player.force.x * 10.)) / 10., static_cast<float>(static_cast<int>(player.force.y * 10.)) / 10.);

        //clear and background color
        window.clear(sf::Color(250, 150, 100));

        //display objects
        window.draw(player.sprite);
        window.draw(ob.sprite);
        window.draw(score_txt);
        window.draw(highscore);
        window.display();

        this_thread::sleep_for(16ms);
    }
    
    isPlaying = false;

    sf::Text lose;
    lose.setString("GAME OVER");
    lose.setPosition(155, 170);
    lose.setCharacterSize(50);
    lose.setFont(font);
    
    window.draw(lose);
    window.display();

    if ((h_fromfile != "") ? score > stoi(h_fromfile) : true)
    {
        ofstream highscore_fileout;
        highscore_fileout.open("highscore.txt", ios::trunc);
        highscore_fileout << to_string(score);
        highscore_fileout.close();
    }

    this_thread::sleep_for(3000ms);

    bcg_music.stop();

    physics_handler.join();
    inputs_handler.join();

    return 0;
}