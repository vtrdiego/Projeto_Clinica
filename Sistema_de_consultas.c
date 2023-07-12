
#include <stdio.h>
#include <time.h> // Biblioteca para saber dia e hora atuais.
#include <string.h>
#include <stdlib.h>
#include <locale.h>  // Biblioteca para atualizar o idioma, caso o programa não esteja localizado.
#define tamNome 70

void cadastrarPaciente(void);
void marcarConsulta(void);
void excluirCadastros(void);
void cancelarConsulta(void);
int data_hora_atual(int data,int hora); // Função para comparar dia e hora atuais.

// Início do Main contendo o menu do sistema e suas respectivas chamadas de funções
int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "Portuguese"); // Para atualizar o terminal para português.
  int opcao;

  printf("\n-------------( CLÍNICA DE CONSULTAS BEM-ESTAR )------------- ");
  printf("\n                         BEM-VINDO!");

  do{

  printf("\n\n\n---------------( MENU )---------------\n");
  printf("\n\n  Nº        Opções:");
  printf("\n\n [1] - CADASTRAR PACIENTE");           
  printf("\n\n [2] - MARCAR CONSULTA");
  printf("\n\n [3] - EXCLUIR CADASTROS"); 
  printf("\n\n [4] - CANCELAR CONSULTAS"); 
  printf("\n\n [5] - SAIR DO SISTEMA");
  printf("\n\n\n DIGITE O Nº DA OPÇÃO DESEJADA: ");
  scanf("%d",&opcao);
  int c; while ((c = getchar()) != '\n' && c != EOF); // Código para retirar bug que ocorre ao usar gets e scanf na mesma estrutura.

  //swtich contendo as funções das respectivas opções do menu.
  switch(opcao){
    case 1:
      cadastrarPaciente();   
      break;
    case 2:
      marcarConsulta();    
      break;
    case 3:
      excluirCadastros();   
      break;
    case 4:
      cancelarConsulta();
    case 5:
      break;
    default:
    printf("\n\n            OPÇÃO INVÁLIDA!");
    break;
    }
    
  }while(opcao!=5); 

  printf("\n\n     SISTEMA FINALIZADO!");
  
  return 0;
}

void cadastrarPaciente(void){
  char nome[tamNome],copiaNome[tamNome];
  int telefone=0,copiaTelefone=0,confirma=0,validacao=0,cont=0;
  long telMin=11111111,telMax=999999999999999; 
  FILE *pt;

  printf("\n\n\n------------( CADASTRO DE PACIENTE )------------\n");

  
  pt=fopen("pacientes.txt","a+");// Função fopen para criar ou alterar arquivo de texto de pacientes.

  do{ // do while para verificar se o nome contêm apenas letras e espaço.
  printf("\n\n Informe o nome do novo paciente: ");
  gets(nome);

    for(int i=0;i<strlen(nome);i++){
      if(nome[i]>='a' && nome[i]<='z' || nome[i]>='A' && nome[i]<='Z' || nome[i]==' '){
        cont++;
      }
    }

    if(cont!=strlen(nome)){
      printf("\n\n             INFORME UM NOME VÁLIDO!\n");
      cont=0;
    }
  }while(cont==0);

  do{ // do while para verificar se o telefone contêm apenas dígitos (8 a 15 dígitos).
  cont=0;
  printf("\n\n Informe o telefone do novo paciente (apenas dígitos!): ");
  scanf("%d",&telefone);
  int c; while ((c = getchar()) != '\n' && c != EOF); 

    if(telefone>=telMin && telefone<=telMax){ //Para verificar se o tel inserido é válido
      cont=1;
    }else{
      printf("\n\n            INFORME UM TELEFONE VÁLIDO!\n");
    }
  }while(cont==0);
    
  while(fscanf(pt,"%d,%[^\n]",&copiaTelefone,copiaNome)!=EOF){ // While com fscanf para verificar se o telefone informado já foi cadastrado no sistema.
    if(copiaTelefone==telefone){
      printf("\n\n             PACIENTE JÁ CADASTRADO!");
      printf("\n            Informe um novo paciente!");
      fclose(pt);
      return;
      }
    }

  validacao=fprintf(pt,"%d,%s\n",telefone,nome); // fprintf para registrar as informações de paciente no arquivo, caso ocorra, validacao recebe 1.

  if(validacao==EOF){ // Verifica se validacao confirma o registro das informações.
    printf("Erro de I/O.");
    exit(1);
  }else{
    printf("\n\n         PACIENTE CADASTRADO COM SUCESSO!");
  }

  fclose(pt); 
}

