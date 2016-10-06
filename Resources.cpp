#include "Resources.hpp"

//PLACE HERE THE RESOURCES YOU WANT TO LOAD

// sf::Texture        Resources::....
sf::Texture            Resources::key;
sf::Texture            Resources::log;
sf::Texture            Resources::boss;
sf::Texture            Resources::eyes;
sf::Texture            Resources::heart;
sf::Texture            Resources::enemy;
sf::Texture            Resources::chain;
sf::Texture            Resources::ghost;
sf::Texture            Resources::ninja;
sf::Texture            Resources::bullet;
sf::Texture            Resources::endHook;
sf::Texture            Resources::bullet2;
sf::Texture            Resources::shooter;
sf::Texture            Resources::Portada;
sf::Texture            Resources::pointer;
sf::Texture            Resources::talkBox;
sf::Texture            Resources::hatNone;
sf::Texture            Resources::doors_OX;
sf::Texture            Resources::doors_OO;
sf::Texture            Resources::doors_XX;
sf::Texture            Resources::enemyBloc;
sf::Texture            Resources::enemyStar;

std::vector<sf::Texture> Resources::one(1);
std::vector<sf::Texture> Resources::none (1);
std::vector<sf::Texture> Resources::puff (9);
std::vector<sf::Texture> Resources::puff0 (9);
std::vector<sf::Texture> Resources::spawnAnim (9);
std::vector<sf::Texture> Resources::destroyAnim (9);
std::vector<sf::Texture> Resources::destroyBullet (9);
std::vector<sf::Texture> Resources::destroyPlayer (9);

sf::Shader             Resources::cInvert;

sf::Font               Resources::pauseMenuFont;

std::vector<SpriteSheetDescription> Resources::descriptions;

/*void printError(std::string s){
    std::cerr << "Resources:: Error loading... " << s << std::endl;
}*/

