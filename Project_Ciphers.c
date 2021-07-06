/*
Projeto realizado por:
  -Eduardo Palma nº201900054;
  -Nuno Melo nº201700465;
  -Ricardo Santos nº201700524.
*/

//Importar as bibliotecas necessárias
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<pthread.h>
#include<assert.h>
#include<unistd.h>
#include<time.h>
#include<stdbool.h>

//Definir variáveis globais
#define MAX_BUFFER 30
#define CHEIO false
#define VAZIO true
#define limite 200

//Criar um mutex para trancar e destrancar as threads
pthread_mutex_t mutex;

//Criar variáveis
bool state = VAZIO;
char buffer[MAX_BUFFER], temp;
int key,i=0,j=0, count=-1;
 
//Função para introduzir a chave
void key_input()
{
      printf("Enter a Key:\t");
      scanf("%d", &key);
}

//Função da cifra Caesar
void caesar()
{ 
    for(count = 0; buffer[count] != '\0'; count++)
      {
            temp = buffer[count];
            if(temp >= 'a' && temp <= 'z')
            {
                  temp = temp + key;
                  if(temp > 'z')
                  {
                        temp = temp - 'z' + 'a' - 1;
                  }
                  buffer[count] = temp;
            }
            else if(temp >= 'A' && temp <= 'Z')
            {
                  temp = temp + key;
                  if(temp > 'Z')
                  {
                        temp = temp - 'Z' + 'A' - 1;
                  }
                  buffer[count] = temp;
            }
      }
      printf("\nCaesar encrypted message:\n%s\n", buffer);
}

//Função da cifra Affine 
void affine()
{
 int CalcGCD(int);

 int i,j,gcd,alpha,beta,numbuffer[100],numcipher[100];
 
 //converting entered buffering to Capital letters
 for(i=0,j=0;i<strlen(buffer);i++)
 {
  if(buffer[i]!=' ')
  {
   buffer[j]= toupper(buffer[i]);
   j++;
  }
  else
  {
   buffer[j]=' ';
   j++;
  }
 }
 buffer[j]='\0';
 printf("Enter Alpha value and must be odd numbers between 1 and 25 both included:\t");
 scanf("%d",&alpha); 
 //Checking consitions
 if(alpha<1 || alpha>25)
 {
  printf("Alpha should lie in between 1 and 25\nSorry Try again !\n");
  exit(0);
 } 
 gcd=CalcGCD(alpha);
 if(gcd!=1)
 {
  printf("gcd(alpha,26)=1 but \n gcd(%d,26)=%d\nSorry Try again !\n",alpha,gcd);
  exit(0);
 }
 printf("Enter Beta value and must be between 0 and 25 both included:\t");
 scanf("%d",&beta);
 if(beta<0 || beta>25)
 {
  printf("Beta value should lie between 0 and 25\nSorry Try again !\n");
  exit(0);
 }
 //Conditions Over
 //Program Starts
 //Storing buffering in terms of ascii and to restore spaces I used -20
 for(i=0;i<strlen(buffer);i++)
 {
  if(buffer[i]!=' ')
  numbuffer[i]=buffer[i]-'A';
  else
  numbuffer[i]=-20;
 }
 //Ciphering Process
    //If numcipher is more than 25 .We need to convert and ensure that lie in between 0 and 25.(indicating Alphabets)
    //A-0,B-1,C-2,.....Y-24,Z-25
  printf("Affine Cipher message:\n");
  for(i=0;i<strlen(buffer);i++)
  {
    if(numbuffer[i]!=-20)
    {
    numcipher[i]=((alpha*numbuffer[i])+beta)%26;
        printf("%c",(numcipher[i]+'A'));
    }
    else
    {
        printf(" ");
    }
  }
printf("\n");
 
}

//Função para calcular o GCD 
int CalcGCD(int alpha)
{
   int x;
   int temp1=alpha;
   int temp2=26;

     while(temp2!=0)
      {
        x=temp2;
        temp2=temp1%temp2;
        temp1=x;
      }
     return(temp1);
}

