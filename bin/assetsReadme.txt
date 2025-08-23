Texture asset specifiacation:
Texture N P
name of the texture   -N    : std::string (no spaces)
path to the file      -P    : std::string (no spaces)

Animation asset specifiacation
Animation N T F S SX SY
Animation name        -N    : std::string (no spaces)
Texture name          -T    : std::string (refers to an existing texture)
frame count           -F    : int (no of frames in the animation)     
Animation speed       -S    : int (number of game frames between animation frames)
Start Index X         -SX   : float
Start Index Y         -SY   : float
Size X                -LX   : float
Size Y                -LY   : float

Font asset specifiacation:
Font N P 
name of the Font      -N    : std::string (no spaces)
path to the file      -P    : std::string (no spaces)