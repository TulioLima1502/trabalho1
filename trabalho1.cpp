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

bool file_exist( std::string fileName)
{
	//fileName = fileName + ".asm" ;
    std::ifstream infile(fileName);
    return infile.good();
}

string filtro_comentarios(string line) {
	size_t poscom=line.find(";");
	int coluna;
	
	if (poscom!=(line).npos)
	{
		coluna=poscom;
		line=line.substr(0,coluna);
	}
	return(line);
}

string formato_padrao(string line) {
	size_t posspace;
	size_t postab = line.find("\t");

	while (postab!=line.npos) 						//loop que tira tabs e troca por espacos.
	{
		if (postab==0){
			line.erase(line.begin()+postab);
		}
		else {
			line.replace(line.begin()+postab, line.begin()+postab+1," ");
		}
		postab=line.find("\t");
	}

	posspace = line.find(" ");					// loop que tira espacos a mais.
	while (posspace!=line.npos) {				// o formato padrao eh com todos argumentos 
		if (posspace==0) {						// com apenas um espaco entre eles.
			do {
				line.erase(line.begin()+posspace);
				posspace=line.find(" ");	
			} while (posspace==0);		
		}
		else
		{
			posspace=line.find("  ");
			while (posspace!=line.npos) 
			{
				line.erase(line.begin()+posspace);
				posspace=line.find("  ");
			}
		}
	}
	if (line[line.size()-1]==' ') {      //retira espacos no final
		size_t posfinal = line.size()-1;
		line.erase(line.begin()+posfinal);
	}

	if (line=="\n") {					//se a linha se resumir a uma quebra de linha,
		line = "";						//a mesma eh descartada.
	}


	return (line);
}

//void lerarquivo(char* file_name,char* file_name2 ) { 
int lerarquivo(std::string file_name,char* file_name2 ) { 
	string line;
	string nome,saida,mcr,pontoo;
	nome=file_name2;

	nome=nome.substr(0,nome.size());
	cout << "nome: " << nome << endl;

	saida = nome.substr(0,nome.size())+".pre";
	cout << "saida: " << saida << endl;
	mcr=nome.substr(0,nome.size())+".MCR";
	//cout << mcr << endl;
	pontoo=nome.substr(0,nome.size())+".o";

	const char * psaida = saida.c_str();
	const char * pmcr = mcr.c_str();
	const char * ppontoo = pontoo.c_str();

	//cout<<file_name<<endl;
	ifstream myfile(file_name);
	int achoutext=0, achoudata=0, errosection = 0, erro_ordem_section = 0;

	remove ("auxiliar");
	remove ("MNT");
	remove ("MDT");
	remove ("EQU");
	remove (psaida);
	remove (pmcr);
	remove("tabela_de_simbolos");
	remove (ppontoo);

	int lineachousection = 0;

	ofstream mfile("auxiliar", ios::app);
	if (myfile.is_open())
	{
		int linecounter = 0;	
		while (getline(myfile, line))
		{
			linecounter++;
			line=filtro_comentarios(line);
			line=formato_padrao(line); 	// remove tabulacoes, espacos extras e quebras de linhas.
			if (mfile.is_open() && line!="")
			{
				for(int i=0;i < line.size();i++)
				{
					line[i]=toupper(line[i]);
				}
				//cout << line << endl;
				mfile << line << endl;
			}
			if (line.find("SECTION TEXT")==0){
				achoutext=1;
				if (lineachousection == 0){
					lineachousection = linecounter;
				}				
			}
			if (line.find("SECTION DATA")==0){
				achoudata=1;
				if (achoutext==0){
					erro_ordem_section=1;
				}
				if (lineachousection == 0){
					lineachousection = linecounter;
				}	
			}
			if (line.find("SECTION")==0){
				size_t pos = line.find("SECTION");
				int tamlinha = line.size();
				string sectionerrada = line.substr(pos+8,tamlinha);
				//cout << sectionerrada << endl;
				if ((sectionerrada.compare("DATA")!=0) && (sectionerrada.compare("TEXT")!=0)){
					errosection = 1;
				}
			}
		}
		//cout << "\n";
		myfile.close();
	}

	else cout << "\nArquivo nao pode ser aberto!!!\n\n";

	if (achoutext==0){
		cout << "ERRO, FALTOU A SECTION TEXT" << endl;
	}
	if (achoudata==0){
		cout << "ERRO, FALTOU A SECTION DATA" << endl;
	}
	if (errosection==1) {
		cout << "ERRO na difinição do Section" << endl;
	}
	if (erro_ordem_section==1){
		cout << "ERRO, A DIRETIVA 'TEXT' DEVE SEMPRE VIR ANTES DA DIRETIVA 'DATA'" << endl;
	}

	return lineachousection;
}

