#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"
#include "Trabalho.h"

int main()
{
	Lista * numero = criar();
	Lista * potencia = criar();
    Lista * resultado = criar();
    int num;
    int pot;

	menu(numero, potencia, resultado);
	
	// feito altera��o para teste no github.


	destruir(numero);
	destruir(resultado);
	destruir(potencia);

	system("pause");
	return 0;
}
