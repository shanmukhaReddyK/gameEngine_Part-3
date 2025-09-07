#include"Action.hpp"
#include"Assets.hpp"
#include"Components.hpp"
#include"GameEngine.h"
#include"Scene_Menu.h"
#include"Scene_Play.h"

Scene_Play::Scene_Play(GameEngine& gameEngine,const std::string& levelPath) : Scene(gameEngine), m_levelPath(levelPath) {
    init(m_levelPath);
}

void Scene_Play::init(const std::string& levelPath){
    registerAction(sf::Keyboard::Key::P,     "PAUSE");
    registerAction(sf::Keyboard::Key::Escape,"QUIT");
    registerAction(sf::Keyboard::Key::T,     "TOGGLE_TEXTURE");
    registerAction(sf::Keyboard::Key::C,     "TOGGLE_COLLISION");
    registerAction(sf::Keyboard::Key::G,     "TOGGLE_GRID");

    //TODO: Register remaining actions
    m_gridText= sf::Text(m_game.getAssets().getFont("Tech"));
    m_gridText->setCharacterSize(8);

    loadLevel(levelPath);
}

Vec2f Scene_Play::gridToMidPixel(float x, float y, std::shared_ptr<Entity> entity){
    //  return a vec2f indicationg  where a centre postion should be
    //  you must use Entity's animation size to postion it correctly
    //          entity->get<CAnimation>().getSize()
    //  the size of the grid width and height is stored in m_gridSize.x and m_gridSize.y
    //  the bottom-left corner of the animation should align with bottomleft of the the specified grid cell
    
    //remember that SFML has (0,0) in the top left, while grid co ordinates are specified from bottom left
    //you can get the size of the SFML window via m_game.window().getSize();
    //* could also use bounding box half size if the bounding box is added before trannsform pos gets added
    float midX = x*m_gridSize.x+ entity->get<CAnimation>().animation.getSize().y/2; 
    float midY = m_game.window().getSize().y-( y * m_gridSize.y + entity->get<CAnimation>().animation.getSize().y/2 );
    return Vec2f(midX,midY);
}

void Scene_Play::loadLevel(const std::string& levelpath){
    //reset the entity manager everytime we load a level
    m_entityManager = EntityManager();

    //TODO:: read in the file and add appropriate entities
    //      use playerConfig struct m_playerConfig to store player properties
    //      this struct is defined at the top of Scene_Play
    // std::ifstream fin(levelpath);

    // if(!fin.is_open()) {
    //     std::cerr<<"Error opening file "<< levelpath <<"\n";
    // }

    // std::string word;

    // while(fin >> word) {



    // }
    //NOTE::all of the code below is sample code which shows you how to set up and use entites with new syntax , it should be removed

    spawnPlayer(); 

    //some sample entites
    auto brick = m_entityManager.addEntity("tile");
    //IMPORTANT: always add CAnimation first so that gridToMidPixel first so that it can compute the position required
    brick->add<CAnimation>(m_game.getAssets().getAnimation("Brick1"), true);
    brick->add<CTransform>(Vec2f(224, 480));
    //NOTE: you final code should position the entity with grid x,y position read from level.txt
    //brick->add<CTransform>(gridToMidPixel(gridX, gridY, brick));

    if(brick->get<CAnimation>().animation.getName() == "Brick1") {
        //This could be a good way of identifying if a tile is brick!
    }

    auto block = m_entityManager.addEntity("tile");
    block->add<CAnimation>(m_game.getAssets().getAnimation("Block2"), true );
    block->add<CTransform>(Vec2f(254,480));
    //add a bounding box , this will show up if press the 'C' key
    block->add<CBoundingBox>(m_game.getAssets().getAnimation("Block2").getSize());

    // auto block=m_entityManager.addEntity("tile");
    // block->add<CAnimation>(m_game.getAssets().getAnimation("Question"), true);
    // block->add<CTransform>(Vec2f(352,480));

    /*Note //!important
            Components are now returned as references rather that pointers
            if you do not specify a reference variable type,it will copy the component
            eg:
            This will copy the transform into the variable 'transform1' - it is incorrect
            any changes you make to transform1 will not be changed inside the entity 
            auto transform1 = entity->get<CTransform>();

            this will reference the transform with variable 'transform2' -it is correct
            now the changes you make to transform2 will be changed inside the entity
            auto& transform1 = entity->get<CTransform>();
    */   
}

