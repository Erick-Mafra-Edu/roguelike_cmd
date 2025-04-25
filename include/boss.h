
using namespace std; 

// Variável que identifica se o boss está atacando
bool bossIsAttacking = false;

// Posição atual do projétil do boss
COORD bossProjectilePosition = {0, 0};

// Direção que o projétil do boss está se movendo
COORD bossProjectileMoveDirection = {0, 0};

// Cooldown entre os ataques do boss
int bossAttackCooldown = 0;

// Constante que define o tempo de espera entre os ataques do boss
const int BOSS_ATTACK_COOLDOWN_FRAMES = 20;

// Chance de o boss atacar em cada frame (%)
const int BOSS_ATTACK_CHANCE = 5;

// Caractere visual do projétil do boss
const char BOSS_PROJECTILE_CHAR = '^';


// Função que limpa o caractere em uma posição específica do console
void clearConsolePosition(HANDLE &hConsole, COORD pos) {
    SetConsoleCursorPosition(hConsole, pos);
    cout << " ";
}

// Função que desenha o boss na posição indicada
void drawBossArt(HANDLE &hConsole, Position pos) {
    string artBoss[5] = {"¬¬¬¬¬", "[= =]", "|0 0|", "|@ @|", "/|||\\"};

    COORD consolePos;
    for (size_t i = 0; i < 5; i++) {
        consolePos.X = pos.x;
        consolePos.Y = pos.y + (SHORT)i;

        // Garante que o desenho fique dentro da tela
        if (consolePos.Y < 0 || consolePos.Y >= 100) continue;

        SetConsoleCursorPosition(hConsole, consolePos);
        cout << artBoss[i];
    }
}

// Função que limpa a arte do boss da tela na posição antiga
void clearBossArt(HANDLE hConsole, Position pos) {
    COORD consolePos;
    for (size_t i = 0; i < 5; i++) {
        consolePos.X = pos.x;
        consolePos.Y = pos.y + (SHORT)i;

        // Garante que a limpeza fique dentro da tela
        if (consolePos.Y < 0 || consolePos.Y >= 100) continue;

        SetConsoleCursorPosition(hConsole, consolePos);
        cout << "     "; // Apaga 5 caracteres por linha
    }
}

// Função que desenha as bordas da sala do boss
void printBossRoom() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO windowSize;
    GetConsoleScreenBufferInfo(hConsole, &windowSize);
    COORD pos;

    // Desenha as paredes laterais
    for (SHORT i = 0; i < windowSize.dwSize.Y; i++) {
        pos = {0, i};
        SetConsoleCursorPosition(hConsole, pos);
        cout << "█";
        pos = {(SHORT)(windowSize.dwSize.X - 1), i};
        SetConsoleCursorPosition(hConsole, pos);
        cout << "█";
    }

    // Desenha as paredes superior e inferior
    for (SHORT i = 0; i < windowSize.dwSize.X; i++) {
        pos = {i, 0};
        SetConsoleCursorPosition(hConsole, pos);
        cout << "█";
        pos = {i, (SHORT)(windowSize.dwSize.Y - 1)};
        SetConsoleCursorPosition(hConsole, pos);
        cout << "█";
    }
}

