//Codigo em C++ do trabalho de Software Basico

// Desenvolvedores: Túlio Mariano da Silva Lima e Débora Ferreira dos Santos

// Descrição do trabalho 1
// Objetivos:
// Funcoes:

// Como compilar

#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <string>
#include <cstring>
#include <iostream>
#include <map>
#include <cstddef>
#include <vector>

using namespace std;

//DEFINIÇÃO DE STRUCTS
typedef struct tabela_simbolo
{
	string simbolo;
	int valor;
} tabela_simbolo;

typedef struct tabela_instrucao
{
  string mnemonico;
  string opcode; 
  int n_operando;
} tabela_instrucao;

typedef struct tabela_diretiva
{
	string mnemonico;
	int n_operando;
} tabela_diretiva;


//DEFINIÇÃO DAS TABELAS
vector<tabela_simbolo> tabela_simbolo_vector;

vector<tabela_instrucao> tabela_instrucao_vector;

vector<tabela_diretiva> tabela_diretiva_vector;



//INICIALIZAÇÃO DAS TABELAS
//*****TABELA DE INSTRUÇÕES
void inicia_tabela_instrucao()
{
	tabela_instrucao temp;

	temp.mnemonico = "ADD";
	temp.opcode = "01";
	temp.n_operando = 1;
	tabela_instrucao_vector.push_back(temp); 

	temp.mnemonico = "SUB";
	temp.opcode = "02";
	temp.n_operando = 1 ;
	tabela_instrucao_vector.push_back(temp); 

	temp.mnemonico = "MULT";
	temp.opcode = "03";
	temp.n_operando = 1 ;
	tabela_instrucao_vector.push_back(temp); 

	temp.mnemonico = "DIV";
	temp.opcode = "04";
	temp.n_operando = 1 ;
	tabela_instrucao_vector.push_back(temp); 

	temp.mnemonico = "JMP";
	temp.opcode = "05";
	temp.n_operando = 1  ;
	tabela_instrucao_vector.push_back(temp); 

	temp.mnemonico = "JMPN";
	temp.opcode = "06";
	temp.n_operando = 1 ;
	tabela_instrucao_vector.push_back(temp); 

	temp.mnemonico = "JMPP";
	temp.opcode = "07";
	temp.n_operando = 1 ;
	tabela_instrucao_vector.push_back(temp); 

	temp.mnemonico = "JMPZ";
	temp.opcode = "08";
	temp.n_operando = 1 ;
	tabela_instrucao_vector.push_back(temp); 

	temp.mnemonico = "COPY";
	temp.opcode = "09";
	temp.n_operando = 2  ;
	tabela_instrucao_vector.push_back(temp); 

	temp.mnemonico = "LOAD";
	temp.opcode = "10";
	temp.n_operando = 1 ;
	tabela_instrucao_vector.push_back(temp); 

	temp.mnemonico = "STORE";
	temp.opcode = "11";
	temp.n_operando = 1  ;
	tabela_instrucao_vector.push_back(temp); 

	temp.mnemonico = "INPUT";
	temp.opcode = "12";
	temp.n_operando = 1  ;
	tabela_instrucao_vector.push_back(temp); 

	temp.mnemonico = "OUTPUT";
	temp.opcode = "13";
	temp.n_operando = 1 ;
	tabela_instrucao_vector.push_back(temp); 

	temp.mnemonico = "STOP";
	temp.opcode = "14";
	temp.n_operando = 0 ;
	tabela_instrucao_vector.push_back(temp); 
}

void inicia_tabela_diretiva()
{
	tabela_diretiva temp2;

	temp2.mnemonico = "SECTION";
	temp2.n_operando = 1;
	tabela_diretiva_vector.push_back(temp2); 

	temp2.mnemonico = "SPACE";
	temp2.n_operando = 1;
	tabela_diretiva_vector.push_back(temp2); 

	temp2.mnemonico = "CONST";
	temp2.n_operando = 1;
	tabela_diretiva_vector.push_back(temp2); 
}


bool file_exist(std::string fileName)
{
	//fileName = fileName + ".asm" ;
	std::ifstream infile(fileName);
	return infile.good();
}

string filtro_comentarios(string line)
{
	size_t poscom = line.find(";");
	int coluna;

	if (poscom != (line).npos)
	{
		coluna = poscom;
		line = line.substr(0, coluna);
	}
	return (line);
}

