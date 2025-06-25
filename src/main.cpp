#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

#include "systems/TestSystem.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    //Graphics tests
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    //Include tests
    TestSystem::print_hello_world();

    //Texture and Sprite test
    const sf::Texture texture("assets/images/smile.png");
    sf::Sprite sprite(texture);

    //SoundBuffer and Sound test
    const sf::SoundBuffer buffer("assets/audios/Jazz_Background_Music.mp3");
    sf::Sound backgroundMusic(buffer);
    backgroundMusic.setLooping(true);
    backgroundMusic.play();

    sf::Clock deltaClock;
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

#ifdef DEBUG_MODE
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::ShowDemoWindow();

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();
#endif

        window.clear();
        window.draw(shape);
        window.draw(sprite);

#ifdef DEBUG_MODE
        ImGui::SFML::Render(window);
#endif
        window.display();
    }

    ImGui::SFML::Shutdown();
}