void Resources::load() {
    //LOAD THE INFORMATION IN THE VARIABLES
    //...loadFromFile(); or whatever
    if(! key.loadFromFile                    (TEXTURETPATH+std::string("key.png"))        ) printError("keyTex");
    if(! log.loadFromFile                    (TEXTURETPATH+std::string("log.png"))        ) printError("logTex");
    if(! boss.loadFromFile                   (TEXTURETPATH+std::string("boss.png"))       ) printError("bossTex");
    if(! eyes.loadFromFile                   (TEXTURETPATH+std::string("eyes.png"))       ) printError("eyesTex");
    if(! heart.loadFromFile                  (TEXTURETPATH+std::string("vida.png"))       ) printError("heartTex");
    if(! enemy.loadFromFile                  (TEXTURETPATH+std::string("enemy.png"))      ) printError("enemyTex");
    if(! chain.loadFromFile                  (TEXTURETPATH+std::string("hook.png"))       ) printError("chainTex");
    if(! ghost.loadFromFile                  (TEXTURETPATH+std::string("ghost.png"))      ) printError("ghostTex");
    if(! ninja.loadFromFile                  (TEXTURETPATH+std::string("ninja.png"))      ) printError("ninjaTex");
    if(! bullet.loadFromFile                 (TEXTURETPATH+std::string("bullet.png"))     ) printError("bulleTex");
    if(! bullet2.loadFromFile                (TEXTURETPATH+std::string("bullet2.png"))    ) printError("bulleTex");
    if(! talkBox.loadFromFile                (TEXTURETPATH+std::string("talkBox.png"))    ) printError("talkbTex");
    if(! endHook.loadFromFile                (TEXTURETPATH+std::string("endHook.png"))    ) printError("endHkTex");
    if(! pointer.loadFromFile                (TEXTURETPATH+std::string("pointer.png"))    ) printError("poinrTex");
    if(! shooter.loadFromFile                (TEXTURETPATH+std::string("shooter.png"))    ) printError("shterTex");
    if(! Portada.loadFromFile                (TEXTURETPATH+std::string("Portada.png"))    ) printError("portaTex");
    if(! hatNone.loadFromFile                (TEXTURETPATH+std::string("none/none.png"))  ) printError("hatnoneT");
    if(! doors_OX.loadFromFile               (TEXTURETPATH+std::string("doors_OX.png"))   ) printError("doorOXTex");
    if(! doors_OO.loadFromFile               (TEXTURETPATH+std::string("doors_OO.png"))   ) printError("doorOOTex");
    if(! doors_XX.loadFromFile               (TEXTURETPATH+std::string("doors_XX.png"))   ) printError("doorXXTex");
    if(! enemyBloc.loadFromFile              (TEXTURETPATH+std::string("enemyBloc.png"))  ) printError("enemyBloc");
    if(! enemyStar.loadFromFile              (TEXTURETPATH+std::string("enemyStar.png"))  ) printError("enemyStar");

    for(int i = 0; i < 1; ++i){
        if(! none[i].loadFromFile  (TEXTURETPATH+std::string("none/none.png") )) printError("noneAnim");
    }
    for(int i = 0; i < 9; ++i){
        if(! puff[i].loadFromFile  (TEXTURETPATH+std::string("puff_clean/smoke_puff_000")+std::string(std::to_string(i+1))+std::string(".png") )) printError("puffAnim");
    }
    for(int i = 9; i > 0; --i){
        if(! puff0[9-i].loadFromFile  (TEXTURETPATH+std::string("puff/smoke_puff_000")+std::string(std::to_string(i))+std::string(".png") )) printError("puff0Anim");
    }
    for(int i = 0; i < 9; ++i){
        if(! spawnAnim[i].loadFromFile  (TEXTURETPATH+std::string("spawn/smoke_plume_000")+std::string(std::to_string(i+1))+std::string(".png") )) printError("spawnAnim");
    }
    for(int i = 0; i < 9; ++i){
        if(! destroyAnim[i].loadFromFile  (TEXTURETPATH+std::string("destroy/smoke_jump_000")+std::string(std::to_string(i+1))+std::string(".png") )) printError("destroyAnim");
    }
    for(int i = 0; i < 9; ++i){
        if(! destroyPlayer[i].loadFromFile  (TEXTURETPATH+std::string("puff_player/smoke_puff_000")+std::string(std::to_string(i+1))+std::string(".png") )) printError("destroyplayer");
    }
    for(int i = 0; i < 9; ++i){
        if(! destroyBullet[i].loadFromFile  (TEXTURETPATH+std::string("bullet_puff/smoke_plume_000")+std::string(std::to_string(i+1))+std::string(".png") )) printError("destroybullet");
    }

        if(sf::Shader::isAvailable() ){
const std::string fragmentShader = \
"uniform sampler2D texture;" \
"uniform float Time;" \
"uniform float deltaTime;" \
"void main()" \
"{"  \
	"float blinkTimes;" \
    "blinkTimes = Time*8.0;" \
    "float aux = ((deltaTime/Time)*blinkTimes);" \
    "float x = step(mod(aux,2.0), 1.0);" \
    "vec4 originalColor = texture2D(texture, gl_TexCoord[0].xy) * gl_Color;" \
    "gl_FragColor = vec4(originalColor.r+0.7,originalColor.g,originalColor.b,originalColor.a);"  \
"}";

//    "gl_FragColor = vec4(vec3(1.0-x,1.0-x,1.0-x) +(-1.0+2.0*x)*originalColor.rgb, originalColor.a);"
// load only the fragment shader
if (!cInvert.loadFromMemory(fragmentShader, sf::Shader::Fragment))
{
    std::cout << "mux shader failed" <<std::endl; // error...
}
        }
    if (!pauseMenuFont.loadFromFile("Resources/Fonts/font.TTF")) exit(EXIT_FAILURE);

   // descriptions = std::vector<SpriteSheetDescription>(spriteDescriptionsQtt);
   // descriptions[linkSpritesDescriptions]       = loadDescription("linkSheet");
    mlog(" Resources Loaded ");
}


//ONLY USED IF USING DESCRIPTORS
SpriteSheetDescription Resources::loadDescription(std::string) {
    SpriteSheetDescription s;
    return s;
    //Ja els llegeix cada nivell, així que la funció no fa falta.
}