string formato_padrao(string line)
{
	size_t posspace;
	size_t postab = line.find("\t");

	while (postab != line.npos) //loop que tira tabs e troca por espacos.
	{
		if (postab == 0)
		{
			line.erase(line.begin() + postab);
		}
		else
		{
			line.replace(line.begin() + postab, line.begin() + postab + 1, " ");
		}
		postab = line.find("\t");
	}

	posspace = line.find(" "); // loop que tira espacos a mais.
	while (posspace != line.npos)
	{ // o formato padrao eh com todos argumentos
		if (posspace == 0)
		{ // com apenas um espaco entre eles.
			do
			{
				line.erase(line.begin() + posspace);
				posspace = line.find(" ");
			} while (posspace == 0);
		}
		else
		{
			posspace = line.find("  ");
			while (posspace != line.npos)
			{
				line.erase(line.begin() + posspace);
				posspace = line.find("  ");
			}
		}
	}
	if (line[line.size() - 1] == ' ')
	{ //retira espacos no final
		size_t posfinal = line.size() - 1;
		line.erase(line.begin() + posfinal);
	}

	if (line == "\n")
	{			   //se a linha se resumir a uma quebra de linha,
		line = ""; //a mesma eh descartada.
	}

	return (line);
}

//void lerarquivo(char* file_name,char* file_name2 ) {
int lerarquivo(std::string file_name, char *file_name2)
{
	string line;
	string nome, saida, mcr, pontoo;
	nome = file_name2;

	nome = nome.substr(0, nome.size());
	cout << "nome: " << nome << endl;

	saida = nome.substr(0, nome.size()) + ".pre";
	cout << "saida: " << saida << endl;
	mcr = nome.substr(0, nome.size()) + ".MCR";
	//cout << mcr << endl;
	pontoo = nome.substr(0, nome.size()) + ".o";

	const char *psaida = saida.c_str();
	const char *pmcr = mcr.c_str();
	const char *ppontoo = pontoo.c_str();

	//cout<<file_name<<endl;
	ifstream myfile(file_name);
	int achoutext = 0, achoudata = 0, errosection = 0, erro_ordem_section = 0;

	remove("auxiliar");
	remove("MNT");
	remove("MDT");
	remove("EQU");
	remove(psaida);
	remove(pmcr);
	remove("tabela_de_simbolos");
	remove(ppontoo);

	int lineachousection = 0;

	ofstream mfile("auxiliar", ios::app);
	if (myfile.is_open())
	{
		int linecounter = 0;
		while (getline(myfile, line))
		{
			linecounter++;
			line = filtro_comentarios(line);
			line = formato_padrao(line); // remove tabulacoes, espacos extras e quebras de linhas.
			if (mfile.is_open() && line != "")
			{
				for (int i = 0; i < line.size(); i++)
				{
					line[i] = toupper(line[i]);
				}
				//cout << line << endl;
				mfile << line << endl;
			}
			if (line.find("SECTION TEXT") == 0)
			{
				achoutext = 1;
				if (lineachousection == 0)
				{
					lineachousection = linecounter;
				}
			}
			if (line.find("SECTION DATA") == 0)
			{
				achoudata = 1;
				if (achoutext == 0)
				{
					erro_ordem_section = 1;
				}
				if (lineachousection == 0)
				{
					lineachousection = linecounter;
				}
			}
			if (line.find("SECTION") == 0)
			{
				size_t pos = line.find("SECTION");
				int tamlinha = line.size();
				string sectionerrada = line.substr(pos + 8, tamlinha);
				//cout << sectionerrada << endl;
				if ((sectionerrada.compare("DATA") != 0) && (sectionerrada.compare("TEXT") != 0))
				{
					errosection = 1;
				}
			}
		}
		//cout << "\n";
		myfile.close();
	}

	else
		cout << "\nArquivo nao pode ser aberto!!!\n\n";

	if (achoutext == 0)
	{
		cout << "ERRO, FALTOU A SECTION TEXT" << endl;
	}
	if (achoudata == 0)
	{
		cout << "ERRO, FALTOU A SECTION DATA" << endl;
	}
	if (errosection == 1)
	{
		cout << "ERRO na difinição do Section" << endl;
	}
	if (erro_ordem_section == 1)
	{
		cout << "ERRO, A DIRETIVA 'TEXT' DEVE SEMPRE VIR ANTES DA DIRETIVA 'DATA'" << endl;
	}

	return lineachousection;
}

