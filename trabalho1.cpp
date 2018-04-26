//Codigo em C++ do trabalho de Software Basico

// Desenvolvedores: Túlio Lima e Débora Ferreira dos Santos

// Descrição do trabalho 1
// Objetivos:
// Funcoes:

// Como compilar


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
	if ( !file_exist(argv[2]) )
	{
		string arg1 = argv[1];
		string file_entrada = arg1 + ".asm";
		cout << file_entrada << endl;	//TESTE
		std::cout << file_exist(teste);	//TESTE
		printf("Erro! Arquivo não foi encontrado nesse diretório.\n");
		return 0;
	}


	// 2 - INICIALIZAÇÃO DE VARIÁVEIS
 	const char* file_entrada = argv[2];
 	const char* file_saida = argv[3];

	string spre = "file.pre";
	string smcr = "file.mcr";
	const char* file_pre = spre.c_str();
	const char* file_mcr = smcr.c_str();


	//3 - CHAMADA E AVALIAÇÃO DE OPERAÇÕES
	if ( ! strcmp (argv[1], "-p") )
	{
		if (  preprocessamento(file_entrada, file_saida) )
		{
			printf("\n \n Pré-processamento não pode ser concluído \n");
			return 0;
		}
		printf("\n \n Pré-processamento concluído com sucesso. \n");
		return 0;
	}	
	if ( ! strcmp (argv[1], "-m") )
	{
		if (  preprocessamento(file_entrada, file_pre) )
		{
			printf("\n \n Pré-processamento não pode ser concluído \n");
			return 0;
		}
		printf("\n \n Pré-processamento concluído com sucesso. \n");


		if ( macro(file_pre, file_saida) ) 
		{
			printf("\n \n Processamento de macros não pode ser concluído \n");
			return 0;
		}
		printf("\n \n Processamento de macros concluído com sucesso. \n");
		return 0;
	}	

	if ( ! strcmp (argv[1], "-o") )
	{
		if (  preprocessamento(file_entrada, file_pre) )
		{
			printf("\n \n Pré-processamento não pode ser concluído \n");
			return 0;
		}
		printf("\n \n Pré-processamento concluído com sucesso. \n");


		if ( macro(file_pre, file_mcr) ) 
		{
			printf("\n \n Processamento de macros não pode ser concluído \n");
			return 0;
		}
		printf("\n \n Processamento de macros concluído com sucesso. \n");
		return 0;

		if ( montagem(file_mcr, file_saida) ) 
		{
			printf("\n \n Montagem não pode ser concluída \n");
			return 0;
		}
		printf("\n \n Montagem concluída com sucesso. \n");
		return 0;
	}

	else
	{
		printf("\n \n Erro! Tipo de operação deve ser indicado por: -p -m ou -o \n");
	}
	return 0;


}