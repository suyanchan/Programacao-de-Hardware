/****************************************************************************
 * Copyright (C) 2020 by Programacao de Hardware Engenharia de computacao   *
 *                                                                          *
 * This file is part of TP02.                                               *
 *                                                                          *
 * TP02 e um software livre: voce pode redistribui-lo e / ou modifica-lo    *
 * sob os termos da GNU Lesser General Public License conforme publicada    *
 * pela Free Software Foundation, seja a versao 3 da Licenca, ou            *
 * (a sua escolha) qualquer versao posterior.                               *
 *                                                                          *
 * O TP02 e distribuido na esperanca de que seja util,                      *
 * mas SEM QUALQUER GARANTIA; sem mesmo a garantia implicita de             *
 * COMERCIALIZACAO ou ADEQUACAO A UM DETERMINADO FIM. Veja o                *
 * GNU Lesser General Public License para obter mais detalhes.              *
 *                                                                          *
 * Voce deve ter recebido uma copia do GNU Lesser General Public            *
 * Licenca junto com TP02. Caso contrario, consulte                         *
 *<http://www.gnu.org/licenses/>.                                           *
 * <https://www.doxygen.nl/manual/index.html>                               *
 ****************************************************************************/

/**
 * @file TP02.c
 * @author <b>Suyan Rocha Vidal RA 080350, Giovanna Pimenta RA 171886, Vinicius Mazitelli RA 173997,
 * Daniel Santos RA 159713 e Aguinaldo Parreira RA 176888</b>
 * @date 21 Aug 2021
 * @brief <b>TP02 da materia Programacao de Hardware do 6 ciclo de Engenharia de Computacao.</b>
 *
 * O aluno(a) devera desenvolver um codigo em C, em que ele devera criar as funcoes de manipulacao de IO 
 * (usando os registros DDRx,PINx,PORTx) onde cada devera proporcionar ao usuario poder escolher qualquer 
 * pino e port que ele quiser.  Em seguida, na funcao main, o aluno devera implementar um exemplo usando 
 * as funcoes, e de preferencia para implementar como se fosse um projeto (de sua escolha. EX: Sensor de 
 * janelas).A resposta devera ser implementado cabecalho de acordo com o exemplo deste e descricao de cada
 * comando usando Doxygen. A resposta devera ser enviada para o proprio github do aluno, e postar os 
 * arquivos fonte na tarefa do teams.
 * 
 * O envio dos arquivos deverao ser enviados os codigos fontes puros e a documentacao gerada pelo doxygen 
 * em uma pasta zipada(no teams). No seu github, deve-se colocar da forma mais organizada que o aluno achar
 * (deve-se colocar o link do github dele no codigo fonte principal).
 * 
 * TP realizado em grupo devido a alta complexidade.
 * 
 * Aplicacao de um projeto baseado num sensor de presenca para o acionamento de uma lampada atraves de 
 * de um rele.
 *
 * @note https://github.com/suyanchan/Programacao-de-Hardware
 * @see http://inovfablab.unisanta.br
 * @see http://fabmanager.unisanta.br
 */


#include <avr/io.h>
#include <avr/delay.h>
#include <string.h>
#include <stdio.h>
#include <avr/sfr_defs.h>

#define _BV(bit) (1 << bit)

/**
 * @brief Cria uma struct para entrada de dados, fornecida pelo usuario.
 */

struct Ent_Usuario  
{
	char porta1;	/**< Campo da struct Ent_Usuario que recebera o valor da porta 1 escolhida pelo usuario. */
	char pino1;		/**< Campo da struct Ent_Usuario que recebera o valor do pino 1 escolhido pelo usuario. */
	char porta2;	/**< Campo da struct Ent_Usuario que recebera o valor da porta 2 escolhida pelo usuario. */
	char pino2;		/**< Campo da struct Ent_Usuario que recebera o valor do pino 2 escolhido pelo usuario. */
};	
struct Ent_Usuario usuario;  /**< Define o nome usuario usada para referenciar a struct. */

char ddr1= 'DDR';		/**< Variavel ddr1 com a string a ser concatenada com a entrada do usuario no campo porta1. */
char ddr2 = 'DDR';		/**< Variavel ddr2 com a string a ser concatenada com a entrada do usuario no campo porta2. */
char pin1 = 'PIN';		/**< Variavel pin1 com a string a ser concatenada com a entrada do usuario no campo porta1. */
char prt2 = 'PORT';		/**< Variavel prt2 com a string a ser concatenada com a entrada do usuario no campo porta2. */

int main(void)
{
    printf("Favor digitar qual porta (B, C ou D) está conectada o sensor: ");		/**< Solicita a entrada do dados para o usuario. */
    scanf("%s", &usuario.porta1);													/**< Armazena a entrada da string no campo porta1 da struct usuario. */
    
    printf("Favor digitar qual pino (0-7) está conectado o sensor: ");				/**< Solicita a entrada do dados para o usuario. */
    scanf("%s", &usuario.pino1);													/**< Armazena a entrada da string no campo pino1 da struct usuario. */

    printf("Favor digitar qual porta (B, C ou D) está conectada o rele: ");			/**< Solicita a entrada do dados para o usuario. */
    scanf("%s", &usuario.porta2);													/**< Armazena a entrada da string no campo porta2 da struct usuario. */
    
    printf("Favor digitar qual pino (0-7) está conectado o rele: ");				/**< Solicita a entrada do dados para o usuario. */
    scanf("%s", &usuario.pino2);													/**< Armazena a entrada da string no campo pino2 da struct usuario. */
	
	strcat(ddr1, usuario.porta1);			/**< Concatena as duas strings e armazena na variavel ddr1. */
	strcat(ddr2, usuario.porta2);			/**< Concatena as duas strings e armazena na variavel ddr2. */
	strcat(pin1, usuario.porta1);			/**< Concatena as duas strings e armazena na variavel pin1. */
    strcat(prt2, usuario.porta2);			/**< Concatena as duas strings e armazena na variavel prt2. */
    
	return (0);

	ddr1 &= ~ _BV(usuario.pino1);			/**< Configura a porta ddr1 como INPUT, utilizando a macro. (sensor) */
	ddr2 |= _BV(usuario.pino2);				/**< Configura a porta ddr2 como OUTPUT, utilizando a macro.(rele - lampada) */

    while (1) 
    {
		int sensor = pin1 & _BV(usuario.pino1);			/**< Le o estado do sensor no pino e armazena na variavel sensor. */
		
		if(sensor == 0)									/**< Verifica se o valor da variavel e 0, ou seja, desligado. */
		{
			prt2 &= ~_BV(usuario.pino2);				/**< Desliga o Rele. */
		}
		else
		{
			prt2 |= _BV(usuario.pino2);					/**< Liga o Rele. */
		}
			
    }
}

