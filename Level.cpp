#include "Level.h"
#include "ResourceManager.h"

Level::Level() {
    space = new Block[50*50];
    gridSize = 32.;
    width = 50;
    height = 50;
    portalAccessed = 0;
    noteAccessed = 0;

    for (int i = 0; i < 50; i++) for (int j = 0; j < 50; j++) {
        if (i < 2 || i > 47 || j < 2 || j > 47) space[i+50*j] = Level::Ground;
        else space[i+50*j] = (rand() % 2) ? Level::Ground : Level::Air;
    }

    Block* genSpace;
    int neighborCount;
    for (int i = 0; i < 30; i++) {
        genSpace = new Block[50*50];
        for (int x = 0; x < 50; x++) for (int y = 0; y < 50; y++) {
            if (x < 2 || x > 47 || y < 2 || y > 47) genSpace[x+50*y] = Ground;
            else {
                neighborCount = 0;
                for (int u = -1; u < 2; u++) for (int v = -1; v < 2; v++) {
                    if (space[x+u+50*(y+v)] == Ground) neighborCount++;
                }
                genSpace[x+50*y] = (neighborCount > 4) ? Ground : Air;
            }
        }
        space = genSpace;
    }
    int x = rand()%width;
    int y = rand()%height;
    while (space[x+width*y] != Air) {
        x = rand()%width;
        y = rand()%height;
    }
    space[x+width*y] = DownPassage;
    downLoc = sf::Vector2f(x*32+16., y*32+16.);

    while (space[x+width*y] != Air) {
        x = rand()%width;
        y = rand()%height;
    }
    space[x+width*y] = UpPassage;
    upLoc = sf::Vector2f(x*32+16., y*32+16.);

    while (space[x+width*y] != Air) {
        x = rand()%width;
        y = rand()%height;
    }
    space[x+width*y] = Note;
    //establish note ID here


    //draw up stage
    fg.create(1600,1600);
    fg.clear(sf::Color::Transparent);
    sf::Sprite wallSegment = sf::Sprite(ResourceManager::GroundTiling, sf::IntRect(0,0,32,32));
    int u = 0;
    int v = 0;
    for (int x = 0; x < 49; x++) for (int y = 0; y < 49; y++) {
        u = 0;
        v = 0;
        if (space[x+y*50] == Ground) u += 32;
        if (space[x+1+y*50] == Ground) u += 64;
        if (space[x+(y+1)*50] == Ground) v += 32;
        if (space[x+1+(y+1)*50] == Ground) v += 64;
        wallSegment.setTextureRect(sf::IntRect(u,v,32,32));
        wallSegment.setPosition(16+32*x,16+32*y);
        fg.draw(wallSegment);
    }
    fg.display();

    bg.create(1600,1600);
    bg.clear();
    wallSegment.setTexture(ResourceManager::WallTiling);
    for (int x = 1; x < 49; x++) for (int y = 1; y < 49; y++) {
        switch(space[x+width*y]) {
        case Ground:
        case Air:
            wallSegment.setTextureRect((rand()%2)? sf::IntRect(0,0,32,32) : sf::IntRect(32,32,32,32));
            break;
        case Smear:
            wallSegment.setTextureRect(sf::IntRect(0,32,32,32));
            break;
        case Note:
            wallSegment.setTextureRect(sf::IntRect(96,0,32,32));
            break;
        case DownPassage:
            wallSegment.setTextureRect(sf::IntRect(32,0,32,32));
            break;
        case UpPassage:
            wallSegment.setTextureRect(sf::IntRect(64,0,32,32));
            break;
        }
        wallSegment.setPosition(x*32.,y*32);
        bg.draw(wallSegment);
    }
    bg.display();
}

Level::Level(std::istream& stream) {
    gridSize = 32.;
    noteAccessed = 0;
    portalAccessed = 0;

    std::cout << "Begin Load\n";
    stream >> width;
    stream >> height;
    space = new Block[width*height];
    std::cout << "Loading Blocks\n";
    char piece;
    for (int v = 0; v < height; v++) for (int u = 0; u < width; u++) {
        stream >> piece;
        std::cout << piece;
        if (piece == '\n') stream >> piece;
        switch (piece) {
        case '`':
            space[u+v*width] = Air;
            break;
        case '#':
            space[u+v*width] = Ground;
            break;
        case '!':
            space[u+v*width] = Note;
            break;
        case '*':
            space[u+v*width] = Smear;
            break;
        case 'U':
            space[u+v*width] = UpPassage;
            upLoc = sf::Vector2f(u*32.+16,v*32+16);
            break;
        case 'D':
            space[u+v*width] = DownPassage;
            downLoc = sf::Vector2f(u*32.+16,v*32+16);
            break;
        }
    }

    std::cout << "Generating graphics\n";
    //draw up stage
    fg.create(1600,1600);
    fg.clear(sf::Color::Transparent);
    sf::Sprite wallSegment = sf::Sprite(ResourceManager::GroundTiling, sf::IntRect(0,0,32,32));
    int u = 0;
    int v = 0;
    for (int x = 0; x < 49; x++) for (int y = 0; y < 49; y++) {
        u = 0;
        v = 0;
        if (space[x+y*50] == Ground) u += 32;
        if (space[x+1+y*50] == Ground) u += 64;
        if (space[x+(y+1)*50] == Ground) v += 32;
        if (space[x+1+(y+1)*50] == Ground) v += 64;
        wallSegment.setTextureRect(sf::IntRect(u,v,32,32));
        wallSegment.setPosition(16+32*x,16+32*y);
        fg.draw(wallSegment);
    }
    fg.display();

    bg.create(1600,1600);
    bg.clear();
    wallSegment.setTexture(ResourceManager::WallTiling);
    for (int x = 1; x < 49; x++) for (int y = 1; y < 49; y++) {
        switch(space[x+width*y]) {
        case Ground:
        case Air:
            wallSegment.setTextureRect((rand()%2)? sf::IntRect(0,0,32,32) : sf::IntRect(32,32,32,32));
            break;
        case Smear:
            wallSegment.setTextureRect(sf::IntRect(0,32,32,32));
            break;
        case Note:
            wallSegment.setTextureRect(sf::IntRect(96,0,32,32));
            break;
        case DownPassage:
            wallSegment.setTextureRect(sf::IntRect(32,0,32,32));
            break;
        case UpPassage:
            wallSegment.setTextureRect(sf::IntRect(64,0,32,32));
            break;
        }
        wallSegment.setPosition(x*32.,y*32);
        bg.draw(wallSegment);
    }
    bg.display();
    std::cout << "Done\n";
}

