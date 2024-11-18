#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct Jugador {
  string nombre;
  int vidas;

  Jugador(const string& nombre, int vidasIniciales)
      : nombre(nombre), vidas(vidasIniciales) {}

  bool estaVivo() const { return vidas > 0; }

  void perderVida() { vidas--; }
};

void juegoBuckshotRoulette();

void menuEscopeta(int* MenuPrincipal) {
  int opcion;
  do {
    cout << endl << "Bienvenido a Buckshot Roulette" << endl;
    cout << endl << "=== Menú del Juego ===" << endl;
    cout << "1. Iniciar Juego" << endl;
    cout << "2. Ver Reglas" << endl;
    cout << "3. Volver al Menú Principal"
         << endl; 
    cout << "Seleccione una opción: ";

    cin >> opcion;

    if (cin.fail()) {
      cout << "Entrada no válida. Por favor, introduce un número." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    switch (opcion) {
      case 1:
        juegoBuckshotRoulette();
        break;
      case 2:
        cout << endl << "Reglas del juego:\n";
        cout << "1. Dos jugadores se turnan para dispararse.\n";
        cout << "2. En cada ronda, se añaden balas verdaderas y falsas a la "
                "recámara.\n";
        cout << "3. Si un jugador se dispara y la bala es verdadera, pierde "
                "una vida.\n";
        cout << "4. Si la bala es falsa, el jugador continúa su turno.\n";
        cout << "5. El juego termina cuando un jugador pierde todas sus "
                "vidas.\n";
        cout << "6. El jugador con vidas restantes es el ganador.\n";
        break;
      case 3:
        *MenuPrincipal = 0; 
        break;
      default:
        cout << "Opción no válida. Por favor, elige una opción del 1 al 3."
             << endl;
        break;
    }
  } while (opcion != 3); 
}

void probabilidadBuckshot(int balasVerdaderas, int balasFalsas) {
  int totalBalas = balasVerdaderas + balasFalsas;
  double probabilidadVerdadera = (double)balasVerdaderas / totalBalas;
  double probabilidadFalsa = (double)balasFalsas / totalBalas;

  cout << endl
       << "Probabilidad de que la bala sea verdadera: \n"
       << probabilidadVerdadera * 100 << "%" << endl;
  cout << endl
       << "Probabilidad de que la bala sea falsa: \n"
       << probabilidadFalsa * 100 << "%" << endl;
}

void mostrarVidasRestantes(const Jugador& jugador1, const Jugador& jugador2) {
  cout << endl
       << jugador1.nombre << " tiene " << jugador1.vidas
       << " vidas restantes.\n";
  cout << jugador2.nombre << " tiene " << jugador2.vidas
       << " vidas restantes.\n";
}

void juegoBuckshotRoulette() {
  string nombreJugador1, nombreJugador2;

  do {
    cout << "Ingrese el nombre del Jugador 1: ";
    cin >> nombreJugador1;
    if (nombreJugador1.empty()) {
      cout << "El nombre no puede estar vacío. Intente nuevamente." << endl;
    }
  } while (nombreJugador1.empty());

  do {
    cout << "Ingrese el nombre del Jugador 2: ";
    cin >> nombreJugador2;
    if (nombreJugador2.empty()) {
      cout << "El nombre no puede estar vacío. Intente nuevamente." << endl;
    }
  } while (nombreJugador2.empty());

  Jugador jugador1(nombreJugador1, 2);
  Jugador jugador2(nombreJugador2, 2);

  int turno = 0;
  int ronda = 1;

  srand(time(0));

  while (jugador1.estaVivo() && jugador2.estaVivo()) {
    int balasVerdaderas = ronda;
    int balasFalsas = ronda + 1;

    cout << endl
         << "Ronda " << ronda << ": " << endl
         << balasVerdaderas << " balas verdaderas y " << balasFalsas
         << " balas falsas." << endl;
    probabilidadBuckshot(balasVerdaderas, balasFalsas);

    mostrarVidasRestantes(jugador1, jugador2);

    vector<int> recamara(balasVerdaderas + balasFalsas, 0);
    for (int i = 0; i < balasVerdaderas; i++) {
      recamara[i] = 1;
    }
    random_shuffle(recamara.begin(), recamara.end());

    int balasVerdaderasRestantes = balasVerdaderas;

    while (balasVerdaderasRestantes > 0) {
      Jugador& jugadorActual = (turno == 0) ? jugador1 : jugador2;
      Jugador& jugadorObjetivo = (turno == 0) ? jugador2 : jugador1;

      cout << endl << "Es el turno de " << jugadorActual.nombre << endl;

      int choice;
      do {
        cout << "Dispararse a sí mismo, 1 = mismo, 2 = otro: ";
        cin >> choice;
        if (cin.fail() || (choice != 1 && choice != 2)) {
          cout << "Opción no válida. Por favor, elige 1 o 2." << endl;
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
      } while (choice != 1 && choice != 2);

      bool disparoASiMismo = (choice == 1);
      Jugador& objetivo = disparoASiMismo ? jugadorActual : jugadorObjetivo;

      int disparoIndex = rand() % recamara.size();
      int resultado = recamara[disparoIndex];
      recamara.erase(recamara.begin() + disparoIndex);

      if (resultado == 1) {
        balasVerdaderasRestantes--;
        cout << endl
             << "¡BOOM! " << objetivo.nombre << " ha recibido la bala." << endl;
        objetivo.perderVida();

        mostrarVidasRestantes(jugador1, jugador2);

        if (disparoASiMismo) {
          turno = 1 - turno;
        }

      } else {
        cout << endl
             << objetivo.nombre << " milagrosamente ha evitado la bala."
             << endl;

        if (!disparoASiMismo) {
          turno = 1 - turno;
        }
      }

      if (!jugador1.estaVivo() || !jugador2.estaVivo()) {
        cout << endl << "Fin del juego!" << endl;
        if (!jugador1.estaVivo()) {
          cout << endl << jugador2.nombre << " ha ganado!" << endl;
        } else {
          cout << endl << jugador1.nombre << " ha ganado!" << endl;
        }
        return;
      }
    }

    ronda++;
  }
}

int FuncioningresarEleccion(int opciones[], int cantidadOpciones) {
  int decision;
  bool valida = false;

  while (!valida) {
    std::cout << "Toma una decisión: " << std::endl;
    std::cin >> decision;

    // Si la entrada es incorrecta (no un número) o fuera del rango de opciones
    if (std::cin.fail()) {
      // Limpia el estado de error de std::cin
      std::cin.clear();
      // Limpia el buffer de entrada para evitar que se queden caracteres viejos
      std::cin.ignore(10000, '\n');
      std::cout << "Entrada no válida. Por favor, ingresa un número."
                << std::endl;
    } else {
      // Comprobamos si la decisión está dentro de las opciones válidas
      bool opcionValida = false;
      for (int i = 0; i < cantidadOpciones; i++) {
        if (decision == opciones[i]) {
          opcionValida = true;
          break;
        }
      }
      if (opcionValida) {
        valida = true;
      } else {
        std::cout
            << "Opción no válida. Por favor ingresa una opción entre el 1 y 2"
            << std::endl;
      }
    }
  }

  return decision;
}

int juegoLargo() {
  int opcionesValidas[] = {1, 2};
  int cantidadOpciones = sizeof(opcionesValidas) / sizeof(opcionesValidas[0]);
  // SE TOMA UN DECISIÓN POSITIVA QUE CLARAMENTE AUMENTE LAS PROBABILIDADES DE
  // SUPERVIVDENCIA 0.05 SE TOMA UN DECISIÓN QUE TE PONE EN RIESGO EN UNA
  // SITUACIÓN QUE YA ES COMPROMETEDORA -0.05 SI SE TOMA UNA DECISIÓN QUE NO SE
  // CONSIDERE DE RIESGO NI CONVENIENTE EL PORCENTAJE SERA DE 0.025
  int decision;
  float decisión_riesgo = 0.025;
  float supervivencia = 0.5;
  float mala_decisión = 0.05;
  float buena_decisión = 0.05;
  float total = supervivencia;
  std::cout << std::endl
            << "Te despiertas en un lugar desconocido. Al principio no sabes "
               "donde estas, pero al mirar\n"
               "a tu alrededor te das cuenta que el mundo ha cambiado. Las "
               "calles están desiertas y todo parece estar destruido.\n"
               "Ruidos extraños vienen a la distancia. ¿Qué harás?"
            << std::endl;
  std::cout << "[1]-Investigar ruidos extraños" << "-------------------------"
            << "[2]-Buscar refugio rápidamente" << std::endl;
  decision = FuncioningresarEleccion(opcionesValidas, cantidadOpciones);

  if (decision == 1) {
    total -= mala_decisión;
    std::cout
        << std::endl
        << "Tomaste la decisión de investigar, pero tienes miedo, tu corazón "
           "se encuentra acelerado\n"
           "y decides ser precavido. Por lo que ves a través de un muro un "
           "grupo de zombis caminando sin rumbo, a un lado de ellos miras\n"
           "como una niña se encuentra en una situación de mucho riesgo, "
           "puesto que uno de los zombis decide ir hacia ella. ¿Qué harás?"
        << std::endl;
    std::cout << "[1]-No arriesgarte y buscar un refugio"
              << "-------------------------"
              << "[2]-Hacer ruido para distraer al zombi que se dirige hacia "
                 "la pequeña"
              << std::endl;
    decision = FuncioningresarEleccion(opcionesValidas, cantidadOpciones);

    if (decision == 2) {
      total -= mala_decisión;
      std::cout << std::endl
                << "Al hacer ruido logras distraer al zombi que se dirigía "
                   "hacia la niña, pero también logras captar la atención del "
                   "grupo de zombis\n"
                   "que se encontraba cerca, por lo que ahora eres tú quien se "
                   "encuentra en una situación de mucho riesgo. ¿Qué harás?"
                << std::endl;
      std::cout << "[1]-Correr hacia la niña pasando cerca de los zombis"
                << "-------------------------" << "[2]-Correr por tu vida"
                << std::endl;
      decision = FuncioningresarEleccion(opcionesValidas, cantidadOpciones);
      if (decision == 1) {
        total -= mala_decisión;
        std::cout
            << std::endl
            << "Decides correr hacia la niña. Pasas rozando a los zombis, pero "
               "te detienes justo a tiempo para salvarla. Ambos logran\n"
               "esquivar el ataque del zombi y se refugian en una pequeña casa "
               "abandonada. Sin embargo, la niña está asustada y tiene miedo.\n"
               "¿Qué harás?"
            << std::endl;
        std::cout
            << "[1]-Calmar a la niña y continuar buscando un refugio seguro"
            << "-------------------------"
            << "[2]-Salir de la casa y seguir corriendo" << std::endl;
        decision = FuncioningresarEleccion(opcionesValidas, cantidadOpciones);
        if (decision == 1) {
          total += buena_decisión;
          std::cout << std::endl
                    << "Te tomas un momento para calmar a la niña. Después de "
                       "un rato, decide confiar en ti y te dice que su familia "
                       "vive en un pueblo cercano.\n"
                       "Te ofrece acompañarla allí. Juntos comienzan el camino "
                       "hacia el pueblo, aunque el riesgo sigue latente."
                    << std::endl;
          std::cout << std::endl
                    << "Tu porcentaje de supervivencia es del: " << total * 100
                    << "%";
        } else if (decision == 2) {
          total -= mala_decisión;
          std::cout << std::endl
                    << "Decides que lo mejor es seguir corriendo. Saliendo de "
                       "la casa, el peligro sigue acechando, y sin quererlo te "
                       "adentras más en\n"
                       "la ciudad. En un callejón estrecho, te enfrentas a un "
                       "grupo de zombis que te rodean. Ahora no tienes más "
                       "opción que luchar."
                    << std::endl;
          std::cout << std::endl
                    << "Tu porcentaje de supervivencia es del: " << total * 100
                    << "%";
        }
      } else if (decision == 2) {
        total += buena_decisión;
        std::cout
            << std::endl
            << "Decides huir por tu vida. Corres sin mirar atrás, y aunque los "
               "zombis te persiguen durante un rato, logras perderlos entre\n"
               "las calles desiertas. Después de un buen rato, encuentras una "
               "pequeña tienda. Dentro parece haber suministros."
            << std::endl;
        std::cout << "[1]-Entrar a la tienda y buscar suministros"
                  << "-------------------------" << "[2]-Continuar huyendo"
                  << std::endl;
        decision = FuncioningresarEleccion(opcionesValidas, cantidadOpciones);
        if (decision == 1) {
          total += buena_decisión;
          std::cout << std::endl
                    << "Entras a la tienda y, después de buscar un poco, "
                       "encuentras agua, algo de comida y una linterna. Te "
                       "preparas para seguir adelante,\n"
                       "pero un ruido proveniente del fondo de la tienda te "
                       "pone alerta."
                    << std::endl;
          std::cout << "[1]-Investigar el ruido en el fondo de la tienda"
                    << "-------------------------"
                    << "[2]-Salir rápidamente de la tienda" << std::endl;
          decision = FuncioningresarEleccion(opcionesValidas, cantidadOpciones);
          if (decision == 1) {
            total -= mala_decisión;
            std::cout << std::endl
                      << "Decides investigar el ruido y, al fondo, encuentras "
                         "a un hombre atrapado bajo unas estanterías caídas. "
                         "Él te pide ayuda para salir."
                      << std::endl;
            std::cout << "[1]-Ayudar al hombre"
                      << "-------------------------"
                      << "[2]-No ayudar" << std::endl;
            decision =
                FuncioningresarEleccion(opcionesValidas, cantidadOpciones);
            if (decision == 1) {
              total -= mala_decisión;
              std::cout
                  << std::endl
                  << "Te acercas a ayudar al hombre, pero en cuanto das un "
                     "paso más, algo no está bien...\n"
                  << "Notas que la tienda está mucho más oscura de lo que "
                     "parecía desde fuera, y cuando el sujeto te mira "
                     "fijamente, sus ojos son fríos y vacíos.\n"
                  << "De repente, se escucha un ruido desde el fondo de la "
                     "tienda y un gruñido bajo interrumpe el ambiente.\n"
                  << "Es demasiado tarde para dar un paso atrás, el sujeto no "
                     "está pidiendo ayuda, está tratando de atraer a más "
                     "zombis."
                  << std::endl;
              std::cout << "[1]-Sacar rápidamente tu arma y enfrentar al hombre"
                        << "-----------------" << "[2]-Huir sin pensarlo"
                        << std::endl;
              decision =
                  FuncioningresarEleccion(opcionesValidas, cantidadOpciones);
              if (decision == 1) {
                total -= mala_decisión;
                std::cout
                    << std::endl
                    << "Sacaste tu arma rápidamente y apuntas al hombre, que "
                       "ahora se muestra como un zombi sediento de carne "
                       "humana.\n"
                    << "Con un par de disparos certeros, el hombre cae al "
                       "suelo, pero al hacerlo, el ruido atrae a un grupo de "
                       "zombis de la calle.\n"
                    << "Las puertas de la tienda se rompen de inmediato y una "
                       "horda de zombis entra, bloqueando la salida."
                    << std::endl;
                std::cout
                    << "[1]-Luchar hasta el final, buscando la manera de "
                       "sobrevivir"
                    << "-----------------"
                    << "[2]-Intentar escapar por la parte trasera de la tienda"
                    << std::endl;
                decision =
                    FuncioningresarEleccion(opcionesValidas, cantidadOpciones);
                if (decision == 1) {
                  total -= mala_decisión;
                  std::cout
                      << std::endl
                      << "Te armas de valor y decides luchar contra los "
                         "zombis, aprovechando las estanterías y los pasillos "
                         "estrechos de la tienda.\n"
                      << "Durante unos minutos, logras mantener a los zombis a "
                         "raya, pero las fuerzas comienzan a flaquear.\n"
                      << "Al final, te das cuenta de que las probabilidades de "
                         "sobrevivir son mínimas... ¿Lograrás escapar o caerás "
                         "en manos de los zombis?"
                      << std::endl;
                  std::cout << "[1]-Intentar escapar corriendo"
                            << "-----------------"
                            << "[2]-Seguir luchando hasta el último momento"
                            << std::endl;
                  decision = FuncioningresarEleccion(opcionesValidas,
                                                     cantidadOpciones);
                  if (decision == 1) {
                    total += decisión_riesgo;
                    std::cout
                        << std::endl
                        << "Ves a tu alrededor, y no tienes muchas opciones, "
                           "pero ves como hay una ventana que puedes atravesar "
                           "asi que\n "
                           "con todas las fuerzas que aun posees corres hacia "
                           "ella y lo "
                           "logras has escapado pero tienes una herida "
                           "bastante profunda\n "
                           "en una pierda por ahora logras sobrevivir gracias "
                           "a las "
                           "provisiones que encontraste previamente, por ahora "
                           "sigues vivo,"
                           "un largo camino te espera.";
                    std::cout << std::endl
                              << "Tu porcentaje de supervivencia es del: "
                              << total * 100 << "%";
                  } else if (decision == 2) {
                    std::cout
                        << std::endl
                        << "Luchas con todas tus fuerzas y tienes la suerte de "
                           "tumbar a dos, pero otro se avalanza hacia ti y "
                           "como puedes\n "
                           "evitas los dientes pero son demasiados, solo eres "
                           "uno y a "
                           "medida el combate continua te notas muy cansado y "
                           "cuando\n "
                           "piensas en la esperanza de vivir siente un dolor "
                           "punzante en "
                           "tu pierna, asi es, uno de los zombies que estaban "
                           "en el suelo\n "
                           "logro morderte, sin mas opcion corres con la poca "
                           "energia "
                           "que te queda, logras salir pero en el proceso te "
                           "mordieron\n "
                           "multiples veces sabes que tarde o temprano te "
                           "transformaras, "
                           "asi que cuando te encuentras lejos de aquella "
                           "horda te apoyas\n "
                           "contra un muro, disfrutando de las proviciones que "
                           "previamente "
                           "econtraste, sonries porque sabes que es tu ultima "
                           "comida...";
                    std::cout << std::endl
                              << "Tu porcentaje de supervivencia es del: 0%";
                  }

                } else {
                  total += buena_decisión;
                  std::cout
                      << std::endl
                      << "Corres hacia la parte trasera, tratando "
                         "de evadir a los zombis que están por todos lados.\n"
                      << "Tienes suerte y encuentras una salida secundaria, "
                         "pero cuando llegas al exterior, te das cuenta de que "
                         "la ciudad está llena de zombis.\n"
                      << "Ahora, sin saber a dónde ir, ¿qué harás?"
                      << std::endl;
                  std::cout
                      << "[1]-Ir hacia un edificio alto en busca de un punto "
                         "de vista mejor"
                      << "-----------------"
                      << "[2]-Correr sin rumbo, buscando una salida a la ciudad"
                      << std::endl;
                  decision = FuncioningresarEleccion(opcionesValidas,
                                                     cantidadOpciones);
                  if (decision == 1) {
                    total += decisión_riesgo;
                    std::cout << std::endl
                              << "Tardas mas de lo previsto en llegar hasta el "
                                 "edificio, "
                                 "pero con bastante esfuerzo y siendo "
                                 "precavido logras llegar.\n "
                                 "Te encuentras en el punto mas alto y para tu "
                                 "suerte encunetras "
                                 "un grupo de refugiados los cuales te ofrecen "
                                 "ayuda al ver que\n "
                                 "no te encuentras herido. "
                                 "puedes vivir un dias, ahora con compañia y "
                                 "mas suministros";
                    std::cout << std::endl
                              << "Tu porcentaje de supervivencia es del: "
                              << total * 100 << "%";
                  } else {
                    total -= mala_decisión;
                    std::cout
                        << std::endl
                        << "Te encuentras desesperado pero tienes claro que "
                           "tienes "
                           "que escapar a como de lugar, en el camino te "
                           "encuentras mas hordas.\n "
                           "Hasta el momento has tenido suerte ya que no te "
                           "han detectado, pero "
                           "eres muy consciente de que la suerte no durara por "
                           "siempre.\n "
                           "no tienes la suficientes fuerzas para continuar "
                           "buscando una salida "
                           "con tanta desesperacion, asi que optas por "
                           "descansar, de momento sigues vivo "
                           "no tienes suficientes alimentos ni provisiones, tu "
                           "futuro es incierto\n y cada vez "
                           "la probabilidad de que vivas es menor...";
                    std::cout << std::endl
                              << "Tu porcentaje de supervivencia es del: "
                              << total * 100 << "%";
                  }
                }

              } else {
                total += buena_decisión;
                std::cout
                    << std::endl
                    << "Decides que no vale la pena arriesgarte. Salta hacia "
                       "atrás rápidamente y corres fuera de la tienda.\n"
                    << "El sonido de los zombis creciendo más fuerte te hace "
                       "acelerar el paso, pero no estás seguro de hacia dónde "
                       "dirigirte.\n"
                    << "La ciudad parece estar en ruinas, y cada paso te aleja "
                       "más de cualquier lugar seguro."
                    << std::endl;
                std::cout
                    << "[1]-Ir hacia la estación de trenes, pensando que "
                       "podrías salir de la ciudad"
                    << "-----------------"
                    << "[2]-Buscar un refugio seguro donde puedas descansar"
                    << std::endl;
                decision =
                    FuncioningresarEleccion(opcionesValidas, cantidadOpciones);
                if (decision == 1) {
                  total -= decisión_riesgo;

                  std::cout << std::endl
                            << "Te diriges rapidamente hacia la estación de "
                               "trenes, esperando encontrar algún tren que aún "
                               "funcione o algún lugar seguro dentro.\n"
                            << "Sin embargo, cuando llegas, descubres que la "
                               "estación está llena de zombis, y la entrada "
                               "está bloqueada por escombros."
                            << std::endl;
                  std::cout << "[1]-Intentar despejar el camino y entrar en la "
                               "estación"
                            << "-----------------"
                            << "[2]-Buscar otro lugar para refugiarte"
                            << std::endl;
                  decision = FuncioningresarEleccion(opcionesValidas,
                                                     cantidadOpciones);
                  if (decision == 1) {
                    total -= mala_decisión;

                    std::cout << std::endl
                              << "Te decides a intentar despejar el camino, "
                                 "empujando escombros "
                                 "y arriesgándote a atraer la atención de los "
                                 "zombis cercanos.\n"
                              << "Logras abrir un pequeño pasaje, pero justo "
                                 "cuando estás a punto "
                                 "de entrar, un zombi se acerca rápidamente. "
                                 "Con una agilidad sorprendente, "
                                 "te atrapa y te arrastra hacia un grupo de "
                                 "zombis que ya te rodean.\n"
                              << "El dolor es insoportable, y en poco tiempo "
                                 "caes víctima de los monstruos."
                              << std::endl;

                    std::cout << std::endl
                              << "Tu historia termina aquí. El riesgo de "
                                 "intentar enfrentarte a los zombis "
                              << "ha sido fatal. Tu supervivencia fue 0%."
                              << std::endl;

                  } else if (decision == 2) {
                    total += decisión_riesgo;

                    std::cout << std::endl
                              << "Optas por no enfrentarte directamente a los "
                                 "zombis y decides buscar "
                                 "otro refugio. Te alejas rápidamente de la "
                                 "estación, con la esperanza de encontrar "
                                 "un lugar seguro. A medida que te alejas, el "
                                 "sonido de los zombis se va apagando, "
                                 "pero te das cuenta de que has perdido "
                                 "valioso tiempo."
                              << std::endl;

                    std::cout
                        << std::endl
                        << "Después de varias horas buscando sin éxito, caes "
                           "en cuenta de que estás "
                           "totalmente perdido. La ciudad está desierta y el "
                           "peligro acecha en cada esquina. "
                           "Tu fuerza empieza a decaer y tus opciones se "
                           "reducen. Eventualmente, te encuentras "
                           "demasiado exhausto y sin recursos para seguir."
                        << std::endl;

                    std::cout << std::endl
                              << "Tu historia termina aquí. La falta de "
                                 "preparación y las decisiones tardías "
                              << "te han llevado a un destino incierto. ";
                    std::cout << std::endl
                              << "Tu porcentaje de supervivencia es del: "
                              << total * 100 << "%";
                  }

                } else {
                  std::cout << std::endl
                            << "Decides encontrar un lugar seguro donde "
                               "descansar y recuperarte. Después de todo, el "
                               "agotamiento está comenzando a hacer efecto.\n"
                            << "Encuentras una casa abandonada que parece no "
                               "haber sido saqueada. Al entrar, te sientes "
                               "relativamente seguro por el momento."
                            << std::endl;
                  std::cout << "[1]-Revisar la casa en busca de suministros"
                            << "-----------------"
                            << "[2]-Tomar un descanso y esperar que la "
                               "situación mejore"
                            << std::endl;
                  decision = FuncioningresarEleccion(opcionesValidas,
                                                     cantidadOpciones);
                  if (decision == 1) {
                    total += buena_decisión;

                    std::cout
                        << std::endl
                        << "Decides explorar la casa en busca de algo útil. "
                           "Después de revisar varios cuartos, encuentras una "
                           "pequeña "
                           "caja de suministros: algunas latas de comida, agua "
                           "y un botiquín "
                           "de primeros auxilios. Con estos recursos, te "
                           "sientes más "
                           "preparado para lo que pueda venir."
                        << std::endl;
                    std::cout << std::endl
                              << "Te das cuenta de que, aunque el peligro "
                                 "sigue acechando, "
                                 "ahora tienes las herramientas para "
                                 "mantenerte con vida por más tiempo."
                              << std::endl;
                    std::cout << std::endl
                              << "Tu supervivencia mejora. Tu porcentaje de "
                                 "supervivencia es del: "
                              << total * 100 << "%." << std::endl;

                  } else if (decision == 2) {
                    total += decisión_riesgo;

                    std::cout << std::endl
                              << "Decides tomar un descanso, esperando que la "
                                 "situación "
                                 "mejore por sí sola. El agotamiento y la "
                                 "tensión se apoderan de "
                                 "ti mientras descansas en la casa abandonada. "
                                 "El silencio es "
                                 "inquietante, pero en algún momento logras "
                                 "quedarte dormido."
                              << std::endl;
                    std::cout << std::endl
                              << "Cuando despiertas, es tarde. Los ruidos que "
                                 "habías ignorado "
                                 "al principio ahora son más fuertes. Un grupo "
                                 "de zombis ha "
                                 "llegado a las cercanías y la casa ya no te "
                                 "parece tan segura."
                              << std::endl;
                    std::cout << std::endl
                              << "Con la energía renovada pero sin "
                                 "suministros, no puedes "
                                 "evitar el riesgo. El pánico te invade y al "
                                 "intentar escapar, "
                                 "te encuentras atrapado por un zombi que te "
                                 "acorrala en el pasillo."
                              << std::endl;
                    std::cout
                        << std::endl
                        << "Tu historia termina aquí. El descanso fue "
                           "fatal. Tu porcentaje supervivencia es de: 0% ";
                  }
                }
              }

            } else {
              total += buena_decisión;
              std::cout << std::endl
                        << "Decides no acercarte al hombre. Algo en su mirada "
                           "te desconcierta, y prefieres no arriesgarte.\n"
                        << "Sigues caminando a través de la tienda, pero el "
                           "ambiente es cada vez más pesado. Las sombras se "
                           "alargan y el silencio es incómodo.\n"
                        << "De repente, escuchas pasos detrás de ti, y te das "
                           "vuelta rápidamente."
                        << std::endl;
              std::cout << "[1]-Correr hacia la salida sin mirar atrás"
                        << "-----------------"
                        << "[2]-Enfrentar lo que sea que te sigue" << std::endl;
              decision =
                  FuncioningresarEleccion(opcionesValidas, cantidadOpciones);
              if (decision == 1) {
                total += buena_decisión;
                std::cout << std::endl
                          << "Corres rápidamente hacia la salida, sin mirar "
                             "atrás. El sonido de pasos se aleja, pero no "
                             "estás seguro de si te están siguiendo.\n"
                          << "Al salir, te das cuenta de que la ciudad está "
                             "más peligrosa que nunca."
                          << std::endl;
                std::cout << "[1]-Buscar un refugio lo más rápido posible"
                          << "-----------------"
                          << "[2]-Intentar encontrar un vehículo para escapar"
                          << std::endl;
                decision =
                    FuncioningresarEleccion(opcionesValidas, cantidadOpciones);
                if (decision == 1) {
                  total += buena_decisión;  // Aumentamos porque la decision de
                                            // buscar refugio es buena

                  std::cout
                      << std::endl
                      << "Decides que lo mejor es encontrar un refugio "
                         "lo mas rapido posible. Al correr por las calles, "
                         "encuentras una vieja casa con las ventanas cerradas, "
                         "pero parece segura. Entrando rapidamente, encuentras "
                         "algunos suministros basicos: agua, comida enlatada y "
                         "un botiquin de primeros auxilios."
                      << std::endl;
                  std::cout
                      << std::endl
                      << "Ahora tienes tiempo para descansar y recuperarte, "
                         "y el refugio te da una sensacion de seguridad, al "
                         "menos "
                         "por el momento. Tu porcentaje de supervivencia ha "
                         "aumentado."
                      << std::endl;
                  std::cout << std::endl
                            << "Tu porcentaje de supervivencia es del: "
                            << total * 100 << "%." << std::endl;

                } else if (decision == 2) {
                  total -= mala_decisión;

                  std::cout
                      << std::endl
                      << "Decides intentar encontrar un vehiculo para escapar. "
                         "Corres por las calles en busca de un coche que "
                         "todavia "
                         "pueda funcionar, pero pronto te das cuenta de que no "
                         "hay ningun vehiculo en condiciones. Los zombis "
                         "empiezan "
                         "a rodearte, y el ruido de tus pasos atrae mas de "
                         "ellos."
                      << std::endl;
                  std::cout << std::endl
                            << "Con el miedo creciendo, ves una moto "
                               "abandonada, pero "
                               "al intentar arrancarla, el motor no responde. "
                               "Te detienes, "
                               "sin saber que hacer. Un grupo de zombis te "
                               "alcanza y no "
                               "tienes mas opciones que pelear, pero la lucha "
                               "es en vano."
                            << std::endl;
                  std::cout
                      << std::endl
                      << "Tu historia termina aqui. Intentaste escapar sin "
                         "planear con anticipacion.";
                  std::cout << std::endl
                            << "Tu porcentaje de supervivencia es de 0%";
                }

              } else {
                total += decisión_riesgo;
                std::cout << std::endl
                          << "Te das vuelta, y para tu sorpresa, no es un "
                             "zombi, sino otro sobreviviente, también armado.\n"
                          << "Parece que has tropezado con un grupo de humanos "
                             "que están buscando suministros."
                          << std::endl;
                std::cout
                    << std::endl
                    << "Tu porcentaje de supervivencia hasta este punto es: "
                    << total * 100 << "%";
              }
            }

          } else if (decision == 2) {
            total += buena_decisión;
            std::cout << std::endl
                      << "Decides no arriesgarte y salir rápidamente. Mientras "
                         "corres hacia la salida, un grupo de zombis irrumpe "
                         "en la tienda, pero logras escapar."
                      << std::endl;
            std::cout << std::endl
                      << "Tu porcentaje de supervivencia hasta este punto es: "
                      << total * 100 << "%";
          }
        } else if (decision == 2) {
          total += decisión_riesgo;
          std::cout
              << std::endl
              << "Sigues corriendo, sin detenerte ni un segundo. El peligro "
                 "sigue acechando, pero no puedes darte el lujo de quedarte.\n"
                 "Al fondo ves una especie de refugio improvisado, y te "
                 "diriges hacia allí para buscar algo de seguridad."
              << std::endl;
          std::cout << std::endl
                    << "Tu porcentaje de supervivencia hasta este punto es: "
                    << total * 100 << "%";
        }
      }
    } else if (decision == 2) {
      total += decisión_riesgo;
      std::cout << std::endl
                << "Decides no arriesgarte. Rápidamente, te alejas de la zona "
                   "y buscas un refugio cercano. Encuentras un edificio\n"
                   "en ruinas que parece seguro, aunque tienes que ser "
                   "cauteloso con los ruidos. Dentro, encuentras comida y agua."
                << std::endl;
      std::cout << "[1]-Descansar y continuar el camino al día siguiente"
                << "-------------------------"
                << "[2]-Explorar el edificio en busca de más suministros"
                << std::endl;
      decision = FuncioningresarEleccion(opcionesValidas, cantidadOpciones);
      if (decision == 1) {
        total += buena_decisión;
        std::cout
            << std::endl
            << "Decides descansar. Durante la noche, escuchas ruidos extraños "
               "fuera del edificio, pero te mantienes seguro dentro.\n"
               "A la mañana siguiente, sigues tu camino."
            << std::endl;
        std::cout << std::endl
                  << "Tu porcentaje de supervivencia hasta este punto es: "
                  << total * 100 << "%";
      } else if (decision == 2) {
        total -= decisión_riesgo;
        std::cout << std::endl
                  << "Decides explorar el edificio. Al hacerlo, encuentras una "
                     "pequeña trampa que te lleva a un sótano.\n"
                     "Allí encuentras más comida y medicinas, pero también te "
                     "das cuenta de que el lugar está lleno de trampas."
                  << std::endl;
        std::cout << std::endl
                  << "Tu porcentaje de supervivencia hasta este punto es: "
                  << total * 100 << "%";
      }
    }
  }
  if (decision == 2) {
    total += buena_decisión;
    std::cout << std::endl
              << "Decides buscar refugio rápidamente. Después de caminar "
                 "durante un rato, encuentras un pequeño edificio.\n"
                 "La puerta está cerrada, pero parece seguro. ¿Qué harás?"
              << std::endl;
    std::cout << "[1]-Entrar al edificio y explorar"
              << "-------------------------"
              << "[2]-Seguir buscando otro refugio más seguro" << std::endl;
    decision = FuncioningresarEleccion(opcionesValidas, cantidadOpciones);
    if (decision == 1) {
      total += buena_decisión;
      std::cout << std::endl
                << "Entres al edificio y, al explorarlo, encuentras a un grupo "
                   "de sobrevivientes que te reciben con desconfianza.\n"
                   "Después de hablar con ellos, te ofrecen unirte a su grupo."
                << std::endl;
      std::cout << std::endl
                << "Tu porcentaje de supervivencia hasta este punto es: "
                << total * 100 << "%";
    } else if (decision == 2) {
      total += decisión_riesgo;
      std::cout << std::endl
                << "Decides seguir buscando un refugio mejor. Al salir del "
                   "edificio, te encuentras con un pequeño grupo de zombis.\n"
                   "Debes decidir si enfrentarlos o correr."
                << std::endl;
      std::cout << "[1]-Enfrentar a los zombis con lo que tienes"
                << "-------------------------" << "[2]-Correr rápidamente"
                << std::endl;
      decision = FuncioningresarEleccion(opcionesValidas, cantidadOpciones);
      if (decision == 1) {
        total -= mala_decisión;
        std::cout
            << std::endl
            << "Te enfrentas a los zombis con un palo de madera. La lucha es "
               "feroz, pero logras derrotarlos. Después de la pelea,\n"
               "te sientes agotado, pero sigues adelante en busca de más "
               "supervivientes."
            << std::endl;
        std::cout << std::endl
                  << "Tu porcentaje de supervivencia hasta este punto es: "
                  << total * 100 << "%";
      } else if (decision == 2) {
        total += decisión_riesgo;
        std::cout
            << std::endl
            << "Decides no arriesgarte y corres lo más rápido que puedes. "
               "Logras perder a los zombis y llegas a un edificio más grande.\n"
               "Dentro encuentras a un grupo de supervivientes que te ofrecen "
               "refugio."
            << std::endl;
        std::cout << "[1]-Unirte a ellos y quedarte en el refugio"
                  << "-------------------------"
                  << "[2]-Rechazar su oferta y continuar por tu cuenta"
                  << std::endl;
        decision = FuncioningresarEleccion(opcionesValidas, cantidadOpciones);
        if (decision == 1) {
          total += buena_decisión;
          std::cout << std::endl
                    << "Decides unirte al grupo. El refugio parece seguro, "
                       "aunque algo rudimentario. Con el tiempo, te adaptas a "
                       "la nueva vida.\n"
                       "El grupo está compuesto por diferentes personas, "
                       "algunas amables y otras más reservadas. Un día, el "
                       "líder del grupo te pide\n"
                       "que te unas a una misión para buscar más recursos en "
                       "un almacén cercano. ¿Qué harás?"
                    << std::endl;
          std::cout << "[1]-Aceptar la misión y ayudar al grupo"
                    << "-------------------------"
                    << "[2]-Rechazar la misión y quedarte en el refugio"
                    << std::endl;
          std::cin >> decision;

          if (decision == 1) {
            total -= decisión_riesgo;
            std::cout
                << std::endl
                << "Acepte la misión y te adentras con el grupo en las calles. "
                   "A lo lejos, ves el almacén, pero también percibes\n"
                   "que hay algo extraño. El ambiente está demasiado "
                   "tranquilo. Cuando llegan al almacén, descubren que está "
                   "lleno de zombis.\n"
                   "El grupo comienza a luchar, pero las cosas se complican "
                   "rápidamente. ¿Qué harás?"
                << std::endl;
            std::cout << "[1]-Unirte a la lucha y ayudar a tu grupo"
                      << "-------------------------"
                      << "[2]-Correr hacia el edificio cercano y buscar refugio"
                      << std::endl;
            decision =
                FuncioningresarEleccion(opcionesValidas, cantidadOpciones);
            if (decision == 1) {
              total -= decisión_riesgo;
              std::cout
                  << std::endl
                  << "Te unes a la lucha. La batalla es feroz, pero logras "
                     "salvar a algunos miembros del grupo. Finalmente,\n"
                     "consiguen salir del almacén con vida, aunque muchos se "
                     "han herido en el proceso."
                  << std::endl;
              std::cout
                  << std::endl
                  << "Tu porcentaje de supervivencia hasta este punto es: "
                  << total * 100 << "%";
            } else if (decision == 2) {
              total += buena_decisión;
              std::cout
                  << std::endl
                  << "Decides correr hacia el edificio cercano, dejando a tu "
                     "grupo atrás. Aunque logras encontrar un refugio seguro,\n"
                     "te sientes culpable por no haber ayudado a los demás."
                  << std::endl;
              std::cout
                  << std::endl
                  << "Tu porcentaje de supervivencia hasta este punto es: "
                  << total * 100 << "%";
            }
          } else if (decision == 2) {
            total += buena_decisión;
            std::cout
                << std::endl
                << "Decides rechazar la misión y quedarte en el refugio. Con "
                   "el tiempo, el grupo se ve cada vez más vulnerable,\n"
                   "y el líder empieza a perder confianza en tus habilidades. "
                   "Un día, algunos miembros del grupo se van en busca de más "
                   "recursos.\n"
                   "Tú decides seguir por tu cuenta. ¿Qué harás ahora?"
                << std::endl;
            std::cout << "[1]-Buscar otro refugio seguro en las cercanías"
                      << "-------------------------"
                      << "[2]-Ir al mercado cercano en busca de suministros"
                      << std::endl;
            decision =
                FuncioningresarEleccion(opcionesValidas, cantidadOpciones);
            if (decision == 1) {
              std::cout << std::endl
                        << "Decides buscar otro refugio. Después de horas de "
                           "caminar, encuentras un lugar tranquilo.\n"
                           "Te sientes aliviado, pero el miedo nunca "
                           "desaparece. Sabes que el mundo ya no es el mismo."
                        << std::endl;
              std::cout
                  << std::endl
                  << "Tu porcentaje de supervivencia hasta este punto es: "
                  << total * 100 << "%";
            } else if (decision == 2) {
              std::cout << std::endl
                        << "Decides ir al mercado cercano. Al llegar, ves a "
                           "varios zombis deambulando por el lugar. Sin "
                           "embargo, logras evitar\n"
                           "el enfrentamiento y entras al edificio. En el "
                           "interior, encuentras algo de comida, agua y una "
                           "linterna, lo que te da algo de esperanza."
                        << std::endl;
              std::cout
                  << std::endl
                  << "Tu porcentaje de supervivencia hasta este punto es: "
                  << total * 100 << "%";
            }
          }
        } else if (decision == 2) {
          total += buena_decisión;
          std::cout << std::endl
                    << "Decides rechazar la oferta del grupo. Sabes que la "
                       "vida en grupo podría ser más segura, pero también te "
                       "sientes incómodo con la idea.\n"
                       "Sigues tu camino por tu cuenta, explorando la ciudad "
                       "desierta. Después de varios días de caminar, llegas a "
                       "un pequeño parque\n"
                       "y decides descansar. Sin embargo, cuando te sientas a "
                       "tomar agua, escuchas pasos acercándose. ¿Qué harás?"
                    << std::endl;
          std::cout << "[1]-Esconderte entre los árboles y esperar"
                    << "-------------------------"
                    << "[2]-Salir corriendo hacia la ciudad" << std::endl;
          decision = FuncioningresarEleccion(opcionesValidas, cantidadOpciones);

          if (decision == 1) {
            total += buena_decisión;
            std::cout << std::endl
                      << "Te escondes entre los árboles y logras quedarte en "
                         "silencio. Los pasos se acercan, pero luego se alejan "
                         "sin detectar tu presencia.\n"
                         "Parece que los zombis no te han encontrado. Después "
                         "de un rato, continúas tu viaje."
                      << std::endl;
            std::cout << std::endl
                      << "Tu porcentaje de supervivencia hasta este punto es: "
                      << total * 100 << "%";

          } else if (decision == 2) {
            total += decisión_riesgo;
            std::cout << std::endl
                      << "Decides salir corriendo. Te adentras en la ciudad y "
                         "en medio del caos, llegas a un edificio donde "
                         "encuentras más sobrevivientes."
                      << std::endl;
            std::cout << std::endl
                      << "Tu porcentaje de supervivencia hasta este punto es: "
                      << total * 100 << "%";
          }
        }
      }
    }
  }
  return total;
}

int FuncionIngresarEleccion(int x) {
  do {
    cin >> x;
    if ((x != 1) && (x != 2)) {
      cout << "Opcion no valida, Ingresar de nuevo: ";
    }

  } while ((x != 1) && (x != 2));

  return x;
};

int FuncionProbabilidad(double x) {
  srand(time(0));

  int numran = (1 + (rand() % 100));

  double prob = (numran * 0.01);

  if (prob <= x) {
    return 1;
  } else {
    return 0;
  }
};

int JuegoCorto() {
  int choice, a;

  system("cls");

  cout << "Eres uno de los ultimos sobrevivientes en la ciudad infestada de "
          "zombies.\n";
  cout << "Tu objetivo es escapar de la ciudad y encontrar un refugio "
          "seguro.\n\n";

  // Primera elección
  cout << "Ves una casa abandonada y una tienda de armas.\n";
  cout << "Donde quieres ir? \n1 = Casa, 2 = Tienda de armas: " << endl;

  choice = FuncionIngresarEleccion(choice);

  if (choice == 1) {
    cout << "\nEntras en la casa en busca de suministros.\n";
    cout << "Encuentras algo de comida y un botiquin de primeros auxilios.\n";
    cout << "De repente, oyes ruidos, parece que hay un zombie en la casa.\n";

    cout << "Quieres eliges?\nEsconderte(1) ----  Luchar(2): ";

    choice = FuncionIngresarEleccion(choice);

    if (choice == 1) {
      cout << "\nTe escondes detras de una puerta. El zombie pasa de largo y "
              "logras salir de la casa ileso.";
    } else if (choice == 2) {
      cout << "\nDecides enfrentarte al zombie con lo que tienes a mano.\n";
      cout
          << "Luchas valientemente, pero el zombie te hiere.";  // de cada 5
                                                                // ataques
                                                                // zombies 3
                                                                // personas
                                                                // terminan
                                                                // infectada, la
                                                                // formula es
                                                                // (los casos
                                                                // favorables /
                                                                // los casos
                                                                // totales),
                                                                // dando una
                                                                // probabilidad
                                                                // de infectare
                                                                // con un 60 %
      a = FuncionProbabilidad(0.6);
      if (a == 1) {
        cout << "\n\nHas sido infectado, y en pocos minutos te convertiras en "
                "zombie...";
        return 1;
      }
    }

    // Segunda elección
    cout << endl
         << endl
         << " Avanzas por las calles y ves un grupo de zombies bloqueando el "
            "camino principal.\n";
    cout << "Puedes intentar rodearlos o buscar otro camino.\n";
    cout
        << "Que eliges?\nRodear a los zombies(1) ----  Buscar otro camino(2): ";
    choice = FuncionIngresarEleccion(choice);

    if (choice == 1) {
      cout << "\nIntentas rodear al grupo de zombies.\n";
      a = FuncionProbabilidad(0.4);
      if (a == 1) {
        cout << "\n\nHas hecho mucho ruido y atacan todos lo zombies...";
        return 1;
      }

      // DE CADA 10 PERSONAS QUE LO INTENTAN SOLO 4 LO LOGRAN SIN LLAMAR LA
      // ATENCION DE LOS ZOMBIES, la formula es (los casos favorables / los
      // casos totales), dando una probabilidad de infectare con un 60 %

      cout << "¡Sigues avanzando!\n";
    } else if (choice == 2) {
      cout << "\nEncuentras un camino alternativo, pero es mas largo y "
              "escuchas ruidos extraños.\n";
      cout
          << "De repente, un zombie aparece de la nada y te ataca.\n";  // DE
                                                                        // CADA
                                                                        // 5
                                                                        // ATAQUES
                                                                        // ZOMBIES
                                                                        // 3
                                                                        // PERSONAS
                                                                        // TERMINAN
                                                                        // INFECTADAS
      a = FuncionProbabilidad(0.6);
      if (a == 1) {
        cout << "\n\nHas sido infectado, y en pocos minutos te convertiras en "
                "zombie...";
        return 1;
      }
      cout << "Afortunadamente logras defenderte, pero estás herido.\n";
    }

    // Tercera elección
    cout << "\nFinalmente, llegas a la salida de la ciudad, pero está cerrada "
            "con una cerca alta.\n";
    cout << "Ves un auto cerca que podrías usar para derribar la cerca o "
            "podrias intentar treparla.\n";
    cout << "Que decides hacer? (1 = Usar el auto, 2 = Trepar la cerca): ";
    choice = FuncionIngresarEleccion(choice);

    if (choice == 1) {
      a = FuncionProbabilidad(0.4666);
      if (a == 1) {
        cout << "\n\nEL CARRO NO HA LOGRADO AVANZAR, y el ruido del motor "
                "intentando encender ha llamado a muchos zombies lo cuales ya "
                "rodearon el carro completamente";
        return 1;
      }  // 7 de cada 15 carros en un apocalipsis zombie no funcionan
         // correctamente
      cout << "\nSubes al auto y aceleras hacia la cerca.\n";
      cout << "Logras abrirte paso y escapar de la ciudad. Has sobrevivido al "
              "apocalipsis zombie!\n";
      return 1;
    } else if (choice == 2) {
      cout
          << "\nIntentas trepar la cerca, \n";  // De cada 10 personas que
                                                // trepan una reja  2 se caen
                                                // por los nervios a los zombies
      a = FuncionProbabilidad(0.2);
      if (a == 1) {
        cout << "\n pero la cerca esta muy lisa y terminas cayendo, atrayendo "
                "a los zombies.\n";
        return 1;
      } else {
        cout << "Logras escapar, pero estas herido levemente.\n";
        cout << "A lo lejos logras ver un refugio militar, te miran a lo lejos "
                "y van corriendo a salvarte. Sobreviviste al apocalipsis "
                "zombie!\n";
      }
    }
  }

  // CAMBIO DE HISTORIA

  else if (choice == 2) {
    cout << "\nVas a la tienda de armas y encuentras una pistola y algunas "
            "balas.\n";
    cout << "Ahora estas mejor preparado para enfrentarte a los zombies.\n";

    // Segunda eleccion
    cout << "Al salir de la tienda, escuchas ruidos extranos. Puedes:\n";
    cout << " Investigar el ruido (1) ----  Ignorar el ruido y seguir adelante "
            "(2)\n";
    choice = FuncionIngresarEleccion(choice);

    if (choice == 1) {
      cout << "\nTe acercas al ruido y descubres a un grupo de zombies.\n";
      cout << "Decides usar tu pistola para defenderte.\n";  // de cada 100
                                                             // tiros la pistola
                                                             // se encasquilla
                                                             // con 3 disparos
      a = FuncionProbabilidad(0.03);
      if (a == 1) {
        cout << "\n\nTu pistola se ha encasquillado!! Un zombie se ha acercado "
                "demasiado y te ha atacado...";
        a = FuncionProbabilidad(0.6);
        if (a == 1) {
          cout << "\n\nHas sido infectado, y en pocos minutos te convertiras "
                  "en zombie...";
          return 1;
        } else {
          cout << "Lograste esquivar al zombie!!\n";
        }
      } else {
        cout << "¡Disparas y logras eliminar a algunos, pero mas vienen hacia "
                "ti!\n";
      }
      cout << "Tienes que decidir rapidamente:\n";
      cout << "Correr hacia un callejon cercano (1) ---- Seguir disparando "
              "hasta que se acaben las balas (2)\n";
      choice = FuncionIngresarEleccion(choice);

      if (choice == 1) {
        cout << "\nCorres hacia el callejon y logras esconderte. Los zombies "
                "pierden tu rastro.\n";
        cout << "Te tomas un momento para recuperar el aliento y planear tu "
                "proximo movimiento.\n";
      } else if (choice == 2) {
        cout << "\nSigues disparando, pero te quedas sin balas. Los zombies te "
                "rodean y tienes que luchar cuerpo a cuerpo.\n";
        a = FuncionProbabilidad(0.6);
        if (a == 1) {
          cout << "\n\nHas sido infectado, y en pocos minutos te convertiras "
                  "en zombie...";
          return 1;
        }
      }
      cout << "Logras salir con vida, pero estas herido levemente y agotado.\n";
    } else if (choice == 2) {
      cout << "\nDecides ignorar el ruido y seguir adelante.\n";
      cout << "Sin embargo, te encuentras con un zombie que te ataca.\n";

      a = FuncionProbabilidad(0.03);
      if (a == 1) {
        cout << "\n\nTu pistola se ha encasquillado!! Un zombie se ha acercado "
                "demasiado y te ha atacado...";
        a = FuncionProbabilidad(0.6);
        if (a == 1) {
          cout << "\n\nHas sido infectado, y en pocos minutos te convertiras "
                  "en zombie...";
          return 1;
        } else {
          cout << "Lograste esquivar al zombie!!\n";
        }
      } else {
        cout << "¡Disparas y logras eliminar al zombie";
      }
    }

    // Tercera eleccion
    cout << "\nSigues avanzando y llegas a un cruce de caminos.\n";
    cout << "Puedes:\n";
    cout << "Tomar el camino a la izquierda, que parece mas seguro (1) ---- ";
    cout << "Tomar el camino a la derecha, que parece mas peligroso pero mas "
            "corto (2)\n";
    choice = FuncionIngresarEleccion(choice);

    if (choice == 1) {
      cout << "\nLlegas a una estacion de servicio abandonada. Hay comida y "
              "agua adentro, pero parece peligroso.\n";
      cout << "Quieres entrar?  Si (1) ---- No (2): ";
      choice = FuncionIngresarEleccion(choice);

      if (choice == 1) {
        cout << "\nEncuentras comida y agua, pero un zombie te sorprende y te "
                "ataca.\n";

      } else if (choice == 2) {
        cout << "\nDecides no arriesgarte y sigues avanzando.\n";
      }
    } else if (choice == 2) {
      cout << "\nTomas el camino a la derecha y te encuentras con un grupo de "
              "zombies.\n";  // De cada 10 personas  solamente 4 personas logran
                             // escapar sin ser infectados
      a = FuncionProbabilidad(0.4);
      if (a == 1) {
        cout << "\n\nHas hecho mucho ruido y los zombies te han visto, eso ha "
                "probocado que te atacaran todos a la vez...";
        return 1;
      }

      cout << "Pero te ves superado y tienes que escapar.\n";
    }

    cout << "Logras escapar, pero estás herido levemente.\n";
    cout << "A lo lejos logras ver un refugio militar, te miran a lo lejos y "
            "van corriendo a salvarte. Sobreviviste al apocalipsis zombie!\n";
  }
}

void MenuPrincipal(int* menuPrincipal) {
  cout << endl << endl << "-----Pleitechon-----" << endl;
  cout << "1. Modos de supervivencia zombie" << endl;
  cout << "2. Buckshot Roulette" << endl;
  cout << "3. Integrantes del Equipo" << endl;
  cout << "4. Salir" << endl;

  cout << endl << "Elige una opcion:" << endl;
  cin >> *menuPrincipal;

  system("cls");
}

void intergrantesDelEquipo(void) {
  cout << "-----INTEGRANTES-----" << endl << endl;
  cout << "Javier Alejandro Salamanca Reyes 00056824" << endl;
  cout << "Jose Martin Luna Ramos 00308324" << endl;
  cout << "Ulises Edgardo Ramírez Cabrera 00023624" << endl;
  cout << "German David Villalobos Vaquiz 00109224" << endl;

  int continuar;
  cout << endl << endl << "Presiona [1] cuando termines de leer" << endl;
  cin >> continuar;

  if (continuar == 1) {
    system("cls");
  }
}

void ModosZombies(int* modoszombies) {
  cout << endl << "-----SOLITARIO-----" << endl;
  cout << "1. Partida express" << endl;
  cout << "2. Partida Larga" << endl;
  cout << "3. Volver al menu principal" << endl;
  cout << "4. Salir del juego" << endl;

  cout << endl << "Elige una opcion:" << endl;
  cin >> *modoszombies;

  system("cls");
}

int main()

{
  int menuPrincipal = 0, regresarMenuPrincipal = 1, modoszombies = 0,
      menu1vs1 = 0, PuntosJugadorSolitario = 0, verHistorial = 1;
  int PuntosJugador1 = 0, PuntosJugador2 = 0;
  int jugador;
  string jugador1, jugador2;

  do {
    MenuPrincipal(&menuPrincipal);
    do {
      switch (menuPrincipal) {
        case 1:
          ModosZombies(&modoszombies);
          switch (modoszombies) {
            case 1:

              jugador = JuegoCorto();

              break;

            case 2:
              jugador = juegoLargo();

              break;

            case 3:
              regresarMenuPrincipal = 0;
              break;

            case 4:
              menuPrincipal = 6;
              break;

            default:
              cout << endl
                   << "Ha ingesado una opcion de Menu Invalido. Porfavor "
                      "vuelva a intentarlo"
                   << endl;
              break;
          }
          break;
        case 2:
          menuEscopeta(&menuPrincipal);
          break;
        case 3:
          intergrantesDelEquipo();
          break;

        case 4:
          cout << endl << "Hasta Pronto! Gracias por jugar :D" << endl;
          return 0;
          break;

        default:
          cout << "Ha ingresado una opcion de Menu invalido. Porfavor vuelva a "
                  "intentarlo"
               << endl;
          regresarMenuPrincipal = 0;
          break;
      }
    } while (regresarMenuPrincipal != 0);

  } while (menuPrincipal != 5);

  cout << endl << endl;
  return 0;
}
