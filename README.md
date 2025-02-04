Fore-Lore (.fl) Language API Usage Guide
📌 Introduction
Fore-Lore (.fl) is a high-level language that compiles directly to C++ code. It simplifies memory management and provides a structured way to write object-oriented programs while maintaining the flexibility of C++.

This guide covers how to:

Write .fl scripts
Use classes, functions, and variables
Manage memory (new, delete)
Use std::cout for debugging
Compile and execute the .fl scripts
📂 Writing & Organizing .fl Files
Each .fl script should be placed inside the project directory. The compiler will process all .fl files and generate C++ .h and .cpp files inside the bin/ folder.

📝 Example: Creating a Class
fl
Copy
Edit
class Player {
public:
    int health;
    string name;
    
    Player() {
        cout "Player created";
    }
    
    void takeDamage(int amount) {
        health = health - amount;
        cout "Player took damage";
    }
}
💡 How It Translates to C++

cpp
Copy
Edit
#include "Player.h"

Player::Player() {
    std::cout << "Player created" << std::endl;
}

void Player::takeDamage(int amount) {
    health = health - amount;
    std::cout << "Player took damage" << std::endl;
}
📌 Variables & Data Types
Fore-Lore supports the following data types:

Type	Example	Notes
int	int x = 5;	Integer values
float	float y = 3.14;	Floating point values
double	double z = 1.2345;	Higher precision float
bool	bool flag = true;	Boolean values (true/false)
string	string name = "Ivy";	Text values
Vector2	Vector2 pos;	(x, y) coordinate
Vector3	Vector3 position;	(x, y, z) coordinate
📌 Functions & Methods
Functions must be declared inside classes or globally.

📝 Example: Method with Parameters
fl
Copy
Edit
class Game {
public:
    void printMessage(string msg) {
        cout msg;
    }
}
💡 C++ Translation

cpp
Copy
Edit
#include "Game.h"

void Game::printMessage(std::string msg) {
    std::cout << msg << std::endl;
}
📌 Memory Management (new, delete)
Objects can be dynamically allocated and destroyed.

📝 Example: Creating & Deleting Objects
fl
Copy
Edit
class Enemy {
public:
    int damage;
    
    Enemy() {
        cout "Enemy created";
    }
    
    ~Enemy() {
        cout "Enemy destroyed";
    }
}

void spawnEnemy() {
    Enemy* e = new Enemy();
    delete e;
}
💡 C++ Translation

cpp
Copy
Edit
#include "Enemy.h"

Enemy::Enemy() {
    std::cout << "Enemy created" << std::endl;
}

Enemy::~Enemy() {
    std::cout << "Enemy destroyed" << std::endl;
}

void spawnEnemy() {
    Enemy* e = new Enemy();
    delete e;
}
📌 Control Flow (if, else, while, for)
📝 Example: Conditionals
fl
Copy
Edit
void checkHealth(int health) {
    if (health > 50) {
        cout "Player is healthy";
    } else {
        cout "Player is injured";
    }
}
💡 C++ Translation

cpp
Copy
Edit
void checkHealth(int health) {
    if (health > 50) {
        std::cout << "Player is healthy" << std::endl;
    } else {
        std::cout << "Player is injured" << std::endl;
    }
}
📝 Example: Loops
fl
Copy
Edit
void countToFive() {
    for (int i = 1; i <= 5; i++) {
        cout i;
    }
}
💡 C++ Translation

cpp
Copy
Edit
void countToFive() {
    for (int i = 1; i <= 5; i++) {
        std::cout << i << std::endl;
    }
}
📌 Using std::cout for Debugging
std::cout is fully supported in Fore-Lore using the cout keyword.

📝 Example: Debugging Messages
fl
Copy
Edit
void debug() {
    cout "Debugging works!";
}
💡 C++ Translation

cpp
Copy
Edit
void debug() {
    std::cout << "Debugging works!" << std::endl;
}
📌 Importing Libraries (import glfw;)
Fore-Lore allows importing standard libraries.
For example:

fl
Copy
Edit
import glfw;
import iostream;
💡 C++ Translation

cpp
Copy
Edit
#include <glfw.h>
#include <iostream>
📌 Compiling & Running the Code
After writing .fl scripts, run:

sh
Copy
Edit
./compiler
This will:

Parse all .fl files.
Generate .h and .cpp files in bin/.
Compile everything into an executable (bin/game).
📌 Full Example: A Simple Game
fl
Copy
Edit
import iostream;

class Player {
public:
    string name;
    int health;
    
    Player(string pname) {
        name = pname;
        health = 100;
        cout "Player " + name + " created";
    }
    
    void takeDamage(int damage) {
        health -= damage;
        if (health <= 0) {
            cout name + " has died.";
        } else {
            cout name + " took " + damage + " damage.";
        }
    }
}

void main() {
    Player p = new Player("Ivy");
    p.takeDamage(30);
    p.takeDamage(80);
    delete p;
}
💡 C++ Translation

cpp
Copy
Edit
#include "Player.h"

Player::Player(std::string pname) {
    name = pname;
    health = 100;
    std::cout << "Player " << name << " created" << std::endl;
}

void Player::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        std::cout << name << " has died." << std::endl;
    } else {
        std::cout << name << " took " << damage << " damage." << std::endl;
    }
}

int main() {
    Player* p = new Player("Ivy");
    p->takeDamage(30);
    p->takeDamage(80);
    delete p;
    return 0;
}
📌 Conclusion
✅ Fore-Lore (.fl) is now fully functional and can be used to build C++ applications with:

Automatic memory management
Object-oriented programming
Simplified C++ syntax
Cross-platform compilation
🚀 Now you can start developing games and applications using .fl!