int leargumentos(string argumentos)
{
	//return 0 caso não tenha nenhum argumento
	//return 1 caso tenha um argumento
	//return 2 caso tenha 2 argumentos
	//return 3 caso tenha 3 argumentos
	//return 4 caso tenha 4 argumentos
	//para cada retorno a função que chama essa ativa uma rotina diferente
	argumentos = argumentos.substr(1, argumentos.size());
	int i = 0, n = 0, m = 0, l = 0;
	cout << "Chamou a função e está retornando o que foi recebido pela função:" << argumentos << endl;

	//se não encontrar a virgula verifica se tem o '&', se não tiver retorna 0
	//se encontrar entra em uma rotina que conta a quantidade de vírgulas que tem, para saber quantos argumentos tem.

	for (i = 0; argumentos[i] != '\0'; i++)
	{
		if (argumentos[i] == ',')
		{
			n = n + 1;
		}
	}

	for (i = 0; argumentos[i] != '\0'; i++)
	{
		if (argumentos[i] == '&')
		{
			m = m + 1;
		}
	}

	for (i = 0; argumentos[i] != '\0'; i++)
	{
		if (argumentos[i] == ' ')
		{
			l = l + 1;
		}
	}

	if (l > 0)
	{
		cout << "Os argumentos estão separados por espaço, favor retirar os espaços entre os argumentos...\nDefina os argumentos separado apenas por vígulas..." << endl;
		return 5;
	}
	//cout << "A expressão tem " << n << " vírgulas..." << endl;
	//então cria vários caso para resolver esse tipo de macros

	if (n == 0)
	{
		cout << "A expressão tem " << m << " argumentos" << endl;
		if (m == 1)
		{
			return 1;
		}
		else
		{
			cout << "Aqui pode ter um erro aqui caso a MACRO precise de uma argumento, pois não existe declaração de '&' indicando o argumento" << endl;
		}
		return 0;
	}
	else if (n == 1)
	{
		cout << "A expressão tem " << m << " argumentos" << endl;
		if (m == 2)
		{
			return 2;
		}
		else
		{
			cout << "Expressão da MACRO mal definida" << endl;
			return 5;
		}
	}
	else if (n == 2)
	{
		cout << "A expressão tem " << m << " argumentos" << endl;
		if (m == 3)
		{
			return 3;
		}
		else
		{
			cout << "Expressão da MACRO mal definida" << endl;
			return 5;
		}
	}
	else if (n == 3)
	{
		cout << "A expressão tem " << m << " argumentos" << endl;
		if (m == 4)
		{
			return 4;
		}
		else
		{
			cout << "Expressão da MACRO mal definida" << endl;
			return 5;
		}
	}
}

int verifica_argumento_macro(string argumento)
{
	cout << "Vamos analisar se essa linha contém uma macro....." << endl;

	//ofstream mntfile("MNT", ios::app);
	ofstream mdtfile("MDT", ios::app);

	string linha,mntbusca, mdtbusca, token, num_de_args;
	int i, n = 0, m = 0, l = 0, contador = 0;
	string termina = "ENDMACRO";

	linha=argumento;

	for (i = 0; argumento[i] != '\0'; i++)
	{
		if (argumento[i] == ':')
		{
			n = n + 1;
		}
	}

	if (n == 1)
	{
		size_t doispontos = argumento.find(":");
		argumento = argumento.substr(doispontos + 2, argumento.size());
	}
	else if (n == 0)
	{
		cout << argumento << endl;
	}
	argumento = argumento.substr(0, argumento.find(" "));
	//aqui começa a checar na tabela MNT se existe a macro

	ifstream mntfile("MNT");

	if (mntfile.is_open())
	{
		while (getline(mntfile, mntbusca))
		{

			token = argumento;
			size_t postab = mntbusca.find("\t");
			cout << "Token aqui: " << token << endl;
			cout << "mntbusca: " << mntbusca << endl;
			mdtbusca = mntbusca.substr(0, postab);
			cout << "mdtbusca: " << mdtbusca << endl;
			cout << mdtbusca.compare(token) << endl;
			//Se achou um possível membro das macros então pode expandir
			//analisa se tem mais de um argumento, se sim resolve eles aqui... caso contrário deixa como tava.

			if (mdtbusca.compare(token) == 0)
			{
				//agora é necessário descobrir quantos argumentos essa função tem
				cout << "Para descobrir a quantidade de argumentos é necessário usar a linha: " << mntbusca << endl;
				num_de_args = mntbusca.substr(mntbusca.find("\t") + 1, mntbusca.size());
				num_de_args = num_de_args.substr(0, mntbusca.find("\t") - 3);
				cout << num_de_args << endl;
				//assim eu tenho a quantidade de argumentos mínima que eu tenho que ter na chamada dessa linha
				n=0;l=0;
				//cout << linha << endl;
				//linha = linha.substr(linha.find(" ")+1,linha.size());
				for (i = 0; linha[i] != '\0'; i++)
				{
					if (linha[i] == ',')
					{
						n = n + 1;
					}
				}

				for (i = 0; linha[i] != '\0'; i++)
				{
					if (linha[i] == ' ')
					{
						l = l + 1;
					}
				}

				if (l > 0)
				{
					cout << "Os argumentos estão separados por espaço, favor retirar os espaços entre os argumentos...\nDefina os argumentos separado apenas por vígulas..." << endl;
					return 5;
				}

				//cout << n << "\t" << l << endl;

				if (n == 0)
				{
					if (num_de_args == "1")
					{
						cout << "Acertou a quantidade de argumentos 1 ................................." << endl;
					}
					else
					{
						cout << "Erro na quantidade de argumentos 1" << endl;
					}
				}
				else if (n == 1)
				{
					if (num_de_args == "2")
					{
						cout << "Acertou a quantidade de argumentos 2 ................................." << endl;
					}
					else
					{
						cout << "Erro na quantidade de argumentos 2" << endl;
					}
				}
				else if (n == 2)
				{
					if (num_de_args == "3")
					{
						cout << "Acertou a quantidade de argumentos 3 ................................." << endl;
					}
					else
					{
						cout << "Erro na quantidade de argumentos 3" << endl;
					}
				}
				else if (n == 3)
				{
					if (num_de_args == "4")
					{
						cout << "Acertou a quantidade de argumentos 4 ................................." << endl;
					}
					else
					{
						cout << "Erro na quantidade de argumentos 4" << endl;
					}
				}
			}
		}
		mdtfile.close();
		mntfile.close();
		contador = 0;
	}
	else
		cout << "Nao foi possivel abrir o arquivo MNT para expandir macros!" << endl;

	return 0;
}

