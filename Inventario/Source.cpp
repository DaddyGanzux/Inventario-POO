#include <iostream>
#include <string>
#include <vector>
#include <locale>

using namespace std;

// Clase 'item' que representa un objeto dentro del inventario.
class item 
{
private:
    string nombreItem;    // Nombre del ítem.
    string tipoItem;      // Tipo del ítem (por ejemplo: "arma", "poción").
    int cantidadItem;     // Cantidad de ese ítem.

public:
    // Constructor que inicializa los valores del ítem.
    item(string _nombreItem, string _tipoItem, int _cantidadItem)
        : nombreItem(_nombreItem), tipoItem(_tipoItem), cantidadItem(_cantidadItem) {}

    // Función para mostrar la información del ítem.
    void funcMostrarInfoItem() const 
    {
        cout << nombreItem << " | Tipo: " << tipoItem << " | Cantidad: " << cantidadItem << endl;
    }

    // Funciones getter/(para obtener datos privados) para acceder a los atributos.
    string getNombre() const { return nombreItem; }
    int getCantidad() const { return cantidadItem; }

    // Función para reducir la cantidad de ítems.
    void funcReducirCantidad(int cantidad) 
    {
        cantidadItem -= cantidad;
    }
};

// Clase 'personaje' que representa a un jugador con su inventario.
class personaje 
{
private:
    string nombrePersonaje;  // Nombre del personaje.
    vector<item> inventarioPersonaje;  // Vector que contiene los ítems del inventario.

public:
    // Constructor que inicializa el nombre del personaje.
    personaje(string _nombrePersonaje) : nombrePersonaje(_nombrePersonaje) {}

    // Función para agregar un ítem al inventario.
    void funcAgregarItemInventario(const item& paramItem) 
    {
        inventarioPersonaje.push_back(paramItem);
        cout << "Item agregado al inventario." << endl;
    }

    // Función para mostrar todos los ítems del inventario.
    void funcMostrarInfoInventario() const 
    {
        cout << "\n--- Inventario de " << nombrePersonaje << " ---\n";

        // Si el inventario está vacío, mostrar mensaje.
        if (inventarioPersonaje.empty()) 
        {
            cout << "El inventario está vacío.\n";
            return;
        }

        // Mostrar todos los ítems en el inventario.
        for (size_t i = 0; i < inventarioPersonaje.size(); i++) 
        {
            cout << i + 1 << ". "; // Muestra el índice del ítem.
            inventarioPersonaje[i].funcMostrarInfoItem(); // Muestra la info de cada ítem.
        }
    }

    // Función para eliminar o reducir la cantidad de un ítem.
    void funcEliminarItem() 
    {
        if (inventarioPersonaje.empty()) 
        {
            cout << "No hay ítems para eliminar.\n";
            return;
        }

        int indice, cantidadEliminar;
        funcMostrarInfoInventario();  // Muestra el inventario antes de eliminar.
        cout << "Ingrese el número del ítem que desea modificar (0 para cancelar): ";
        cin >> indice;
        cin.ignore();

        // Si el índice es válido, proceder con la eliminación o reducción.
        if (indice > 0 && indice <= static_cast<int>(inventarioPersonaje.size())) 
        {
            cout << "Ingrese la cantidad a eliminar: ";
            cin >> cantidadEliminar;
            cin.ignore();

            // Si la cantidad a eliminar es mayor o igual a la cantidad disponible, eliminar el ítem.
            if (cantidadEliminar >= inventarioPersonaje[indice - 1].getCantidad()) 
            {
                inventarioPersonaje.erase(inventarioPersonaje.begin() + (indice - 1));
                cout << "Ítem eliminado completamente.\n";
            }
            else 
            {
                // Si no, reducir la cantidad del ítem.
                inventarioPersonaje[indice - 1].funcReducirCantidad(cantidadEliminar);
                cout << "Cantidad reducida en " << cantidadEliminar << " unidades.\n";
            }
        }
        else if (indice != 0) {
            cout << "Número inválido, no se eliminó ningún ítem.\n";
        }
    }

