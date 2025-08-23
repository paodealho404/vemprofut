
struct Scoreboard {
    int scoreRedBlackTeam;
    int scoreBlackWhiteTeam;
};

struct ForceVector {
    float x;
    float y;
};
enum Team {
    RED_BLACK,
    BLACK_WHITE
};
struct Ball {
    float x;
    float y;
    float radius;
};

struct Player {
    float x;
    float y;
    enum Team team;
    struct ForceVector attractive;
    struct ForceVector repulsive;

};

void drawFootballField();
void drawPlayers();
void drawBall();
void drawScoreboard();
void drawGoalArea();
void drawFootballFieldOutline();
void drawRedBlackTeam();
void drawBlackWhiteTeam();
void changePlayerAnimation(struct Player player);
void playGameOST();
void playGoalSound();
void movePlayerToBall(struct Player player);



/*

M --> a) Desenhe um Campo de Futebol: retas/circunferências, etc;
M --> b) Crie uma bola - a bola deverá ser movimentada usando o teclado;
P --> c) Crie um placar - toda vez que a bola passar da linha do Gol, o placar deverá ser atualizado; e a bola deverá aparecer no meio do campo;
P --> d) Incluir som; https://github.com/lieff/minimp3
M --> e) Crie os jogadores (liberado o uso de ferramentas (Blender, etc) para este requisito);
P --> f) Crie uma mecanica de movimentação dos jogadores atrás da bolsa (usar criatividade!);
 
*/