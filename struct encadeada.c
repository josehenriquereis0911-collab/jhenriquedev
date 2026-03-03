#include<stdio.h>
#include<string.h>
struct Imovel{
    char tipo[30];
    int comodos;
};
struct Casa{
    int numero;
    char nome_rua[50];
    struct Imovel imovel;
};
struct Pessoa{
    char nome[30];
    float peso;
    struct  Casa casa;
};
int main(){
    printf("digite a qantidade de cadastros:");
    int quant;
    scanf("%d",&quant);
    struct Pessoa pes[quant];
    for (int i=0; i<quant; i++){
        setbuf(stdin,NULL);
        printf("digite o nome:");
        fgets(pes[i].nome,sizeof(pes[i].nome),stdin);
        getchar();
        printf("digite seu peso:");
        scanf("%f",&pes[i].peso);
        getchar();
        printf("digite o nome da sua rua:");
        fgets(pes[i].casa.nome_rua,sizeof(pes[i].casa.nome_rua),stdin);
        getchar();
        printf("digite o numero de sua residencia:");
        scanf("%d",&pes[i].casa.numero);
        printf("digite o tipo de imovel que você mora:");
        scanf("%s",pes[i].casa.imovel.tipo);
        getchar();
        printf("digite a quantidade de comodos:");
        scanf("%d",&pes[i].casa.imovel.comodos);
    }
    printf("\n-------------------------------------------------\n");
    for (int i=0; i<quant; i++){
        printf("nome:%s",pes[i].nome);
        printf("peso:%.2f\n",pes[i].peso);
        printf("nome da rua:%s",pes[i].casa.nome_rua);
        printf("numero da residencia:%d\n",pes[i].casa.numero);
        printf("tipo:%s\n",pes[i].casa.imovel.tipo);
        printf("quantidade de comodos:%d \n",pes[i].casa.imovel.comodos);
        printf("-------------------------------------------------\n");
        
    }
}