void expande_macro(char* file_name){

	string nome;
	cout<<file_name << endl;
	nome=file_name;
	nome=nome.substr(0,nome.size());
	cout << nome;

	string line, nomedamacro, nomeparam, valorparam, nomeequ, valorequ, token, mntbusca, mdtbusca, mdtline, linhabusca, comparando, linhafimacro;

	string saida = nome.substr(0,nome.size())+".pre";

	ifstream meufile(saida);
	ofstream mntfile("MNT",ios::app);
	ofstream mdtfile("MDT",ios::app);
	ofstream menosm(nome.append(".MCR"), ios::app);

	string termina="END";

	int linhamdt=0, tam, contador=0, compara=0, linhafim;

	if (meufile.is_open())
	{

		//cout << "ta aqui?" << endl;
		while (getline(meufile, line))
		{
			
			size_t poscom=line.find("MACRO");
			if (poscom!=line.npos){
				cout << "\nTem uma MACRO aqui \n\n";
				//salva aqui o nome das MACROS definidas no código
				//Chama uma rotina para salvar em um arquivo o nome da macro, a quantidade de parametros e a linha que será adicionada na MDT
				//Pega a linha em que foi achada a macro, e encontra o nome que vem antes dos ':'
				poscom=line.find(":");
				nomedamacro=line.substr(0,poscom);
				cout << nomedamacro << endl;
				//inicialização da variável que diz qual linha estará o escopo da macro
				//cout << nomedamacro << endl;
				if (mntfile.is_open())
				{
					mntfile << nomedamacro << "\t" << linhamdt << endl; //o nome desse arquivo é MNT(Macro Name Table)
					getline(meufile,line);
					do{
						mdtfile << line << endl;
						getline(meufile,line);
						cout << line << endl;
						comparando=line;
						cout << "Comparacao: " << comparando.compare(termina) << endl;
						linhamdt++;				
					}while( ( comparando.compare(termina) != 0 ) );
	
					cout << "\n      finalizou a MACRO      \n" << endl;
				}	else cout << "\nArquivo nao pode ser aberto!!!\n\n";
				//getline(meufile, line);
				//Chama uma rotina para salvar em uma tabela o código da macro até o valor ENDMACRO
				//o nome desse arquivo é MDT(Macro Definition Table)
				//strcmp(pesq, agen[contador].nome) == 0
				cout << line << endl;
				
			} else 
				{
					// Se for uma chamada de macro, aqui ela sera expandida
					size_t posdelimit = line.find(" ");
					// Se nao tiver espacos, ou eh diretiva ou eh macro.
					// Testa aqui se eh macro (pela mnt)
					// Se nao for, tem que ser diretiva (verificar durante a montagem)
					if (posdelimit == line.npos) {
						ifstream mntfile("MNT");
						if (mntfile.is_open()) {
							while (getline(mntfile, mntbusca)) {
								token = line;
								size_t postab = mntbusca.find("\t");
								cout << "Token: " << token << endl;
								cout << "mntbusca: " << mntbusca << endl;
								mdtbusca = mntbusca.substr(0, postab);
								cout << "mdtbusca: " << mdtbusca << endl;
								cout << mdtbusca.compare(token) << endl;
								// Se entrar nesse if, achou o nome da macro na mnt
								// Vai agora entrar no if e ir na mdt.

								// Procura as macros, ainda nao expande mas ta quase la
								
								if (mdtbusca.compare(token)==0) {
									ifstream mdtfile("MDT");									

									if (getline(mntfile,linhafimacro)) {
										int tam2 = linhafimacro.size();
										linhafimacro = linhafimacro.substr(tam2-1,tam2);
										linhafim = stoi(linhafimacro);
									}
									
									else {
										linhafim = 100000;
									}

									tam = mntbusca.size();
									linhabusca = mntbusca.substr(tam-1, tam);
									compara = stoi(linhabusca);	
									cout << "linha fim : " << linhafim << endl;
																														
									if (mdtfile.is_open()) {

										while ((getline(mdtfile, mdtline)) && compara!=contador) {
											contador++;
											cout << "compara: " << compara << endl;
											cout << "contador: " << contador << endl;
											cout << "linha da mdt: " << mdtline << endl;
										}

										// o arquivo MDT esta exatamente na linha da macro chamada
										// linhafim tem o valor da ultima linha que eh pra ser copiada
										
										do {
										cout << "entrou aqui!" << endl;
											if (menosm.is_open()) {
												cout << mdtline << endl;
												menosm << mdtline << endl;
												contador++;
												cout << "contador: " << contador << endl;
												cout << "linha fim: " << linhafim << endl;
											}
										} 	while (getline(mdtfile, mdtline) && contador!=linhafim);
											
										
								
									} else {
										cout << "Nao foi possivel abrir o arquivo MDT para busca" << endl;
									}

								} 
								
							}
							if (token=="STOP") {  				// esse if eh so pra colocar o STOP no .mcr. sem isso o stop nao entra.				
								//cout << "entrou aqui!" << endl;
								if (menosm.is_open()) {
									menosm << token << endl;
								}
							}
							mdtfile.close();
							mntfile.close();
							contador=0;
						} else cout << "Nao foi possivel abrir o arquivo MNT para expandir macros!" << endl;

					} else	{		
						// Se nao for definicao de macro nem chamada de macro, escreve direto no .mcr
						if (menosm.is_open()) {  
							menosm << line << endl;
						} else cout << "Nao foi possivel abrir o arquivo .mcr! " << endl; 
					}	
				} 

		}
	}
	menosm.close();	
	mntfile.close();
	mdtfile.close();
	meufile.close();
}

