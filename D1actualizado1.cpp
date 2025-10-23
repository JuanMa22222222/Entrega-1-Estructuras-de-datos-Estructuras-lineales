/**
 * @file D1.cpp
 * @author Juan Bohorquez (jbohorquezsa@unal.edu.co)
 * @author Julian Quintero (julquinteroca@unal.edu.co)
 * @author Santiago Herrera (sanherrerapa@unal.edu.co)
 * 
 * @brief Inicio del programa. Declaracion de bibliotecas
 * @version 0.1
 * @date 2025-10-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <iostream>  // Estandar, entrada y salida de datos mediante cin y cout
#include <stack>     // Estructura Pila
#include <queue>     // Estructura de cola y cola con prioridad
#include <string>    // Para usar los string
#include <vector>    // Permite usar vectores dinamicos
#include <cstdlib>   // rand(), srand() y otras funciones de utilidad
#include <ctime>     // Sirve para usar el time()
#include <thread>    // Permite generar hilos de ejecucion
#include <chrono>    // Se usa en conjunto con la libreria thread para pausas y tiempos
#include <cctype>    // Sirve para usar la funcion toupper y tolower
#include <limits>    // Sirve para usar la funcion numeric_limits para limpiar cin
#include <tuple>     // Para usar tuplas

#ifdef _WIN32
  #include <windows.h> // si se corre en windows, sirve para manipular la consola del sistema
#endif

using namespace std;

/**
 * @brief Declarar los colores que apareceran en la consola
 * 
 */
const string ANS_RESET   = "\033[0m";
const string ANS_BOLD    = "\033[1m";
const string ANS_RED     = "\033[31m";
const string ANS_GREEN   = "\033[32m";
const string ANS_YELLOW  = "\033[33m";
const string ANS_BLUE    = "\033[34m";
const string ANS_MAGENTA = "\033[35m";
const string ANS_CYAN    = "\033[36m";
const string ANS_WHITE   = "\033[37m"; // codigos ansi para color y formato

/**
 * @brief Efecto de impresion lenta
 * 
 * @param s Cada caracter que se imprime
 * @param ms Tiempo en milisegundos
 */
void slowPrint(const string &s, int ms = 3) {   // funcion que genera una escritura mas lenta
    for (char c : s) {        //Para cada variable "char" en c (que es la misma cadena de texto s)
        cout << c << flush;     //Imprimir el caracter
        if (ms > 0) this_thread::sleep_for(chrono::milliseconds(ms));       //Hacer que cada caracter se imprima un periodo de ms milisegundos (en este caso son 3)
    }
}

/**
 * @brief Funcion para reconocer los codigos ANSI en windows (se ignora en windows o macOS)
 * 
 */
void enableVirtualTerminalProcessingOnWindows() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

/**
 * @brief Funcion para limpiar la pantalla y colocar el cursor al inicio
 * 
 */
void clearScreen() {

    cout << "\033[2J\033[H";
}

/**
 * @brief Funcion que espera a que el usuario presione enter para continuar
 * 
 */
void waitForEnter() {
    cout << ANS_BOLD << ANS_CYAN << "\nPresiona Enter para continuar..." << ANS_RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');      //Ignora cualquier enter anterior al mensaje limpiando el buffer

    if (!cin.good()) return;
    string dummy;
    getline(cin, dummy);      //Lee una linea vacia
}


/**
 * @brief CLASE CARRITO DE COMPRAS (PILA)
 * 
 */
class CarritoDeCompras {
private:
    stack<string> pila; // atributo de pila para almacenar productos
    string nombreCliente; // atributo para identificar de quién es el carrito

public:
    CarritoDeCompras(const string& nombre = "") : nombreCliente(nombre) {} //Constructor para un carrito con o sin nombre
    
    /**
     * @brief Meter elementos al carro de compras
     * 
     * @param producto Texto que respresenta el producto metido al carrito
     */
    void push(const string& producto) {       // agregar producto al carrito por el frente
        pila.push(producto);      // comando que inserta un producto en la parte superior de la pila
        cout << "Agregado al carro de " << nombreCliente << ": " << producto << "\n";
    }

