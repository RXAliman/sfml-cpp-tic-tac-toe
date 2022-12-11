#include "Application.h"

Application::Application() {
    initVariables();
    initWindows();
    resetAll();
}

//ACCESSORS
const sf::RenderWindow* Application::getWindow() const {
    return this->window;
}

//PRIVATE FUNCTIONS
void Application::initVariables() {
    //initiate variables
    if (!this->tahoma.loadFromFile("resources/tahoma.ttf")) this->window->close();
    if (!this->clickSound.loadFromFile("resources/click.wav"));

    this->click.setBuffer(this->clickSound);

    this->t_attrib = sf::Text("by: Rovic Aliman",this->tahoma,15);
    this->t_attrib.setPosition(875.f,10.f);

    this->t_gname = sf::Text("Tic-tac-toe (2022)",this->tahoma,15);
    this->t_gname.setPosition(15.f,10.f);

    this->t_manual = sf::Text("Click & drag any piece to the grid\n  Press spacebar to reset board",this->tahoma);
    this->t_manual.setPosition(272.f,480.f);

    this->t_draw = sf::Text("\t\tIt's a draw!\nPress spacebar to retry",this->tahoma);
    this->t_draw.setPosition(335.f,480.f);

    this->t_Xwins = sf::Text("\t\t\tX wins!\nPress spacebar to retry",this->tahoma);
    this->t_Xwins.setPosition(335.f,480.f);

    this->t_Owins = sf::Text("\t\t\tO wins!\nPress spacebar to retry",this->tahoma);
    this->t_Owins.setPosition(335.f,480.f);
}
void Application::initWindows() {
    this->videoMode.height = 600;
    this->videoMode.width = 1000;

    this->window = new sf::RenderWindow(videoMode, "Tic-tac-toe", sf::Style::Close | sf::Style::Titlebar);

    this->window->setFramerateLimit(60);
}
char Application::check() {
    int checkX = 0; int checkO = 0;
    //horizontal check
    for (int a=0; a<9; a++) {
        if (gameBoard[a]==X_PIECE) checkX++;
        else if (gameBoard[a]==O_PIECE) checkO++;
        if (checkX == 3) return 'X';
        else if (checkO == 3) return 'O';
        if ((a+1)%3==0) {
            checkX = 0;
            checkO = 0;
        }
    }
    //vertical check
    checkX = 0; checkO = 0;
    for (int b=0; b<3; b++) {
        for (int c=b; c<9; c+=3) {
        if (gameBoard[c]==X_PIECE) checkX++;
            else if (gameBoard[c]==O_PIECE) checkO++;
            if (checkX == 3) return 'X';
            else if (checkO == 3) return 'O';
        }
        checkX = 0;
        checkO = 0;
    }
    //backslash check
    checkX = 0; checkO = 0;
    for (int d=0; d<9; d+=4) {
        if (gameBoard[d]==X_PIECE) checkX++;
        else if (gameBoard[d]==O_PIECE) checkO++;
        if (checkX == 3) return 'X';
        else if (checkO == 3) return 'O';
    }
    //forward slash check
    checkX = 0; checkO = 0;
    for (int e=2; e<7; e+=2) {
        if (gameBoard[e]==X_PIECE) checkX++;
        else if (gameBoard[e]==O_PIECE) checkO++;
        if (checkX == 3) return 'X';
        else if (checkO == 3) return 'O';
    }
    return ' ';
}
void Application::resetAll()
{
    this->X.clear(); this->O.clear();
    this->roundX = 0; this->roundO = 0;
    this->hasChosen = false;
    this->hasStarted = false;
    this->X_deligate = false; this->O_deligate = false;
    this->isPressedX = false; this->isPressedO = false;
    this->timeout = false;
    this->spawnGamepieces(true,true);
    for (int a=0; a<9; a++) {
        this->box[a].updateOccupation(false);
        this->gameBoard[a] = NONE;
    }
    this->t_timer = sf::Text((this->max_sec < 10 ? "0" : "")+std::to_string(this->max_sec)+":00",
                             this->tahoma);
    this->t_timer.setPosition(455.f,50.f);
}
float Application::distance(sf::Vector2f vec1, sf::Vector2f vec2)
{
    float diff_x = vec1.x - vec2.x;
    float diff_y = vec1.y - vec2.y;
    return std::sqrt(diff_x * diff_x + diff_y * diff_y);
}

