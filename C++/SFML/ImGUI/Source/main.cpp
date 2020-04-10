#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "");
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    sf::Color bgColor;
    float color[3] = { 0.f, 0.f, 0.f };

    Vector2f position(50.f, 50.f);
    Color sunColor;
    float scolor[3] = { 0.f, 0.f, 0.f };
    CircleShape circle(13);

    // здесь мы будем использовать массив char. Чтобы использовать
    // std::string нужно сделать действия, описанные во второй части
    char windowTitle[255] = "ImGui + SFML = <3";
    window.setTitle(windowTitle);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

	    circle.setPosition(position);
        circle.setFillColor(sunColor);
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Sample window"); // создаём окно

        // Инструмент выбора цвета
        if (ImGui::ColorEdit3("Background color", color)) {
            // код вызывается при изменении значения, поэтому всё
            // обновляется автоматически
            bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
            bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
            bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
        }

        ImGui::InputText("Window title", windowTitle, 255);

        if (ImGui::Button("Update window title")) {
            // этот код выполняется, когда юзер жмёт на кнопку
            // здесь можно было бы написать 
            // if(ImGui::InputText(...))
            window.setTitle(windowTitle);
        }
        ImGui::End(); // end window

        ImGui::Begin("Circle"); // создаём окно
		
        if (ImGui::ColorEdit3("Color", scolor)) {
            // код вызывается при изменении значения, поэтому всё
            // обновляется автоматически
            sunColor.r = static_cast<sf::Uint8>(scolor[0] * 255.f);
            sunColor.g = static_cast<sf::Uint8>(scolor[1] * 255.f);
            sunColor.b = static_cast<sf::Uint8>(scolor[2] * 255.f);
        }
        ImGui::SliderFloat2("Position", &position.x, 0.f, 480.f);
        
        ImGui::End(); // end window

        window.clear(bgColor); // заполняем окно заданным цветом
        ImGui::SFML::Render(window);
        window.draw(circle);
        window.display();
    }

    ImGui::SFML::Shutdown();
}