    /**
     * @brief Eliminar el ultimo elemento insertado al carro de compras
     * 
     */
    void pop() {
        if (!pila.empty()) {      // verificacion de que no este vacia
            cout << "Sacando del carro de " << nombreCliente << ": " << pila.top() << "\n";       // Obtiene la referencia del producto sin eliminarlo
            pila.pop();       // elimina el producto de la pila
        } else {      // verificacion si el carro esta vacio
            cout << "El carro de " << nombreCliente << " está vacío.\n";
        }
    }

    /**
     * @brief Atributo que devuelve true si la pila esta vacia
     * 
     * @return true Si esta vacio
     * @return false Si tiene algun elemento
     */
    bool empty() const {
        return pila.empty();
    }

    size_t size() const {       // Devuelve la cantidad de elementos de la pila
        return pila.size();
    }

    stack<string> getProductos() const {      // Devuelve una copia del stack sin alterar el original
        return pila;
    }

    /**
     * @brief Metodo para imprimir productos sin editar la pila original
     * 
     */
    void mostrarProductos() {
        cout << "Productos en el carrito de " << nombreCliente << ": ";
        if (pila.empty()) {  // verificar que la pila no este vacia
            cout << "(vacío)";
        } else {
        vector<string> temporal; // Vector temporal para guardar los productos

        while (!pila.empty()) {   // Extrae los productos de la pila y los guarda temporalmente
            temporal.push_back(pila.top());   // Agrega el producto al vector temporal
            pila.pop();   // elimina el producto de la pila
        }

        for (int i = temporal.size() - 1; i >= 0; --i)        // Mostrar sin perder orden original
            cout << temporal[i] << (i ? ", " : "");

        for (string& p : temporal)  // Restaurar pila original
            pila.push(p);
    }
    cout << "\n";
    }

    /**
     * @brief Atributo que devuelve el nombre del cliente
     * 
     * @return string de nombre
     */
    string getNombreCliente() const {     
        return nombreCliente;
    }
};


/**
 * @brief ESTRUCTURA CLIENTE
 * 
 */
struct Cliente {            // estructura que representa el cliente con el carro
    string nombre;          // nombre del cliente
    CarritoDeCompras carrito; // carrito de compras del cliente
    bool discapacidad;      // si el cliente tiene discapacidad
    bool adultoMayor;       // si el cliente es adulto mayor
    bool embarazada;        // si el cliente es embarazada
    int ordenLlegada;       // orden en el que llegó el cliente

    /**
     * @brief Construct a new Cliente object
     * 
     * @param n Nombre
     * @param c Carro de compras
     * @param dis Discapacidad
     * @param ad Adulto mayor
     * @param emb Embarazada
     * @param orden Orden de llegada
     */
    Cliente(string n, const CarritoDeCompras& c,
            bool dis, bool ad, bool emb, int orden)       // constructor para inicializar los valores
        : nombre(n), carrito(c),
          discapacidad(dis), adultoMayor(ad),
          embarazada(emb), ordenLlegada(orden) {}
};

/**
 * @brief Estructura de Factura
 * 
 */
struct Factura {
    string nombreCliente;
    vector<pair<string, int>> productos;      //Atributo de tipo vector de la factura que almacena 2 valores juntos siendo el producto y precio
    int total;
    string fechaHora;

    Factura(string nombre, const vector<pair<string,int>>& prods, int tot, const string& fecha)     //Constructor para inicializar los valores
        : nombreCliente(nombre), productos(prods), total(tot), fechaHora(fecha) {}
};

/**
 * @brief Cola global para almacenar facturas en orden cronológico
 * 
 */
queue<Factura> colaFacturas;


/**
 * @brief Estructura comparativa que representa la prioridad en la atencion, devuelve 1 si el cliente a tiene menor prioridad que el cliente b. Utiliza sobrecarga de operadores
 * 
 */