void marcarConsulta(void){
  FILE *pt;
  int telefone=0,copiaTelefone=0,opcao=0,cont=0,confirma=0,dia=0,copiaDia=0,copiaHora=0,hora=0,validarDiaHora=0;
  char nome[tamNome],especialidade[tamNome],copiaNome[tamNome],copiaEspecialidade[tamNome];

  printf("\n\n\n------------( MARCAR CONSULTA )------------\n");

  pt=fopen("pacientes.txt","r"); // Função fopen para ler arquivo de texto de pacientes.
  if(pt==NULL){
    printf("\n\n       NÃO HÁ PACIENTES CADASTRADOS!");
    return;
  }

  while(fscanf(pt,"%d,%[^\n]",&telefone,nome)!=EOF){ // While com fscanf para listar todos os pacientes já registrados.
    ++cont; 
    
    if(cont==1){
      printf("\n\n      LISTA DE PACIENTES:\n");
    }

    printf("\n\n ------[ Paciente Nº %d ]------\n\n",cont);

    printf(" NOME: %s",nome);
    printf("\n TEL: %d\n",telefone);
  }

  if(cont==0){ 
    printf("\n\n       NÃO HÁ PACIENTES CADASTRADOS!");
    return;
  }

  do{ // Do while para retornar a pergunta caso seja digitado uma opção incorreta.
    
  printf("\n\n DIGITE O Nº DO PACIENTE (ou 0 para retornar): ");
  scanf("%d",&opcao);
  int c; while ((c = getchar()) != '\n' && c != EOF); // Código para retirar bug que ocorre ao usar gets e scanf na mesma estrutura.

    if(opcao==0){
      return;
    }

    if(opcao>0 && opcao<=cont){ // Verifica se a opção digitada existe dentro da lista.
      confirma++;
      cont=0;
    }else{
      printf("\n\n             OPÇÃO INVÁLIDA!\n");
    }
  }while(confirma==0);

  fclose(pt); 

  pt=fopen("pacientes.txt","r"); // Função fopen para ler arquivo de texto de pacientes.

  while(fscanf(pt,"%d,%[^\n]",&telefone,nome)!=EOF){ // While para percorrer a lista de pacientes.
    ++cont; 
    if(cont==opcao){ 
      break;
    }
  }

  fclose(pt); 

  pt=fopen("consultas.txt","a+"); // Função fopen para criar/alterar arquivo de texto de consultas.
    
  printf("\n\n Informe o dia da consulta (apenas dígitos!): ");
  scanf("%d",&dia);

  printf("\n Informe a hora da consulta (apenas dígitos!): ");
  scanf("%d",&hora);
  int c; while ((c = getchar()) != '\n' && c != EOF); 

  printf("\n Informe a especialidade do atendimento: ");
  gets(especialidade);

  if(!data_hora_atual(dia,hora)){ // Função receberá dia e hora informados para verificar se é antes de dia e hora atuais.
    printf("\n\n          DIA OU HORÁRIO JÁ ULTRAPASSADOS!");
    printf("\n           Informe um novo dia e horário!");
    fclose(pt); // Fechamento de arquivo.
    return;
    }
    
  while(fscanf(pt,"%d,%[^,],%d,%d,%[^\n]",&copiaTelefone,copiaNome,&copiaDia,&copiaHora,copiaEspecialidade)!=EOF){ // While para percorrer a lista de consultas.

      if(copiaDia==dia && copiaHora==hora){ // Verificar se o dia e hora informados já foram registrados na lista consultas.
        printf("\n\n             DIA E HORÁRIO JÁ AGENDADOS!");
        printf("\n           Informe um novo dia ou horário!");
        fclose(pt);
        return;
      }
    }
    
  confirma=fprintf(pt,"%d,%s,%d,%d,%s\n",telefone,nome,dia,hora,especialidade); // fprintf para registrar as informações de consulta no arquivo, caso o registro ocorra, confirma recebe 1.

  if(confirma==EOF){ // Verifica se foi confirmado o registro das informações.
    printf("Erro de I/O.");
    exit(1);
  }else{
    printf("\n\n         CONSULTA MARCADA COM SUCESSO!");
  }

  fclose(pt); 
}