// Função que atualiza o boss e realiza a lógica de ataque e movimento
void updateBoss(map &mapCurrent, Position playerPos, HANDLE &hConsole , int &health) {
    enemy &boss = mapCurrent.enemyList[0]; // Pega uma referência ao boss na lista de inimigos
    int moveDirX = 0, moveDirY = 0; // Direção de movimento do boss neste frame
    CONSOLE_SCREEN_BUFFER_INFO windowSize;
    GetConsoleScreenBufferInfo(hConsole, &windowSize);
    static bool bossInitialized = false; // Flag simples para inicialização do boss

    if (!bossInitialized || (boss.position.x == 0 && boss.position.y == 0)) {
        // Inicializa o boss no centro da tela
        boss.position.x = (windowSize.dwSize.X / 2) - 2;
        boss.position.y = (windowSize.dwSize.Y / 2) - 2;
        drawBossArt(hConsole, boss.position); // Desenha o boss na tela
        bossIsAttacking = false; // Garante que o boss não está atacando inicialmente
        bossAttackCooldown = BOSS_ATTACK_COOLDOWN_FRAMES / 2; // Inicia com algum cooldown
        bossInitialized = true; // Marca como inicializado
        boss.health = 500; // Define a vida inicial do boss
        boss.damage = 25;  // Define o dano do boss
        boss.c = 'B';      // Representação do boss por um caractere
        boss.position.x = (windowSize.dwSize.X / 2) - 2; // Centro no eixo X
        boss.position.y = (windowSize.dwSize.Y / 2) - 2; // Centro no eixo Y
        drawBossArt(hConsole, boss.position); // Desenha o boss
        bossIsAttacking = false; // Garante que não há ataque ao inicializar
        bossAttackCooldown = BOSS_ATTACK_COOLDOWN_FRAMES / 2; // Cooldown do ataque inicial
    }

    // --- Verificação do estado do boss ---
    if (boss.health <= 0) {
        if (boss.position.x != -1) { // Verifica se o boss não foi removido
            clearBossArt(hConsole, boss.position);
            boss.position = {-1, -1}; // Marca o boss como removido
            // Pode acionar condições de vitória ou atualizar pontuação aqui
        }
        return; // Não atualiza mais o boss se estiver morto
    }

    // --- Lógica do projétil do boss ---
    if (bossIsAttacking) {
        COORD prevProjectilePos = bossProjectilePosition; // Salva a posição anterior do projétil

        // Move o projétil com base na direção armazenada
        bossProjectilePosition.X += bossProjectileMoveDirection.X;
        bossProjectilePosition.Y += bossProjectileMoveDirection.Y;

        // Verifica colisões com parede ou jogador
        bool hitWall = bossProjectilePosition.X <= 0 || bossProjectilePosition.X >= windowSize.dwSize.X - 1 ||
                       bossProjectilePosition.Y <= 0 || bossProjectilePosition.Y >= windowSize.dwSize.Y - 1;
        bool hitPlayer = bossProjectilePosition.X == playerPos.x && bossProjectilePosition.Y == playerPos.y;

        if (hitWall || hitPlayer) {
            bossIsAttacking = false; // Para o ataque
            clearConsolePosition(hConsole, prevProjectilePos); // Limpa a posição anterior

            if (hitPlayer) {
                health -= boss.damage; // Dano ao jogador
                Beep(200, 150); // Som do impacto
            }
            bossAttackCooldown = BOSS_ATTACK_COOLDOWN_FRAMES; // Inicia cooldown após o ataque
        } else {
            // Limpa a posição anterior e desenha o projétil na nova posição
            clearConsolePosition(hConsole, prevProjectilePos);
            SetConsoleCursorPosition(hConsole, bossProjectilePosition); // Define a nova posição
            cout << BOSS_PROJECTILE_CHAR; // Desenha o projétil
        }
    }

    // --- Lógica de movimento e decisão de ataque do boss ---
    if (!bossIsAttacking) {
        // Diminui o cooldown do ataque
        if (bossAttackCooldown > 0) {
            bossAttackCooldown--;
        }

        // Calcula a direção do movimento do boss em direção ao jogador
        if (boss.position.y < playerPos.y) moveDirY = 1;
        else if (boss.position.y > playerPos.y) moveDirY = -1;
        else moveDirY = 0;

        if (boss.position.x < playerPos.x) moveDirX = 1;
        else if (boss.position.x > playerPos.x) moveDirX = -1;
        else moveDirX = 0;

        // --- Decisão de ataque ---
        if (bossAttackCooldown <= 0 && (rand() % 100 < BOSS_ATTACK_CHANCE)) {
            bossIsAttacking = true;

            // Inicializa o projétil próximo ao centro do boss
            bossProjectilePosition.X = boss.position.x + 2; // Centro X do boss
            bossProjectilePosition.Y = boss.position.y + 2; // Centro Y do boss

            // Define a direção do projétil com base na direção calculada
            bossProjectileMoveDirection.X = (SHORT)moveDirX;
            bossProjectileMoveDirection.Y = (SHORT)moveDirY;

            // Garante que o projétil se mova mesmo se o boss estiver alinhado com o jogador
            if (bossProjectileMoveDirection.X == 0 && bossProjectileMoveDirection.Y == 0) {
                bossProjectileMoveDirection.X = (rand() % 2 == 0) ? 1 : -1;
                bossProjectileMoveDirection.Y = 0;
            }

            Beep(800, 50); // Som do ataque

            moveDirX = 0; // Não move o boss enquanto ele ataca
            moveDirY = 0;
        }
        // --- Fim da decisão de ataque ---

        // Se o boss não está atacando, tenta se mover
        Position nextPos = boss.position;
        // Verifica se sobrepõe o player
        bool overlapsPlayer = (playerPos.x >= nextPos.x && playerPos.x <= nextPos.x + 4 &&
            playerPos.y >= nextPos.y && playerPos.y <= nextPos.y + 4);
        if (overlapsPlayer) {
        moveDirX = 0;
        moveDirY = 0;
        }
        nextPos.x += moveDirX;
        nextPos.y += moveDirY;

        // Verifica colisão com as paredes
        if (nextPos.x <= 0 || nextPos.x + 4 >= windowSize.dwSize.X - 1) {
            moveDirX = 0; // Para o movimento horizontal se atingir as paredes laterais
        }
        if (nextPos.y <= 0 || nextPos.y + 4 >= windowSize.dwSize.Y - 1) {
            moveDirY = 0; // Para o movimento vertical se atingir o teto ou chão
        }
        

        // Atualiza a posição do boss
        clearBossArt(hConsole, boss.position);
        boss.position = nextPos;
        drawBossArt(hConsole, boss.position);
    }
}
