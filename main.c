#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

//Clientes

struct Ttelefone
{
    int ddd;
    float numero;
};
typedef struct Ttelefone tel;

struct Tclientes
{
    int codigo;
    tel telefone;
    char nome[30],endereco[100];
};
typedef struct Tclientes cliente;

//Funcion�rio

struct Tfuncionario
{
    int codigo,salario,telefone;
    char nome[30],cargo[30];
};
typedef struct Tfuncionario funcionario;

//Loca��o

struct TdtRet
{
    int dia,mes,ano;
};
typedef struct TdtRet dtRet;

struct TdtDev
{
    int dia,mes,ano;
};
typedef struct TdtDev dtDev;

struct Tlocacao
{
    int codigo,seguro,dias,cod_c,cod_v;
    dtRet dataRet;
    dtDev dataDev;
};
typedef struct Tlocacao locacao;

//Veiculo

struct Tveiculo
{
    int codigo,qnt,status;
    char descricao[100],modelo[30],cor[30],placa[9];
    float valor;
};
typedef struct Tveiculo veiculo;


int main()
{
    FILE *aclientes;
    FILE *afuncionarios;
    FILE *aveiculos;
    FILE *alocacao;

    int op;
    setlocale(LC_ALL,"portuguese");

//    Incializando os arquivos

    if ((aclientes=fopen("aclientes.dat","r+b"))==NULL)
    {
        printf("Arquivo n�o existia ... criando novo arquivo!");
        if ((aclientes=fopen("aclientes.dat","w+b"))==NULL)
        {
            printf("Erro na cria��o do arquivo!!");
            exit(1);
        }
        system("pause");
    }

    if ((afuncionarios=fopen("afuncionarios.dat","r+b"))==NULL)
    {
        printf("Arquivo n�o existia ... criando novo arquivo!");
        if ((afuncionarios=fopen("afuncionarios.dat","w+b"))==NULL)
        {
            printf("Erro na cria��o do arquivo!!");
            exit(1);
        }
        system("pause");
    }

    if ((aveiculos=fopen("aveiculos.dat","r+b"))==NULL)
    {
        printf("Arquivo n�o existia ... criando novo arquivo!");
        if ((aveiculos=fopen("aveiculos.dat","w+b"))==NULL)
        {
            printf("Erro na cria��o do arquivo!!");
            exit(1);
        }
        system("pause");
    }

    if ((alocacao=fopen("alocacao.dat","r+b"))==NULL)
    {
        printf("Arquivo n�o existia ... criando novo arquivo!");
        if ((alocacao=fopen("alocacao.dat","w+b"))==NULL)
        {
            printf("Erro na cria��o do arquivo!!");
            exit(1);
        }
        system("pause");
    }

//   MENU


    do
    {
        printf("Escolha:\n");
        printf("1- Cadastrar um cliente\n");
        printf("2- Cadastrar um funcion�rio\n");
        printf("3- Cadastrar loca��o\n");
        printf("4- Cadastrar ve�culo\n");
        printf("5- Premia��o\n");
        printf("6- Imprimir dados do cliente\n");
        printf("7- Imprimir dados do funcion�rio\n");
        printf("8- Imprimir dados de loca��o do cliente\n");
        printf("9 - Sair do programa\n");
        scanf("%d",&op);
        switch(op)
        {
        case 1:
            inclui_cliente(aclientes);
            break;
        case 2:
            inclui_funcionario(afuncionarios);
            break;
        case 3:
            inclui_locacao(alocacao,aclientes,aveiculos);
            break;
        case 4:
            inclui_veiculo(aveiculos);
            break;
        case 5:
            imprime_veiculo(aveiculos);
            system("pause");
            break;
        case 6:
            imprime_cliente(aclientes);
            system("pause");
            break;
        case 7:
            imprime_funcionario(afuncionarios);
            system("pause");
            break;
        case 8:
            imprime_locacao(alocacao);
            system("pause");
            break;

        }
        if (op!=9)
        {
            system("pause");
        }
        system("cls");
    }
    while(op!=9);
    fclose(aclientes);
    fclose(afuncionarios);
    fclose(aveiculos);
    fclose(alocacao);
    return 0;

}