void expande_macro(char *file_name)
{

	string nome;
	//cout<<file_name << endl;
	nome = file_name;
	nome = nome.substr(0, nome.size());
	//cout << nome;

	string line, nomedamacro, nomeparam, valorparam, nomeequ, valorequ, token, mntbusca, mdtbusca, mdtline, linhabusca, comparando, linhafimacro, argumentos, auxiliar, quantidade_de_argumentos;

	string saida = nome.substr(0, nome.size()) + ".pre";

	ifstream meufile(saida);
	ofstream mntfile("MNT", ios::app);
	ofstream mdtfile("MDT", ios::app);
	ofstream menosm(nome.append(".MCR"), ios::app);

	string termina = "ENDMACRO";

	int linhamdt = 0, tam, contador = 0, compara = 0, linhafim, inicio_argumentos = 0, num_argumentos = 0;

	if (meufile.is_open())
	{

		//cout << "ta aqui?" << endl;
		while (getline(meufile, line))
		{

			size_t poscom = line.find("MACRO");
			if (poscom != line.npos)
			{
				cout << "\nTem uma MACRO aqui \n\n";
				//salva aqui o nome das MACROS definidas no código
				//Chama uma rotina para salvar em um arquivo o nome da macro, a quantidade de parametros e a linha que será adicionada na MDT
				//Pega a linha em que foi achada a macro, e encontra o nome que vem antes dos ':'
				poscom = line.find(":");
				cout << "Mostrando a posição na linha que o nome macro está: " << line.find("MACRO") << endl;
				inicio_argumentos = line.find("MACRO") + 5;
				cout << "Mostrando o inicio dos argumentos da macro: " << inicio_argumentos << endl;
				nomedamacro = line.substr(0, poscom);
				cout << nomedamacro << endl;
				cout << "Mostrando a quantidade de argumentos da MACRO:" << line.substr(inicio_argumentos, (line.size() - inicio_argumentos)) << endl;
				argumentos = line.substr(inicio_argumentos, (line.size() - inicio_argumentos));
				num_argumentos = 0;
				//aqui chama uma função para contar a quantidade de argumentos da macro 1,2,3 ou 4
				if (argumentos.size() > 0)
				{
					num_argumentos = leargumentos(argumentos);
					cout << num_argumentos << endl;
				}

				//inicialização da variável que diz qual linha estará o escopo da macro
				//cout << nomedamacro << endl;
				if (mntfile.is_open())
				{
					mntfile << nomedamacro << "\t" << num_argumentos << "\t" << linhamdt << endl; //o nome desse arquivo é MNT(Macro Name Table)
					//cout << "Formato de argumentos que a macro aceita:" << line.substr(inicio_argumentos,(line.size()-inicio_argumentos)) << endl;
					//caso o valor dos argumentos não esteja correto então mostra um erro
					getline(meufile, line);

					do
					{
						mdtfile << line << endl;
						getline(meufile, line);
						cout << line << endl;
						comparando = line;
						cout << "Comparacao: " << comparando.compare(termina) << endl;
						linhamdt++;
					} while ((comparando.compare(termina) != 0));

					cout << "\n      finalizou a MACRO      \n"
						 << endl;
				}
				else
					cout << "\nArquivo nao pode ser aberto!!!\n\n";
				//getline(meufile, line);
				//Chama uma rotina para salvar em uma tabela o código da macro até o valor ENDMACRO
				//o nome desse arquivo é MDT(Macro Definition Table)
				//strcmp(pesq, agen[contador].nome) == 0
				cout << line << endl;
			}
			else
			{
				// Se for uma chamada de macro, aqui ela sera expandida
				size_t posdelimit = line.find(" ");
				// Se nao tiver espacos, ou eh diretiva ou eh macro.
				// Testa aqui se eh macro (pela mnt)
				// Se nao for, tem que ser diretiva (verificar durante a montagem)
				//cout << "Teste 1" << endl;
				//cout << posdelimit << endl;
				//cout << line.npos << endl;
				if (posdelimit == line.npos)
				{
					ifstream mntfile("MNT");
					if (mntfile.is_open())
					{
						while (getline(mntfile, mntbusca))
						{
							token = line;
							size_t postab = mntbusca.find("\t");
							cout << "Token: " << token << endl;
							cout << "mntbusca: " << mntbusca << endl;
							mdtbusca = mntbusca.substr(0, postab);
							cout << "mdtbusca: " << mdtbusca << endl;
							cout << mdtbusca.compare(token) << endl;

							//Aqui tem que consultar a quantidade de argumentos para ver se é maior que 0, para então chamar uma rotina alternativa

							// Se entrar nesse if, achou o nome da macro na mnt
							// Vai agora entrar no if e ir na mdt.

							// Procura as macros, ainda nao expande mas ta quase la

							if (mdtbusca.compare(token) == 0)
							{
								ifstream mdtfile("MDT");
								auxiliar = mntbusca.substr(postab + 1, mntbusca.size());
								postab = auxiliar.find("\t");
								quantidade_de_argumentos = auxiliar.substr(0, postab);
								cout << "Quantidade de argumentos:" << auxiliar.substr(0, postab) << endl;

								if (getline(mntfile, linhafimacro))
								{
									int tam2 = linhafimacro.size();
									linhafimacro = linhafimacro.substr(tam2 - 1, tam2);
									cout << "linha fim da macro:" << linhafimacro << endl;
									linhafim = stoi(linhafimacro);
								}

								else
								{
									linhafim = 100000;
								}

								tam = mntbusca.size();
								linhabusca = mntbusca.substr(tam - 1, tam);
								compara = stoi(linhabusca);
								//cout << linhabusca << endl;
								//cout << compara << endl;
								cout << "linha fim : " << linhafim << endl;

								if (mdtfile.is_open())
								{

									while ((getline(mdtfile, mdtline)) && compara != contador)
									{
										contador++;
										cout << "compara: " << compara << endl;
										cout << "contador: " << contador << endl;
										cout << "linha da mdt: " << mdtline << endl;
									}

									// o arquivo MDT esta exatamente na linha da macro chamada
									// linhafim tem o valor da ultima linha que eh pra ser copiada

									do
									{
										cout << "entrou aqui!" << endl;
										if (menosm.is_open())
										{
											cout << mdtline << endl;
											menosm << mdtline << endl;
											contador++;
											cout << "contador: " << contador << endl;
											cout << "linha fim: " << linhafim << endl;
										}
									} while (getline(mdtfile, mdtline) && contador != linhafim);
								}
								else
								{
									cout << "Nao foi possivel abrir o arquivo MDT para busca" << endl;
								}
							}
						}
						if (token == "STOP")
						{ // esse if eh so pra colocar o STOP no .mcr. sem isso o stop nao entra.
							//cout << "entrou aqui!" << endl;
							if (menosm.is_open())
							{
								menosm << token << endl;
							}
						}
						mdtfile.close();
						mntfile.close();
						contador = 0;
					}
					else
						cout << "Nao foi possivel abrir o arquivo MNT para expandir macros!" << endl;
				}
				else
				{
					// Tem que chamar uma rotina aqui que olha se a linha é de uma macro com argumentos
					cout << "Pode ser uma macro com argumentos:" << line << endl;
					//cria uma função que procura pelo rotulo da macro dentro da MNT
					if (verifica_argumento_macro(line) == 0)
					{
						//caso ele não encontre a definição da macro ele continua o código a seguir
						// Se nao for definicao de macro nem chamada de macro, escreve direto no .mcr
						if (menosm.is_open())
						{
							menosm << line << endl;
						}
						else
							cout << "Nao foi possivel abrir o arquivo .mcr! " << endl;
					}
					else
					{
						cout << "Foi encontrado uma MACRO com argumentos e ela foi resolvida" << endl;
					}
				}
			}
		}
	}
	menosm.close();
	mntfile.close();
	mdtfile.close();
	meufile.close();
}

