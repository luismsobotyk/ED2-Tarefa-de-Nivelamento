#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno{
	char nome[20];
	char email[50];
	float nota1;
	float nota2;
	float media;
}Aluno;
typedef struct{
	Aluno dado;
	struct no* next;
  	struct no* prev;
}tno;
typedef struct{
  tno* first;
  tno* last;
  int size;
}tList;

void start_list(tList *list);
void add_node(tList *list, Aluno a);
void print_list(tList *list);
Aluno search_list(tList *list, char n[20]);
void remove_node(tList *list, char n[20]);

int main(void){
	tList minha_lista;
	start_list(&minha_lista);
	if(&minha_lista == NULL){
		return 1; // Erro na criação da lista. Encerra o programa.
	}
	
	FILE *bin;
	int  tamanho = 0; 
	
	if((bin = fopen("data.bin","rb")) == NULL){
        printf("Erro ao abrir arquivo!");
        return 0;
    }
    
    Aluno aluno_leitura;
    printf("%d\n\n", sizeof(Aluno));
    if(!feof(bin) && !ferror(bin)){
    	//fread(&temp, sizeof(struct entry), 1, fp) == 1
		while(fread(&aluno_leitura, sizeof(Aluno), 1, bin)==1){
		//while (!feof(bin)){
			//fread(&aluno_leitura, 1, sizeof(Aluno), bin);
			add_node(&minha_lista, aluno_leitura);
			printf("Aluno %s carregado![%s, %s, %f, %f, %f]\n", aluno_leitura.nome, aluno_leitura.nome, aluno_leitura.email, aluno_leitura.nota1, aluno_leitura.nota2, aluno_leitura.media);		
			if(feof(bin)) break;
		}
	}
    fclose(bin);
    
    int op=0;
    while(1){
 		do{
 			printf("MENU\n1- Novo Registro\n2- Excluir Registro\n3- Pesquisar (Nome de Aluno)\n4- Listar todos os Registros\n5-Sair.\n");
 			scanf("%d", &op);
		}while(op<1 || op>5);
	
		switch(op){
			case 1:;
				Aluno aluno;
				char nome[20], email[50];
				float nota1, nota2, media;
				
				printf("Nome[20]: ");
				scanf("%s", &nome);
				
				printf("Email[50]: ");
				scanf("%s", &email);
				
				printf("Nota 1 [float]: ");
				scanf("%f", &nota1);
				
				printf("Nota 2 [float]: ");
				scanf("%f", &nota2);
				media= (nota1+nota2)/2;
				printf("Media: %f\n", media);

				strcpy(aluno.nome, nome);
				strcpy(aluno.email, email);
				aluno.nota1= nota1;
				aluno.nota2= nota2;
				aluno.media= media;
				add_node(&minha_lista, aluno);
			break;
			case 2:;
				char nomePesquisa[20];
				printf("Nome[20]: ");
				scanf("%s", &nomePesquisa);
				Aluno result= search_list(&minha_lista, nomePesquisa);
				if(strcmp(result.nome, nomePesquisa)){
					printf("Registro inexistente\n%s\n\n", result.nome);
				}else{
					remove_node(&minha_lista, nomePesquisa);
				}	
			break;
			case 3:; // podia ter retornado um ponteiro pro nó pq ia ser util na hora de exlcuir 
				char nomePesquisa2[20];
				printf("Nome[20]: ");
				scanf("%s", &nomePesquisa2);
				Aluno result2= search_list(&minha_lista, nomePesquisa2);
				if(strcmp(result2.nome, nomePesquisa2)){
					printf("Registro inexistente\n%s\n\n", result2.nome);
				}else{
					printf("\tNome: %s\n\tEmail: %s\n\tNota 1: %f\n\tNota 2: %f\n\tMedia: %f\n\n", result2.nome, result2.email, result2.nota1, result2.nota2, result2.media);
				}				
			break;
			case 4:;
				print_list(&minha_lista);
			break;
			case 5:;
				if((bin = fopen("data.bin","wb")) == NULL){
        			printf("Erro ao abrir arquivo para gravacao!");
        			return 0;
    			}
    			if(minha_lista.size==0){
    				fclose(bin);
					return 0;
				}
				
				tno *current;
  				current = minha_lista.first;
  				int i= 0;
				while(i<minha_lista.size) {
    				Aluno asd;
					strcpy(asd.nome, current->dado.nome);
					strcpy(asd.email, current->dado.email);
					asd.nota1= current->dado.nota1;
					asd.nota2= current->dado.nota2;
					asd.media= current->dado.media;
					//printf("\tNome: %s\n\tEmail: %s\n\tNota 1: %f\n\tNota 2: %f\n\tMedia: %f\n\n", current->dado.nome, current->dado.email, current->dado.nota1, current->dado.nota2, current->dado.media);
					fwrite(&asd, 1, sizeof(asd), bin);
					current = current->next;
  					i++;
  				}
  				//free(minha_lista);
				/*if(minha_lista->size==0){
					return 0;
				}
				while(i<lista->size) {
    				
					//printf("\tNome: %s\n\tEmail: %s\n\tNota 1: %f\n\tNota 2: %f\n\tMedia: %f\n\n", current->dado.nome, current->dado.email, current->dado.nota1, current->dado.nota2, current->dado.media);
					current = current->next;
  					i++;
  				}
				
				exit_program();
				Aluno asd;
				strcpy(asd.nome, "Serjo");
				strcpy(asd.email, "luis@teste.com");
				asd.nota1= 5;
				asd.nota2= 8;
				asd.media= 9;
				
				fwrite(&asd, 1, sizeof(asd), bin);*/
				return 0;
			break;
		}
	}
		
 	printf("Teste");
 	
}