int localiza_cliente(FILE *aclientes,int codigo, char nome[30])
{
    int posicao=-1,achou=0,teste;
    cliente c;
    fseek(aclientes,0,SEEK_SET);
    fread(&c, sizeof(c),1, aclientes);
    while (!feof(aclientes) && !achou)
    {
        posicao++;
        if (c.codigo==codigo || strcmpi(c.nome,nome)==0)
        {
            achou=1;
        }
        fread(&c, sizeof(c),1, aclientes);
    }
    if (achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}
int localiza_funcionario(FILE *afuncionarios,int codigo)
{
    int posicao2=-1,achou=0;
    funcionario f;
    fseek(afuncionarios,0,SEEK_SET);
    fread(&f, sizeof(f),1, afuncionarios);
    while (!feof(afuncionarios) && !achou)
    {
        posicao2++;
        if (f.codigo==codigo)
        {
            achou=1;
        }
        fread(&f, sizeof(f),1, afuncionarios);
    }
    if (achou)
    {
        return posicao2;
    }
    else
    {
        return -1;
    }
}
int localiza_locacao(FILE *alocacao,int codigo)
{
    int posicao=-1,achou=0;
    locacao l;
    fseek(alocacao,0,SEEK_SET);
    fread(&l, sizeof(l),1, alocacao);
    while (!feof(alocacao) && !achou)
    {
        posicao++;
        if (l.codigo==codigo)
        {
            achou=1;
        }
        fread(&l, sizeof(l),1, alocacao);
    }
    if (achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}
int localiza_veiculo(FILE *aveiculos,int codigo,int qnt)
{
    int posicao=-1,achou=0;
    veiculo v;
    fseek(aveiculos,0,SEEK_SET);
    fread(&v, sizeof(v),1, aveiculos);
    while (!feof(aveiculos) && !achou)
    {
        posicao++;
        if (v.codigo==codigo || (v.qnt==qnt && v.status==0))
        {
            achou=1;
        }
        fread(&v, sizeof(v),1, aveiculos);
    }
    if (achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}

void inclui_cliente(FILE *aclientes)
{
    cliente c;
    int posicao;
    printf("Digite o c�digo do cliente...:");
    fflush(stdin);
    scanf("%d",&c.codigo);
    posicao=localiza_cliente(aclientes,c.codigo,"---");
    if (posicao==-1)
    {
        printf("Digite o nome do cliente....:");
        fflush(stdin);
        gets(c.nome);
        printf("Digite o telefone do cliente:\n");
        printf("Digite o DDD................:\n");
        fflush(stdin);
        scanf("%d",&c.telefone.ddd);
        printf("Digite o n�mero.............:\n");
        fflush(stdin);
        scanf("%f",&c.telefone.numero);
        printf("Digite o endere�o do cliente:");
        fflush(stdin);
        gets(c.endereco);
        fseek(aclientes,0,SEEK_END);
        fwrite(&c, sizeof(c),1,aclientes);
        fflush(aclientes);
    }
    else
    {
        printf("J� existe um cliente com esse c�digo. Inclus�o n�o realizada!\n");
    }
}
void inclui_funcionario(FILE *afuncionarios)
{
    funcionario f;
    int posicao2;
    printf("Digite o c�digo do funcion�rio...:");
    fflush(stdin);
    scanf("%d",&f.codigo);
    posicao2=localiza_funcionario(afuncionarios,f.codigo);
    if (posicao2==-1)
    {
        printf("Digite o nome do funcion�rio...:");
        fflush(stdin);
        gets(f.nome);
        printf("Digite o telefone do funcion�rio...:");
        fflush(stdin);
        scanf("%d",&f.telefone);
        printf("Digite o cargo do funcion�rio...:");
        fflush(stdin);
        gets(f.cargo);
        printf("Digite o sal�rio do funcion�rio...:");
        fflush(stdin);
        scanf("%d",&f.salario);
        fseek(afuncionarios,0,SEEK_END);
        fwrite(&f, sizeof(f),1,afuncionarios);
        fflush(afuncionarios);
    }
    else
    {
        printf("J� existe um funcion�rio com esse c�digo. Inclus�o n�o realizada!\n");
    }
}
int calcula_dias(int dia1,int mes1,int ano1,int dia2,int mes2,int ano2)
{
    int i, total1=0, total2=0,res;

// Calcula dias da data de retirada (01/01/2020 como dia 1)

    for (i=2020;i<ano1;i++)
    {

        if((i%4==0 && i%100!=0)||i%400==0)
        {
            total1+=366;
        }
        else
        {
            total1+=365;
        }
    }
    for (i=1;i<mes1;i++)
    {
        printf("i=%d",i);
        if((i%2!=0 && i<=7)||(i%2==0 && i>7))
        {
            total1+=31;
        }

        if(i==2 && ((ano1%4==0 && ano1%100!=0)||i%400==0))
        {
            total1+=29;
        }
        if(i==2 && !((ano1%4==0 && ano1%100!=0)||i%400==0))
        {
            total1+=28;
        }
        if((i%2==0 && i<=7)||(i%2!=0 && i>7))
        {
            total1+=30;
        }
    }

    total1+=dia1;

// Calculando dias da data de devolu��o

        for(i=2020;i<ano2;i++)
    {
        if((i%4==0 && i%100!=0)||i%400==0)
        {
            total2+=366;
        }
        else
        {
            total2+=365;
        }
    }
    for(i=1;i<mes2;i++)
    {
        if((i%2!=0 && i<=7)||(i%2==0 && i>7))
        {
            total2+=31;
        }

        if(i==2 && ((ano1%4==0 && ano1%100!=0)||i%400==0))
        {
            total2+=29;
        }
        if(i==2 && !((ano1%4==0 && ano1%100!=0)||i%400==0))
        {
            total2+=28;
        }
        if((i%2==0 && i<=7)||(i%2!=0 && i>7))
        {
            total2+=30;
        }
    }

    total2+=dia2;

    res=total2-total1;
    return res;


}

void inclui_locacao(FILE *alocacao, FILE *aclientes, FILE *aveiculos)
{
    locacao l;
    cliente c;
    veiculo v;
    int posicao1,posicao2,posicao3,qtd;
    char nome[30];
    printf("Digite o c�digo da loca��o...:");
    fflush(stdin);
    scanf("%d",&l.codigo);
    posicao1=localiza_locacao(alocacao,l.codigo);
    if (posicao1==-1)
    {
        printf("Digite o nome completo do cliente:");
        fflush(stdin);
        gets(nome);
        posicao2=localiza_cliente(aclientes,-1,nome);
        if (posicao2!=-1)
        {
            fseek(aclientes,sizeof(c)*posicao2,SEEK_SET);
            fread(&c,sizeof(c),1,aclientes);
            fflush(stdin);
            l.cod_c=c.codigo;
            printf("Digite o dia, m�s e ano da retirada do ve�culo:");
            fflush(stdin);
            scanf("%d%d%d",&l.dataRet.dia,&l.dataRet.mes,&l.dataRet.ano);
            printf("Digite o dia, m�s e ano da devolu��o do ve�culo:");
            fflush(stdin);
            scanf("%d%d%d",&l.dataDev.dia,&l.dataDev.mes,&l.dataDev.ano);
            printf("Digite a quantidade de ocupantes do veiculo:");
            fflush(stdin);
            scanf("%d",&qtd);
            l.dias=calcula_dias(l.dataRet.dia,l.dataRet.mes,l.dataRet.ano,l.dataDev.dia,l.dataDev.mes,l.dataDev.ano);
            fflush(stdin);
            posicao3=localiza_veiculo(aveiculos,-1,qtd);
            if (posicao3!=-1){
                fseek(aveiculos,sizeof(v)*posicao3,SEEK_SET);
                fread(&v,sizeof(v),1,aveiculos);
                fflush(stdin);
                l.cod_v=v.codigo;
                v.status=1;

                printf("Modelo......:%s\n",v.modelo);
                printf("Descri��o...:%s\n",v.descricao);
                printf("Cor.........:%s\n",v.cor);
                printf("Placa.......:%s\n",v.placa);
                printf("Ocupantes...:%d\n",v.qnt);
                printf("Valor/di�ria:%f\n",v.valor);

                printf("Seguro?");
                fflush(stdin);
                scanf("%d",&l.seguro);

                fseek(aveiculos,0,SEEK_END);
                fwrite(&v, sizeof(v),1,aveiculos);
                fflush(aveiculos);

                fseek(alocacao,0,SEEK_END);
                fwrite(&l, sizeof(l),1,alocacao);
                fflush(alocacao);
            }
            else
            {
                printf("N�o h� carros dispon�veis");
            }

        }
        else
        {
            printf("N�o h� clientes com esse nome. Por favor, cadastrar o cliente antes de realizar a loca��o.");
        }

    }
    else
    {
        printf("J� existe uma loca��o com esse c�digo. Inclus�o n�o realizada!\n");
    }
}

void inclui_veiculo(FILE *aveiculos)
{
    veiculo v;
    int posicao;
    printf("Digite o c�digo do ve�culo...:");
    fflush(stdin);
    scanf("%d",&v.codigo);
    posicao=localiza_veiculo(aveiculos,v.codigo,0);
    if (posicao==-1)
    {
        printf("Digite o modelo do ve�culo...:");
        fflush(stdin);
        gets(v.modelo);
        printf("Digite a descri��o do ve�culo...:");
        fflush(stdin);
        gets(v.descricao);
        printf("Digite a cor do ve�culo...:");
        fflush(stdin);
        gets(v.cor);
        printf("Digite a placa do ve�culo...:");
        fflush(stdin);
        scanf("%s",v.placa);
        printf("Digite o valor da di�ria do ve�culo...:");
        fflush(stdin);
        scanf("%f",&v.valor);
        printf("Digite a quantidade de ocupantes do ve�culo...:");
        fflush(stdin);
        scanf("%d",&v.qnt);
        v.status=0;
        fseek(aveiculos,0,SEEK_END);
        fwrite(&v, sizeof(v),1,aveiculos);
        fflush(aveiculos);
    }
    else
    {
        printf("J� existe um cliente com esse c�digo. Inclus�o n�o realizada!\n");
    }
}

void imprime_veiculo(FILE *aveiculos)
{
    int codigo,qnt,status;
    char descricao[100],modelo[30],cor[30],placa[9];
    float valor;

    veiculo v;
    fseek(aveiculos,0,SEEK_SET);
    fread(&v, sizeof(v),1, aveiculos);
    while (!feof(aveiculos))
    {
        printf("C�digo......:%d\n",v.codigo);
        printf("Descri��o...:%s\n",v.descricao);
        printf("Modelo......:%s\n",v.modelo);
        printf("Cor.........:%s\n",v.cor);
        printf("Placa.......:%s\n",v.placa);
        printf("Ocupantes...:%d\n",v.qnt);
        printf("Valor/di�ria:%f\n",v.valor);
        printf("Status......:%d\n",v.status);
        fread(&v, sizeof(v),1, aveiculos);
    }
}

void imprime_cliente(FILE *aclientes)
{
    cliente c;
    fseek(aclientes,0,SEEK_SET);
    fread(&c, sizeof(c),1, aclientes);
    while (!feof(aclientes))
    {
        printf("C�digo....:%d \n",c.codigo);
        printf("Nome.:%s \n",c.nome);
        printf("Telefone.....:(%d) %.0f\n",c.telefone.ddd,c.telefone.numero);
        printf("Endere�o.....:%s\n",c.endereco);
        fread(&c, sizeof(c),1, aclientes);
    }
}
void imprime_funcionario(FILE *afuncionarios)
{
    funcionario f;
    fseek(afuncionarios,0,SEEK_SET);
    fread(&f, sizeof(f),1, afuncionarios);
    while (!feof(afuncionarios))
    {
        printf("C�digo....:%d \n",f.codigo);
        printf("Nome.:%s \n",f.nome);
        printf("Telefone.....:%d\n",f.telefone);
        printf("Cargo.....:%s\n",f.cargo);
        printf("Sal�rio.....:%d\n",f.salario);
        fread(&f, sizeof(f),1, afuncionarios);
    }
}

void imprime_locacao(FILE *alocacao)
{
    locacao l;
    fseek(alocacao,0,SEEK_SET);
    fread(&l, sizeof(l),1, alocacao);
    while (!feof(alocacao))
    {
        printf("C�digo...........:%d \n",l.codigo);
        printf("Data da Retirada.:%d/%d/%d \n",l.dataRet.dia,l.dataRet.mes,l.dataRet.ano);
        printf("Data da Devolu��o:%d/%d/%d\n",l.dataDev.dia,l.dataDev.mes,l.dataDev.ano);
        printf("Dias de Aluguel..:%d\n",l.dias);
        printf("Seguro?..........:%d\n",l.seguro);
        printf("C�digo do Cliente:%d\n",l.cod_c);
        printf("C�digo do Ve�culo:%d\n",l.cod_v);
        fread(&l, sizeof(l),1, alocacao);
    }
}