void pre_procesamento(char* file_name, int lineachousection) {
	
	cout << "Começando a fazer o pre processamento do arquivo: ";
	string nome;
	cout<<file_name << endl;
	nome=file_name;
	nome=nome.substr(0,nome.size());
	//nome.append(".pre");
	//cout << nome;


	string line, nomedamacro, nomeparam, valorparam, nomeequ, valorequ;
	int fim, posequ, fimequ, remover, teste, erroequ=0;
	ifstream meufile("auxiliar");
	ofstream equfile("EQU",ios::app);
	ofstream saidafile(nome.append(".pre"),ios::app);


	if (meufile.is_open()) 
	{
		int linecounter = 0;
		while(getline(meufile, line))
		{
			linecounter++;
			if (line.find("EQU")!=line.npos)
			{
				cout << "\nTem um EQU aqui\n";
				fim=line.size();

				valorparam=line[fim-1];

				posequ=line.find(":");
				nomeparam=line.substr(0,posequ);

				//salva na tabela o nome e o valor do parametro
				if (equfile.is_open())
				{
					equfile << nomeparam + "\t";
					equfile << valorparam <<endl;
				}
				else cout << "\nArquivo nao pode ser aberto EQU!!!\n\n";

				//Verifica se EQU vem depois de SECTION
				if ( linecounter  >= lineachousection ){
					cout << "\n. Diretiva EQU encontrada após a diretiva SECTION na linha " << linecounter;
				}

			}else if(line.find("IF")!=line.npos){
				cout << "\nTem um IF aqui\n";
				fim=line.size();
				size_t posif=line.find("IF");
				nomeparam=line.substr(posif+3,fim);
				teste = nomeparam.size();
				nomeparam=line.substr(3,teste);
				//cout << line << endl;	
				//cout << nomeparam << endl;
				//cout << nomeparam.size() << endl;
				ifstream equfile("EQU");				
 				if(equfile.is_open()){
					while(getline(equfile,line)){
						//le a linha ate o espaço depois disso
						posequ=line.find("\t");
						//depois pega o valor até o espaço e compara com o if que queremos
						nomeequ=line.substr(0,posequ);
						fimequ=line.size();
						valorequ=line[fimequ-1];
						//line.substr(posequ,fim);
						//cout << nomeequ.size() << endl;
						//cout << valorequ.size() << endl;
						//olha na tabela de EQU procurando o valor que está logo após o IF(0 ou 1)
						if(nomeequ.compare(nomeparam)==0){
							//parametro existe na tabela e podemos verificar o seu valor
							cout << nomeequ << endl;
							cout << "aqui" <<endl;
							cout << valorequ << endl;
							//verifica o valor de nomeequ
							if(valorequ=="1"){
								remover=0;
								erroequ=1;
								getline(meufile,line);
								saidafile << line << endl;
							}else if(valorequ=="0"){
								remover=1;
								erroequ=1;
								cout << "Remover: " << remover << endl;
								getline(meufile,line);
							}
							//se for 1 adiciona a linha posterior ao if
							//se for 0 remove a linha posterior ao if
						}

					}
					if(erroequ==0){ //Retornando o erro para a resolução de EQU não válida
						cout<<"Valor de EQU válido para " << nomeparam << " não foi encontrado no arquivo, revise o código .asm."<<endl;
						erroequ=0;
					}
				} 	else cout << "\nArquivo EQU nao pode ser aberto!!!\n\n";
			}	else{saidafile << line << endl;}
		}
		equfile.close();
		meufile.close();
		saidafile.close();			
	}
}