struct ComparadorPrioridad {   
    bool operator()(const Cliente& a, const Cliente& b) const {       //Sobrecarga de operador que permite usar la estructura como una funcion agregando dos clientes y comprobando si la prioridad a es menor que b, o viceversa
        auto prioridad = [](const Cliente& c) {     //Funcion lambda que define la prioridad de cada cliente
            if (c.discapacidad || c.adultoMayor || c.embarazada) return 3;      // si tiene atencion especial
            if (c.carrito.size() < 5) return 2;      // si tiene un carrito pequeño
            return 1;       // si no tiene atencion especial ni carrito pequeño
        };

        int pa = prioridad(a);       // obtiene la prioridad del cliente a
        int pb = prioridad(b);       // obtiene la prioridad del cliente b

        if (pa != pb) return pa < pb;     //En caso de empate, la prioridad la tiene el que halla llegado antes (tenga un orden de llegada menor)
        return a.ordenLlegada > b.ordenLlegada;
    }
};


/**
 * @brief PROCESAR EL CARRITO (ASIGNAR PRECIOS Y GUARDAR FACTURA)
 * 
 * @param nombreCliente Nombre del cliente al que se le esta cobrando
 * @param carrito Carro que tiene los objetos
 * @return int Devuelve el precio total
 */
int procesarCarrito(const string& nombreCliente, stack<string> carrito) {
    srand(static_cast<unsigned>(time(0)) + rand());       // Genera precios aleatorios para que ningun producto tenga el mismo precio
    int total = 0;      // sirve para obtener el precio total
    vector<pair<string, int>> productosFactura;     //Declaracion de vectores que guarda pares conformados por un string y un int (el nombre y precio del producto)

    cout << ANS_YELLOW << "Procesando carrito...\n" << ANS_RESET;
    while (!carrito.empty()) {      // mientras que el carrito no este vacio
        string producto = carrito.top();      // guarda el nombre del producto superior
        carrito.pop();      // elimina el producto


        int precio = 1000 + rand() % 19001;       // precio aleatorio entre 1000 y 20000
        cout << " - " << producto << ": $" << precio << endl;
        total += precio;      //Se va acumulando el precio total en la variable total

        productosFactura.push_back({producto, precio});     //Se guarda en el vector las el nombre y precio del producto
    }


    time_t now = time(0);
    string fechaHora = ctime(&now);       // Obtener fecha y hora actuales
    if (!fechaHora.empty() && fechaHora.back() == '\n') fechaHora.pop_back();       // eliminar el "\n" del final (salto de línea)

    cout << ANS_GREEN << "Total a pagar: $" << total << ANS_RESET << "\n";
    cout << "----------------------------------------\n";
    this_thread::sleep_for(chrono::milliseconds(450));


    Factura nueva(nombreCliente, productosFactura, total, fechaHora);       // Crear factura y almacenarla en la cola
    colaFacturas.push(nueva);

    return total;
}




/**
 * @brief CLASE COLA CON PRIORIDAD (FILA DEL D1): simula la fila del supermercado pero con niveles de prioridad
 * 
 */
class ColaPrioritariaD1 {
private:
    priority_queue<Cliente, vector<Cliente>, ComparadorPrioridad> cola;       //Define una cola con prioridad de tipo cliente, que van a ser almacenados en un vector y tienen de comparador a ComparadorPrioridad
    int contadorLlegadas = 0;       //Contador para el orden de llegada de los clientes

public:

    /**
     * @brief Agrega un cliente a la cola
     * 
     * @param nombre Nombre del cliente
     * @param carrito Carro del cliente
     * @param discapacidad Si el cliente presenta discapacidad
     * @param adultoMayor Si el cliente es un adulto mayor
     * @param embarazada Si el cliente esta embarazada
     */
    void agregarCliente(const string& nombre, const CarritoDeCompras& carrito,      // agrega un cliente a la cola
                        bool discapacidad, bool adultoMayor, bool embarazada) {
        cola.emplace(nombre, carrito, discapacidad, adultoMayor, embarazada, contadorLlegadas++);       //Agrega el cliente a la cola mediante .emplace() y aumenta el contador de llegadas
        cout << ANS_GREEN << " " << nombre << " ha llegado al D1 con " << carrito.size() << " productos." << ANS_RESET << "\n";       //Muestra el nombre del cliente y numero de productos
    }