void pre_procesamento(char *file_name, int lineachousection)
{

	cout << "Começando a fazer o pre processamento do arquivo: ";
	string nome;
	cout << file_name << endl;
	nome = file_name;
	nome = nome.substr(0, nome.size());
	//nome.append(".pre");
	//cout << nome;

	string line, nomedamacro, nomeparam, valorparam, nomeequ, valorequ;
	int fim, posequ, fimequ, remover, teste, erroequ = 0;
	ifstream meufile("auxiliar");
	ofstream equfile("EQU", ios::app);
	ofstream saidafile(nome.append(".pre"), ios::app);

	if (meufile.is_open())
	{
		int linecounter = 0;
		while (getline(meufile, line))
		{
			linecounter++;
			if (line.find("EQU") != line.npos)
			{
				//cout << "\nTem um EQU aqui\n";
				fim = line.size();

				valorparam = line[fim - 1];

				posequ = line.find(":");
				nomeparam = line.substr(0, posequ);

				//salva na tabela o nome e o valor do parametro
				if (equfile.is_open())
				{
					equfile << nomeparam + "\t";
					equfile << valorparam << endl;
				}
				else
					cout << "\nArquivo nao pode ser aberto EQU!!!\n\n";

				//Verifica se EQU vem depois de SECTION
				if (linecounter >= lineachousection)
				{
					cout << "\nDiretiva EQU encontrada após a diretiva SECTION na linha " << linecounter << endl;
				}
			}
			else if (line.find("IF") != line.npos)
			{
				//cout << "\nTem um IF aqui\n";
				fim = line.size();
				size_t posif = line.find("IF");
				nomeparam = line.substr(posif + 3, fim);
				teste = nomeparam.size();
				nomeparam = line.substr(3, teste);
				//cout << line << endl;
				//cout << nomeparam << endl;
				//cout << nomeparam.size() << endl;
				ifstream equfile("EQU");
				if (equfile.is_open())
				{
					while (getline(equfile, line))
					{
						//le a linha ate o espaço depois disso
						posequ = line.find("\t");
						//depois pega o valor até o espaço e compara com o if que queremos
						nomeequ = line.substr(0, posequ);
						fimequ = line.size();
						valorequ = line[fimequ - 1];
						//line.substr(posequ,fim);
						//cout << nomeequ.size() << endl;
						//cout << valorequ.size() << endl;
						//olha na tabela de EQU procurando o valor que está logo após o IF(0 ou 1)
						if (nomeequ.compare(nomeparam) == 0)
						{
							//parametro existe na tabela e podemos verificar o seu valor
							//cout << nomeequ << endl;
							//cout << "aqui" <<endl;
							//cout << valorequ << endl;
							//verifica o valor de nomeequ
							if (valorequ == "1")
							{
								remover = 0;
								erroequ = 1;
								getline(meufile, line);
								saidafile << line << endl;
							}
							else if (valorequ == "0")
							{
								remover = 1;
								erroequ = 1;
								cout << "Remover: " << remover << endl;
								getline(meufile, line);
							}
							//se for 1 adiciona a linha posterior ao if
							//se for 0 remove a linha posterior ao if
						}
					}
					if (erroequ == 0)
					{ //Retornando o erro para a resolução de EQU não válida
						cout << "Valor de EQU válido para " << nomeparam << " não foi encontrado no arquivo, revise o código .asm." << endl;
						erroequ = 0;
					}
				}
				else
					cout << "\nArquivo EQU nao pode ser aberto!!!\n\n";
			}
			else
			{
				saidafile << line << endl;
			}
		}
		equfile.close();
		meufile.close();
		saidafile.close();
	}
}