void excluirCadastros(void){
  FILE *originalPacientes,*copiaPacientes,*originalConsultas,*copiaConsultas;
  int telefone=0,copiaTelefone=0,cont=0,opcao=0,confirma=0,dia=0,hora=0;
  char nome[tamNome],especialidade[tamNome];

  printf("\n\n\n------------( EXCLUIR CADASTROS )------------\n");

  originalPacientes=fopen("pacientes.txt","r");
    if(originalPacientes==NULL){
      printf("\n\n         NÃO HÁ PACIENTES CADASTRADOS!");
      return;
    }

  while(fscanf(originalPacientes,"%d,%[^\n]",&telefone,nome)!=EOF){
    ++cont;

    if(cont==1){
        printf("\n\n      LISTA DE PACIENTES:\n");
      }

    printf("\n\n ------[ Paciente Nº %d ]------\n\n",cont);
    printf(" NOME: %s",nome);
    printf("\n TEL: %d\n",telefone);
  }

    if(cont==0){ 
      printf("\n\n       NÃO HÁ PACIENTES CADASTRADOS!");
      return;
    }

  do{
    printf("\n\n DIGITE O Nº DO PACIENTE (ou 0 para retornar): ");
    scanf("%d",&opcao);
    int c; while ((c = getchar()) != '\n' && c != EOF); 

    if(opcao==0){
      return;
    }

    if(opcao>0 && opcao<=cont){ 
      confirma++;
      cont=0; //zera para ser usado no próximo while
    }else{
      printf("\n\n             OPÇÃO INVÁLIDA!\n");
    }
  }while(confirma==0);

  fclose(originalPacientes); 

  originalPacientes=fopen("pacientes.txt","r");
  copiaPacientes=fopen("pacientesTemporarios.txt","a+");

  while(fscanf(originalPacientes,"%d,%[^\n]",&telefone,nome)!=EOF){
    ++cont;

    if(cont==opcao){
      copiaTelefone=telefone; // Cópia de telefone para ser usado na redefinição de consultas
    }

    if(cont!=opcao){
      fprintf(copiaPacientes,"%d,%s\n",telefone,nome);
    }
  }

  fclose(originalPacientes);
  fclose(copiaPacientes);

  remove("pacientes.txt");
  rename("pacientesTemporarios.txt","pacientes.txt");

  originalConsultas=fopen("consultas.txt","r");

  if(originalConsultas==NULL){
    printf("\n\n         CADASTRO EXCLUÍDO COM SUCESSO!");
    return;
  }else{
  copiaConsultas=fopen("consultasTemporarias.txt","a+");

  while(fscanf(originalConsultas,"%d,%[^,],%d,%d,%[^\n]",&telefone,nome,&dia,&hora,especialidade)!=EOF){
    if(copiaTelefone!=telefone){
      fprintf(copiaConsultas,"%d,%s,%d,%d,%s\n",telefone,nome,dia,hora,especialidade);
    }
  }

  fclose(originalConsultas);
  fclose(copiaConsultas);

  remove("consultas.txt");
  rename("consultasTemporarias.txt","consultas.txt");

  printf("\n\n         CADASTRO EXCLUÍDO COM SUCESSO!");
  }
}