void Scene_Play::spawnPlayer() {
    //sample player entity
    auto player = m_entityManager.addEntity("player");
    player->add<CAnimation>(m_game.getAssets().getAnimation("SamuraiStill"), true);
    player->add<CTransform>(Vec2f(224,352));
    player->add<CBoundingBox>(Vec2f(32,32));
    player->add<CState>("stand");
    player->add<CInput>();

    //TODO: be sure to add the remaining components to the player
    // be sure to destory the dead player if we are respawning
}

void Scene_Play::spawnBullet(std::shared_ptr<Entity> entity) {
    //TODO : this should spawn a bullet at the given entity , going in the direction the entity is facing (use scale to check -1/1 to left/right)
}

void Scene_Play::update() {
    m_entityManager.update();
    
    ImGui::SFML::Update(m_game.window(),m_game.clock().restart());
    //TODO: Implement pause functionality

    // sMovement();
    // sLifespan();
    // sCollision();
    sAnimation();
    sGUI();
    sRender();
}

void Scene_Play::sMovement() {
    //TODO: Implement player movement / jumpimg based on its CInput component
    //TODO: Implement gravity effect on player
    //TODO: Implement the maximum player speed in both x and y directions
    //NOTE: Setting an Entity scale.x to -1/1 will make it face to the left/right
}

void Scene_Play::sLifespan() {
    //TODO: Check life span of the entities that have them , and destroy them if they go over
}

void Scene_Play::sCollision() {
    /*
        Remember: SFML's (0,0) position is on the top left corner
                  This mean jumping will have a negative y component
                  And gravity will have a positive y component
                  Also, something BELOW something else will have a y value greater than it
                  also, somthing ABOVE something else will have a y value less than it

        TODO: Implement Physics::GetOverlap() function and use it here
        TODO: Implement bullet tiles collision, destroy the tile if it has a brick animation
        TODO: Implement player/tile collison and resolutions
              update the CState component of the player to store weather it is currently on the ground or in the air. this will be used by the animation system
        TODO: Check to see if the player has fallen down a hole (y>heigth())
        TODO: Dont let the player walk off the left side of the map 
    */
}

void Scene_Play::sDoAction(const Action& action) {
    if (action.type()=="START") {
        if(action.name()=="TOGGLE_TEXTURE")             { m_drawTextures=!m_drawTextures; }
        else if (action.name()=="TOGGLE_COLLISION")     { m_drawCollision=!m_drawCollision; }
        else if (action.name()=="TOGGLE_GRID")          { m_drawGrid=!m_drawGrid; }
        else if (action.name()=="PAUSE")                { setPaused(!m_paused); }
        else if (action.name()=="QUIT")                 { onEnd(); }
    }

    else if (action.type()=="END") {
        //TODO
    }
}

void Scene_Play::sAnimation() {
    //TODO: Complete the animation class implementation first

    //TODO: for each entity with an animation, call entity->get<CAnimation>().animation.update()
    for(auto& e : m_entityManager.getEntities()) {
        if(e->get<CAnimation>().exists) {
            e->get<CAnimation>().animation.update();
    
        }
    } 
        // if the animation is not repeated, and it has ended , destroy the entityj

    //TODO: set the aninmation opf the player based on its CState component
    //if player state has been set to running
    // if(player()->get<CState>().state == "run") {
    //     //change its animation to repeating run animation 
    //     //NOTE: adding a component that already exists simply overwrites it
    //     player()->add<CAnimation>(m_game.getAssets().getAnimation("Run"), true);
    // }
}

void Scene_Play::onEnd() {
    //TODO: when scene ends, change back to the MENU scene 
    // use m_game.changeScene(correct parmas);
}

