(GX,GY) is grid and (0,0) is the bottom left corner

TILE ENTITY SPECIFICATION:
Tile N GX GY
    Animation name  N           std:string (Animation asset name for the tile)
    GX Grid X pos   GX          float
    GY Grid Y pos   GY          float

DECORATION ENTITY SPECIFICATION:
Dec N GX GY
    Animation name  N           std:string (Animation asset name for the tile)
    GX Grid X pos   GX          float
    GY Grid Y pos   GY          float

PLAYER SPECIFICATION
Player GX GY CW CH SX SY SM GY B
    GX GY Grid pos   X Y         float, float (starting position of the player)
    BoundingBox W/H  CW CH       float, float
    Left/Right Speed SX          float
    Jump Speed       SY          float    
    Max Speed        SM          float
    Gravity          GY          float
    Bullet Animation B           std::string (Animation Asset to use for Bullets)

