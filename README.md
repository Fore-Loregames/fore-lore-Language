# **Fore-Lore (.fl) Language API Usage Guide**

## **📌 Introduction**
Fore-Lore (`.fl`) is a high-level language that compiles directly to C++ code. It simplifies memory management and provides a structured way to write object-oriented programs while maintaining the flexibility of C++.
I made this to simplify my workflows into a more C# style coding with C++. Might be buggy. Working on clion and vscode plugins.
This guide covers how to:
- Write `.fl` scripts
- Use classes, functions, and variables
- Manage memory (`new`, `delete`)
- Use `std::cout` for debugging
- Compile and execute the `.fl` scripts

---

## **📂 Writing & Organizing `.fl` Files**
Each `.fl` script should be placed inside the project directory. The compiler will process all `.fl` files and generate C++ `.h` and `.cpp` files inside the `bin/` folder.

#### **📝 Example: Creating a Class**
```fl
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
```

---

## **📌 Variables & Data Types**
Fore-Lore supports the following data types:
| Type        | Example               | Notes                        |
|------------|-----------------------|------------------------------|
| `int`      | `int x = 5;`          | Integer values               |
| `float`    | `float y = 3.14;`      | Floating point values        |
| `double`   | `double z = 1.2345;`   | Higher precision float       |
| `bool`     | `bool flag = true;`    | Boolean values (true/false)  |
| `string`   | `string name = "Ivy";` | Text values                  |
| `Vector2`  | `Vector2 pos;`        | (x, y) coordinate            |
| `Vector3`  | `Vector3 position;`    | (x, y, z) coordinate         |

---

## **📌 Functions & Methods**
Functions must be declared inside classes or globally.

#### **📝 Example: Method with Parameters**
```fl
class Game {
public:
    void printMessage(string msg) {
        cout msg;
    }
}
```

---

## **📌 Memory Management (`new`, `delete`)**
Objects can be dynamically allocated and destroyed.

#### **📝 Example: Creating & Deleting Objects**
```fl
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
```

---

## **📌 Control Flow (`if`, `else`, `while`, `for`)**
#### **📝 Example: Conditionals**
```fl
void checkHealth(int health) {
    if (health > 50) {
        cout "Player is healthy";
    } else {
        cout "Player is injured";
    }
}
```

#### **📝 Example: Loops**
```fl
void countToFive() {
    for (int i = 1; i <= 5; i++) {
        cout i;
    }
}
```

---

## **📌 Using `std::cout` for Debugging**
`std::cout` is fully supported in Fore-Lore using the `cout` keyword.

#### **📝 Example: Debugging Messages**
```fl
void debug() {
    cout "Debugging works!";
}
```

---

## **📌 Importing Libraries (`import glfw;`)**
Fore-Lore allows importing standard libraries.  
For example:
```fl
import glfw;
import iostream;
```

---

## **📌 Compiling & Running the Code**
After writing `.fl` scripts, run:
```sh
./compiler
```
This will:
1. Parse all `.fl` files.
2. Generate `.h` and `.cpp` files in `bin/`.
3. Compile everything into an executable (`bin/game`).

---

## **📌 Full Example: A Simple Game**
```fl
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
```

---

## **📌 Conclusion**
✅ Fore-Lore (`.fl`) is now fully functional and can be used to build **C++ applications** with:
- **Automatic memory management**
- **Object-oriented programming**
- **Simplified C++ syntax**
- **Cross-platform compilation**

🚀 **Now you can start developing games and applications using `.fl`!**
