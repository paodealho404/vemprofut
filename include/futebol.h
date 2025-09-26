
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

/**
 * @brief Desenha o campo de futebol
 */
void drawFootballField();

/**
 * @brief Desenha todos os jogadores
 */
void drawPlayers();

/**
 * @brief Desenha a bola
 */
void drawBall();

/**
 * @brief Desenha o placar
 */
void drawScoreboard();

/**
 * @brief Desenha a área do gol
 */
void drawGoalArea();

/**
 * @brief Desenha o contorno do campo de futebol
 */
void drawFootballFieldOutline();

/**
 * @brief Desenha o time rubro-negro
 */
void drawRedBlackTeam();

/**
 * @brief Desenha o time alvinegro
 */
void drawBlackWhiteTeam();

/**
 * @brief Muda a animação do jogador
 * @param player Jogador cuja animação será alterada
 */
void changePlayerAnimation(struct Player player);

/**
 * @brief Toca a trilha sonora do jogo
 */
void playGameOST();

/**
 * @brief Toca o som de gol
 */
void playGoalSound();

/**
 * @brief Move o jogador em direção à bola
 * @param player Jogador a ser movido
 */
void movePlayerToBall(struct Player player);

/*
M --> a) Desenhe um Campo de Futebol: retas/circunferências, etc;
M --> b) Crie uma bola - a bola deverá ser movimentada usando o teclado;
P --> c) Crie um placar - toda vez que a bola passar da linha do Gol, o placar
deverá ser atualizado; e a bola deveráaparecer no meio do campo;
P --> d) Incluir som; https://github.com/lieff/minimp3
M --> e) Crie os jogadores (liberado o uso de ferramentas (Blender, etc) para
este requisito);
P --> f) Crie uma mecanica de movimentação dos jogadores atrás da bolsa (usar
criatividade!);
*/