vector<string> separate_tokens(string line)
{
	stringstream stream_line(line);
	vector<string> token_vector;
	size_t prev = 0, pos;
	//Separa tokens por espaços ou vírgulas
	while (((pos = line.find_first_of(" ", prev)) != std::string::npos) || (pos = line.find_first_of(",", prev)) != std::string::npos)
	{
		if (pos > prev)
			token_vector.push_back(line.substr(prev, pos - prev));
		prev = pos + 1;
	}
	if (prev < line.length())
		token_vector.push_back(line.substr(prev, std::string::npos));

	return token_vector;
}

void lexer(std::vector<std::string> token_vector, int n_linha)
{
	for (vector<string>::iterator it = token_vector.begin(); it != token_vector.end(); ++it)
	{
		string str = *it;
		if (isalpha(str.at(0)) || (str.at(0) == '_'))
		{
			for (string::iterator it3 = str.begin(); it3 != str.end(); ++it3)
			{
				if (!isdigit(*it3) && !isalpha(*it3) && !((*it3) == '_'))
				{
					if ((*it3) == ':')
					{
						//se for primeira string e ':' no final, então ok. Se não for isso erro
						if (!( ( it == token_vector.begin() ) &&  ((*it).back() == (*it3)) ) )
							printf("Erro léxico! \n Token inválido. Token deve ser composto por dígitos, letras ou underscore. \n Linha: %d.", n_linha);
					}
					else
					{
						printf("Erro léxico! \n Token inválido. Token deve ser composto por dígitos, letras ou underscore. \n Linha: %d.", n_linha);
						break;
					}
				}
			}
		}
		else
		{
			for (string::iterator it3 = str.begin(); it3 != str.end(); ++it3)
			{
				if (!isdigit(*it3))
				{
					printf("Erro léxico! \n Token inválido. Token deve ser iniciado por dígito ou underscore. \n Linha: %d.", n_linha);
					break;
				}
			}
		}
	}
}


