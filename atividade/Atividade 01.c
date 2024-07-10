#include <stdio.h>   // Biblioteca padrão para funções de entrada e saída
#include <stdlib.h>  // Biblioteca padrão para funções de alocação de memória, conversão de tipos, etc.

#define TAM_NOME 40  		// Define o tamanho máximo do nome do aluno
#define ARG_COUNT 2  		// Define o número esperado de argumentos na linha de comando
#define TAM_DISCIPLINA 40 	// Define o tamanho maximo da disciplina

/*
 * MINI SIGAA
 * Este código é um exemplo de como implementar estruturas e funções em C 
 * para representar e manipular alunos e turmas (como um mini SIGAA).
 */

// Estrutura para representar um aluno
typedef struct {
	char nome[TAM_NOME];  // Nome do aluno
	int matricula;        // Número de matrícula do aluno
	float cra;            // Coeficiente de Rendimento Acadêmico (CRA) do aluno
} t_aluno;

// Estrutura para representa o professor
typedef struct 
{
    char nome[TAM_NOME]; 			// Nome do professor 
	int codigo_de_departamento; 	// Numero do Departamento
	int ano_entrada;				// Ano da entrada do professor
	char disciplina[TAM_DISCIPLINA]; // Nome da Disciplina 
} t_professor;


// Estrutura para representar uma turma
typedef struct {
	t_aluno* alunos; 			// Ponteiro para um array de alunos
	int tam_turma;    			// Tamanho da turma (número de alunos)
	int sala;         			// Número da sala de aula
	t_professor* professor;		// Ponteiro apontando para o professor
} t_turma;

// Função para cadastrar um aluno
void cadastra_aluno(t_aluno *a) {
	char c;
	printf("Digite o nome do aluno: ");
	scanf("%[^\n]", a->nome);  // Lê o nome do aluno
	printf("Digite a matricula do aluno: ");
	scanf("%d", &a->matricula);  // Lê a matrícula do aluno
	printf("Digite o CRA do aluno: ");
	scanf("%f", &a->cra);  // Lê o CRA do aluno
	scanf("%c", &c); // ATS: consome o caractere '\n' remanescente
}

// Função para cadastrar um professor
void cadastra_professor(t_professor *p) {
	char c;
	printf("Digite o nome do professor: ");
	scanf("%[^\n]", p->nome);  					// Lê o nome do professor
	printf("Digite o codigo de departamento: ");
	scanf("%d", &p->codigo_de_departamento);  	// Lê numero do departmento 
	printf("Digite o ano entrada: ");
	scanf("%d", &p->ano_entrada);  				// Lê o ano de entrada
    printf("Digite o nome da disciplina: ");    // Lê o nome da disciplina
	scanf("%s", p->disciplina);
	scanf("%c", &c); 							// ATS: consome o caractere '\n' remanescente
}


// Função para exibir informações de um aluno
void exibe_aluno(t_aluno *a) {
	printf("Nome: %s\n", a->nome);  // Exibe o nome do aluno
	printf("Matricula: %d\n", a->matricula);  // Exibe a matrícula do aluno
	printf("CRA: %.2f\n", a->cra);  // Exibe o CRA do aluno
}

// Função para cadastrar uma turma
void cadastra_turma(t_turma* t, int tam) {
    char c;
	printf("Cadastrando turma com %d alunos...\n", tam);
	t->alunos = (t_aluno*) malloc(sizeof(t_aluno) * tam);  // Aloca memória para os alunos
	t->tam_turma = tam;  // Define o tamanho da turma
	for (int i = 0; i < tam; i++) {
		cadastra_aluno(&t->alunos[i]);  // Cadastra cada aluno na turma
	}

	printf("Digite o numero da sala: ");
	scanf("%d", &t->sala);  // Lê o número da sala de aula
    scanf("%c", &c); // ATS: consome o caractere '\n' remanescente
}

// Função para exibir informações de uma turma
void exibe_turma(t_turma* t) {
	printf("Sala: %d\n", t->sala);  // Exibe o número da sala de aula
	for (int i = 0; i < t->tam_turma; i++) {
		exibe_aluno(&t->alunos[i]);  // Exibe as informações de cada aluno na turma
	}
}




void exibe_professor(t_professor *p) {
	printf("Nome do professor: %s\n", p->nome);  							// Exibe o nome do professor
	printf("Codigo de Departamento: %d\n", p->codigo_de_departamento);  	// Exibe o codigo do departamento do professor
	printf("Ano de Entrada: %d\n", p->ano_entrada);  						// Exibe o ano de entrada
    printf("Diciplina: %s\n", p->disciplina);
}


void associa_professor_turma (t_turma *t, t_professor *p){
	t ->professor = p;
}

float calcula_media_cru_turma(t_turma *t){
	float soma_turma = 0;
	for (int i = 0; i < t->tam_turma; i++) {
		soma_turma = soma_turma + t->alunos[i].cra;  // Fazendo a soma do CRA
	}
	soma_turma = (soma_turma/t->tam_turma);
	return soma_turma;
}

// Função principal
// Recebe o número de alunos da turma como argumento na linha de comando
// Cadastra a turma e exibe as informações dos alunos
int main(int argc, char** argv) {
	t_turma turma1, turma2;
	t_professor professor1, professor2;
	int tam_turma = 0;
	
	// Verifica se o número de argumentos passados na linha de comando é o esperado
	if (argc != ARG_COUNT) {
		printf("Use: %s <NUMERO_DE_ALUNOS>\n", argv[0]);  // Informa o uso correto do programa
		exit(0);  // Termina o programa se o número de argumentos estiver incorreto
	} else {
		tam_turma = atoi(argv[1]);  // Converte o argumento da linha de comando para inteiro
		cadastra_turma(&turma1, tam_turma);  // Cadastra a turma
        cadastra_professor(&professor1);     // Cadastra prof

        exibe_turma(&turma1);  // Exibe as informações da turma
        exibe_professor(&professor1);

        printf("CRA TURMA 1: %.2f\n", calcula_media_cru_turma(&turma1));
        
        printf("\n\n");

        cadastra_turma(&turma2, tam_turma);  // Cadastra a turma
        cadastra_professor(&professor2); 

        exibe_turma(&turma2);  // Exibe as informações da turma
        printf("\n\n");
        exibe_professor(&professor2);


        printf("CRA TURMA 2: %.2f\n", calcula_media_cru_turma(&turma2));
	}

	// Libera a memória alocada para os alunos da turma
	for (int i = 0; i < tam_turma; i++) {
		free(&turma1.alunos[i]);  // Libera a memória alocada para cada aluno
        free(&turma2.alunos[i]);
	}

	return 0;
}