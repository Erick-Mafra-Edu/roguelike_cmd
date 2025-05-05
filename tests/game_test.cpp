#include "gtest/gtest.h"
#include "player.h"

TEST(PlayerTest, PlayerCreation) {
    
    Player player;
    EXPECT_EQ(player.position.X,0);
    EXPECT_EQ(player.position.Y,0);
}
/*RelativeMovement*/
TEST(PlayerTest, PlayerRelativeMovement) {
  COORD position;
  position.X = 2;
  position.Y = 3;
  int sum = 1;
  Inventory inventory;
  Player player= {position,inventory,100, 1, 1};
  player.setRelativePosition(sum,sum);
  EXPECT_EQ(player.position.X,2+sum);
  EXPECT_EQ(player.position.Y,3+sum);
}

TEST(PlayerTest, PlayerSetPosition) {
    Player player;
    player.setPosition(5, 10);
    EXPECT_EQ(player.position.X, 5);
    EXPECT_EQ(player.position.Y, 10);
}

TEST(PlayerTest, PlayerInitialStats) {
    Player player;
    EXPECT_EQ(player.health, 100);
    EXPECT_EQ(player.shield, 0);
    EXPECT_EQ(player.damage, 10);
}

TEST(GameTest, GameCreation) {
    Game game;
    EXPECT_EQ(game.returnType, Game::exit);
    EXPECT_EQ(game.points, 0);
    EXPECT_EQ(game.roomsMoved, 0);
}

TEST(GameTest, GameInitialValues) {
    Game game;
    EXPECT_EQ(game.player.health, 100);
    EXPECT_EQ(game.player.damage, 10);
    EXPECT_EQ(game.player.position.X, 0);
    EXPECT_EQ(game.player.position.Y, 0);
}
/*Boss Tests*/

// Mock para função COORD simples (exemplo de função independente)
TEST(BossLogicTest, OverlapsPlayerTrue) {
    Position boss = {10, 10};
    Position player = {12, 12}; // Dentro da área 5x5 do boss
    EXPECT_TRUE(overlapsPlayer(boss, player));
}

TEST(BossLogicTest, OverlapsPlayerFalse) {
    Position boss = {10, 10};
    Position player = {20, 20}; // Fora da área do boss
    EXPECT_FALSE(overlapsPlayer(boss, player));
}
TEST(BossLogicTest, BossInitializesInCenter) {
    Gamemap map;
    Position player = {0, 0};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int health = 100;

    updateBoss(map, player, hConsole, health);

    // Espera que o boss esteja em algum ponto central (com tolerância)
    EXPECT_GT(map.enemyList[0].position.x, 0);
    EXPECT_GT(map.enemyList[0].position.y, 0);
    EXPECT_EQ(map.enemyList[0].health, 500);
}