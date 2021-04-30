# MC504 - Sistemas Operacionais

## 💽 Projeto 1: Aplicação Multithread 

### 🎲 Tema 
O tema do nosso projeto 1 é  [Campo Minado](https://pt.wikipedia.org/wiki/Campo_minado), o jogo de computador que tem como objetivo revelar um campo de minas sem que alguma seja detonada.

### 📌 Requisitos 
- [x] Uso da biblioteca pthread 
- [x] Matriz de dados a ser lida e processada
- [x] Threads colaboram neste processamento
- [x] Estratégias para divisão de trabalho
- [x] Problema que dispense sincronização durante o processamento

#### 📋 Matriz 
Matriz com 9 linhas e 9 colunas. 

#### 🃏 Campo

Cada espaço da matriz possui três propriedades:

* ``value``: valor, que pode ser o valor de bombas ao seu redor (0 a 8) ou 10 que é o valor das bombas
* ``is_open``: dita se o campo foi aberto, é iniciado fechado
* ``is_flagged``: dita se há uma bandeira, sinalização feita pelo usuário para mostrar onde acredita ter uma mina

## Projeto 2: Animação multithread com semáforos

### Tema
O tema do nosso segundo projeto será festas clandestinas durante a pandemia. Baseado em ["The room party problem"](https://greenteapress.com/semaphores/LittleBookOfSemaphores.pdf).

### Objetivo
Implementação de uma aplicação multithread que utiliza semáforos para sincronização e de um visualizador para o progresso desta aplicação.

### Problema
Durante a pandemia, um grupo de alunos organiza festas clandestinas. A polícia faz fiscalização de acomodações e multa pessoas que estiverem se aglomerando inadequadamente.

#### Sincronização
As seguintes restrições se aplicam aos alunos e à polícia:
* Qualquer número de estudantes pode estar na festa ao mesmo tempo.
* A polícia só pode entrar na acomodação se não houverem alunos no lugar (fiscalização) ou se houverem mais de 20 (multa as pessoas e dispersa a aglomeração).
* Enquanto a polícia estiver no lugar, nenhum aluno poderá entrar, mas podem sair.
* A polícia não sairá do lugar enquanto tiverem alunos na casa.
* Só existe uma unidade de polícia atendendo o local.

## 💻 Autores 

<img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/42704998?v=4" width="50px;" alt=""/><sub><b> Enrico Delbuono </b></sub>
<img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/48157146?v=4" width="50px;" alt=""/><sub><b> Matheus Hatzlhoffer </b></sub>
<img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/42664943?v=4" width="50px;" alt=""/><sub><b> Mariana Izumizawa </b></sub>
