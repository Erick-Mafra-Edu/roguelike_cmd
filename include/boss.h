#pragma once // Good practice include guard

// #include <windows.h> // For COORD, console functions
// #include <cmath>     // For potential future use
// #include <cstdlib>   // For rand()
// #include <string>    // For string
// #include <iostream>  // For cout

// // #include "./enemy.h" // Already included via map.h if map.h includes enemy.h
// // #include "./primitiveTypes.h" // Already included via enemy.h

using namespace std; // Assuming you are using this namespace

// --- Globals (Consider encapsulating these in a Boss class/struct later) ---
bool bossIsAttacking = false;      // Renamed to avoid conflict with potential local variables
COORD bossProjectilePosition = {0, 0};
COORD bossProjectileMoveDirection = {0, 0}; // Stores the direction the projectile travels
int bossAttackCooldown = 0;        // Simple cooldown timer
const int BOSS_ATTACK_COOLDOWN_FRAMES = 60; // Cooldown frames (e.g., 1 second at ~60fps)
const int BOSS_ATTACK_CHANCE = 5; // Chance (out of 100) to start an attack per frame (if not cooling down)
const char BOSS_PROJECTILE_CHAR = '*';
// --- End Globals ---

// Forward declaration if needed, or ensure player.h includes necessary structs/classes
// struct Player; // If player struct/class is needed for damage calculation

// --- Helper Functions ---

// Helper to clear a specific console position
void clearConsolePosition(HANDLE hConsole, COORD pos) {
    SetConsoleCursorPosition(hConsole, pos);
    cout << " ";
}

// Helper to draw the boss art at a specific Position
void drawBossArt(HANDLE hConsole, Position pos) { // Takes Position
    string artBoss[5]={"¬¬¬¬¬","[= =]","|0 0|","|@ @|","/|||\\"};
    COORD consolePos;
    for (size_t i = 0; i < 5; i++)
    {
        // Convert Position to COORD for SetConsoleCursorPosition
        consolePos.X = pos.x;
        consolePos.Y = pos.y + (SHORT)i; // Cast i to SHORT

        // Basic boundary check for drawing (adjust Y limit if needed)
        if (consolePos.Y < 0 || consolePos.Y >= 100) continue;

        SetConsoleCursorPosition(hConsole, consolePos);
        cout << artBoss[i];
    }
}

// Helper to clear the boss art area at a specific Position
void clearBossArt(HANDLE hConsole, Position pos) { // Takes Position
    COORD consolePos;
     for (size_t i = 0; i < 5; i++)
    {
        // Convert Position to COORD for SetConsoleCursorPosition
        consolePos.X = pos.x;
        consolePos.Y = pos.y + (SHORT)i; // Cast i to SHORT

        // Basic boundary check for clearing (adjust Y limit if needed)
        if (consolePos.Y < 0 || consolePos.Y >= 100) continue;

        SetConsoleCursorPosition(hConsole, consolePos);
        cout << "     "; // Assuming boss width is 5
    }
}

// Draws the bounding box for the boss room
void printBossRoom() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO windowSize;
    GetConsoleScreenBufferInfo(hConsole, &windowSize);
    COORD pos;

    // Draw vertical walls
    for (SHORT i = 0; i < windowSize.dwSize.Y; i++) {
        pos = {0, i};
        SetConsoleCursorPosition(hConsole, pos);
        cout << "\u2588";
        pos = {(SHORT)(windowSize.dwSize.X - 1), i};
        SetConsoleCursorPosition(hConsole, pos);
        cout << "\u2588";
    }
    // Draw horizontal walls
    for (SHORT i = 0; i < windowSize.dwSize.X; i++) {
        pos = {i, 0};
        SetConsoleCursorPosition(hConsole, pos);
        cout << "\u2588";
        pos = {i, (SHORT)(windowSize.dwSize.Y - 1)};
        SetConsoleCursorPosition(hConsole, pos);
        cout << "\u2588";
    }
}


