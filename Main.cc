#include <iostream>
#include <stdlib.h>//Libreria necesaria para generar numeros  al azar con rand() y srand
#include <stdio.h>//Libreria para hacer operaciones
#include <time.h>


using namespace std;


int FuncionIngresarEleccion(int x ){

    do
    {
        cin >> x;
        if ((x !=1) && (x != 2))
        {
            cout << "Opcion no valida, Ingresar de nuevo: ";
        }
        

    } while ((x !=1) && (x != 2)  );
    


    
    return x;


};

int FuncionProbabilidad(double x){

        
    srand(time (0));

    int  numran =  (1 +(rand () % 100));

    double prob = (numran * 0.01);




    if  (prob <= x ){

        return 1;
    }
    else {
 
        return 0;
    }
    
    


};

int JuegoJavier(){

    int choice, a;


    system("cls");

    cout << "Eres uno de los ultimos sobrevivientes en la ciudad infestada de zombies.\n";
    cout << "Tu objetivo es escapar de la ciudad y encontrar un refugio seguro.\n\n";

    // Primera elección
    cout << "Ves una casa abandonada y una tienda de armas.\n";
    cout << "Donde quieres ir? \n1 = Casa, 2 = Tienda de armas: "<<endl;

    choice = FuncionIngresarEleccion (choice);

    if (choice == 1) {
        cout << "\nEntras en la casa en busca de suministros.\n";
        cout << "Encuentras algo de comida y un botiquin de primeros auxilios.\n";
        cout << "De repente, oyes ruidos, parece que hay un zombie en la casa.\n";
        
        cout << "Quieres eliges?\nEsconderte(1) ----  Luchar(2): ";
 
        choice = FuncionIngresarEleccion (choice);

        if (choice == 1) {  
            cout << "\nTe escondes detras de una puerta. El zombie pasa de largo y logras salir de la casa ileso.";
        } else if (choice == 2) {
            cout << "\nDecides enfrentarte al zombie con lo que tienes a mano.\n";
            cout << "Luchas valientemente, pero el zombie te hiere.";// de cada 5 ataques zombies 3 personas terminan infectada, la formula es (los casos favorables / los casos totales), dando una probabilidad de infectare con un 60 %
            a =FuncionProbabilidad(0.6);
            if (a == 1){
                cout<< "\n\nHas sido infectado, y en pocos minutos te convertiras en zombie...";
                return 1;
            }
        }



                    // Segunda elección
            cout <<endl<<endl<< " Avanzas por las calles y ves un grupo de zombies bloqueando el camino principal.\n";
            cout << "Puedes intentar rodearlos o buscar otro camino.\n";
            cout << "Que eliges?\nRodear a los zombies(1) ----  Buscar otro camino(2): ";
            choice = FuncionIngresarEleccion (choice);

            if (choice == 1) {
                cout << "\nIntentas rodear al grupo de zombies.\n";
                                a =FuncionProbabilidad(0.4);
                if (a == 1){
                   cout<< "\n\nHas hecho mucho ruido y atacan todos lo zombies...";
                    return 1;
                }

                //DE CADA 10 PERSONAS QUE LO INTENTAN SOLO 4 LO LOGRAN SIN LLAMAR LA ATENCION DE LOS ZOMBIES, la formula es (los casos favorables / los casos totales), dando una probabilidad de infectare con un 60 %

                cout << "¡Sigues avanzando!\n";
            } else if (choice == 2) {
                cout << "\nEncuentras un camino alternativo, pero es mas largo y escuchas ruidos extraños.\n";
                cout << "De repente, un zombie aparece de la nada y te ataca.\n";// DE CADA 5 ATAQUES ZOMBIES  3 PERSONAS TERMINAN INFECTADAS
                a =FuncionProbabilidad(0.6);
                if (a == 1){
                   cout<< "\n\nHas sido infectado, y en pocos minutos te convertiras en zombie...";
                    return 1;
                }
                    cout << "Afortunadamente logras defenderte, pero estás herido.\n";}


                    // Tercera elección
                    cout << "\nFinalmente, llegas a la salida de la ciudad, pero está cerrada con una cerca alta.\n";
                    cout << "Ves un auto cerca que podrías usar para derribar la cerca o podrias intentar treparla.\n";
                    cout << "Que decides hacer? (1 = Usar el auto, 2 = Trepar la cerca): ";
                    choice = FuncionIngresarEleccion (choice);

                    if (choice == 1) {
                        a =FuncionProbabilidad(0.4666);
                        if (a == 1){
                            cout<< "\n\nEL CARRO NO HA LOGRADO AVANZAR, y el ruido del motor intentando encender ha llamado a muchos zombies lo cuales ya rodearon el carro completamente";
                            return 1;
                        }// 7 de cada 15 carros en un apocalipsis zombie no funcionan correctamente
                        cout << "\nSubes al auto y aceleras hacia la cerca.\n";
                        cout << "Logras abrirte paso y escapar de la ciudad. Has sobrevivido al apocalipsis zombie!\n";
                        return 1;
                    } else if (choice == 2) {
                        cout << "\nIntentas trepar la cerca, \n";//De cada 10 personas que trepan una reja  2 se caen por los nervios a los zombies
                            a =FuncionProbabilidad(0.2);
                            if (a == 1){
                            cout<< "\n pero la cerca esta muy lisa y terminas cayendo, atrayendo a los zombies.\n";
                            return 1;}
                            else{
                        
                        
                            cout << "Logras escapar, pero estas herido levemente.\n";
                            cout << "A lo lejos logras ver un refugio militar, te miran a lo lejos y van corriendo a salvarte. Sobreviviste al apocalipsis zombie!\n";
                            }}
                        }

    
    
    // CAMBIO DE HISTORIA




    else if (choice == 2) {
    cout << "\nVas a la tienda de armas y encuentras una pistola y algunas balas.\n";
    cout << "Ahora estas mejor preparado para enfrentarte a los zombies.\n";

    // Segunda eleccion
    cout << "Al salir de la tienda, escuchas ruidos extranos. Puedes:\n";
    cout << " Investigar el ruido (1) ----  Ignorar el ruido y seguir adelante (2)\n";
    choice = FuncionIngresarEleccion(choice);

                if (choice == 1) {
                    cout << "\nTe acercas al ruido y descubres a un grupo de zombies.\n";
                    cout << "Decides usar tu pistola para defenderte.\n";// de cada 100 tiros la pistola se encasquilla con 3 disparos
                    a =FuncionProbabilidad(0.03);
                            if (a == 1){
                            cout<< "\n\nTu pistola se ha encasquillado!! Un zombie se ha acercado demasiado y te ha atacado...";
                                a =FuncionProbabilidad(0.6);
                                if (a == 1){
                            cout<< "\n\nHas sido infectado, y en pocos minutos te convertiras en zombie...";
                                return 1;
                                }
                                else{
                                    cout<<"Lograste esquivar al zombie!!\n";
                                }
                            }
                            else{
                                cout << "¡Disparas y logras eliminar a algunos, pero mas vienen hacia ti!\n";
                            }
                    cout << "Tienes que decidir rapidamente:\n";
                    cout << "Correr hacia un callejon cercano (1) ---- Seguir disparando hasta que se acaben las balas (2)\n";
                    choice = FuncionIngresarEleccion(choice);

                    if (choice == 1) {
                        cout << "\nCorres hacia el callejon y logras esconderte. Los zombies pierden tu rastro.\n";
                        cout << "Te tomas un momento para recuperar el aliento y planear tu proximo movimiento.\n";
                    } else if (choice == 2) {
                        cout << "\nSigues disparando, pero te quedas sin balas. Los zombies te rodean y tienes que luchar cuerpo a cuerpo.\n";
                                            a =FuncionProbabilidad(0.6);
                                if (a == 1){
                            cout<< "\n\nHas sido infectado, y en pocos minutos te convertiras en zombie...";
                                return 1;
                                }
                    }
                     cout << "Logras salir con vida, pero estas herido levemente y agotado.\n";
                } else if (choice == 2) {
                    cout << "\nDecides ignorar el ruido y seguir adelante.\n";
                    cout << "Sin embargo, te encuentras con un zombie que te ataca.\n";

                    a =FuncionProbabilidad(0.03);
                    if (a == 1){
                        cout<< "\n\nTu pistola se ha encasquillado!! Un zombie se ha acercado demasiado y te ha atacado...";
                        a =FuncionProbabilidad(0.6);
                        if (a == 1){
                            cout<< "\n\nHas sido infectado, y en pocos minutos te convertiras en zombie...";
                            return 1;
                            }
                            else{
                                    cout<<"Lograste esquivar al zombie!!\n";
                                }
                            }
                            else{
                                cout << "¡Disparas y logras eliminar al zombie";
                            }
                }

                // Tercera eleccion
                cout << "\nSigues avanzando y llegas a un cruce de caminos.\n";
                cout << "Puedes:\n";
                cout << "Tomar el camino a la izquierda, que parece mas seguro (1) ---- ";
                cout << "Tomar el camino a la derecha, que parece mas peligroso pero mas corto (2)\n";
                choice = FuncionIngresarEleccion(choice);

                if (choice == 1) {
                        cout << "\nLlegas a una estacion de servicio abandonada. Hay comida y agua adentro, pero parece peligroso.\n";
                        cout << "Quieres entrar?  Si (1) ---- No (2): ";
                        choice = FuncionIngresarEleccion(choice);

                        if (choice == 1) {
                            cout << "\nEncuentras comida y agua, pero un zombie te sorprende y te ataca.\n";

                        } else if (choice == 2) {
                            cout << "\nDecides no arriesgarte y sigues avanzando.\n";
                        
                        }
                } else if (choice == 2) {
                    cout << "\nTomas el camino a la derecha y te encuentras con un grupo de zombies.\n";//De cada 10 personas  solamente 4 personas logran escapar sin ser infectados
                    a =FuncionProbabilidad(0.4);
                     if (a == 1){
                        cout<< "\n\nHas hecho mucho ruido y los zombies te han visto, eso ha probocado que te atacaran todos a la vez...";
                        return 1;
                        }
                    
                    cout << "Pero te ves superado y tienes que escapar.\n";
                }
            
                cout << "Logras escapar, pero estás herido levemente.\n";
                cout << "A lo lejos logras ver un refugio militar, te miran a lo lejos y van corriendo a salvarte. Sobreviviste al apocalipsis zombie!\n";}

    }


