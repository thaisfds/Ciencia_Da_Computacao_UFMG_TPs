#include "menuAjuda.hpp"


MenuAjuda::MenuAjuda(){}

// Imprime as regras do jogo de acordo com a escolha do jogador
// @param opcao inteiro utilizado para validar se a opção do usuário é válida ou não
void MenuAjuda::menuDeAjuda(){
	system("cls||clear");
	cout << "- MENU DE AJUDA -" << endl;
	cout << "Escolha uma das opcoes:" << endl;
	cout << "1 - Ajuda com modo de jogo padrao." << endl;
	cout << "2 - Ajuda com modo de jogo personalizado." << endl;
	cout << "3 - Voltar ao menu inicial." << endl;
	
	int opcao;
	opcao = opcaoEhValida(3);

	switch (opcao){
		case 1:
		{
			system("cls||clear");
			cout << "Escolha uma das opçoes:" << endl;
			cout << "1 - Ver regras do modo de jogo padrao." << endl;
			cout << "2 - Ver cartas do modo de jogo padrao." << endl;
			cout << "3 - Voltar ao menu inicial." << endl;
			opcao = opcaoEhValida(3);
			switch (opcao){
				case 1:
				{
					system("cls||clear");
					mostrarRegras(1);
					cout << "Escolha uma das opcoes:" << endl;
					cout << "1 - Voltar ao menu de ajuda." << endl;
					cout << "2 - Voltar ao menu de inicial." << endl;
					
					opcao = opcaoEhValida(2);

					switch (opcao){
						case 1:
						{
							menuDeAjuda();
							break;
						}
						case 2:
						{
							break;
						}
					}
					break;
				}
				
				case 2:
				{
					system("cls||clear");
					mostrarDescricaoCartas(1);
					cout << "Escolha uma das opcoes:" << endl;
					cout << "1 - Voltar ao menu de ajuda." << endl;
					cout << "2 - Voltar ao menu de inicial." << endl;
					
					opcao = opcaoEhValida(2);

					switch (opcao){
						case 1:
						{
							menuDeAjuda();
							break;
						}
						case 2:
						{
							break;
						}
					}
					break;
				}
				
				case 3:
					break;

			}
			break;
		}
		
		case 2:
		{
			system("cls||clear");
			cout << " Escolha uma das opcoes:" << endl;
			cout << "1 - Ver regras do modo de jogo personalizado." << endl;
			cout << "2 - Ver cartas do modo de jogo personalizado." << endl;
			cout << "3 - Voltar ao menu inicial." << endl;
			
			opcao = opcaoEhValida(3);
			
			switch (opcao){
				case 1:
				{
					system("cls||clear");
					mostrarRegras(2);
					cout << " Escolha uma das opcoes:" << endl;
					cout << "1 - Voltar ao menu de ajuda." << endl;
					cout << "2 - Voltar ao menu de inicial." << endl;

					opcao = opcaoEhValida(2);

					switch (opcao){
						case 1:
						{
							menuDeAjuda();
							break;
						}
						case 2:
						{
							break;
						}
					}
					break;
				}
				
				case 2:
				{
					system("cls||clear");
					mostrarDescricaoCartas(2);
					cout << " Escolha uma das opcoes:" << endl;
					cout << "1 - Voltar ao menu de ajuda." << endl;
					cout << "2 - Voltar ao menu de inicial." << endl;

					opcao = opcaoEhValida(2);
					
					switch (opcao){
						case 1:
						{
							menuDeAjuda();
							break;
						}
						case 2:
						{
							break;
						}
					}
					break;
				}
				  
				case 3:
					break;
			}
			break;
		}
		case 3:
			break;
	}

}

// Imprime as regras do jogo de acordo com o modo de jogo
// @param modoDeJogo um inteiro que define o modo de jogo (1 - padrão, 2 - personalizado)
void MenuAjuda::mostrarRegras(int modoDeJogo){
	switch (modoDeJogo){
		case 1:
		{
			system("cls||clear");
			cout << "- REGRAS DO JOGO PALIO -\n O conteudo do jogo consiste em 108 cartas de jogo, sendo:" << endl;
			cout << "\n- 19 Cartas Azuis - 0 a 9.\n- 19 Cartas Verdes - 0 a 9.\n- 19 Cartas Amarelas - 0 a 9." << endl;
			cout << "- 19 Cartas Vermelhas - 0 a 9.\n- 8 Cartas Comprar Duas Cartas - 2 de cada cor." << endl;
			cout <<  "- 8 Cartas Inverter - 2 de cada cor.\n- 8 Cartas Pular - 2 de cada cor." <<endl;
			cout << "- 4 Cartas Curinga. \n- 4 Cartas Curinga Comprar Quatro Cartas." << endl;
			cout << "\nO objetivo do PALIO e ser o primeiro jogador a ficar sem cartas na mao. " << endl;
			cout << "Para o efeito tera de jogar uma carta de cada vez, que corresponda ao " << endl;
			cout << "numero ou cor da carta jogada anteriormente. O jogo termina quando os jogadores " << endl;
			cout << "ficarem sem cartas na mao. " << endl;
			cout << "\nO jogo inicia-se tirando uma carta de cima da pilha. De seguida o jogador " << endl;
			cout << "a esquerda pode dar inicio ao jogo.\n" << endl;
			break;
		}

		case 2:
		{
			system("cls||clear");
			cout << "- REGRAS DO JOGO PALIO -\n O conteudo do jogo consiste em 108 cartas de jogo, sendo:" << endl;
			cout << "\n- 19 Cartas Azuis - 0 a 9.\n- 19 Cartas Verdes - 0 a 9.\n- 19 Cartas Amarelas - 0 a 9." << endl;
			cout << "- 19 Cartas Vermelhas - 0 a 9.\n- 8 Cartas Comprar Duas Cartas - 2 de cada cor." << endl;
			cout <<  "- 8 Cartas Inverter - 2 de cada cor.\n- 8 Cartas Pular - 2 de cada cor." <<endl;
			cout << "- 4 Cartas Curinga. \n- 4 Cartas Curinga Comprar Quatro Cartas." << endl;
			cout << "\nO objetivo do PALIO e ser o primeiro jogador a ficar sem cartas na mao. " << endl;
			cout << "Para o efeito tera de jogar uma carta de cada vez, que corresponda ao " << endl;
			cout << "numero ou cor da carta jogada anteriormente. O jogo termina quando os jogadores " << endl;
			cout << "ficarem sem cartas na mao. " << endl;
			cout << "\nO jogo inicia-se tirando uma carta de cima da pilha. De seguida o jogador " << endl;
			cout << "a esquerda pode dar inicio ao jogo.\n" << endl;
			cout << "No modo de jogo personalizado voce pode optar por ativar ou desativar algumas" << endl;
			cout << "regras do jogo padrao." << endl;
			cout << "\nE possivel ativar ou desativar regras como:" << endl;
			cout << "Empilhar cartas de comprar (+2 em cima de +2, +4 em cima de +4 etc.)." << endl;
			cout << "Jogar carta depois de comprar no seu turno." << endl;
			cout << "Comprar carta sem precisar no seu turno." << endl;
			cout << "Pular ou nao o seu turno." << endl;
			cout << "Jogar com cartas padrão ou remover algumas cartas.\n" << endl;
			break;
		}        
	}
}