// --- Main Boss Update Logic ---
// Takes the map (for boss enemy data), player's position, and console handle
void updateBoss(map &mapCurrent, Position playerPos, HANDLE &hConsole , int &health) 
{
    enemy &boss = mapCurrent.enemyList[0]; // Get a reference to the boss enemy struct
    int moveDirX = 0, moveDirY = 0; // Boss movement direction this frame
    CONSOLE_SCREEN_BUFFER_INFO windowSize;
    GetConsoleScreenBufferInfo(hConsole, &windowSize);
    static bool bossInitialized = false; // Simple static flag for demo
    if (!bossInitialized || (boss.position.x == 0 && boss.position.y == 0)) // Check if needs init
    {
        boss.position.x = (windowSize.dwSize.X / 2) - 2; // Center X, offset by half width
        boss.position.y = (windowSize.dwSize.Y / 2) - 2; // Center Y, offset by half height
        drawBossArt(hConsole, boss.position); // Initial draw
        bossIsAttacking = false; // Ensure not attacking on init
        bossAttackCooldown = BOSS_ATTACK_COOLDOWN_FRAMES / 2; // Start with some cooldown
        bossInitialized = true; // Mark as initialized for this run
        boss.health = 500; // Set initial health
        boss.damage = 25;  // Set boss damage
        boss.c = 'B';      // Optional: Change boss character representation if needed
        // Center the boss (consider its art size 5x5)
        boss.position.x = (windowSize.dwSize.X / 2) - 2; // Center X, offset by half width
        boss.position.y = (windowSize.dwSize.Y / 2) - 2; // Center Y, offset by half height
        drawBossArt(hConsole, boss.position); // Initial draw
        bossIsAttacking = false; // Ensure not attacking on init
        bossAttackCooldown = BOSS_ATTACK_COOLDOWN_FRAMES / 2; // Start with some cooldown
    }

    // --- Get Boss Reference ---
    // Assuming enemyList[0] is always the boss in the boss room map
    if (mapCurrent.enemyList == nullptr || mapCurrent.maxEnemy == 0) {
         // Should not happen if map is initialized correctly for boss room
         return;
    }

    // --- Boss State Check ---
    if (boss.health <= 0) {
        if (boss.position.x != -1) { // If not already marked as dead/removed
             clearBossArt(hConsole, boss.position);
             boss.position = {-1, -1}; // Mark as dead/removed
             // Maybe trigger win condition or score update here
             // gameSaved.points += 500; // Example
        }
         return; // No more updates if dead
    }

    // --- Boss Initialization (First time update in this room) ---
    // Use a flag or check position/health to initialize only once per room entry
    
    // --- End Boss Initialization ---

    Position previousBossPos = boss.position; // Store position before any movement

    // --- Projectile Logic ---
    if (bossIsAttacking)
    {
        COORD prevProjectilePos = bossProjectilePosition; // Store previous projectile position (Type: COORD)

        // Move projectile based on its stored direction
        bossProjectilePosition.X += bossProjectileMoveDirection.X;
        bossProjectilePosition.Y += bossProjectileMoveDirection.Y;

        // Check for collisions (Using COORD.X/Y and Position.x/y)
        bool hitWall = bossProjectilePosition.X <= 0 || bossProjectilePosition.X >= windowSize.dwSize.X - 1 ||
                       bossProjectilePosition.Y <= 0 || bossProjectilePosition.Y >= windowSize.dwSize.Y - 1;

        // Check collision with player (COORD vs Position)
        // Player's position is a single point '@'
        bool hitPlayer = bossProjectilePosition.X == playerPos.x && bossProjectilePosition.Y == playerPos.y;

        if (hitWall || hitPlayer)
        {
            bossIsAttacking = false; // Stop the attack
            clearConsolePosition(hConsole, prevProjectilePos); // Clear the last valid spot

            if (hitPlayer) {
                // Player takes damage - Requires access to player object or a damage function
                health -= boss.damage;
                Beep(200, 150); // Hit sound
                 // You MUST implement the actual damage dealing to the player here
            }
            bossAttackCooldown = BOSS_ATTACK_COOLDOWN_FRAMES; // Start cooldown after attack ends
        }
        else
        {
            // Clear previous spot and draw new spot
            clearConsolePosition(hConsole, prevProjectilePos);
            SetConsoleCursorPosition(hConsole, bossProjectilePosition); // Takes COORD
            cout << BOSS_PROJECTILE_CHAR; // Draw projectile
        }
    }
    // --- End Projectile Logic ---


    // --- Boss Movement & Attack Decision ---
    // Boss only moves or decides to attack if not currently firing a projectile
    if (!bossIsAttacking)
    {
        // Decrease cooldown timer
        if (bossAttackCooldown > 0) {
            bossAttackCooldown--;
        }

        // Calculate direction towards player (using Position.x/y)
        // Simple direct pathfinding
        if (boss.position.y < playerPos.y) moveDirY = 1;
        else if (boss.position.y > playerPos.y) moveDirY = -1;
        else moveDirY = 0;

        if (boss.position.x < playerPos.x) moveDirX = 1;
        else if (boss.position.x > playerPos.x) moveDirX = -1;
        else moveDirX = 0;

        // --- Attack Decision ---
        // Only attack if cooldown is over and random chance hits
        if (bossAttackCooldown <= 0 && (rand() % 100 < BOSS_ATTACK_CHANCE))
        {
            bossIsAttacking = true;

            // Start projectile near boss center (adjust offset as needed)
            // Convert boss Position to COORD for projectile start
            bossProjectilePosition.X = boss.position.x + 2; // Approx center X of 5-wide sprite
            bossProjectilePosition.Y = boss.position.y + 2; // Approx center Y of 5-high sprite

            // Set projectile direction (store the calculated moveDirX/Y)
            // This direction is fixed for the duration of the projectile's flight
            bossProjectileMoveDirection.X = (SHORT)moveDirX;
            bossProjectileMoveDirection.Y = (SHORT)moveDirY;

            // Ensure projectile moves even if perfectly aligned (prevent getting stuck)
            if (bossProjectileMoveDirection.X == 0 && bossProjectileMoveDirection.Y == 0) {
                 // If directly on player, fire randomly (e.g., horizontal)
                 bossProjectileMoveDirection.X = (rand() % 2 == 0) ? 1 : -1;
                 bossProjectileMoveDirection.Y = 0; // Or make this random too
            }

             Beep(800, 50); // Attack wind-up sound

            // Don't move the boss in the same frame it decides to attack
            moveDirX = 0;
            moveDirY = 0;
        }
        // --- End Attack Decision ---
        else // If not attacking this frame, attempt to move
        {
             // Calculate Boss's *next* potential position (Type: Position)
            Position nextPos = boss.position;
            nextPos.x += moveDirX;
            nextPos.y += moveDirY;
            // if (nextPos.x <= )
            // {
            //     /* code */
            // }
            
            // Basic Boss Collision with Walls (adjust for boss size 5x5)
            // Check boundaries using the next potential position
            // Boss top-left is at nextPos.x, nextPos.y
            // Boss bottom-right is at nextPos.x + 4, nextPos.y + 4
            if (nextPos.x <= 0 || nextPos.x + 4 >= windowSize.dwSize.X - 1 ) {
                moveDirX = 0; // Stop horizontal movement if hitting side walls
            }
            if (nextPos.y <= 0 || nextPos.y + 4 >= windowSize.dwSize.Y - 1 ) {
                moveDirY = 0; // Stop vertical movement if hitting top/bottom walls
            }

            // Add collision check with player? (Optional: prevent boss overlapping player)
            // This requires checking the player's position against the boss's bounding box
            bool overlapsPlayer = (playerPos.x >= nextPos.x && playerPos.x <= nextPos.x + 4 &&
                                  playerPos.y >= nextPos.y && playerPos.y <= nextPos.y + 4);
            if (overlapsPlayer) {
                moveDirX = 0;
                moveDirY = 0;
            }


            // Update boss position (Type: Position) if movement is allowed
            boss.position.x += moveDirX;
            boss.position.y += moveDirY;
        }
    }
    // --- End Boss Movement & Attack Decision ---


    // --- Drawing ---
    // Clear previous boss position only if it moved
    if (previousBossPos.x != boss.position.x || previousBossPos.y != boss.position.y) {
       clearBossArt(hConsole, previousBossPos); // Use Position
    }

    // Draw boss at its new position (if alive)
    if(boss.health > 0 && boss.position.x != -1) {
        drawBossArt(hConsole, boss.position); // Use Position
    }
    // --- End Drawing ---
}