void definir_label(string str, int n_address)
{
	tabela_simbolo temp;
	temp.simbolo = str;
	temp.valor = n_address;
	tabela_simbolo_vector.push_back(temp);
}


void primeira_passagem2(string file_in)
{
	//*******PRIMEIRA PASSAGEM*******
	std::ifstream infile(file_in);
	std::string line;
	string str;

	int n_linha = 1;		//número da linha do programa
	int pc = 0;				//número do endereço equivalente

	int simbolo_redefinido = 0;
	int found = 0;

	vector<string>::iterator it;

	//Cria arquivo intermediario
	//ofstream ofile("file_inter.txt");
	//While lê arquivo de entrada até o arquivo acabar
	while (std::getline(infile, line))
	{

		//ANÁLISE LÉXICA
		vector<string> token_vector = separate_tokens(line);
		lexer(token_vector, n_linha);
	
		it = token_vector.begin();
		str = *it;
		//VERIFICA SE É LABEL
		if ( str.back() == ':' )
		{
			str.erase(std::prev(str.end()));
			cout << "primeira passagem, encontrou label, o token agora é: " << str << endl; //teste
			if ( token_vector.size()) //TODO que?
			{
				for (vector<tabela_simbolo>::iterator it_s = tabela_simbolo_vector.begin(); it_s != tabela_simbolo_vector.end(); ++it_s)
					if ( ! str.compare((*it_s).simbolo) )
					{
						printf("Erro Semântico! \n Símbolo redefinido. \n Linha: %d \n", n_linha);
						simbolo_redefinido = 1;
					}
				if (! simbolo_redefinido)
				{
					//str.erase(std::prev(str.end()));
					definir_label(str,pc);
				}
			}
			if (token_vector.size()>1)
				++it;
				str = *it;
		}
		//VERIFICA SE É INSTRUÇÃO
		for (vector<tabela_instrucao>::iterator it_i = tabela_instrucao_vector.begin(); it_i != tabela_instrucao_vector.end(); ++it_i)
		{
			if ( ! str.compare( (*it_i).mnemonico) )
			{
				pc = pc + (*it_i).n_operando + 1;
				found =1;		
			}
		}
		//VERIFICA SE É DIRETIVA
		if (!found)
		{
			if ( ! str.compare("CONST"))
			{
				pc = pc;
			}
			else
			{
				if ( ! str.compare("SPACE"))
				{
					it++;
					if (it != token_vector.end())
						pc = pc + stoi(*it) -1;
				}
				else
				{
					if ( ! str.compare("SECTION"))
					{
						pc=pc;
					}
					else
					{
						printf("Erro! \n Símbolo não definido. \n Linha: %d \n", n_linha);
					}
				}
			}
		}
		++ n_linha;
	}

	for (vector<tabela_simbolo>::iterator it = tabela_simbolo_vector.begin(); it != tabela_simbolo_vector.end(); ++it)
	{
		cout << endl<< (*it).simbolo <<endl;
	}
}

int procura_simbolo( vector<string>::iterator it)
{
	if (tabela_simbolo_vector.size())
	{
		for(vector<tabela_simbolo>::iterator it_s = tabela_simbolo_vector.begin(); it_s != tabela_simbolo_vector.end(); ++it_s)
		{
			if ( ! (*it).compare( (*it_s).simbolo) )
			{
				return (*it_s).valor;
			}
		}
		return -1;
	}
	else
		return -1;
}


