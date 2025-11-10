# 🎵 Projeto Final — Cadastro de Músicos  

### 👨‍💻 Autores
- **João Gabriel Carvalho Criscolo**  
- **Plínio Alves Cardoso**  
- **Bernardo Corradi Oliveira**

---

## 🧾 Descrição

Este projeto consiste em um sistema de **cadastro e gerenciamento de músicos**, desenvolvido em **C++**, como parte do projeto prático da disciplina de IALG.  

O sistema permite **inserir, buscar, alterar e excluir** informações de músicos, armazenadas em um **arquivo CSV**, simulando uma pequena base de dados.  

---

## ⚙️ Funcionalidades

✅ Leitura e escrita em arquivo CSV  
✅ Inserção de novos músicos  
✅ Remoção lógica (com exclusão definitiva ao salvar)  
✅ Busca binária por CPF  
✅ Ordenação eficiente (sem uso de `sort()` ou `bubblesort()`)  
✅ Alteração de dados existentes  
✅ Exibição completa ou por intervalo (ex: posição 10 a 20)  
✅ Identificação da banda com mais músicos cadastrados  
✅ Redimensionamento automático do vetor (+5 posições)  

---

## 🧮 Estrutura de Dados

Cada músico é representado pela estrutura:

```cpp
struct musico {
    int CPF;
    string nome;
    int idade;
    string instrumento;
    string banda;
    bool removido = false;
};