void Scene_Play::sGUI() {
    ImGui::Begin("Scene_Properties");

    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("MyTabBar",tab_bar_flags)) {
        if (ImGui::BeginTabItem("Actions")) {
            for (const auto& [key,name] : getActionMap() ) {
                std::string ss = "START##" + name;
                std::string se = "END##" + name;

                if (ImGui::Button(ss.c_str())) {
                    doAction(Action(name, "START"));
                }
                ImGui::SameLine();
                if (ImGui::Button(se.c_str())) {
                    doAction(Action(name, "END"));
                }
                ImGui::SameLine();
                ImGui::Text("%s", name.c_str());
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Assets")) {
            
            if(ImGui::CollapsingHeader("Animations",ImGuiTreeNodeFlags_None)) {
                ImGui::Indent();
                int count=0;
                for(const auto& [name, anim]: m_game.getAssets().getAnimation()) {
                    count++;
                    //TODO
                    // ImGui::ImageButton((Animation)anim.getSprite(name));
                    // if ((count % 6)!=0 && count!=m_game.getAssets.m_animations.size()) .....
                }
                ImGui::Unindent();
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}

void Scene_Play::sRender() {
    //color the background darker so that you know game is paused
    if(!m_paused) { m_game.window().clear(sf::Color(100,100,250));}
    else { m_game.window().clear(sf::Color(50,50,150));}

    //set up the viewport of the window to be centred to the player
    auto &pPos = player()->get<CTransform>().pos;
    float windowCentreX = std::max((int)m_game.window().getSize().x/2,(int) pPos.x);
    sf::View view = m_game.window().getView();
    view.setCenter({windowCentreX,(float)m_game.window().getSize().y/2});
    m_game.window().setView(view);

    // Draw all the entity texture
    if (m_drawTextures) {

        for (auto& e:m_entityManager.getEntities()) {
            
            auto & transform = e->get<CTransform>();
            if(e->has<CAnimation>()) {
                auto& animation = e->get<CAnimation>().animation;
                // animation.getSprite()->SetRotation(transform.angl...);
                animation.getSprite()->setPosition(transform.pos);
                // animation.getSprite()->SetScale(transform.scale.x..);
                m_game.window().draw(*animation.getSprite());
            }
        }
    }

    if(m_drawCollision) {

        for (auto& e:m_entityManager.getEntities()) {
            if(e->has<CBoundingBox>()) {
                auto& box = e->get<CBoundingBox>();
                auto& transform = e->get<CTransform>();
                sf::RectangleShape rect;
                rect.setSize(sf::Vector2f(box.size.x-1,box.size.y-1));
                rect.setOrigin(sf::Vector2f(box.halfSize.x,box.halfSize.y));
                rect.setPosition({transform.pos.x,transform.pos.y});
                rect.setFillColor(sf::Color(0,0,0,0));
                rect.setOutlineColor(sf::Color(255,255,255,255));
                rect.setOutlineThickness(1);
                m_game.window().draw(rect);
            }
        }
    }

    if(m_drawGrid) {
        // m_gridText=sf::Text(m_game.getAssets().getFont("Tech"));
        
        //lamda functions to get height and width
        auto width = [this]() {return m_game.window().getSize().x;};
        auto height = [this]() {return m_game.window().getSize().y;};

        float leftX = m_game.window().getView().getCenter().x -width()/2-m_gridSize.x;
        float rightX = leftX + width() + m_gridSize.x;
        float nextGridX = leftX - ((int)leftX % (int)m_gridSize.x);

        for (float x = nextGridX; x<rightX; x +=m_gridSize.x) {
            //vertical lines drawing
            drawLine(Vec2f(x,0),Vec2f(x,height()));
        }

        for (float y = 0; y<height(); y +=m_gridSize.y) {
            //horizontal lines drawing
            drawLine(Vec2f(leftX,height()-y),Vec2f(rightX,height()-y));

            //grid labelling
            for(float x = nextGridX; x<rightX; x +=m_gridSize.x) {

                std::string xCell = std::to_string((int)x/(int)m_gridSize.x);
                std::string yCell = std::to_string((int)y/(int)m_gridSize.y);
                m_gridText->setString("(" + xCell+ "," + yCell +")" );
                m_gridText->setPosition({x+3, height()-y-m_gridSize.y+3});
                m_game.window().draw(*m_gridText);
            }
        }
    }

    ImGui::SFML::Render(m_game.window());
    m_game.window().display();
}

void Scene_Play::drawLine(const Vec2f& p1, const Vec2f& p2) {
    sf::Vertex line[] = { 
                            {sf::Vector2f(p1.x,p1.y), sf::Color(255,255,255,255),sf::Vector2f(p1.x,p1.y)},
                            {sf::Vector2f(p2.x,p2.y), sf::Color(255,255,255,255),sf::Vector2f(p2.x,p2.y)}
                        };
 
    m_game.window().draw (line, 2, sf::PrimitiveType::Lines);
}

std::shared_ptr<Entity> Scene_Play::player() {
    auto& players = m_entityManager.getEntities("player");
    assert(players.size()==1); //only one player in game
    return players.front();
}

void Scene_Play::setPaused(bool setPause) {
    m_paused=setPause;
}