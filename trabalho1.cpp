//Codigo em C++ do trabalho de Software Basico

// Desenvolvedores: Túlio Lima e Débora Ferreira dos Santos

// Descrição do trabalho 1
// Objetivos:
// Funcoes:

// Como compilar

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;


/**
 *@brief Verifica existência de arquivo
 *
 *@param fileName Nome do arquivo
 *
 */
bool file_exist( std::string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}



int main(int argc, char** argv)
{
	//NOTE: argv[0]=name_of_executable; argv[1]=tipo de operação
	//NOTE: argv[2]=arquivo entrada; argv[3] = arquivo saida

	//VERIFICA ARGUMENTOS 
	//Verifica número de argumentos
	if (argc != 4)
	{
		printf("Erro! Comando deve incluir 3 argumentos.\n");
		return 0;
	}

	//Verifica existência de arquivo
	string arg1 = argv[2];
	string file_entrada = arg1 + ".asm";
	cout << "Arquivo de entrada: " file_entrada << endl;	//TESTE
	std::cout << "Arquivo existe: " << file_exist(file_entrada);	//TESTE
	if ( !file_exist(file_entrada) )
	{
		printf("Erro! Arquivo não foi encontrado nesse diretório.\n");
		return 0;
	}


	//TODO: criar a variável de file_saida pa usar na chamada das funçoes a seguir

	//CHAMADA E AVALIAÇÃO DE OPERAÇÕES
	if ( ! strcmp (argv[1], "-p") )
	{
		//TODO: chamar preprocessamento
		return 0;
	}	
	if ( ! strcmp (argv[1], "-m") )
	{
		//TODO: chamar preprocesamento
		//TODO: chamar macro
		return 0;
	}	
	if ( ! strcmp (argv[1], "-o") )
	{
		//TODO: chamar preprocesamento
		//TODO: chamar macro
		//TODO: chamar montagem
		return 0;
	}
	else
	{
		printf("\n \n Erro! Tipo de operação deve ser indicado por: -p -m ou -o \n");
	}
	return 0;


}