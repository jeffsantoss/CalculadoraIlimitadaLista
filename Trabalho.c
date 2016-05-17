#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"
#include "Trabalho.h"

void menu(Lista *numero, Lista* potencia,Lista *resultado)
{
 
    char ch;
	int num1, pot;

	printf("Bem vindo a \"Smart Calculator\", a calculadora de potências ilimitadas! \n");
    printf("Selecione o que deseja fazer: \n");
    printf("\t\t1 - Soma \n");
    printf("\t\t2 - Multiplicacao \n");
    printf("\t\t3 - Potencia \n");
    printf("\t\t4 - Sair \n");
    printf("\n\t\tEste programa foi desenvolvido por Eron Fernandes e Jefferson Santos \n");

    ch = getch();

    while(ch != '1' && ch != '2' && ch != '3' && ch != '4')
    {
        printf("\nSelecione um valor valido: ");
        ch = getch();
    }

    switch(ch)
    {
        case '1':
            printf("Escolha seu numero1 e numero2 para somar. \n");
            printf("Ex: '120 13' equivale a 120 mais 13. \n");
            scanf_s("%d %d", &num1, &pot);
            numero = numero_para_lista(num1);
            potencia = numero_para_lista(pot);
            resultado = somar(numero, potencia);
            printf("Resultado: ");
            imprimir(resultado);
            printf("\n");
            break;
        case '2':
            printf("Escolha seu numero1 e numero2 para multiplicar. \n");
            printf("Ex: '120 13' equivale a 120 vezes 13. \n");
            scanf_s("%d %d", &num1, &pot);
			numero = numero_para_lista(num1);
            potencia = numero_para_lista(pot);
            resultado = multiplicar(numero, pot);
            printf("Resultado: ");
            imprimir(resultado);
            printf("\n");
            break;
        case '3':
            printf("Escolha seu numero e a potencia para elevar. \n");
            printf("Ex: '120 13' equivale a 120 elevado a 13. \n");
            scanf_s("%d %d", &num1, &pot);
            numero = numero_para_lista(num1);
            potencia = numero_para_lista(pot);
            resultado = potenciacao(numero, pot);
            printf("Resultado: ");
            imprimir(resultado);
            printf("\n");
            break;
        case '4':
            exit(0);
            break;
        default:
            printf("Switch deu errado \n");
            break;
    }

}


Lista * numero_para_lista(int n) // funcionando perfeitamente
{
    Lista *resultado = criar();

    while( n > 0 )
    {
        inserir_primeiro(resultado,n%10);
        n /= 10;
    }

    return resultado;
}

Lista * somar(Lista *operando1, Lista *operando2) //funcionando perfeitamente
{
	int i;
	int valor = 0;
	int tam1 = tamanho(operando1);
	int tam2 = tamanho(operando2);
	Lista *resultadoSoma = criar();

    // caso os operandos sejam de tamanhos distintos, completa-se com zeros no inicio.
	if(tam1 > tam2){
        for(i = 0; i < tam1-tam2; i++)
            inserir_primeiro(operando2, 0);
	}
    // caso os operandos sejam de tamanhos distintos, completa-se com zeros no inicio.
	if(tam2 > tam1){
        for(i = 0; i < tam2-tam1; i++)
            inserir_primeiro(operando1, 0);
    }

    // soma do ultimo algarismo até o primeiro
    // colocando as unidades no resultado e somando a dezena na proxima soma.
	tam1 = tamanho(operando1);

	while(tam1 > 0){
	        /*printf("Somando: \n");  // somando -------------------------------------------------
		    imprimir(operando1);    // operando1 -----------------------------------------------
	        imprimir(operando2);    // operando2 -----------------------------------------------*/
		valor = ler_pos(operando1, tam1-1) + ler_pos(operando2, tam1-1) + valor/10 ; // valor/10 é o "vai um" da operação.
		inserir_primeiro(resultadoSoma, valor%10);
		tam1--;
	}

    // caso sobre uma dezena da soma do primeiro algarismo, ela é adicionada no inicio do numero.
	if(valor/10 > 0)
        inserir_primeiro(resultadoSoma, valor/10);
/*
    printf("Soma efetuada: \n");// soma efetuada -------------------------------------------
    imprimir(resultadoSoma);    // resultado -----------------------------------------------
    system("pause");*/
    return resultadoSoma;
}

Lista * multiplicar(Lista * l, int n) // funcionando perfeitamente
{
	Lista * resultadoMult = criar();
	int valor = 0; // resultado da multiplicação de 'n' por um valor da lista
	int tam;

    // multiplica 'n' por toda a lista 'l'
	for(tam = tamanho(l); tam > 0; tam--)
    {
		valor = n*ler_pos(l, tam-1) + valor/10;     //valor é um numero de dois digitos
		inserir_primeiro(resultadoMult, valor%10);  // insere a unidade no final
	}

	// ao terminar a multiplicacao, insere o "vai um", que é a dezena, no inicio do numero;
	if(valor/10 > 0)
		inserir_primeiro(resultadoMult, valor/10);

	return resultadoMult;
}

Lista * multiplicar_listas(Lista *operando1, Lista *operando2) // funcionando perfeitamente
{
    int tam2 = tamanho(operando2);
    int i,j;
    Lista *resultado1 = criar();
    Lista *resultado2;
    Lista *lixo;

    for(j = 0; tam2 > 0; j++, tam2--)
    {
        resultado2 = multiplicar(operando1, ler_pos(operando2, tam2-1));
        for(i = 0; i<j ;i++)
        {
            inserir_ultimo(resultado2, 0);
        }
        // como o resultado1 sempre vai pegar um valor de soma e vai perder o caminho para a lista original
        // a variavel "lixo" sempre pega os endereços perdidos e destrói.
        lixo = resultado1;
        resultado1 = somar(resultado1, resultado2);
        destruir(lixo);
    }

    return resultado1;
}

Lista * potenciacao(Lista *numero, int pot)
{
    Lista *resultado;
    int i;

    resultado = numero;

    for(i=1; i<pot; i++)
    {
        resultado = multiplicar_listas(resultado, numero);
    }
    return resultado;
}

