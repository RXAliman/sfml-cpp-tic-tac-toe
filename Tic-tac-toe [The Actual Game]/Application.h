#include "Gamepiece.h"

class Application {
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;
    //objects
    sf::Vector2f gridPos = sf::Vector2f(345,140);
    const int len = 100;
    Gamepiece box[9] = {
        Gamepiece(len,len,sf::Vector2f(gridPos)),
        Gamepiece(len,len,sf::Vector2f(gridPos.x+len-3,gridPos.y)),
        Gamepiece(len,len,sf::Vector2f(gridPos.x+len*2-6,gridPos.y)),
        Gamepiece(len,len,sf::Vector2f(gridPos.x,gridPos.y+len-3)),
        Gamepiece(len,len,sf::Vector2f(gridPos.x+len-3,gridPos.y+len-3)),
        Gamepiece(len,len,sf::Vector2f(gridPos.x+len*2-6,gridPos.y+len-3)),
        Gamepiece(len,len,sf::Vector2f(gridPos.x,gridPos.y+len*2-6)),
        Gamepiece(len,len,sf::Vector2f(gridPos.x+len-3,gridPos.y+len*2-6)),
        Gamepiece(len,len,sf::Vector2f(gridPos.x+len*2-6,gridPos.y+len*2-6)),
    };
    std::vector<Gamepiece> X;
    std::vector<Gamepiece> O;
    sf::Vertex background[4] =
    {
        sf::Vertex(sf::Vector2f(0,0), sf::Color(0,100,0)),
        sf::Vertex(sf::Vector2f(1000,0), sf::Color(0,50,0)),
        sf::Vertex(sf::Vector2f(1000,600), sf::Color(0,100,0)),
        sf::Vertex(sf::Vector2f(0,600), sf::Color(0,50,0))
    };
    //logics
    enum {
        NONE = 0,
        X_PIECE = -1,
        O_PIECE = -2
    };
    sf::Mouse mouse;
    sf::Vector2f m_pos;
    sf::Clock timer;
    bool isPressedX = false, isPressedO = false;
    bool hasChosen = false;
    bool aVirgin = true;
    bool hasStarted = false;
    bool X_deligate;
    bool O_deligate;
    bool timeout;
    const int max_sec = 5; //maximum seconds to take in timed tictactoe
    int min = 0;
    int arr[9];
    int roundX = 0;
    int roundO = 0;
    int gameBoard[9];
    //text
    sf::Text t_attrib;
    sf::Text t_gname;
    sf::Text t_manual;
    sf::Text t_draw;
    sf::Text t_Xwins;
    sf::Text t_Owins;
    sf::Text t_timer;
    //sounds
    sf::Sound click;
    //resources
    sf::Font tahoma;
    sf::SoundBuffer clickSound;
    //functions
    void initWindows();
    void initVariables();
    char check();
    void resetAll();
    float distance(sf::Vector2f vec1, sf::Vector2f vec2);
public:
    Application();
    void pollEvents();
    void spawnGamepieces(bool Enable_X = false, bool Enable_O = false);
    void update();
    void updateMousePos();
    void updateInput();
    void updateGUI();
    void updateTimer();
    void render();
    const sf::RenderWindow* getWindow() const;
    ~Application();
};