// Imprime as cartas do jogo de acordo com o modo de jogo
// @param modoDeJogo um inteiro que define o modo de jogo (1 - padrão, 2 - personalizado)
void MenuAjuda::mostrarDescricaoCartas(int modoDeJogo){ 
	switch (modoDeJogo){
		case 1:
		{
			system("cls||clear");
			cout << "- Comprar Duas Cartas ( +2 ) - Quando esta carta for jogada, o proximo jogador deve " << endl;
			cout << "comprar 2 cartas e perde a vez. Ela apenas pode ser jogada sobre uma cor que combine." << endl;
			cout << "\n- Inverter ( S ) - Ao descartar esta carta, o sentido do jogo e invertido (se estiver " <<endl;
			cout << "indo para a esquera, muda para direita e vice-versa). Ela apenas pode ser jogada sobre " <<endl;
			cout << "uma cor que combine ou sobre outra carta Inverter." << endl;
			cout << "\n- Bloquear ( @ ) - Quando voce joga esta carta, o proximo jogador e 'pulado' (perde a vez)." << endl;
			cout << "Ela apenas pode ser jogada sobre uma cor que combine ou sobre outra carta Pular." <<endl;
			cout << "\n- Curinga - Ao jogar esta carta, voce escolhe a cor que continuara o jogo (pode ser " <<endl;
			cout << "qualquer cor, inclusive a que estava sendo jogada antes do Curinga)." << endl;
			cout << "\n- Comprar Quatro Cartas ( +4 ) - Ao jogar esta carta, voce pode escolher a cor a ser " << endl;
			cout << "jogada, alem de fazer com que o proximo jogador tenha que comprar 4 cartas da pilha de Compras, " << endl;
			cout << "perdendo tambem a vez.\n" << endl;
			break;
		}

		case 2:
		{
			system("cls||clear");
			cout << "- Comprar Duas Cartas ( +2 ) - Quando esta carta for jogada, o proximo jogador deve " << endl;
			cout << "comprar 2 cartas e perde a vez. Ela apenas pode ser jogada sobre uma cor que combine." << endl;
			cout << "\n- Inverter ( S ) - Ao descartar esta carta, o sentido do jogo e invertido (se estiver " <<endl;
			cout << "indo para a esquera, muda para direita e vice-versa). Ela apenas pode ser jogada sobre " <<endl;
			cout << "uma cor que combine ou sobre outra carta Inverter." << endl;
			cout << "\n- Bloquear ( @ ) - Quando voce joga esta carta, o proximo jogador e 'pulado' (perde a vez)." << endl;
			cout << "Ela apenas pode ser jogada sobre uma cor que combine ou sobre outra carta Pular." <<endl;
			cout << "\n- Curinga - Ao jogar esta carta, voce escolhe a cor que continuara o jogo (pode ser " <<endl;
			cout << "qualquer cor, inclusive a que estava sendo jogada antes do Curinga)." << endl;
			cout << "\n- Comprar Quatro Cartas ( +4 ) - Ao jogar esta carta, voce pode escolher a cor a ser " << endl;
			cout << "jogada, alem de fazer com que o proximo jogador tenha que comprar 4 cartas da pilha de Compras, " << endl;
			cout << "perdendo tambem a vez.\n" << endl;
			break;
		}

	}
}

// Força o jogador a escolher uma opção válida.
// @param nOpcoes inteiro com o número de opçoes disponíveis de acordo com quem chama a função
// @return A opção válida para o menu que chamou a função
int MenuAjuda::opcaoEhValida (int nOpcoes){
	// Verifica se o jogador colocou uma opção válida e sai do loop
	bool opcaoValida;
	string opcao;
	do{
	cin >> opcao;
	try{
		if(stoi(opcao) < 1 || stoi (opcao) > nOpcoes){
			throw OpcaoInvalida();
		}
		else{
			opcaoValida = true;
		}
		}catch (const OpcaoInvalida& vci){
			cout << vci.what() << endl;
			opcaoValida = false;
		}catch (const exception& e){
			cout << "Por favor insira um número!" << endl;
			opcaoValida = false;
		}	
	}while(!opcaoValida);

	return stoi(opcao);
}