# MC504 - Sistemas Operacionais

## Projeto 1: Aplicação Multithread

### Tema
Paciência, o jogo de cartas.

### Requisitos
- [ ] Uso da biblioteca pthread 

- [ ] Matriz de dados a ser lida e processada
Matriz com 12 linhas representando os 12 montes, 1 de compra, 7 de organização e 4 de montagem. 
O tamanho máximo de cada vetor:
* Compra: 23 cartas
* Organização: 19 cartas, sendo este o monte com maior número de cartas fechadas e a sequência completa de K (Rei) até A (Ás)
* Montagem: 13 cartas

Sobre as cartas
Um baralho possui 52 cartas, cada carta possui um valor e um naipe. O valor pode ser um número de 2 a 10, ou A (Ás), K (Rei), Q (Rainha) ou J (Valete). E o naipe pode variar entre 4 símbolos, paus (♣), ouros (♦), copas (♥) e espadas (♠). No jogo, as cartas também vão ser consideradas abertas ou fechadas. 

- [ ] Threads colaboram neste processamento

- [ ] Estratégias para divisão de trabalho

- [ ] Problema que dispense sincronização durante o processamento
