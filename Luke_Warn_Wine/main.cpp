#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <fstream>
#include <iostream>


using namespace sf;

int main()
{
    // Non SFML
    float delta, hyp, spd;
    int win_hole = 0,x,y, lives = 3, score = 0, bonus = 0, marker = 0;
    bool reset = false;
    std::time_t clock = std::time(nullptr);
    std::string in_put = "";
    
    std::ifstream in_l_file, in_p_file;
    in_l_file.open("lose_hole/lose_hole_locations.txt");
    in_p_file.open("point_hole/point_hole_locations.txt");
    
    // Creating the main window
    RenderWindow window(VideoMode(768, 1024), "SFML window");
    // Creating the font
    Font arial;
    if (!arial.loadFromFile("arial.ttf"))
    {
        std::cout << "AN ERROR HAS OCCURED";
    }
    // --- Game Visuals --- //
    // Creating the background
    RectangleShape background(Vector2f(768,1024));
    background.setFillColor(Color(153,0,0));
    // Creating the ball
    CircleShape ball(20);
    ball.setFillColor(Color(160,160,160));
    ball.setPosition(540, 856);
    CircleShape ball_hb(5);
    // Creating the bar
    ConvexShape bar (4);
    bar.setFillColor(Color(0,0,0));
    bar.setPoint(0, Vector2f(0,891));
    bar.setPoint(1, Vector2f(0,911));
    bar.setPoint(2, Vector2f(768,916));
    bar.setPoint(3, Vector2f(768,896));
    // Creating the winning holes
    CircleShape point_hole[10];
    CircleShape point_hole_hb[10];
    for (int i = 0; i < 10; i++){
        point_hole[i].setRadius(25);
        point_hole_hb[i].setRadius(7);
        point_hole[i].setFillColor(Color(255,255,0));
        point_hole_hb[i].setFillColor(Color(0,0,0));
        in_p_file >> x;
        in_p_file >> y;
        point_hole[i].setPosition(x,y);
        point_hole_hb[i].setPosition(x+17,y+17);
        if (i == 0 ){ point_hole[i].setFillColor(Color(255,165,0)); }
    }
    in_p_file.close();
    // Creating the losing holes
    CircleShape lose_hole[47];
    CircleShape lose_hole_hb[47];
    for (int i = 0; i < 47; i++){
        lose_hole[i].setRadius(30);
        lose_hole_hb[i].setRadius(9);
        lose_hole[i].setFillColor(Color(0,0,0));
        in_l_file >> x;
        in_l_file >> y;
        lose_hole[i].setPosition(x,y);
        lose_hole_hb[i].setPosition(x+20,y+20);
    }
    in_l_file.close();
    
    Text lives_t;
    lives_t.setFont(arial);
    lives_t.setString("LIVES : "+std::to_string(lives));
    lives_t.setCharacterSize(50);
    lives_t.setPosition(10,900);
    lives_t.setFillColor(Color(160,160,160));
    
    Text score_t;
    score_t.setFont(arial);
    score_t.setString("SCORE : "+std::to_string(score));
    score_t.setCharacterSize(50);
    score_t.setPosition(10,960);
    score_t.setFillColor(Color(160,160,160));
    
    Text clock_t;
    clock_t.setFont(arial);
    clock_t.setString("BONUS : "+std::to_string(bonus));
    clock_t.setCharacterSize(50);
    clock_t.setPosition(400,960);
    clock_t.setFillColor(Color(160,160,160));
    
    // --- Menu Visuals --- //
    RectangleShape menu_bg(Vector2f(768,1024));
    menu_bg.setFillColor(Color(153,0,0));
    
    Text menu_t;
    menu_t.setFont(arial);
    menu_t.setString("Luke Warm Wine");
    menu_t.setCharacterSize(70);
    menu_t.setPosition(110,30);
    menu_t.setFillColor(Color(0,0,0));
    
    RectangleShape game_btn(Vector2f(640,102));
    game_btn.setPosition(64, 204);
    
    Text game_btn_t;
    game_btn_t.setFont(arial);
    game_btn_t.setString("Play Game");
    game_btn_t.setCharacterSize(70);
    game_btn_t.setPosition(200,204);
    game_btn_t.setFillColor(Color(0,0,0));
    
    RectangleShape help_btn(Vector2f(640,102));
    help_btn.setPosition(64, 408);
    
    Text help_btn_t;
    help_btn_t.setFont(arial);
    help_btn_t.setString("Help");
    help_btn_t.setCharacterSize(70);
    help_btn_t.setPosition(300,408);
    help_btn_t.setFillColor(Color(0,0,0));
    
    RectangleShape make_btn(Vector2f(640,102));
    make_btn.setPosition(64, 610);
    
    Text make_btn_t;
    make_btn_t.setFont(arial);
    make_btn_t.setString("Make");
    make_btn_t.setCharacterSize(70);
    make_btn_t.setPosition(300,610);
    make_btn_t.setFillColor(Color(0,0,0));
    
    // -- Help Visuals -- //
    
    Text help_t;
    help_t.setFont(arial);
    help_t.setString("HELP MENU\n\n\
W : Left Side Up\n\
S : Left Side Down\n\
UP : Righ Side Up\n\
Down : Right Side Down\n\
Space : Both Sides Up\n\
Enter : Both Sides Down\n\
Q : Return To Menu");
    help_t.setFillColor(Color(0,0,0));
    help_t.setCharacterSize(50);
    help_t.setPosition(100,102);
    
    // -- Make Visuals -- //
    Text make_t;
    make_t.setFont(arial);
    make_t.setString("Level Maker");
    make_t.setCharacterSize(70);
    make_t.setPosition(110,30);
    make_t.setFillColor(Color(0,0,0));
    
    RectangleShape mgame_btn(Vector2f(640,102));
    mgame_btn.setPosition(64, 204);
    
    Text mgame_btn_t;
    mgame_btn_t.setFont(arial);
    mgame_btn_t.setString("Make Game");
    mgame_btn_t.setCharacterSize(70);
    mgame_btn_t.setPosition(200,204);
    mgame_btn_t.setFillColor(Color(0,0,0));
    
    RectangleShape pgame_btn(Vector2f(640,102));
    pgame_btn.setPosition(64, 408);
    
    Text pgame_btn_t;
    pgame_btn_t.setFont(arial);
    pgame_btn_t.setString("Play Game");
    pgame_btn_t.setCharacterSize(70);
    pgame_btn_t.setPosition(200,408);
    pgame_btn_t.setFillColor(Color(0,0,0));
    
    // Start the game loop
    bool menu = true;
    bool game = false;
    bool help = false;
    bool make = false;
    bool mgame = false;
    while (window.isOpen())
    {
        // Clear screen
        window.clear();
        
        // Process events
        Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == Event::Closed)
                window.close();
            else if(event.type == Event::MouseButtonPressed){
                if (menu == true){
                    if (game_btn.getGlobalBounds().contains( window.mapPixelToCoords(Mouse::getPosition(window)))){
                        menu = false;
                        game = true;
                        help = false;
                        lives = 3;
                        score = 0;
                        clock = std::time(nullptr);
                        point_hole[0].setFillColor(Color(255,165,0));
                        in_l_file.open("lose_hole/lose_hole_locations.txt");
                        in_p_file.open("point_hole/point_hole_locations.txt");
                        for (int i = 0; i < 10; i++){
                            in_p_file >> x;
                            in_p_file >> y;
                            point_hole[i].setPosition(x,y);
                            point_hole_hb[i].setPosition(x+17,y+17);
                            if (i == 0 ){ point_hole[i].setFillColor(Color(255,165,0)); }
                        }
                        in_p_file.close();
                        // Creating the losing holes
                        for (int i = 0; i < 47; i++){
                            in_l_file >> x;
                            in_l_file >> y;
                            lose_hole[i].setPosition(x,y);
                            lose_hole_hb[i].setPosition(x+20,y+20);
                        }
                        in_l_file.close();
                    }
                    else if(help_btn.getGlobalBounds().contains( window.mapPixelToCoords(Mouse::getPosition(window)))){
                        menu = false;
                        game = false;
                        help = true;
                    }
                    else if(make_btn.getGlobalBounds().contains( window.mapPixelToCoords(Mouse::getPosition(window)))){
                        menu = false;
                        mgame = false;
                        game = false;
                        help = false;
                        make = true;
                        in_put = "";
                    }
                }
                else if (mgame == true){
                    float posx = Mouse::getPosition(window).x;
                    float posy = Mouse::getPosition(window).y;
                    in_put += std::to_string(int(posx)) + " " + std::to_string(int(posy)) + " ";
                    if (marker == 47){
                        std::ofstream myoutfile("lose_hole/lose_hole_locations_1.txt");
                        myoutfile << in_put;
                        myoutfile.close();
                    }else if(marker == 57){
                        std::ofstream myoutfile("point_hole/point_hole_locations_1.txt");
                        myoutfile << in_put;
                        myoutfile.close();
                    }
                    if ((marker == 0)||(marker == 47)||(marker == 57)){
                        in_put = "";
                    }
                    if (marker < 47){
                        lose_hole[marker].setPosition(posx, posy);
                        lose_hole_hb[marker].setPosition(posx+20, posy+20);
                    }else if (marker < 57){
                        point_hole[marker-47].setPosition(posx, posy);
                        point_hole_hb[marker-47].setPosition(posx+17, posy+17);
                    }else{
                        marker = 0;
                        mgame = false;
                        make = true;
                    }
                    marker++;
                }
                else if (make == true){
                    if (mgame_btn.getGlobalBounds().contains( window.mapPixelToCoords(Mouse::getPosition(window)))){
                        menu = false;
                        mgame = true;
                        game = false;
                        help = false;
                        make = false;
                    }
                    else if(pgame_btn.getGlobalBounds().contains( window.mapPixelToCoords(Mouse::getPosition(window)))){
                        menu = false;
                        game = true;
                        help = false;
                        make = false;
                        lives = 3;
                        score = 0;
                        clock = std::time(nullptr);
                        point_hole[0].setFillColor(Color(255,165,0));
                        in_l_file.open("lose_hole/lose_hole_locations_1.txt");
                        in_p_file.open("point_hole/point_hole_locations_1.txt");
                        for (int i = 0; i < 10; i++){
                            in_p_file >> x;
                            in_p_file >> y;
                            point_hole[i].setPosition(x,y);
                            point_hole_hb[i].setPosition(x+17,y+17);
                            if (i == 0 ){ point_hole[i].setFillColor(Color(255,165,0)); }
                        }
                        in_p_file.close();
                        // Creating the losing holes
                        for (int i = 0; i < 47; i++){
                            in_l_file >> x;
                            in_l_file >> y;
                            lose_hole[i].setPosition(x,y);
                            lose_hole_hb[i].setPosition(x+20,y+20);
                        }
                        in_l_file.close();
                    }
                }
            }
            
            else if (event.type == Event::KeyPressed){
                if (game == true){
                    if (event.key.code == Keyboard::Up){
                        bar.setPoint(2, Vector2f(768,bar.getPoint(2).y-10));
                        bar.setPoint(3, Vector2f(768,bar.getPoint(3).y-10));
                    }
                    else if (event.key.code == Keyboard::Down){
                        bar.setPoint(2, Vector2f(768,bar.getPoint(2).y+10));
                        bar.setPoint(3, Vector2f(768,bar.getPoint(3).y+10));
                    }
                    else if (event.key.code == Keyboard::W){
                        bar.setPoint(0, Vector2f(0,bar.getPoint(0).y-10));
                        bar.setPoint(1, Vector2f(0,bar.getPoint(1).y-10));
                    }
                    else if (event.key.code == Keyboard::S){
                        bar.setPoint(0, Vector2f(0,bar.getPoint(0).y+10));
                        bar.setPoint(1, Vector2f(0,bar.getPoint(1).y+10));
                    }
                    else if (event.key.code == Keyboard::Space){
                        bar.setPoint(0, Vector2f(0,bar.getPoint(0).y-10));
                        bar.setPoint(1, Vector2f(0,bar.getPoint(1).y-10));
                        bar.setPoint(2, Vector2f(768,bar.getPoint(2).y-10));
                        bar.setPoint(3, Vector2f(768,bar.getPoint(3).y-10));
                    }
                    else if (event.key.code == Keyboard::Enter){
                        bar.setPoint(0, Vector2f(0,bar.getPoint(0).y+10));
                        bar.setPoint(1, Vector2f(0,bar.getPoint(1).y+10));
                        bar.setPoint(2, Vector2f(768,bar.getPoint(2).y+10));
                        bar.setPoint(3, Vector2f(768,bar.getPoint(3).y+10));
                    }
                }
                if (event.key.code == Keyboard::Q){
                    menu = true;
                    mgame = false;
                    game = false;
                    help = false;
                    make = false;
                }
            }
        }
        if (menu == true){
            window.draw(menu_bg);
            window.draw(menu_t);
            window.draw(game_btn);
            window.draw(game_btn_t);
            window.draw(help_btn);
            window.draw(help_btn_t);
            window.draw(make_btn);
            window.draw(make_btn_t);
            window.draw(score_t);
            lives_t.setString("LIVES : "+std::to_string(lives));
            win_hole = 0;
        }
        else if (help == true){
            window.draw(menu_bg);
            window.draw(help_t);
        }
        else if (game == true){
            // --- THIS CODE MAKE THE BALL ROLL ON THE BAR : --- //
            
            // This is always a right triangle with a given side of 768 that means that we need
            // To find the rest of the sides and one angle using the law of sins
            // Getting one side of the triangle
            delta = bar.getPoint(0).y-bar.getPoint(3).y;
            // Finding the hypotonues of the triangle with both the given side of 768^2 and
            // The newly found side of the space between the start and end point of the bar
            hyp = sqrt(pow(delta,2) + 589824);
            // If the location of the ball is greater than the point at which the ball should
            // Be when x distance away from the point of reference. This point of reference
            // Is set to the far right hand corner of the screen.
            
            // We apply the law of sines to get the reference angel, then take the reference
            // Angel and multiply it by the distance the ball is away from the far right hand
            // Side. Adding the bar position is because the (0,0) is at the top left of the
            // Screen so we need to shift the ball down a certain amount. The Subtraction of
            // 40 is because that is the balls diamater, so now the ball will appear as on top
            // of the bar.
            if (ball.getPosition().y > bar.getPoint(3).y - 40 + (768 - ball.getPosition().x) * sin(sinh(delta/hyp))){
                // Moves the ball up on the screen
                ball.move(0,-1);
            // Moves the ball down on the screen
            }else{ ball.move(0,1); }
            
            // A simple speed formula, positive speed is motion in the right, negative speed
            // Is motion in the left
            spd = -1 * delta/100;
            if (bar.getPoint(0).y > bar.getPoint(3).y){
                // If the ball has room to move in the left, then move to the left
                if (!(ball.getPosition().x + spd < 0)){ ball.move(spd,0); }
                // If not, then set the ball so it is up against the wall
                else{ ball.setPosition(0,ball.getPosition().y); }
            }else{
                // If the ball has room to move in the right, then move to the right
                // 728 is used instead of 768 because the balls diamater is 40
                if (!(ball.getPosition().x + spd > 728)){ ball.move(spd,0); }
                // If not, then set the ball so it is up against the wall
                else{ ball.setPosition(728,ball.getPosition().y); }
            }
            // Move the hit box to the center of the ball
            ball_hb.setPosition(ball.getPosition().x+15,ball.getPosition().y+15);
            
            
            for (int i = 0; i < 10; i++){
                if ((ball_hb.getGlobalBounds().intersects(point_hole_hb[i].getGlobalBounds()))
                && (i != win_hole)){
                    reset = true;
                }
            }
            for (int i = 0; i < 47;i++){
                if ((ball_hb.getGlobalBounds().intersects(lose_hole_hb[i].getGlobalBounds()))){
                    reset = true;
                    lives -= 1;
                    if (lives == 0){
                        game = false;
                        menu = true;
                    }
                    lives_t.setString("LIVES : "+std::to_string(lives));
                }
            }
            if (ball_hb.getGlobalBounds().intersects(point_hole_hb[win_hole].getGlobalBounds())){
                point_hole[win_hole].setFillColor(Color(255,255,0));
                win_hole++;
                point_hole[win_hole].setFillColor(Color(255,165,0));
                score += win_hole * (1 + bonus);
                reset = true;
                clock = std::time(nullptr);
                if (win_hole == 10){
                    game = false;
                    menu = true;
                }
            }
            
            if(reset){
                bar.setPoint(0, Vector2f(0,891));
                bar.setPoint(1, Vector2f(0,911));
                bar.setPoint(2, Vector2f(768,916));
                bar.setPoint(3, Vector2f(768,896));
                ball.setPosition(540, 856);
                reset = false;
            }
            
            bonus = 60 + int(clock) - int(std::time(nullptr));
            bonus = bonus > 0 ? bonus : 0;
            clock_t.setString("BONUS : "+std::to_string(bonus));
            score_t.setString("SCORE : "+std::to_string(score));
            // --- ALL THE VISUAL STUFF : --- //
            // Drawing all the images
            window.draw(background);
            for (int i = 0; i < 10; i++){ window.draw(point_hole[i]); }
            for (int i = 0; i < 47; i++){ window.draw(lose_hole[i]); }
            window.draw(ball);
            
            /*window.draw(ball_hb);
            for (int i = 0; i < 10; i++){ window.draw(point_hole_hb[i]); }
            for (int i = 0; i < 47; i++){ window.draw(lose_hole_hb[i]); }*/
            window.draw(bar);
            window.draw(lives_t);
            window.draw(score_t);
            window.draw(clock_t);
        }
        else if(make == true){
            window.draw(menu_bg);
            window.draw(make_t);
            window.draw(mgame_btn);
            window.draw(mgame_btn_t);
            window.draw(pgame_btn);
            window.draw(pgame_btn_t);
        }
        else if (mgame == true){
            if (marker < 47){
                lose_hole[46].setPosition(Mouse::getPosition(window).x,Mouse::getPosition(window).y);
                window.draw(lose_hole[46]);
            }else if(marker < 57){
                point_hole[9].setPosition(Mouse::getPosition(window).x,Mouse::getPosition(window).y);
                window.draw(point_hole[9]);
            }
            /*
            for (int i = 0; i < 10; i++){ window.draw(point_hole_hb[i]); }
            for (int i = 0; i < 47; i++){ window.draw(lose_hole_hb[i]); }*/
            
            for (int i = 0; i < marker; i++){ window.draw(lose_hole[i]); }
            for (int i = 0; i < (marker-47); i++){ window.draw(point_hole[i]); }
            
        }
        
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
