/*
Centro Universitário SENAC - Santo Amaro
Eng de Computação - 3º semestre 2017
Programação Orientada a Objetos - POO

-- Máquina de Estado Finita - Porta Automática --

Desenvolvido por:
Rafael Flôr Goto

*/
#include <iostream>

#define doorClosed 0               
#define doorOpen 1
#define doorOpening 2
#define doorClosing -1
#define havePerson 1
#define noPerson 0

class stateMachine {
protected:
	int state, person;

public:
	void print(int value) {								// Função mostra a saída da maquina de estado,
		std::cout << "State value: " << state << std::endl;			// sendo seu atual estado e a entrada.
		std::cout << "Person value: " << value << std::endl;
	}
};

class automaticDoor : public stateMachine {
public:
	automaticDoor(int value) {							// Construtor da classe automaticDoor onde inicia 
		state = person = value;							// a mesma com o estado de "porta fechada".
	}

	void opening() {								// As funções a seguir tem a finalidade de definir
		state = doorOpening;							// cada estado que a porta pode oscilar, que são:
		std::cout << "The door is opening!" << std::endl;			// Abrindo, Aberta, Fechando e Fechada.
	}

	void open() {
		state = doorOpen;
		std::cout << "The door is open!" << std::endl;
	}

	void closing() {
		state = doorClosing;
		std::cout << "The door is closing!" << std::endl;
	}

	void closed() {
		state = doorClosed;
		std::cout << "The door is closed!" << std::endl;
	}

	int checking(int value) {							// A função checking tem a finalidade
		if (state == doorClosed && value == havePerson) {			// de verificar as possibilidades de entradas  
			opening();							// que são recebidas e assim definir o para qual 
			return doorOpening;						// estado a maquina irá.
		}

		if (state == doorOpening && value == havePerson) {
			open();
			return doorOpen;
		}

		if (state == doorClosing && value == havePerson) {
			opening();
			return doorOpening;
		}

		if (state == doorOpen && value == havePerson) {
			open();
			return doorOpen;
		}

		if (state == doorOpen && value == noPerson) {
			closing();
			return doorClosing;
		}

		if (state == doorClosing && value == noPerson) {
			closed();
			return doorClosed;
		}

		if (state == doorOpening && value == noPerson) {
			closing();
			return doorClosing;
		}

		if (state == doorClosed && value == noPerson) {
			closed();
			return doorClosed;
		}

		return 0;
	}
};

int main(void) {									// Main do código onde, irá chamar a classe 
	int value;									// e colocar ela em um looping

	automaticDoor ad(0);

	while (1) {
		std::cout << "Entry value: ";
		std::cin >> value;

		if (value == havePerson || value == noPerson) {
			ad.checking(value);
			ad.print(value);
			std::cout << std::endl;
		}
		else continue;
	}
	return 0;
}
