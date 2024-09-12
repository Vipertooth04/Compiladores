#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;


// Definición de los diferentes tipos de tokens basados en los tokens proporcionados
enum TokenType {
    TOKEN_ID, TOKEN_DECLAR, TOKEN_ASIG, TOKEN_DELIM_SC, TOKEN_DELIM_B_O,
    TOKEN_DELIM_B_C, TOKEN_DELIM_P_O, TOKEN_DELIM_P_C, TOKEN_OPER_SUM,
    TOKEN_OPER_REST, TOKEN_OPER_EX, TOKEN_OPER_EXP, TOKEN_OPER_MUL,
    TOKEN_OPER_DIV, TOKEN_OPER_MOD, TOKEN_OPER_MENOR, TOKEN_OPER_MAYOR,
    TOKEN_OPER_S_SUMA, TOKEN_OPER_S_RESTA, TOKEN_OPER_MAY_E, TOKEN_OPER_MEN_E,
    TOKEN_OPER_COMP_E, TOKEN_OPER_COMP_D, TOKEN_OPER_AND, TOKEN_OPER_OR,
    TOKEN_COMEN, TOKEN_COMEN_OPEN, TOKEN_COMEN_CLOSE, TOKEN_UNKNOWN, TOKEN_EOF
};


// Estructura para representar un token
struct Token {
    TokenType type;   // Tipo de token (keyword, identifier, etc.)
    string value;  // Valor del token
    int line;           // Línea del token
    int column;         // Columna del token
};


string buffer;
int bufferIndex = 0;
int currentLine = 0;
int currentColumn = 0;
char currentChar = '\0';


bool loadFileIntoBuffer(string filename) {
    ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    buffer.assign((istreambuf_iterator<char>(file)), //
        (istreambuf_iterator<char>()));

    file.close();
    return true;
}


// Función getchar: Lee el siguiente carácter del buffer
char Mi_getchar() {
    if (bufferIndex < buffer.size()) {
        currentChar = buffer[bufferIndex++];
        if (currentChar == '\n') {
            currentLine++;
            currentColumn = 1;
        }
        else {
            currentColumn++;
        }
    }
    else {
        currentChar = '\0';  // Fin del buffer
    }
    return currentChar;
}

char peekchar() {
    if (bufferIndex<buffer.size())
    {
        return buffer[bufferIndex];
    }
    else {
        return '\0';
    }
}

void SkipWhiteSpace() {
    if (isspace(currentChar))
    {
        getchar();
    }
}

//Identificar ID o Numeros
Token readIDorNumber() {
    string value;
    while (isalnum(currentChar) || currentChar == '_')
    {
        value += currentChar;
        Mi_getchar();
    }

    //retrocedemos un caracter ya que hemos leido uno mas
    bufferIndex--;
    currentColumn--;

    return{TOKEN_ID, value, currentLine, currentColumn};
}


// Función para leer delimitadores
Token readDelimiter() {
    std::string value;
    value += currentChar;

    switch (currentChar) {
    case ';': return { TOKEN_DELIM_SC, value, currentLine, currentColumn };
    case '[': return { TOKEN_DELIM_B_O, value, currentLine, currentColumn };
    case ']': return { TOKEN_DELIM_B_C, value, currentLine, currentColumn };
    case '(': return { TOKEN_DELIM_P_O, value, currentLine, currentColumn };
    case ')': return { TOKEN_DELIM_P_C, value, currentLine, currentColumn };
    case ':': return { TOKEN_DECLAR, value, currentLine, currentColumn };
    case '=': return { TOKEN_ASIG, value, currentLine, currentColumn };
    default: return { TOKEN_UNKNOWN, value, currentLine, currentColumn };
    }
}

Token getToken() {
    SkipWhiteSpace();

    if (currentChar=='\0')
    {
        return{ TOKEN_EOF,"",currentLine,currentColumn };
    }


    //Palabras reservadas

    // Identificadores o números
    if (isalpha(currentChar) || currentChar == '_') {
        return readIDorNumber();
    }

    // Delimitadores
    if (currentChar == ';' || currentChar == '[' || currentChar == ']' ||
        currentChar == '(' || currentChar == ')' || currentChar == ':') {
        return readDelimiter();
    }

    //Operadores

    //Comentarios

    


    Mi_getchar();

}

int main() {
    std::string filename = "codigo.txt";  // Archivo de código fuente
    if (!loadFileIntoBuffer(filename)) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }

   Mi_getchar();  // Inicializa la lectura con el primer carácter del buffer

    Token token;
    /*while ((token = gettoken()).type != TOKEN_EOF) {
        std::cout << "Token: " << token.value << ", Tipo: " << token.type
            << ", Línea: " << token.line << ", Columna: " << token.column << std::endl;
    }*/

    return 0;
}