    /**
     * @brief Funcion para saber si quedan clientes en la cola
     * 
     * @return true Si no hay mas clientes
     * @return false Si quedan clientes
     */
    bool empty() const { return cola.empty(); }       //True si no hay mas clientes en la cola

    /**
     * @brief Funcion que atiende los clientes y los elimina de la cola
     * 
     */
    void atenderClientes() {
        cout << "\n" << ANS_BLUE << " INICIO DE ATENCIÓN EN D1 \n\n" << ANS_RESET;

        while (!cola.empty()) {
            Cliente c = cola.top();       //Obtiene el primer cliente de la cola (El de mayor prioridad)
            cola.pop();       // Elimina el primer cliente de la cola

            cout << ANS_MAGENTA << "Atendiendo a " << c.nombre << " (" << c.carrito.size() << " productos)";
            if (c.discapacidad) cout << " Discapacitado";
            else if (c.adultoMayor) cout << " Adulto Mayor";
            else if (c.embarazada) cout << " Embarazada"; // mostrar las razones de la prioridad
            cout << ANS_RESET << "\n";
            c.carrito.mostrarProductos(); // imprime los productos
            int total = procesarCarrito(c.nombre, c.carrito.getProductos()); // Procesa el carrito

            cout << ANS_GREEN << " " << c.nombre << " pagó $" << total << ANS_RESET << "\n\n";
            // Pausa pequeña entre clientes para que sea legible
            this_thread::sleep_for(chrono::milliseconds(800));
        }

        cout << ANS_YELLOW << " Todos los clientes han sido atendidos correctamente.\n" << ANS_RESET;
    }
};

/**
 * @brief VISUALES ASCII: Pantallas
 * 
 * @param title 
 */
void printHeader(const string &title) {
    const int WIDTH = 90;
    cout << ANS_BOLD << ANS_BLUE;
    cout << string(WIDTH, '=') << "\n";
    int pad = (WIDTH - static_cast<int>(title.size())) / 2;
    if (pad < 0) pad = 0;
    cout << string(pad, ' ') << title << "\n";
    cout << string(WIDTH, '=') << ANS_RESET << "\n";
}

/**
 * @brief Escena 1: Pasillo con estantes (ASCII puro)
 * 
 */
void pantallaInicio() {
    clearScreen();
    printHeader(" BIENVENIDO AL D1 - PASILLO PRINCIPAL ");

    // Representacion de los articulos a comprar (Luego sera implementado con diccionarios)
    cout << "\n";
    cout << ANS_YELLOW << "[ESTANTE SUPERIOR] " << ANS_RESET;
    cout << ANS_RED << "[Tomates] " << ANS_GREEN << "[Lechuga] " << ANS_RED << "[Manzanas] ";
    cout << ANS_MAGENTA << "[Galletas] " << ANS_CYAN << "[Bebidas] " << ANS_RESET << "\n\n";

    cout << ANS_YELLOW << "[ESTANTE MEDIO]    " << ANS_RESET;
    cout << ANS_GREEN << "[Arroz] " << ANS_YELLOW << "[Aceite] " << ANS_RED << "[Carne] ";
    cout << ANS_MAGENTA << "[Galletas] " << ANS_CYAN << "[Agua] " << ANS_RESET << "\n\n";

    cout << ANS_YELLOW << "[ESTANTE INFERIOR] " << ANS_RESET;
    cout << ANS_CYAN << "[Leche] " << ANS_GREEN << "[Huevos] " << ANS_YELLOW << "[Pan] ";
    cout << ANS_RED << "[Dulces] " << ANS_MAGENTA << "[Snacks] " << ANS_RESET << "\n\n";

    // Explanatory text
    cout << ANS_WHITE << "Modo: " << ANS_RESET;
    cout << "Prueba rápida (clientes predefinidos) o crear tus propios clientes.\n\n";

    cout << ANS_BOLD << "¿Deseas usar el modo de prueba (clientes predefinidos)? (S/N): " << ANS_RESET;
    // Pregunta para empezar un modo precargado.
}


/**
 * @brief Transicion
 * 
 */