void start_list(tList *list) {
  list->first = NULL;
  list->last = NULL;
  list->size = 0;
}
void add_node(tList *list, Aluno a) {
	//printf("testesssss");
	
	//printf("Media: %f\n", a.media);
	tno *no = malloc(sizeof(tno));
  	tno *prev;
  	if(no!= NULL){
  		if (list->first == NULL && list->last == NULL) {
			list->first = list->last = no;
    		strcpy(no->dado.nome, a.nome);
			strcpy(no->dado.email, a.email);
			no->dado.nota1= a.nota1;
			no->dado.nota2= a.nota2;
			no->dado.media= a.media;
			
			//printf("Media no: %f\n", no->dado.media);
			list->size++;
  		} else {
  			no->next = list->first;
			no->prev = list->last;
			strcpy(no->dado.nome, a.nome);
			strcpy(no->dado.email, a.email);
			no->dado.nota1= a.nota1;
			no->dado.nota2= a.nota2;
			no->dado.media= a.media;
			list->last->next= no;
			list->last = no;
			list->size++;
  		}
  	}else{
  		printf("Erro no malloc");	
	}
	//free(no);
}

Aluno search_list(tList *list, char n[20]){
	tno *current;
	current = list->first;
	Aluno a;
	int i=0;
	while(i<list->size){
		if(!strcmp(n, current->dado.nome)){
			strcpy(a.nome, current->dado.nome);
			strcpy(a.email, current->dado.email);
			a.nota1= current->dado.nota1;
			a.nota2= current->dado.nota2;
			a.media= current->dado.media;
			i= list->size;
			//printf("\n%d - Teste If - %d", i, list->size);
		}
		current = current->next;
		i++;
	}
	return a;
}

void print_list(tList *lista) {
  printf("Imprimindo Alunos:\n");
  tno *current;

  current = lista->first;
  int i= 0;
  while(i<lista->size) {
  //while(current->next != NULL) {
    printf("\tNome: %s\n\tEmail: %s\n\tNota 1: %f\n\tNota 2: %f\n\tMedia: %f\n\n", current->dado.nome, current->dado.email, current->dado.nota1, current->dado.nota2, current->dado.media);
	current = current->next;
  	i++;
  }
}
void remove_node(tList *list, char n[20]){
	tno *current;
	tno *next;
	tno *prev;
	current = list->first;
	Aluno a;
	int i=0;
	while(i<list->size){
		if(!strcmp(n, current->dado.nome)){
			i= list->size;
		}else{
			current = current->next;
			i++;
		}
	}

	if(current->next==NULL){
  		// é unico elemento
		free(current);
  		list->size--;
	}else if(current->prev==NULL){
		// é o primeiro elemento
		next= current->next;
		next->prev= NULL;
		list->first= next;
		free(current);
		list->size--;
	}else{
		next= current->next;
		prev= current->prev;
		next->prev= current->prev;
		prev->next= current->next;
		free(current);
		list->size--;
	}
}
