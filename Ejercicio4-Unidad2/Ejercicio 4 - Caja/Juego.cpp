#include "Juego.h"
#include "Box2DHelper.h"
#include <iostream>

// Constructor de la clase Game
Game::Game(int ancho, int alto, std::string titulo)
{
    // Inicialización de la ventana y configuración de propiedades
    wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
    wnd->setVisible(true);
    fps = 60;
    wnd->setFramerateLimit(fps);
    frameTime = 1.0f / fps;
    SetZoom(); // Configuración de la vista del juego
    InitPhysics(); // Inicialización del motor de física
}

// Bucle principal del juego
void Game::Loop()
{
    while (wnd->isOpen())
    {
        wnd->clear(clearColor); // Limpiar la ventana
        DoEvents(); // Procesar eventos de entrada
        UpdatePhysics(); // Actualizar la simulación física
        DrawGame(); // Dibujar el juego
        wnd->display(); // Mostrar la ventana
    }
}

// Actualización de la simulación física
void Game::UpdatePhysics()
{
    phyWorld->Step(frameTime, 8, 8); // Simular el mundo físico
    phyWorld->ClearForces(); // Limpiar las fuerzas aplicadas a los cuerpos
    phyWorld->DebugDraw(); // Dibujar el mundo físico para depuración
}

// Dibujo de los elementos del juego
void Game::DrawGame() //Borrar y ver que todavia se dibuja pero usando SFMLRender por el SetDebugDraw de Box2D implementado en el método InitPhysics
{
    // Dibujar el suelo
    sf::RectangleShape groundShape(sf::Vector2f(500, 5));
    groundShape.setFillColor(sf::Color::Green);
    groundShape.setPosition(0, 95);
    wnd->draw(groundShape);

    //Dibujar el techo
    sf::RectangleShape roofShape(sf::Vector2f(500, 5));
    roofShape.setFillColor(sf::Color::Yellow);
    roofShape.setPosition(0, 0);
    wnd->draw(roofShape);

    // Dibujar las paredes
    sf::RectangleShape leftWallShape(sf::Vector2f(10, 600)); // Alto de la ventana
    leftWallShape.setFillColor(sf::Color::Blue);
    leftWallShape.setPosition(-5, -505);
    wnd->draw(leftWallShape);

    sf::RectangleShape rightWallShape(sf::Vector2f(10, 600)); // Alto de la ventana
    rightWallShape.setFillColor(sf::Color::Cyan);
    rightWallShape.setPosition(95, -505);
    wnd->draw(rightWallShape);

    //Caja
    sf::RectangleShape controlShape(sf::Vector2f(15, 15));
    controlShape.setFillColor(sf::Color::Red);
    controlShape.setPosition(controlBody->GetPosition().x-7.5f, controlBody->GetPosition().y - 7.5f);
    wnd->draw(controlShape);


}

// Procesamiento de eventos de entrada
void Game::DoEvents()
{
    Event evt;
    while (wnd->pollEvent(evt))
    {
        switch (evt.type)
        {
        case Event::Closed:
            wnd->close(); // Cerrar la ventana si se presiona el botón de cerrar
            break;
 
        }
    }

    controlBody->SetAwake(true);

    //Velocidad Fuerza por el Jugador
    if (Keyboard::isKeyPressed(Keyboard::Left))
        controlBody->SetLinearVelocity(b2Vec2(-5.0f, 0.0f));
    if (Keyboard::isKeyPressed(Keyboard::Right))
        controlBody->SetLinearVelocity(b2Vec2(5.0f, 0.0f));

    //Aplicar fuerza con ApplyForce
    if (Keyboard::isKeyPressed(Keyboard::D))
     controlBody->ApplyForce(b2Vec2(80000.0f, 0.0f), controlBody->GetWorldCenter(), true);
    if (Keyboard::isKeyPressed(Keyboard::A))
        controlBody->ApplyForce(b2Vec2(-80000.0f, 0.0f), controlBody->GetWorldCenter(), true);


}


// Configuración de la vista del juego
void Game::SetZoom()
{
    View camara;
    // Posicionamiento y tamaño de la vista
    camara.setSize(100.0f, 100.0f); //(100.0f,100.0f * 600/800.0f) para que no se deforme y mantener el ratio de la pantalla original
    camara.setCenter(50.0f, 50.0f);
    wnd->setView(camara); // Asignar la vista a la ventana
}

// Inicialización del motor de física y los cuerpos del mundo físico
void Game::InitPhysics()
{
    // Inicializar el mundo físico con la gravedad por defecto
    phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

    // Crear un renderer de debug para visualizar el mundo físico
    debugRender = new SFMLRenderer(wnd);
    debugRender->SetFlags(UINT_MAX);
    phyWorld->SetDebugDraw(debugRender);

    // Crear el suelo,techo y las paredes estáticas del mundo físico

    // 0.02 hielo sobre hielo, laton sobre hielo
    //0.3-0.4 cuero sobre madera
    //0.6 cuero sobre metal, acero sobre acero
    //0.25-0.50 madera sobre medera
    b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100,10,0.6);
    groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

    b2Body* roofBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100,10,0);
    roofBody->SetTransform(b2Vec2(50.0f, 0.0f), 0.0f);

    b2Body* leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10,100,0);
    leftWallBody->SetTransform(b2Vec2(0.0f, 50.0f), 0.0f);

    b2Body* rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10,100,0);
    rightWallBody->SetTransform(b2Vec2(100.0f, 50.0f), 0.0f);

    //Caja
    controlBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld,15,15,30.0f,0.1f,0.0f);
    controlBody->SetTransform(b2Vec2(50.0f,90.0f),0.0f);

}

// Destructor de la clase

Game::~Game(void)
{
}