void pantallaIntermedia() {
    clearScreen();
    const string text = " INICIO DE ATENCIÓN EN D1 ";
    const int WIDTH = 90;
    // Simulate sliding from right to center slowly
    for (int pos = WIDTH; pos >= (WIDTH - static_cast<int>(text.size())) / 2; pos -= 2) {
        clearScreen();
        printHeader("");
        // print empty lines to center vertically a bit
        cout << "\n\n\n";
        int leftPad = max(0, pos);
        cout << string(leftPad, ' ');
        cout << ANS_BOLD << ANS_YELLOW << text << ANS_RESET << "\n\n\n";
        this_thread::sleep_for(chrono::milliseconds(120)); // lento y vistoso
    }

    cout << "\n";               //Pequeña pausa
    cout << ANS_CYAN << "Presiona Enter para comenzar la atención..." << ANS_RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string dummy;
    getline(cin, dummy);
}

/**
 * @brief Escena 2: Caja registradora y cinta
 * 
 */
void pantallaCaja() {
    clearScreen();
    printHeader(" CAJA REGISTRADORA - SECCIÓN DE ATENCIÓN ");
    cout << "\n";

    // Simple ASCII representation: cinta y caja
    cout << ANS_WHITE << "Cinta transportadora:\n" << ANS_RESET;
    cout << ANS_CYAN << "[====][====][====][====][====][====][====][====][====][====]" << ANS_RESET << "\n\n";

    cout << ANS_BLUE << "   [CAJA]  " << ANS_RESET << "  Aquí se mostrará la atención a clientes y los mensajes.\n\n";

    cout << ANS_GREEN << "Mensajes de atención aparecerán aquí mientras los clientes son procesados.\n\n" << ANS_RESET;
    cout << ANS_BOLD << "Presiona Enter para comenzar a procesar la fila..." << ANS_RESET;
    string dummy;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, dummy);
}


/**
 * @brief Pantalla final
 * 
 */
void pantallaFinal() {
    clearScreen();
    printHeader(" GRACIAS POR COMPRAR EN D1 ");
    cout << "\n";
    cout << ANS_YELLOW << ANS_BOLD;
    slowPrint("Gracias por preferirnos. Esperamos verte pronto en D1.\n\n", 3);
    cout << ANS_RESET;
    cout << ANS_CYAN << "Pulse Enter para finalizar el programa..." << ANS_RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string dummy;
    getline(cin, dummy);
}


/**
 * @brief Pedirle al usuario un input que se volvera un string
 * 
 * @param prompt Mensaje que se muestra en la pantalla (En negrilla)
 * @return string Devuelve el nombre
 */
string askLine(const string &prompt) {
    cout << ANS_BOLD << prompt << ANS_RESET;
    string line;
    getline(cin, line);       //Con getline los espacios tambien se guarden
    return line;
}

/**
 * @brief 
 * 
 * @param prompt Preguntar al usuario si (s) o no (n) (acepta minusculas y mayusculas en la entrada)
 * @return true En caso de que diga si(s)
 * @return false En caso de que diga no (n)
 */
bool askYesNo(const string &prompt) {
    while (true) {
        cout << ANS_BOLD << prompt << " (S/N): " << ANS_RESET;
        string resp;
        getline(cin, resp);
        if (resp.empty()) continue;
        char c = toupper(static_cast<unsigned char>(resp[0]));        //toupper Permite usar mayusculas y minusculas
        if (c == 'S') return true;
        if (c == 'N') return false;
        cout << ANS_RED << "Entrada no válida. Por favor escribe 'S' o 'N'." << ANS_RESET << "\n";
    }
}

/**
 * @brief Pregunta los atributos de propridad de un cliente y los agrupa en un vector: discapacidad, adultoMayor, embarazada (booleanos)
 * 
 * @return tuple<bool,bool,bool> Representa las posibles causas de prioridad del cliente
 */