vector<string> separate_tokens(string line){
	stringstream stream_line(line);
	vector<string> token_vector;  
	size_t prev = 0, pos;
	//Separa tokens por espaços ou vírgulas
    while (((pos = line.find_first_of(" ", prev)) != std::string::npos) || (pos = line.find_first_of(",", prev)) != std::string::npos)
    {
        if (pos > prev)
            token_vector.push_back(line.substr(prev, pos-prev));
        prev = pos+1;
    }
    if (prev < line.length())
        token_vector.push_back(line.substr(prev, std::string::npos));

    return token_vector;
}


void lexer(std::vector<std::string> token_vector, int n_linha){
	for (vector<string>::iterator it = token_vector.begin(); it != token_vector.end(); ++it)
	{
		string str = *it;
		if (   isalpha(str.at(0)) || ( str.at(0) == '_' )   )
		{ 
			for (string::iterator it3 = str.begin(); it3 != str.end(); ++it3)
			{
				if (  !isdigit(*it3)   &&  !isalpha(*it3) &&  !((*it3)=='_')   )
				{
					if ((*it3) == ':' )
					{
						if ( (*it).back() == (*it3) )
							(*it).erase(std::prev((*it).end()));
						else
							printf("Erro léxico! \n Token inválido. Token deve ser composto por dígitos, letras ou underscore. \n Linha: %d.", n_linha );
					} 
					else
					{
						printf("Erro léxico! \n Token inválido. Token deve ser composto por dígitos, letras ou underscore. \n Linha: %d.", n_linha );
						break;
					}
				}
			}
		}
		else 
		{
			for (string::iterator it3 = str.begin(); it3 != str.end(); ++it3)
			{ 
				if ( !isdigit(*it3) )
				{
					printf("Erro léxico! \n Token inválido. Token deve ser iniciado por dígito ou underscore. \n Linha: %d.", n_linha );
					break;
				}
			}
		}
	}
}

void montagem(string file_in, string file_out){
	
	std::ifstream infile(file_in); 
	std::string line;

	//Cria arquivo de saída
	ofstream outputFile(file_out);

	int n_linha = 0;
	//While lê arquivo de entrada até o arquivo acabar.
	while (std::getline(infile, line))  
	{
		n_linha++;
		vector<string> token_vector = separate_tokens(line);
		lexer(token_vector, n_linha);
		//até aqui o programa leu uma linha, separou os token em um vector<string> e fez análise léxica
	}

}

int main(int argc, char* argv[]) {	
	//argc eh um inteiro com o numero de argumentos passados pela linha de comando
	//argv eh um vetor com os argumentos. argv[0] sempre sera o path do programa,
	//entao eh basicamente ignorado. por isso, o argc na verdade vai ser o numero
	//de argumentos mais um.
	string file_name;

	file_name = argv[2]; // passar para learquivo(). eh o nome do arquivo .asm.
	string file_in = file_name + ".asm";
	if ( ! file_exist(file_in) )
	{
		cout << "\nArquivo não existe nessa pasta!!!\n\n";
		return 0;
	}

	//lerarquivo(argv[2],argv[3]);
	int lineachousection = lerarquivo(file_in,argv[3]);

	if (string(argv[1])=="-p"){
		cout << endl << "Iniciando o -p" << endl;
		pre_procesamento(argv[3], lineachousection);
	}else if (string(argv[1])=="-m"){
		pre_procesamento(argv[3], lineachousection);
		expande_macro(argv[3]);
		// realiza a expansão das macros em um arquivo com extensão .mcr
		// pega o arquivo da etapa anterior, le o que está nele e executa a criação da MNT e da MDT
		// depois utiliza o algoritmo de expansão das macros que está na função de passagem zero
		// mostra esse arquivo com as macros expandidas

		//montagem();
		//codigo_objeto();
	}else if (string(argv[1])=="-o"){
		pre_procesamento(argv[3], lineachousection);
		expande_macro(argv[3]);
		//montagem(argv[3]);
		//Realiza a montagem do código depois de expandir as macros
	}else {
		cout << " Comando de execução não encontrado.    ERRO     " << endl;
	}
	
	//montagem("bin.pre","bin.teste");
	montagem("teste.pre","teste.teste");

	return 0;
}