void MenuPrincipal (int *menuPrincipal) {
    cout <<endl <<endl <<"-----Pleitechon-----" <<endl; 
    cout << "1. Modos de supervivencia zombie" <<endl; 
    cout << "2. Ruleta Rusa" <<endl;
    cout << "3. Ayuda" <<endl;
    cout << "4. Integrantes del Equipo" <<endl; 
    cout << "5. Salir" <<endl; 

    cout <<endl <<"Elige una opcion:" <<endl; 
    cin >> *menuPrincipal; 

    system("cls");
}



void intergrantesDelEquipo (void) {
    cout << "-----INTEGRANTES-----" <<endl <<endl;
    cout << "Javier Alejandro Salamanca Reyes 00056824" <<endl;
    cout << "Jose Martin Luna Ramos 00308324" <<endl;
    cout << " ---------------------------------------" <<endl;
    cout << " ---------------------------------------" <<endl;

    int continuar; 
    cout <<endl <<endl << "Presiona [1] cuando termines de leer" <<endl; 
    cin >> continuar; 

    if (continuar == 1) {
        system("cls");
    }
}

void ModosZombies (int *modoszombies) {
    cout <<endl <<"-----SOLITARIO-----" <<endl; 
    cout << "1. Partida express" <<endl; 
    cout << "2. Partida Larga" <<endl;
    cout << "3. Ayuda" <<endl;
    cout << "4. Volver al menu principal" <<endl;
    cout << "5. Salir del juego" <<endl; 

    cout <<endl <<"Elige una opcion:" <<endl; 
    cin >> *modoszombies;

    system("cls");
}