tuple<bool,bool,bool> askPriorityFlags() {        // Pregunta los atributos de propridad de un cliente y los agrupa en un vector: discapacidad, adultoMayor, embarazada (booleanos)
    cout << ANS_WHITE << "Selecciona si el cliente tiene alguna condición especial:\n" << ANS_RESET;
    cout << "  1) Discapacidad\n";
    cout << "  2) Adulto mayor\n";
    cout << "  3) Embarazada\n";
    cout << "  4) Ninguna de las anteriores\n";
    while (true) {
        cout << ANS_BOLD << "Ingresa el número de la opción (1-4): " << ANS_RESET;
        string opt;
        getline(cin, opt);
        if (opt.empty()) continue;
        if (opt == "1") return {true, false, false};
        if (opt == "2") return {false, true, false};
        if (opt == "3") return {false, false, true};
        if (opt == "4") return {false, false, false};
        cout << ANS_RED << "Opción inválida. Intenta de nuevo.\n" << ANS_RESET;
    }
}

/**
 * @brief Funcion que devuelve un cliente creado por el usuario
 * 
 * @param ordenIdx Orden de entrada
 * @return Cliente Devuelve el cliente generado por el usuario
 */
Cliente buildClientInteractive(int ordenIdx) {
    string nombre;
    while (true) {
        nombre = askLine("Nombre del cliente: ");       //Pedir el nombre del cliente hasta que se deje de escribir un texto vacio
        if (!nombre.empty()) break;
        cout << ANS_RED << "El nombre no puede estar vacío.\n" << ANS_RESET;
    }

    CarritoDeCompras carrito(nombre);       //Crea el carrito de compras que va a tener el cliente (actua como una pila)
    cout << ANS_CYAN
     << "Ingresa productos para el carrito. Escribe una línea vacía para terminar.\n"
     << "Si te equivocas, escribe 'BORRAR', 'ELIMINAR' o 'DESHACER' para eliminar el último producto.\n"
     << ANS_RESET;

while (true) {
    string prod = askLine("  Producto (Enter para terminar): ");
    if (prod.empty()) break;  // salir si el usuario presiona solo Enter

    string mayus = prod;         // Permitir eliminar el último producto
    for (char &c : mayus) c = toupper(static_cast<unsigned char>(c));
    if (mayus == "BORRAR" || mayus == "ELIMINAR" || mayus == "DESHACER") {
        carrito.pop();
        continue;       // saltar al siguiente ciclo
    }

    carrito.push(prod);       // Si no escribió "BORRAR", agregar normalmente
}

    auto [dis, ad, emb] = askPriorityFlags();       //Guarda los valores de la tupla en 3 variables (dis, ad, emb)
    Cliente c(nombre, carrito, dis, ad, emb, ordenIdx);
    return c;       //Devuelve el cliente creado
}


/**
 * @brief Funcion MAIN que habilita las pantallas y procesos
 * 
 * @return int 0
 */