void segunda_passagem(string file_in, string file_out)
{
	//*******PRIMEIRA PASSAGEM*******
	std::ifstream infile(file_in);
	std::string line;
	string str;


	int n_linha = 1;		//número da linha do programa
	int pc = 0;				//número do endereço equivalente

	int found = 0;
	int symbol_value;

	vector<string>::iterator it;
	vector<string>::iterator it_end;

	vector<string> aux;
	//Cria arquivo intermediario
	ofstream ofile(file_out);
	//While lê arquivo de entrada até o arquivo acabar
	while (std::getline(infile, line))
	{

		//ANÁLISE LÉXICA
		vector<string> token_vector = separate_tokens(line);
		lexer(token_vector, n_linha);
	
		it = token_vector.begin();
		it_end = token_vector.end();
		str = *it;
		//VERIFICA SE É LABEL
		if ( str.back() == ':' )
		{
			if (token_vector.size()>1)
				++it;
				str = *it;
		}
		//VERIFICA SE É INSTRUÇÃO
		for (vector<tabela_instrucao>::iterator it_i = tabela_instrucao_vector.begin(); it_i != tabela_instrucao_vector.end(); ++it_i)
		{
			if ( ! str.compare( (*it_i).mnemonico) )
			{			
				if ( distance(it,it_end) != ((*it_i).n_operando + 1) )
				{
					printf("Erro! \n Número de operandos da instrução errado. \n Linha: %d \n", n_linha);
					//todo o que fazer?
				}
				else
				{
					aux.push_back((*it_i).opcode);
					for (int i = 0; i < (*it_i).n_operando ; i++)
					{
						++it;
						symbol_value = procura_simbolo( it);
						if ( symbol_value == -1 )
							printf("Erro! \n Símbolo não declarado. \n Linha: %d \n", n_linha);
						else
							aux.push_back(to_string(symbol_value));
						//TODO corrigir substituiçao de simbolos					
					}
				}
				found = 1;		
			}
		}
		//VERIFICA SE É DIRETIVA
		if (!found)
		{
			if ( ! str.compare("CONST"))
			{
				if ( distance(it,it_end) != 2) 
				{
					printf("Erro Sintático! \n Quantidade de operandos inválida. \n Linha: %d \n", n_linha);
				} 
				else
				{
					++it;
					if ( (*it).size() > 1)
					{
						if ((*it).at(1) == 'x')
						{
							//todo corrigir hexadecimal
							aux.push_back( to_string( stoi(*it, nullptr, 0) ) ) ;
						}
						else
							aux.push_back(*it);
					}
					else
						aux.push_back(*it);	
				}

			}
			else
			{
				if ( ! str.compare("SPACE"))
				{
					++it;
					if (it != token_vector.end())
					{
						for (int i = 0; i < stoi (*it) ; i++)
							aux.push_back("X");
					}
					else
					{
						aux.push_back("X");
					}
						
				}
				else
				{
					if ( str.compare("SECTION"))
						printf("Erro! \n Símbolo não definido. \n Linha: %d \n", n_linha);
				}
			}
		}
		found = 0;
		for (const auto &e : aux)
    		ofile << e << " ";
    	//TODO retirar linha abaixo depois
    	ofile << endl;

		++ n_linha;
		token_vector.clear();
    	aux.clear();
	}
	infile.close(); 
	ofile.close();
}



int main(int argc, char *argv[])
{
	//argc eh um inteiro com o numero de argumentos passados pela linha de comando
	//argv eh um vetor com os argumentos. argv[0] sempre sera o path do programa,
	//entao eh basicamente ignorado. por isso, o argc na verdade vai ser o numero
	//de argumentos mais um.
	string file_name;

	file_name = argv[2]; // passar para learquivo(). eh o nome do arquivo .asm.
	string file_in = file_name + ".asm";
	if (!file_exist(file_in))
	{
		cout << "\nArquivo não existe nessa pasta!!!\n\n";
		return 0;
	}

	//lerarquivo(argv[2],argv[3]);
	int lineachousection = lerarquivo(file_in, argv[3]);

	if (string(argv[1]) == "-p")
	{
		cout << endl
			 << "Iniciando o -p" << endl;
		pre_procesamento(argv[3], lineachousection);
	}
	else if (string(argv[1]) == "-m")
	{
		pre_procesamento(argv[3], lineachousection);
		expande_macro(argv[3]);
		// realiza a expansão das macros em um arquivo com extensão .mcr
		// pega o arquivo da etapa anterior, le o que está nele e executa a criação da MNT e da MDT
		// depois utiliza o algoritmo de expansão das macros que está na função de passagem zero
		// mostra esse arquivo com as macros expandidas

		//montagem();
		//codigo_objeto();
	}
	else if (string(argv[1]) == "-o")
	{
		pre_procesamento(argv[3], lineachousection);
		expande_macro(argv[3]);
		//montagem(argv[3]);
		//Realiza a montagem do código depois de expandir as macros
	}

	else
	{
		cout << " Comando de execução não encontrado.    ERRO     " << endl;
	}

	//montagem("bin.pre","bin.teste");
	//montagem("teste.pre", "teste.teste");
	//montagem2("teste.pre", "teste.teste");
	inicia_tabela_diretiva();
	inicia_tabela_instrucao();
	primeira_passagem2("teste.pre");
	//segunda_passagem("teste.teste");

	//TESTE bloco inteiro de teste
	if (tabela_simbolo_vector.size())
	{
		cout << "VALORES DA TABELA DE SIMBOLOS" << endl;
		for(vector<tabela_simbolo>::iterator it_s = tabela_simbolo_vector.begin(); it_s != tabela_simbolo_vector.end(); ++it_s)
		{
			cout << "Simbolo: " << (*it_s).simbolo << endl << "Valor: " << (*it_s).valor << endl;
		}
	}


	segunda_passagem("teste.pre", "file_final.txt");

	return 0;
}