int main() 

{
    int menuPrincipal = 0, regresarMenuPrincipal = 1, modoszombies = 0, menu1vs1 = 0, PuntosJugadorSolitario = 0, verHistorial = 1; 
    int PuntosJugador1 = 0, PuntosJugador2 = 0; 
    int jugador; 
    string jugador1, jugador2;
    

    do {
        MenuPrincipal (&menuPrincipal);
        do {
            switch (menuPrincipal)
            {
            case 1: 
                ModosZombies (&modoszombies);
                    switch (modoszombies)
                    {
                    case 1:

                        jugador = JuegoJavier ();                        

                        

                        break;

                    case 2:

                        
                        break;
                    
                    case 3:
                        
                        break;

                    case 4:
                        regresarMenuPrincipal = 0; 
                        break;

                    case 5:
                        menuPrincipal = 6; 
                        break;
                    
                    default:
                        cout <<endl << "Ha ingesado una opcion de Menu Invalido. Porfavor vuelva a intentarlo" <<endl; 
                        break;
                    }
                break;
            case 2: 
                
                break;
            case 3: 
            
                break;
            
            case 4: 
                intergrantesDelEquipo ();
                break;

            case 5: 
                cout <<endl << "Hasta Pronto! Gracias por jugar :D" <<endl; 
                regresarMenuPrincipal = 0; 
                break;
            
            default:
                cout << "Ha ingresado una opcion de Menu invalido. Porfavor vuelva a intentarlo" <<endl;
                regresarMenuPrincipal = 0; 
                break;
            }
        } while (regresarMenuPrincipal != 0);

    } while (menuPrincipal != 5);

    cout <<endl <<endl; 
    return 0; 
}





