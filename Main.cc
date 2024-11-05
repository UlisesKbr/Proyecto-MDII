#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

class BuckshotShotgun {
private:
    int chamberSize;
    std::vector<bool> chamber;
    int currentPosition;
    bool isSpinning;

public:
    BuckshotShotgun(int size) : chamberSize(size), isSpinning(true) {
        srand(time(0));
        chamber.resize(chamberSize);
        spinChamber();
    }

    void spinChamber() {
        std::fill(chamber.begin(), chamber.end(), false); 
        int bulletIndex = rand() % chamberSize;          
        chamber[bulletIndex] = true;
        currentPosition = 0;
    }

    void advanceChamber() {
        currentPosition = (currentPosition + 1) % chamberSize;
    }

    bool playerTurn(bool isTargetPlayer) {
        bool isLosingShot = chamber[currentPosition];

        if (isSpinning) {
            spinChamber();
        } else {
            advanceChamber();
        }

        return isLosingShot;  
    }

    void setSpinning(bool spin) {
        isSpinning = spin;
    }

    bool isCurrentPositionLosingShot() {
        return chamber[currentPosition];
    }

    int bulletsRemaining() {
        return std::count(chamber.begin(), chamber.end(), true);
    }
};

void playGame(int mode) {
    int chamberSize = 6;
    BuckshotShotgun game(chamberSize);

    std::string choice;
    int lives[2] = {2, 2};  
    bool isAlive[2] = {true, true};  
    int roundsSurvived = 0;

    std::cout << "Iniciando partida...\n";

    while (isAlive[0] && isAlive[1]) {
        std::cout << "\n--- Ronda " << roundsSurvived + 1 << " ---" << std::endl;
        std::cout << "Balas restantes en el tambor: " << game.bulletsRemaining() << "\n";
        std::cout << "Vidas restantes - Jugador 1: " << lives[0] << ", Jugador 2: " << lives[1] << "\n";

        if (mode == 1) {
            // Turno del Jugador 1
            std::cout << "Jugador 1, ¿quieres dispararte a ti mismo o al Jugador 2? (mismo/otro): ";
            std::cin >> choice;
            bool isTargetPlayer = (choice == "mismo");
            game.setSpinning(isTargetPlayer);

            bool shotResult = game.playerTurn(isTargetPlayer);
            if (shotResult) {
                if (isTargetPlayer) {
                    std::cout << "¡BOOM! Jugador 1 ha perdido una vida en la ronda " << roundsSurvived + 1 << ".\n";
                    lives[0]--;
                    if (lives[0] <= 0) isAlive[0] = false;
                } else {
                    std::cout << "¡BOOM! Jugador 2 ha perdido una vida en la ronda " << roundsSurvived + 1 << ".\n";
                    lives[1]--;
                    if (lives[1] <= 0) isAlive[1] = false;
                }
            } else {
                std::cout << "¡Clic! No hubo disparo fatal.\n";
                roundsSurvived++;
            }

        } else if (mode == 2) {
            std::cout << "Jugador, ¿quieres dispararte a ti mismo o a la computadora? (mismo/compu): ";
            std::cin >> choice;
            bool isTargetPlayer = (choice == "mismo");
            game.setSpinning(isTargetPlayer);

            bool shotResult = game.playerTurn(isTargetPlayer);
            if (shotResult) {
                if (isTargetPlayer) {
                    std::cout << "¡BOOM! Has perdido una vida en la ronda " << roundsSurvived + 1 << ".\n";
                    lives[0]--;
                    if (lives[0] <= 0) isAlive[0] = false;
                } else {
                    std::cout << "¡BOOM! La computadora ha perdido una vida en la ronda " << roundsSurvived + 1 << ".\n";
                    lives[1]--;
                    if (lives[1] <= 0) isAlive[1] = false;
                }
            } else {
                std::cout << "¡Clic! No hubo disparo fatal.\n";
                roundsSurvived++;

                bool computerChoice = (rand() % 2 == 0);
                std::cout << "La computadora decide " << (computerChoice ? "dispararse a sí misma." : "disparar al jugador.") << std::endl;
                game.setSpinning(computerChoice);

                if (game.isCurrentPositionLosingShot()) {
                    if (computerChoice) {
                        std::cout << "¡BOOM! La computadora ha perdido una vida.\n";
                        lives[1]--;
                        if (lives[1] <= 0) isAlive[1] = false;
                    } else {
                        std::cout << "¡BOOM! El jugador ha perdido una vida.\n";
                        lives[0]--;
                        if (lives[0] <= 0) isAlive[0] = false;
                    }
                } else {
                    std::cout << "¡Clic! La computadora también ha sobrevivido esta ronda.\n";
                }
            }
        }
    }

    if (!isAlive[0]) {
        std::cout << "\nJugador 1 ha perdido todas sus vidas. Fin del juego.\n";
    } else if (!isAlive[1]) {
        std::cout << "\nJugador 2 o la computadora ha perdido todas sus vidas. Fin del juego.\n";
    }
}

int main() {
    int mode;
    while (true) {
        std::cout << "\n--- Bienvenido a Buckshot Shotgun ---" << std::endl;
        std::cout << "Sobrevive cada ronda para ganar." << std::endl;
        std::cout << "Elige el modo de juego:\n1. Dos jugadores\n2. Contra la computadora\n3. Salir del juego\n";
        std::cout << "Modo: ";
        std::cin >> mode;

        if (mode == 3) {
            break;
        }

        playGame(mode);
    }

    std::cout << "Gracias por jugar a Buckshot Shotgun. ¡Hasta la próxima!\n";
    return 0;
}
