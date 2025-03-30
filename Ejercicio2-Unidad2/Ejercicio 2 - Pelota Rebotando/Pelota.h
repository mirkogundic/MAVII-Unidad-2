#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

using namespace sf; // Espacio de nombres para la biblioteca SFML

class Pelota
{
private:
    // Sprite y su imagen para representaci�n gr�fica
    Sprite* _sprite;
    Texture* _image;
    RenderWindow* wnd;
    // Body para representaci�n f�sica
    b2Body* _body;

public:
    // Constructor de la clase Pelota
    Pelota(b2World* _world, RenderWindow* _wnd)
    {
        // Guardamos un puntero a la ventana para dibujar luego
        wnd = _wnd;
        _image = new Texture();
        _image->loadFromFile("Pelota.png"); // Carga la textura de la pelota
        // Cargamos el sprite
        _sprite = new Sprite(*_image);
        _sprite->setScale(0.06f,0.06f);

        // Definimos el cuerpo f�sico y lo creamos
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(50.0f, 50.0f);
        _body = _world->CreateBody(&bodyDef);

        // Creamos su figura de colisi�n
        b2CircleShape pelota;
        pelota.m_radius = 6;

        // Creamos el fixture, le asignamos la figura de colisi�n y lo agregamos al cuerpo
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &pelota;
        fixtureDef.density = 10.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 3.0f;
        _body->CreateFixture(&fixtureDef);

    }

    // M�todo que actualiza la posici�n del sprite seg�n la posici�n del cuerpo f�sico
    void ActualizarPosiciones()
    {
        b2Vec2 pos = _body->GetPosition();
        _sprite->setPosition(pos.x-6, pos.y-6);
   
    }

    //Cambio de velocidad por tecla
    void Velocidad(float x_vel, float y_vel) {
        _body->SetLinearVelocity(b2Vec2(x_vel, y_vel));
    }

    // M�todo que dibuja el sprite en la ventana
    void Dibujar()
    {
        wnd->draw(*_sprite);
    }

    void Awake() {

        _body->SetAwake(true);
    }

};
