/*
    BalloonShooting is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    BalloonShooting is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with BalloonShooting.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "BalloonShoot.h"
#include "TextureHolder.h"
#include "Bow.h"
#include "Arrow.h"
#include "Balloon.h"

using namespace sf;

int main() {
    TextureHolder holder;

    //  The game will alway in one state
    enum class State {
        PAUSED, GAME_OVER, PLAYING, LEVEL_UP
    };

    //  Start with game over state
    State state = State::GAME_OVER;

    //  Get the screen resolution and create the SFML window
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(resolution.x, resolution.y), "BallonShoot");

    //  Create an SFML View for the main action
    View mainView(FloatRect (0, 0, resolution.x, resolution.y));

    //  Here is clock for timing everything
    Clock clock;

    //  How long is the PLAYING state been active
    Time gameTimeTotal;

    //  Where is the mouse in relation to world coordinate system
    Vector2f mouseWorldPosition;
    //  Where is the mouse in relation to screen coordinate system
    Vector2i mouseScreenPosition;

    // Instance of bow
    Bow bow;

    //  Create boundarys of arena for balloons to fly
    IntRect ballonArena;
    
    ballonArena.left = resolution.x / 2 + 20;     //  20 more than half the screen
    ballonArena.top = 0;
    ballonArena.width = resolution.x / 2 - 70;    //  Balloon should not be half visible
    ballonArena.height = resolution.y;

    //  Balloons
    int numBallons;
    int numBallonsFlying;
    Balloon* balloons = nullptr;

    //  100 Arrows should do
    Arrow arrows[100];
    float fireRate = 1;
    int currentArrow = 0;

    //  When was the fire button last pressed
    Time lastPrassed;

    //  Hide the mouse pointer and replace it with crosshair
    window.setMouseCursorVisible(false);
    Sprite spriteCrosshair;
    Texture textureCrosshair = TextureHolder::GetTexture("../assets/graphics/crosshair.png");
    spriteCrosshair.setTexture(textureCrosshair);
    spriteCrosshair.setOrigin(25, 25);

    //  make clouds sprites and textures
    //Texture textureCloud = TextureHolder::GetTexture("graphics/Cloud1.png");
    const int NUM_CLOUD_TEXTURES = 2;
    Texture textureClouds[NUM_CLOUD_TEXTURES];
    textureClouds[0] = TextureHolder::GetTexture("../assets/graphics/Cloud1.png");
    textureClouds[1] = TextureHolder::GetTexture("../assets/graphics/Cloud2.png");

    //  Make the cloudw with array
    const int NUM_CLOUDS = 3;
    Sprite Clouds[NUM_CLOUDS];
    int cloudSpeed[NUM_CLOUDS];
    bool cloudsActive[NUM_CLOUDS];

    //  Make tree sprite
    Texture textureTree = TextureHolder::GetTexture("../assets/graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(0, 350);

    for (int i = 0; i < NUM_CLOUDS; i++) {
        srand((int)time(0) * i);
        Clouds[i].setTexture(textureClouds[rand() % NUM_CLOUD_TEXTURES]);
        Clouds[i].setPosition(-800, i * 80);
        cloudsActive[i] = false;
        cloudSpeed[i] = 0;    //    initializing speed to 0 
    }

    //  About the game
    int score = 0;
    int highScore = 0;

    //  For the home/game over screen
    Sprite spriteGameOver;
    Texture textureGameOver = TextureHolder::GetTexture("../assets/graphics/background.png");
    spriteGameOver.setTexture(textureGameOver);
    spriteGameOver.setPosition(0, 0);

    //  Create a view for the HUD
    View hudView(FloatRect(0, 0, resolution.x, resolution.y));

    //  Load the font
    Font font;
    font.loadFromFile("../assets/font/Pacifico.ttf");

    //  Paused
    Text pausedText;
    pausedText.setFont(font);
    pausedText.setCharacterSize(65);
    pausedText.setColor(Color::White);
    pausedText.setPosition(resolution.x/2, resolution.y/2);
    pausedText.setString("Press Enter \nto continue");

    //  Game Over
    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(55);
    gameOverText.setColor(Color::White);
    gameOverText.setPosition(resolution.x/2, resolution.y/2);
    gameOverText.setString("Press Enter to play");

    //  Levelling up text
    Text levelUpText;
    levelUpText.setFont(font);
    levelUpText.setCharacterSize(50);
    levelUpText.setColor(Color::White);
    levelUpText.setPosition(80, 120);
    std::stringstream levelUpStream;
    levelUpStream << "1 - Increase rate of fire." <<
                     "\n2 - Increase balloons, and fire.";
    levelUpText.setString(levelUpStream.str());

    //  Score
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setColor(Color::White);
    scoreText.setPosition(20, 0);

    //  Ballons Remaining
    Text balloonsRemainingText;
    balloonsRemainingText.setFont(font);
    balloonsRemainingText.setCharacterSize(35);
    balloonsRemainingText.setColor(Color::Red);
    balloonsRemainingText.setPosition(550, 0);
    balloonsRemainingText.setString("Ballons: ");


    //  Prepare the shoot sound
    SoundBuffer shootBuffer;
    shootBuffer.loadFromFile("../assets/sounds/shoot.wav"); 
    Sound shoot;
    shoot.setBuffer(shootBuffer);

    //  Balloon blown sound
    SoundBuffer blowBuffer;
    blowBuffer.loadFromFile("../assets/sounds/balloon_blown.wav");
    Sound blown;
    blown.setBuffer(blowBuffer);

    //  Balloon hit sound
    SoundBuffer blowHitBuffer;
    blowHitBuffer.loadFromFile("../assets/sounds/balloon_run.wav");
    Sound bHit;
    bHit.setBuffer(blowHitBuffer);

    //  Create number of balloons
    numBallons = 5;
    delete[] balloons;
    balloons = createHorde(numBallons, ballonArena);
    numBallonsFlying = numBallons;

    //  The main game loop
    while (window.isOpen()) {
        /*
        *********************
        Handle input
        *********************
        */
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed) {
                //  Pause the game while playing
                if (event.key.code == Keyboard::Return && state == State::PLAYING) {
                    state = State::PAUSED;
                    std::cout << "Playing -> Paused\n";
                } else if (event.key.code == Keyboard::Return && state == State::PAUSED) {
                    //  Restart while paused
                    state = State::PLAYING;
                    //  Restart the clock so there isnt a frame jump
                    std::cout << "Paused -> Playing\n";
                    clock.restart();
                } else if (event.key.code == Keyboard::Return && state == State::GAME_OVER) {
                    //  This is only untill implimenting levelling up
                    //state = State::PLAYING;
                    //currentArrow = 0;

                    state = State::LEVEL_UP;
                    score = 0;
                }
            }
        }// End polling event

        //  Handling the player Quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        //  Handle controll while playing 
        if (state == State::PLAYING) {

            //  Fire a arrow
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (gameTimeTotal.asMilliseconds() - lastPrassed.asMilliseconds() > 1000/fireRate) {
                    //  Pass the center of Bow and center of crosshair
                    //  to the shoot function
                    arrows[currentArrow].shoot(bow.getCenter().x, bow.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);
                    currentArrow++;
                    if (currentArrow > 99) {
                        currentArrow = 0;
                    }
                    //  Play shoot sound
                    shoot.play();
                    lastPrassed = gameTimeTotal;
                }
            }// End fire button
        }


        //  Handling leveling up state
        if (state == State::LEVEL_UP) {
            //  Handle player laveling up
            if (event.key.code == Keyboard::Num1) {
                //  Increase firerate 
                //numBallons += 5;
                fireRate += 1; 
                numBallonsFlying = numBallons;
                state = State::PLAYING;
            }

            if (event.key.code == Keyboard::Num2) {
                //  Increse ballons and firerate too
                numBallons += 5;
                numBallonsFlying = numBallons;
                fireRate += 1; 
                state = State::PLAYING;
            }

            if (state == State::PLAYING) {
                //  increase wave num ballons and all
                //  Delete previously allocated memory if it exists
                delete[] balloons;
                balloons = createHorde(numBallons + 10, ballonArena);
                clock.restart();
            }
        }

        /*
        ***********************
        Update the frame
        ***********************
        */

        if (state == State::PLAYING) {
            //  Update the delta time
            Time dt = clock.restart();

            //  Update the total game time
            gameTimeTotal += dt;

            //  Make a decimal fraction of 1 from the delta time 
            float dtAsSeconds = dt.asSeconds();

            //  Where is mouse pointer
            mouseScreenPosition = Mouse::getPosition();

            //  Convert mouse position to world coordinates of mainView
            mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);

            //  Set the crosshair to mouse world location
            spriteCrosshair.setPosition(mouseWorldPosition);

            //  Manage the cloudes
            for (int i = 0; i < NUM_CLOUDS; i++) {
                if (!cloudsActive[i]) {
                    //  How fast is the cloud
                    srand((int)time(0) * i);
                    cloudSpeed[i] = (rand() % 70);

                    //  How high is the cloud
                    srand((int)time(0) * i);
                    float height = (rand() % 120);
                    Clouds[i].setPosition(-300, height);
                    cloudsActive[i] = true;
                } else {
                    //  Set the new position
                    Clouds[i].setPosition(Clouds[i].getPosition().x + (cloudSpeed[i] * dt.asSeconds()), Clouds[i].getPosition().y);

                    //  Has the cloud reached right hand edge of the screen
                    if (Clouds[i].getPosition().x > resolution.x) {
                        //  set it up to be new cloude
                        cloudsActive[i] = false;
                    }
                }
            }

            //  Update the Bow
            bow.update(dtAsSeconds, mouseScreenPosition);

            //  Loop through ballons and update them
            for (int i = 0; i < numBallons; i++) {
                if (balloons[i].isAlive()) {
                    balloons[i].update(dt.asSeconds(), Vector2f(0, 0));
                } 
            }

            //  update any arraw in flight
            for (int i = 0; i < 100; i++) {
                if (arrows[i].isInFlight()) {
                    arrows[i].update(dtAsSeconds);
                }
            }

            // Collision detection
            for (int i = 0; i < 100; i++) {
                for (int j = 0; j < numBallons; j++) {
                    if (arrows[i].isInFlight() && balloons[j].isAlive()) {
                        if (arrows[i].getPosition().intersects(balloons[j].getPosition())) {
                            //  Stop the arrow
                            arrows[i].stop();

                            //  Play arrow on balloon
                            bHit.play();
                            //  On hit your earn 1 point
                            score++;

                            //  Register the hit and see if it was a kill shot
                            if (balloons[j].hit()) {
                                //  Not just hit but blown too
                                //  Add the exact score
                                score += balloons[j].getEarnPoints();
                                //balloons[j]
                                if (score > highScore) {
                                    highScore = score;
                                }
                                numBallonsFlying--;

                                if (numBallonsFlying == 0) {
                                    state = State::LEVEL_UP;
                                }

                                //  play blow sound
                                blown.play();
                            }
                        }
                    }
                }
            }

            //  Update the game HUD
            std::stringstream ssScore;
            std::stringstream ssBalloonsFlying;

            //  update the score text
            ssScore << "Score: " << score;
            scoreText.setString(ssScore.str());

            //  update ballons remaining
            ssBalloonsFlying << "Ballons: " << numBallonsFlying;
            balloonsRemainingText.setString(ssBalloonsFlying.str());


        }// End updating scene

        /*
        ***********************
        Draw the scene
        ***********************
        */
        if (state == State::PLAYING) {
            window.clear();
            //  Set the mainView to be displayed in window
            //  And draw everything related to it
            window.setView(mainView);

            //  Draw the clouds
            for (int i = 0; i < NUM_CLOUDS; i++) {
                window.draw(Clouds[i]);
            }

            //  Draw the ballons
            for (int i = 0; i < numBallons; i++) {
                window.draw(balloons[i].getSprite());
            }

            //  Draw the tree
            window.draw(spriteTree);

            for (int i = 0; i < 100; i++) {
                if (arrows[i].isInFlight()) {
                    window.draw(arrows[i].getShape());
                }
            }

            //  Draw the bow
            window.draw(bow.getSprite());

            //  Draw the crosshair
            window.draw(spriteCrosshair);

            //  Switch to HUD elements
            window.setView(hudView);

            //  Draw all HUD text
            window.draw(scoreText);
            window.draw(balloonsRemainingText);
        }

        if (state == State::LEVEL_UP) {
            window.draw(spriteGameOver);
            window.draw(levelUpText);
        }

        if (state == State::PAUSED) {
            window.draw(pausedText);
        }

        if (state == State::GAME_OVER) {
            window.draw(spriteGameOver);
            window.draw(gameOverText);
        }
        window.display();
    }// End of game loop
    //  Delete the allocated memory
    delete[] balloons;
    return 0;
}
