#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <filesystem>
#include <unordered_set>
#include <map>
#include <list>
#include <thread>
#include <functional>

namespace fs = std::filesystem;

// Simple Lexer
std::vector<std::string> tokenize(const std::string& source) {
    std::vector<std::string> tokens;
    std::regex token_regex(R"(class|extends|operator|public|private|static|virtual|bool|int|float|double|string|Vector2|Vector3|void|import|list|map|thread|lambda|struct|enum|return|if|else|for|while|break|continue|new|delete|\{|\}|\(|\)|,|;|=|\+|-|\*|\/|[a-zA-Z_][a-zA-Z0-9_]*)");
    std::sregex_iterator it(source.begin(), source.end(), token_regex);
    std::sregex_iterator end;
    while (it != end) {
        tokens.push_back(it->str());
        ++it;
    }
    return tokens;
}

// Basic Parser & Code Generator (Source-to-Source Translation)
std::pair<std::string, std::string> generateCpp(const std::vector<std::string>& tokens, const std::string& filename) {
    std::string headerOutput = "#ifndef " + filename + "_H\n#define " + filename + "_H\n\n";
    headerOutput += "#include <memory>\n#include <string>\n#include <vector>\n#include <iostream>\n#include <map>\n#include <list>\n#include <thread>\n#include <functional>\n\n";

    std::string sourceOutput = "#include \"" + filename + ".h\"\n\n";

    bool inClass = false;
    std::string currentClass;
    bool inFunction = false;
    std::string functionReturnType;
    std::string functionName;
    std::string functionParams;
    std::string functionBody;
    std::unordered_set<std::string> includedLibraries;

    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i] == "import") {
            std::string libraryName = tokens[i + 1];
            if (includedLibraries.find(libraryName) == includedLibraries.end()) {
                sourceOutput = "#include <" + libraryName + ".h>\n" + sourceOutput;
                includedLibraries.insert(libraryName);
            }
            i++;
        } else if (tokens[i] == "class" || tokens[i] == "struct" || tokens[i] == "enum") {
            currentClass = tokens[i + 1];
            headerOutput += tokens[i] + " " + currentClass + " {\npublic:\n";
            headerOutput += "    " + currentClass + "();\n    ~" + currentClass + "();\n";
            sourceOutput += currentClass + "::" + currentClass + "() {\n    std::cout << \"Constructor for " + currentClass + "\" << std::endl;\n}\n\n";
            sourceOutput += currentClass + "::~" + currentClass + "() {\n    std::cout << \"Destructor for " + currentClass + "\" << std::endl;\n}\n\n";
            inClass = true;
            i++;
        } else if (tokens[i] == "new") {
            functionBody += "new " + tokens[i + 1] + "(); ";
            i++;
        } else if (tokens[i] == "delete") {
            functionBody += "delete " + tokens[i + 1] + "; ";
            i++;
        } else if (tokens[i] == "public" || tokens[i] == "private") {
            headerOutput += tokens[i] + ":\n";
        } else if (inClass && (tokens[i] == "int" || tokens[i] == "float" || tokens[i] == "double" || tokens[i] == "string" || tokens[i] == "bool" || tokens[i] == "void" || tokens[i] == "vector" || tokens[i] == "map")) {
            functionReturnType = tokens[i];
            functionName = tokens[i + 1];
            functionParams = "";
            i += 2;
            while (i < tokens.size() && tokens[i] != "{") {
                functionParams += tokens[i] + " ";
                i++;
            }
            headerOutput += "    " + functionReturnType + " " + functionName + "(" + functionParams + ");\n";
            sourceOutput += functionReturnType + " " + currentClass + "::" + functionName + "(" + functionParams + ") {\n";
            inFunction = true;
            functionBody = "";
        } else if (inFunction) {
            if (tokens[i] == "}") {
                sourceOutput += functionBody + "\n}\n\n";
                inFunction = false;
            }
            else if (tokens[i] == "cout") {  // Handling cout
                functionBody += "std::cout << ";
                i++; // Move to the next token (the output value)
                while (i < tokens.size() && tokens[i] != ";") { // Output until semicolon
                    functionBody += tokens[i] + " ";
                    i++;
                }
                functionBody += "; "; // Add the semicolon.
            }
            else {
                functionBody += tokens[i] + " ";
            }
        } else if (tokens[i] == "}") {
            headerOutput += "};\n\n";
            inClass = false;
        }
    }
    headerOutput += "#endif\n";
    return {headerOutput, sourceOutput};
}

// Compile Function
void compileToBin() {
    std::unordered_set<std::string> processedFiles;
    fs::create_directory("bin");
    for (const auto& entry : fs::directory_iterator(".")) {
        if (entry.path().extension() == ".fl") {
            std::ifstream file(entry.path());
            if (!file.is_open()) {
                std::cerr << "Error: Could not open " << entry.path() << std::endl;
                continue;
            }
            std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            file.close();

            std::vector<std::string> tokens = tokenize(source);
            std::string filename = entry.path().stem().string();
            auto [headerCode, sourceCode] = generateCpp(tokens, filename);

            std::ofstream outHeader("bin/" + filename + ".h");
            outHeader << headerCode;
            outHeader.close();

            std::ofstream outSource("bin/" + filename + ".cpp");
            outSource << sourceCode;
            outSource.close();

            processedFiles.insert(filename);
        }
    }

    std::cout << "Compiling generated C++ files...\n";
        #if defined(_WIN32)
        system("g++ bin/*.cpp -o bin/game.exe -lglfw3 -lopengl32 -lgdi32");
    #elif defined(__APPLE__)
        system("g++ bin/*.cpp -o bin/game -framework OpenGL -lglfw");
    #elif defined(__linux__)
        system("g++ bin/*.cpp -o bin/game -lglfw -lGL");
    #endif
    std::cout << "Compilation finished! Executable saved in bin/game\n";
}