void cancelarConsulta(void){
  FILE *original,*copia;
  int telefone=0,copiaTelefone=0,dia=0,hora=0,cont=0,opcao=0,confirma=0;
  char nome[tamNome],especialidade[tamNome];

  printf("\n\n\n------------( CANCELAR CONSULTAS )------------\n");

  original=fopen("consultas.txt","r"); // Função fopen para ler arquivo de texto de consultas.
  if(original==NULL){
    printf("\n\n          NÃO HÁ CONSULTAS MARCADAS!");
    return;
  }

  while(fscanf(original,"%d,%[^,],%d,%d,%[^\n]",&telefone,nome,&dia,&hora,especialidade)!=EOF){ // While com fscanf para listar todos as consultas já registrados.
    ++cont; 

    if(cont==1){
      printf("\n\n      LISTA DE CONSULTAS:\n");
    }
    printf("\n\n ------[ Consulta Nº %d ]------\n\n",cont);

    printf(" DIA: %d\n",dia);
    printf(" HORÁRIO: %dh\n",hora);
    printf(" ESPECIALIDADE: %s\n",especialidade);
    printf(" PACIENTE: %s / Tel: %d\n",nome,telefone);
  }

  if(cont==0){
    printf("\n\n        NÃO HÁ CONSULTAS AGENDADAS!");
    return;
  }

  fclose(original); 

  do{ // Do while para retornar a pergunta caso seja digitado uma opção incorreta.
  printf("\n\n DIGITE O Nº DA CONSULTA (ou 0 para retornar): ");
  scanf("%d",&opcao);
  int c; while ((c = getchar()) != '\n' && c != EOF); 

    if(opcao==0){
      return;
    }

    if(opcao>0 && opcao<=cont){ 
      confirma++;
      cont=0;
    }else{
      printf("\n\n              OPÇÃO INVÁLIDA!\n");
    }
  }while(confirma==0);

  original=fopen("consultas.txt","r"); // Função fopen para ler arquivo de texto de consultas.
  copia=fopen("consultasTemporarias.txt","a+"); // Função fopen para criar/alterar cópia de arquivo de texto de consultas.
  
  while(fscanf(original,"%d,%[^,],%d,%d,%[^\n]",&telefone,nome,&dia,&hora,especialidade)!=EOF){ // While para percorrer a lista de consultas.
    ++cont; 
    if(cont!=opcao){ 
      fprintf(copia,"%d,%s,%d,%d,%s\n",telefone,nome,dia,hora,especialidade); // fprintf para registrar as informações em uma cópia de consultas.
    }
  }

  fclose(original); // Fechamento de arquivo consultas (original). 
  fclose(copia); // Fechamento de arquivo de cópia de consultas.
  
  remove("consultas.txt"); // Arquivo original de consultas é excluído.
  rename("consultasTemporarias.txt","consultas.txt"); // Arquivo cópia de consultas com as novas informações é renomeado para consultas.

  printf("\n\n         CONSULTA EXCLUÍDA COM SUCESSO!");
} 

int data_hora_atual(int data,int hora){  // Função recebe dia e hora como parâmmetro.
  struct tm *dataEhora_atual; // Struct da função que recebe dia e hora atuais.

  time_t segundos;

  time(&segundos);

  dataEhora_atual=localtime(&segundos);

  if(data==dataEhora_atual->tm_mday && hora>dataEhora_atual->tm_hour && hora<=23){ // Se agendamento for no dia atual, verifica se ultrapassou horário atual.
    return 1;
  }else{
    switch(dataEhora_atual->tm_mon+1){ // switch para verififcar se o mês atual vai até 28, 30 ou 31. (+1 porque o ponteiro de mês atual inicia do zero).
      case 2:  
        if(dataEhora_atual->tm_year%4==0 && dataEhora_atual->tm_year%100==0 && dataEhora_atual->tm_year%400==0){ //Verifica se é ano bissexto
          if(data>dataEhora_atual->tm_mday && data<=29 && hora<=23){
            return 1;
          }
        }
        if(data>dataEhora_atual->tm_mday && data<=28 && hora<=23){
          return 1;
        }else{
          break;
        }
      case 4: case 6: case 9: case 11: 
        if(data>dataEhora_atual->tm_mday && data<=30 && hora<=23){ 
        return 1;
        }else{
          break;
        }
      default:
        if(data>dataEhora_atual->tm_mday && data<=31 && hora<=23){ 
        return 1;
      }else{
          break;
      }
    }
  }
  
  return 0; // Caso o dia para agendamento seja diferente dos parâmetros acima, a consulta não é marcada.
}