//Função da cifra Polybius
void poly(){
 int i,j,poly[26],x,k;
 
 x=0;
 k=11;

 for(i=0;i<=25;i++){
  if(i<=8){
    if(i%5==0&&i!=0){
      k+=5;
      poly[x]=k++;
      }
    else{
      poly[x]=k++;
    }
 }
  if(i>=10){
    if(i%5==0&&i!=0){
      poly[x]=k++;
      k+=5;
      }
    else{
      poly[x]=k++;
    }  
 }
 if(i==9){
   poly[x]=24;
   }

  x++;
}
i=0;
printf("Encrypted Code using Polybius Square Cipher \n");
while(buffer[i]!='\0'){
  if(!((buffer[i]>=0&&buffer[i]<=31)||(buffer[i]>=33&&buffer[i]<65)||(buffer[i]>90&&buffer[i]<97)||(buffer[i]>122&&buffer[i]<=127))){
    if(buffer[i]>='A'&&buffer[i]<='Z'){
      printf("%d ",poly[buffer[i]-'A']);
    }
    if(buffer[i]>='a'&&buffer[i]<='z'){
      printf("%d ",poly[buffer[i]-'a']);}
    } 
    if(buffer[i]==' '){
      printf("%c ",buffer[i]);    
    }
   i++;
  }
  printf("\n");
  
}

//Função para fornecer um caracter aleatório do alfabeto latim
char rand_str() {
   
   char char1[] = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
   return  char1[rand() % (sizeof char1 - 1)];
}


//Função menu, permite escolher a cifra
void menu(){
  int choice;
        while(1)
      {     
            //Imprime o texto do menu
            printf("\n---------------MENU---------------\n");
            printf("        AVAILABLE CIPHERS        \n");
            printf("\n1. Caesar\n2. Affine\n3. Polybius\n");
            printf("----------------------------------\n");
            printf("\nEnter You Choice:\t");
            //Recebe a escolha do utilizador
            scanf("%d", &choice);
            switch(choice)
            {
                  case 1: key_input();   
                          caesar();
                          exit(0);
                  case 2: affine();
                          exit(0);
                  case 3: poly();
                          exit(0);
                  default: printf("\nPlease select a correct option:\n");
            }
      }
      printf("\n");
}

//Chamar as funções do produtor e consumidor
int *producer(void *pno);
int *consumer(void *cno);

//Função main
int main()
{        
int a, b;

//Permite ao utilizador escolher o número de produtores e consumidores, até 30.

printf("Enter the number of entity A (Producer) [0-30]:\t");
scanf("%i", &a);

printf("Enter the number of entity B (Consumer) [0-30]:\t");
scanf("%i", &b);

    //Criar as threads
    pthread_t pro[a],con[b];
    //Iniciar o mutex
    pthread_mutex_init(&mutex, NULL);
   
    //Numerar o produtor e o consumidor
    int c[MAX_BUFFER] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30}; 

    //Ciclo para criar os produtores
    for(int i = 0; i < a; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&c[i]);
    }
    //Ciclo para criar os consumidores
    for(int i = 0; i < b; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&c[i]);
    }

    //Junta as threads do produtor
    for(int i = 0; i < a; i++) {
        pthread_join(pro[i], NULL);
    }
    
    //Junta as threads do consumidor
    for(int i = 0; i < b; i++) {
        pthread_join(con[i], NULL);
    }

    //Abre o menu
    menu();

    //Remover o mutex
    pthread_mutex_destroy(&mutex);
    
   
return 0;
}


//Função do produtor
int *producer(void *pno)
{   
    //Declarar variáveis
    char item;
    
    //Vai criar uma seed ao tempo do computador 
    srand(time(0));

    //Verificar se o estado está vazio
    if(state==VAZIO){
    //Ciclo para produzir itens
    for(int i = 0; i < MAX_BUFFER; i++) {
        //Atribui-se à variável item um caracter aleatório
        item = rand_str();
        //Bloqueia o mutex
        pthread_mutex_lock(&mutex);
        //Vai produzir até ao buffer ficar cheio 
        if(count<limite){
        count++;
        buffer[count] = item;
        printf("Producer %d: Insert Item %c at %d\n", *((int *)pno),buffer[count],count);
        }
        //Desbloqueia o mutex
        pthread_mutex_unlock(&mutex);
        
        }
        //Estado passa a cheio
        state=CHEIO;
    }
    return 0;
}

//Função do consumidor
int *consumer(void *cno)
{   
    //Ciclo para remover itens 
    for(int i = 0; i < MAX_BUFFER; i++) {
        
        //Bloqueia o mutex
        pthread_mutex_lock(&mutex);
        //Vai consumir até ao buffer ficar vazio
        if(count>=0){
        char item = buffer[count];
        printf("Consumer %d: Remove Item %c from %d\n",*((int *)cno),item, count);
        count--;
        }
        //Desbloqueia o mutex
        pthread_mutex_unlock(&mutex);
    }
    
    //Estado passa a vazio
    state=VAZIO;
   return 0; 
}

