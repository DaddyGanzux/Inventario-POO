#include <iostream>
#include <string>
#include <vector>
#include <locale>

using namespace std;

// Clase 'item' que representa un objeto dentro del inventario.
class item 
{
private:
    string nombreItem;    // Nombre del �tem.
    string tipoItem;      // Tipo del �tem (por ejemplo: "arma", "poci�n").
    int cantidadItem;     // Cantidad de ese �tem.

public:
    // Constructor que inicializa los valores del �tem.
    item(string _nombreItem, string _tipoItem, int _cantidadItem)
        : nombreItem(_nombreItem), tipoItem(_tipoItem), cantidadItem(_cantidadItem) {}

    // Funci�n para mostrar la informaci�n del �tem.
    void funcMostrarInfoItem() const 
    {
        cout << nombreItem << " | Tipo: " << tipoItem << " | Cantidad: " << cantidadItem << endl;
    }

    // Funciones getter/(para obtener datos privados) para acceder a los atributos.
    string getNombre() const { return nombreItem; }
    int getCantidad() const { return cantidadItem; }

    // Funci�n para reducir la cantidad de �tems.
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
    vector<item> inventarioPersonaje;  // Vector que contiene los �tems del inventario.

public:
    // Constructor que inicializa el nombre del personaje.
    personaje(string _nombrePersonaje) : nombrePersonaje(_nombrePersonaje) {}

    // Funci�n para agregar un �tem al inventario.
    void funcAgregarItemInventario(const item& paramItem) 
    {
        inventarioPersonaje.push_back(paramItem);
        cout << "Item agregado al inventario." << endl;
    }

    // Funci�n para mostrar todos los �tems del inventario.
    void funcMostrarInfoInventario() const 
    {
        cout << "\n--- Inventario de " << nombrePersonaje << " ---\n";

        // Si el inventario est� vac�o, mostrar mensaje.
        if (inventarioPersonaje.empty()) 
        {
            cout << "El inventario est� vac�o.\n";
            return;
        }

        // Mostrar todos los �tems en el inventario.
        for (size_t i = 0; i < inventarioPersonaje.size(); i++) 
        {
            cout << i + 1 << ". "; // Muestra el �ndice del �tem.
            inventarioPersonaje[i].funcMostrarInfoItem(); // Muestra la info de cada �tem.
        }
    }

    // Funci�n para eliminar o reducir la cantidad de un �tem.
    void funcEliminarItem() 
    {
        if (inventarioPersonaje.empty()) 
        {
            cout << "No hay �tems para eliminar.\n";
            return;
        }

        int indice, cantidadEliminar;
        funcMostrarInfoInventario();  // Muestra el inventario antes de eliminar.
        cout << "Ingrese el n�mero del �tem que desea modificar (0 para cancelar): ";
        cin >> indice;
        cin.ignore();

        // Si el �ndice es v�lido, proceder con la eliminaci�n o reducci�n.
        if (indice > 0 && indice <= static_cast<int>(inventarioPersonaje.size())) 
        {
            cout << "Ingrese la cantidad a eliminar: ";
            cin >> cantidadEliminar;
            cin.ignore();

            // Si la cantidad a eliminar es mayor o igual a la cantidad disponible, eliminar el �tem.
            if (cantidadEliminar >= inventarioPersonaje[indice - 1].getCantidad()) 
            {
                inventarioPersonaje.erase(inventarioPersonaje.begin() + (indice - 1));
                cout << "�tem eliminado completamente.\n";
            }
            else 
            {
                // Si no, reducir la cantidad del �tem.
                inventarioPersonaje[indice - 1].funcReducirCantidad(cantidadEliminar);
                cout << "Cantidad reducida en " << cantidadEliminar << " unidades.\n";
            }
        }
        else if (indice != 0) {
            cout << "N�mero inv�lido, no se elimin� ning�n �tem.\n";
        }
    }

    // Funci�n para verificar si el inventario est� vac�o.
    bool funcEstaInventarioVacio() const 
    {
        return inventarioPersonaje.empty();
    }
};

// Funci�n para validar las respuestas de los usuarios (s/n).
bool funcValidarRespuesta(char respuesta) 
{
    // Si la respuesta no es 's' ni 'n', muestra mensaje de error.
    if (respuesta != 's' && respuesta != 'S' && respuesta != 'n' && respuesta != 'N') 
    {
        cout << "Car�cter inv�lido. Por favor, ingrese 's' para s� o 'n' para no.\n";
        return false;
    }
    return true;
}

// Funci�n principal que ejecuta el programa.
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
                // Solicita al usuario ingresar los detalles de un �tem.
                cin.ignore();
                cout << "\n ----------ingresa items--------- \nNombre del Item: ";
                getline(cin, nombreItem);
                cout << "Tipo: ";
                getline(cin, tipoItem);
                cout << "Cantidad: ";
                cin >> cantidadItem;

                // Agrega el �tem al inventario del jugador.
                jugador.funcAgregarItemInventario(item(nombreItem, tipoItem, cantidadItem));

                // Pregunta si desea agregar otro �tem.
                do
                {
                    cout << "�Desea agregar otro item? (s/n): ";
                    cin >> opcion;
                    cin.ignore();
                } while (!funcValidarRespuesta(opcion));  // Validaci�n de la respuesta.
            } while (opcion == 's' || opcion == 'S');  // Repite si la respuesta es 's' o 'S'.
            break;

        case 2:

            char eliminarOpcion;
            do 
            {
                // Pregunta si el usuario quiere eliminar un �tem.
                do 
                {
                    cout << "\n�Desea eliminar alg�n �tem del inventario? (s/n): ";
                    cin >> eliminarOpcion;
                    cin.ignore();
                } while (!funcValidarRespuesta(eliminarOpcion));  // Validaci�n de la respuesta.

                // Si el usuario decide eliminar, se llama a la funci�n para eliminar el �tem.
                if (eliminarOpcion == 's' || eliminarOpcion == 'S') {
                    jugador.funcEliminarItem();
                }
            } while ((eliminarOpcion == 's' || eliminarOpcion == 'S') && !jugador.funcEstaInventarioVacio());  // Contin�a mientras el inventario no est� vac�o.

            // Pregunta si el usuario desea agregar m�s �tems.
            do
            {
                cout << "\n�Desea agregar m�s �tems? (s/n): ";
                cin >> opcion;
                cin.ignore();
            } while (!funcValidarRespuesta(opcion));  // Validaci�n de la respuesta.

            // Si el usuario decide agregar m�s �tems, reinicia el proceso de agregar �tems.
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