//PUBLIC FUNCTIONS
void Application::spawnGamepieces(bool Enable_X, bool Enable_O)
{
    if (Enable_X) this->X.push_back(Gamepiece(len,len,sf::Vector2f(50,237),'X',this->tahoma));
    if (Enable_O) this->O.push_back(Gamepiece(len,len,sf::Vector2f(850,237),'O',this->tahoma));
}
void Application::update()
{
    this->pollEvents();
    if (this->roundX + this->roundO < 8 && this->check() == ' ' && !this->timeout)
    {
        this->updateMousePos();
        this->updateInput();
        if (this->isPressedX || this->isPressedO)
        {
            this->updateGUI();
        }
        if (this->hasChosen)
        {
            if (!this->hasStarted)
            {
                this->timer.restart();
                this->hasStarted = true;
            }
            else this->updateTimer();
        }
    }
    else
    {
        if (this->event.key.code == sf::Keyboard::Space) this->resetAll();
        for (int b=0; b<9; b++) box[b].update(sf::Color::White);
        if (this->isPressedX) this->X[roundX].move(sf::Vector2f(100,287));
        if (this->isPressedO) this->O[roundO].move(sf::Vector2f(900,287));
    }
}
void Application::updateMousePos()
{
    this->m_pos = sf::Vector2f(this->mouse.getPosition(*this->window));
}
void Application::updateInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->hasChosen) this->resetAll();
    if (this->event.type == sf::Event::MouseButtonPressed)
    {
        if (this->event.mouseButton.button == sf::Mouse::Left)
        {
            if (this->X[roundX].getShape().getGlobalBounds().contains(this->m_pos)
                && this->X[roundX].getMovable()) {
                this->isPressedX = true;
                this->aVirgin = false;
            }
            else if (this->O[roundO].getShape().getGlobalBounds().contains(this->m_pos)
                     && this->O[roundO].getMovable()) {
                this->isPressedO = true;
                this->aVirgin = false;
            }
        }
    }
    else if (this->event.type == sf::Event::MouseButtonReleased)
    {
        if (this->event.mouseButton.button == sf::Mouse::Left)
        {
            if (isPressedX) {
                if (this->arr[min] < 75 && !this->box[min].getOccupation()) {
                    this->X[roundX].move(sf::Vector2f(this->box[this->min].getShape().getPosition().x+50,
                                                      this->box[this->min].getShape().getPosition().y+50));
                    this->X[roundX].updateMovable();
                    if (this->hasChosen && roundX + ++roundO < 8) spawnGamepieces(false,true);
                    else this->hasChosen = true;
                    this->box[min].updateOccupation(true);
                    this->gameBoard[min] = X_PIECE;
                    this->O_deligate = true;
                    this->X_deligate = false;
                    this->click.play();
                    this->timer.restart();
                }
                else this->X[roundX].move(sf::Vector2f(100,287));
                this->isPressedX = false;
            }
            else if (isPressedO) {
                if (this->arr[min] < 75 && !this->box[min].getOccupation()) {
                    this->O[roundO].move(sf::Vector2f(this->box[this->min].getShape().getPosition().x+50,
                                                      this->box[this->min].getShape().getPosition().y+50));
                    this->O[roundO].updateMovable();
                    if (this->hasChosen && ++roundX + roundO < 8) spawnGamepieces(true);
                    else this->hasChosen = true;
                    this->box[min].updateOccupation(true);
                    this->gameBoard[min] = O_PIECE;
                    this->X_deligate = true;
                    this->O_deligate = false;
                    this->click.play();
                    this->timer.restart();
                }
                else this->O[roundO].move(sf::Vector2f(900,287));
                this->isPressedO = false;
            }
        }
        for (int b=0; b<9; b++) box[b].update(sf::Color::White);
    }
    if (this->isPressedX) this->X[roundX].move(this->m_pos);
    else if (this->isPressedO) this->O[roundO].move(this->m_pos);
}
void Application::updateGUI()
{
    /*
    Box indices according to Gridbox
        0   1   2
        3   4   5
        6   7   8
    */
    for (int a=0; a<9; a++)
    {
        sf::FloatRect boxRect = sf::FloatRect(box[a].getShape().getLocalBounds());
        sf::Vector2f boxCent = sf::Vector2f(box[a].getShape().getPosition().x+boxRect.width/2,
                                            box[a].getShape().getPosition().y+boxRect.height/2);
        arr[a] = distance(m_pos,boxCent);
    }
    for (int b=0; b<9; b++) min = (arr[min] < arr[b] ? min : b);
    for (int c=0; c<9; c++) {
        if (c == min && arr[min] < 75) this->box[min].update(sf::Color(200,200,200));
        else this->box[c].update(sf::Color::White);
    }
}
void Application::updateTimer()
{
    std::stringstream ss;
    int l = this->max_sec * 100 - this->timer.getElapsedTime().asMilliseconds()/10;
    int n = l / 100;
    int m = l - n * 100;
    if (n <= 0 && m <= 0)
    {
        n = 0; m = 0;
        this->timeout = true;
    }
    if (n < 10) ss << 0;
    ss << n << ":";
    if (m < 10) ss << 0;
    ss << m;
    t_timer.setString(ss.str());
}
void Application::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed) this->window->close();
        if (this->event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) this->window->close();
        }
    }
}
void Application::render()
{
    this->window->clear(sf::Color(0,100,0));
    //draw objects
    this->window->draw(background,4,sf::Quads);
    this->window->draw(this->t_attrib);
    this->window->draw(this->t_gname);
    this->window->draw(this->t_timer);
    for (auto i : this->box) i.render(this->window);
    if (this->isPressedX) {
        for (auto k : this->O) k.render(this->window);
        for (auto j : this->X) j.render(this->window);
    }
    else {
        for (auto j : this->X) j.render(this->window);
        for (auto k : this->O) k.render(this->window);
    }
    if (this->aVirgin) this->window->draw(this->t_manual);
    if (this->check() == 'X' || (this->timeout && this->O_deligate)) this->window->draw(this->t_Xwins);
    else if (this->check() == 'O' || (this->timeout && this->X_deligate)) this->window->draw(this->t_Owins);
    else if (this->roundX + this->roundO == 8) this->window->draw(this->t_draw);

    this->window->display();
}

Application::~Application() {
    delete this->window;
}