int main() {
    enableVirtualTerminalProcessingOnWindows();       //Habilita que los codigos ANSI funcionen correctamente

    srand(static_cast<unsigned>(time(0)));        //Inicializa el gnerador de numeros aleatorios con la hora actual

    ColaPrioritariaD1 fila;       //Crea la cola con prioridad que guarda los clientes del supermercado

    pantallaInicio();       //Muestra la escena inicial y pide al usuario que modo usar (crear clientes o no)

    string choice;
    while (true) {
        getline(cin, choice);
        if (choice.empty()) continue;
        char c = toupper(static_cast<unsigned char>(choice[0]));        //Selecciona el primer valor escrito (la primera "letra")
        if (c == 'S' || c == 'N') {
            choice = string(1, c);        //Limpia la primera de letra de espacios o otros caracteres extra y lo convierte en string
            break;
        } else {
            cout << ANS_RED << "Por favor escribe 'S' o 'N'." << ANS_RESET << "\n";
        }
    }

    /**
     * @brief Modo de prueba con clientes pre-definidos
     * 
     */
    bool modoPrueba = (choice == "S");
    if (modoPrueba) {
        // Cliente Sofía (discapacidad)
        CarritoDeCompras carritoSofia("Sofía");
        carritoSofia.push("Huevos");
        carritoSofia.push("Leche");
        carritoSofia.push("Pan");
        fila.agregarCliente("Sofía", carritoSofia, true, false, false);

        // Cliente Carlos (adulto mayor)
        CarritoDeCompras carritoCarlos("Carlos");
        carritoCarlos.push("Café");
        carritoCarlos.push("Queso");
        carritoCarlos.push("Pan integral");
        fila.agregarCliente("Carlos", carritoCarlos, false, true, false);

        // Cliente Marta (embarazada)
        CarritoDeCompras carritoMarta("Marta");
        carritoMarta.push("Yogurt");
        carritoMarta.push("Manzanas");
        carritoMarta.push("Galletas");
        carritoMarta.push("Agua");
        fila.agregarCliente("Marta", carritoMarta, false, false, true);

        // Cliente Ana (pocos productos)
        CarritoDeCompras carritoAna("Ana");
        carritoAna.push("Leche");
        carritoAna.push("Pan");
        carritoAna.push("Huevos");
        fila.agregarCliente("Ana", carritoAna, false, false, false);

        // Cliente Luis (carro grande)
        CarritoDeCompras carritoLuis("Luis");
        carritoLuis.push("Arroz");
        carritoLuis.push("Aceite");
        carritoLuis.push("Azúcar");
        carritoLuis.push("Lentejas");
        carritoLuis.push("Cereal");
        carritoLuis.push("Papel higiénico");
        fila.agregarCliente("Luis", carritoLuis, false, false, false);
    } else {

        /**
         * @brief Modo manual, que permite crear varios clientes
         * 
         */
        cout << ANS_GREEN << "\nModo MANUAL: Crea tus propios clientes.\n" << ANS_RESET;
        cout << "Vas a añadir clientes uno a uno. Cuando termines de añadir clientes, escribe 'FIN' como nombre.\n\n";

        int orden = 0;
        while (true) {
            cout << ANS_BOLD << "¿Deseas agregar un cliente? (S/N): " << ANS_RESET;
            string resp;
            getline(cin, resp);
            if (resp.empty()) continue;
            char c = toupper(static_cast<unsigned char>(resp[0]));
            if (c == 'N') break;
            if (c == 'S') {
                Cliente nuevo = buildClientInteractive(orden++);        //Se crea un nuevo cliente
                fila.agregarCliente(nuevo.nombre, nuevo.carrito, nuevo.discapacidad, nuevo.adultoMayor, nuevo.embarazada);        //Se agrega el cliente a la cola
            } else {
                cout << ANS_RED << "Respuesta inválida. Por favor S o N.\n" << ANS_RESET;
            }
        }
    }

    if (fila.empty()) {       //Si no hay clientes, el programa se cierra
        cout << ANS_RED << "No hay clientes para procesar. Finalizando programa.\n" << ANS_RESET;
        pantallaFinal();
        return 0;
    }

    /**
     * @brief Construye una pantalla intermedia de inicio de atención (animada y pausada)
     * 
     */
    pantallaIntermedia();

    /**
     * @brief Construye una pantalla caja (visual) y pause
     * 
     */
    pantallaCaja();

    /**
     * @brief Atender clientes (usa la lógica original)
     * 
     */
    fila.atenderClientes();

    /**
     * @brief Mostrar facturas generadas (historial de atención)
     * 
     */
    cout << "\n" << ANS_BOLD << ANS_BLUE << "FACTURAS GENERADAS:\n" << ANS_RESET;
    int contador = 1;
    while (!colaFacturas.empty()) { // mientras la cola no este vacia
        Factura f = colaFacturas.front(); // obtiene el primer puesto
        colaFacturas.pop(); // elimina el primer puesto

        cout << ANS_YELLOW << "Factura #" << contador++ << ANS_RESET << "\n";
        cout << "Cliente: " << f.nombreCliente << "\n";
        cout << "Fecha y hora: " << f.fechaHora << "\n";
        cout << "Productos:\n";
        for (auto &p : f.productos) {
        cout << "  - " << p.first << ": $" << p.second << "\n";
        }
        cout << ANS_GREEN << "Total: $" << f.total << ANS_RESET << "\n";
        cout << "----------------------------------------\n";
    }

    /**
     * @brief Construcye una nueva pantalla Final
     * 
     */
    pantallaFinal();

    return 0;
}