void Level::updateFgAt(int x, int y) {

    sf::Sprite wallSegment = sf::Sprite(ResourceManager::GroundTiling, sf::IntRect(0,0,32,32));
    int u = 0;
    int v = 0;
    for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) {
        u = 0;
        v = 0;
        if (space[x-1+i+(y-1+j)*50] == Ground) u += 32;
        if (space[x+i+(y-1+j)*50] == Ground) u += 64;
        if (space[x-1+i+(y+j)*50] == Ground) v += 32;
        if (space[x+i+(y+j)*50] == Ground) v += 64;
        wallSegment.setTextureRect(sf::IntRect(u,v,32,32));
        wallSegment.setPosition(32*x+32*i-16,32*y+32*j-16);
        fg.draw(wallSegment, sf::BlendNone);
    }
}

void Level::updateBgAt(int x, int y) {
    sf::Sprite wallSegment(ResourceManager::WallTiling);
    switch(space[x+width*y]) {
    case Ground:
    case Air:
        wallSegment.setTextureRect((rand()%2)? sf::IntRect(0,0,32,32) : sf::IntRect(32,32,32,32));
        break;
    case Smear:
        wallSegment.setTextureRect(sf::IntRect(0,32,32,32));
        break;
    case Note:
        wallSegment.setTextureRect(sf::IntRect(96,0,32,32));
        break;
    case DownPassage:
        wallSegment.setTextureRect(sf::IntRect(32,0,32,32));
        break;
    case UpPassage:
        wallSegment.setTextureRect(sf::IntRect(64,0,32,32));
        break;
    }
    wallSegment.setPosition(x*32.,y*32);
    bg.draw(wallSegment);
}

sf::Vector2f Level::getPixelSize() { return sf::Vector2f(width*gridSize,height*gridSize); }

int Level::logic() {
    if (portalAccessed == 1) {
        portalAccessed = 0;
        return ADVANCE_LEVEL;
    }
    else if (portalAccessed == -1) {
        portalAccessed = 0;
        return RETURN_LEVEL;
    }
    else if (noteAccessed == 2) {
        noteAccessed = 0;
        return OPEN_NOTE;
    }
    return 0;
}

bool Level::colAt(float x, float y) {
    int u = x/32;
    int v = y/32;
    return (space[u+width*v] == Level::Ground);
}

void Level::activateAt(float x, float y) {
    int u = x/32;
    int v = y/32;

    if (u < 2 || u >= width-2 || v < 2 || v >= height-2) return;

    switch (space[u+width*v]) {
        case Ground:
        case Smear:
            space[u+width*v] = Air;
            break;
        case Air:
            space[u+width*v] = Smear;
            break;
        case DownPassage:
            portalAccessed = 1;
            break;
        case UpPassage:
            portalAccessed = -1;
            break;
        case Note:
            noteAccessed = 2;
            break;
    }

    updateFgAt(u,v);
    updateBgAt(u,v);
}

void Level::serialize(std::ostream& stream) {
    stream << width << "\n" << height << "\n"; //add noteID later.
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            switch (space[x+y*width]) {
            case Air:
                stream << "`";
                break;
            case Ground:
                stream << "#";
                break;
            case Smear:
                stream << "*";
                break;
            case Note:
                stream << "!";
                break;
            case UpPassage:
                stream << "U";
                break;
            case DownPassage:
                stream << "D";
                break;
            }
        }
        stream << "\n";
    }
}


sf::Sprite Level::getFG() { return sf::Sprite(fg.getTexture()); }

sf::Sprite Level::getBG() { return sf::Sprite(bg.getTexture()); }

sf::Vector2f Level::getDownLoc() { return downLoc; }

sf::Vector2f Level::getUpLoc() { return upLoc; }

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sf::Sprite(fg.getTexture()));
}