    // Función para verificar si el inventario está vacío.
    bool funcEstaInventarioVacio() const 
    {
        return inventarioPersonaje.empty();
    }
};

// Función para validar las respuestas de los usuarios (s/n).
bool funcValidarRespuesta(char respuesta) 
{
    // Si la respuesta no es 's' ni 'n', muestra mensaje de error.
    if (respuesta != 's' && respuesta != 'S' && respuesta != 'n' && respuesta != 'N') 
    {
        cout << "Carácter inválido. Por favor, ingrese 's' para sí o 'n' para no.\n";
        return false;
    }
    return true;
}

// Función principal que ejecuta el programa.
int main() 
{
    setlocale(LC_ALL, "es_MX.UTF-8");
    string nombrePersonaje;
    cout << "Ingrese el nombre del personaje: ";
    getline(cin, nombrePersonaje);
    personaje jugador(nombrePersonaje);  // Crea un objeto 'personaje'.

    char opcion;
    int Opciones;
    bool Mochila = true;

    while (Mochila == true) //Bucle para ver el menu de la mochila
    {
        cout << "Eliga lo que le gustaria hacer. 1: Agregar items a su mochila 2: Tirar items 3: Mostrar items 4: Cerrar mochila" << endl;
        cin >> Opciones;
        switch (Opciones) //Toma el int de Opciones para poder elegir de entre las cuatro opciones disponibles.
        {
        case 1:
            do
            {
                string nombreItem, tipoItem;
                int cantidadItem;
                // Solicita al usuario ingresar los detalles de un ítem.
                cin.ignore();
                cout << "\n ----------ingresa items--------- \nNombre del Item: ";
                getline(cin, nombreItem);
                cout << "Tipo: ";
                getline(cin, tipoItem);
                cout << "Cantidad: ";
                cin >> cantidadItem;

                // Agrega el ítem al inventario del jugador.
                jugador.funcAgregarItemInventario(item(nombreItem, tipoItem, cantidadItem));

                // Pregunta si desea agregar otro ítem.
                do
                {
                    cout << "¿Desea agregar otro item? (s/n): ";
                    cin >> opcion;
                    cin.ignore();
                } while (!funcValidarRespuesta(opcion));  // Validación de la respuesta.
            } while (opcion == 's' || opcion == 'S');  // Repite si la respuesta es 's' o 'S'.
            break;

        case 2:

            char eliminarOpcion;
            do 
            {
                // Pregunta si el usuario quiere eliminar un ítem.
                do 
                {
                    cout << "\n¿Desea eliminar algún ítem del inventario? (s/n): ";
                    cin >> eliminarOpcion;
                    cin.ignore();
                } while (!funcValidarRespuesta(eliminarOpcion));  // Validación de la respuesta.

                // Si el usuario decide eliminar, se llama a la función para eliminar el ítem.
                if (eliminarOpcion == 's' || eliminarOpcion == 'S') {
                    jugador.funcEliminarItem();
                }
            } while ((eliminarOpcion == 's' || eliminarOpcion == 'S') && !jugador.funcEstaInventarioVacio());  // Continúa mientras el inventario no esté vacío.

            // Pregunta si el usuario desea agregar más ítems.
            do
            {
                cout << "\n¿Desea agregar más ítems? (s/n): ";
                cin >> opcion;
                cin.ignore();
            } while (!funcValidarRespuesta(opcion));  // Validación de la respuesta.

            // Si el usuario decide agregar más ítems, reinicia el proceso de agregar ítems.
            Mochila = (opcion == 's' || opcion == 'S');

        case 3:

            jugador.funcMostrarInfoInventario();

            break;

        case 4:
            Mochila = false;
            break;
        }
    }

    return 0;
}
