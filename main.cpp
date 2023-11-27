#include <iostream>

struct BstNo {
    int data;
    BstNo* esquerda;
    BstNo* direita;
};

// Bst significa "Binary Search Tree" ou "Árvore de Pesquisa Binária"
BstNo* CriarNovoNo(int data) {
    BstNo* novoNo = new BstNo();
    novoNo->data = data;
    novoNo->esquerda = novoNo->direita = NULL;
    return novoNo;
}

BstNo* Inserir(BstNo* raiz, int data) {
    if (raiz == NULL) {
        raiz = CriarNovoNo(data);
    }
    else if (data <= raiz->data) {
        raiz->esquerda = Inserir(raiz->esquerda, data);
    }
    else {
        raiz->direita = Inserir(raiz->direita, data);
    }
    return raiz;
}

bool Buscar(BstNo* raiz, int data) {
    if (raiz == NULL) return false;
    else if (raiz->data == data) return true;
    else if (data <= raiz->data) return Buscar(raiz->esquerda, data);
    else return Buscar(raiz->direita, data);
}

int MenorValor(BstNo* raiz) {
    int menorValor = raiz->data;
    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
        menorValor = raiz->data;
    }
    return menorValor;
}

void Listar(BstNo* raiz) {
    if (raiz == NULL) return;

    Listar(raiz->esquerda);
    std::cout << std::to_string(raiz->data) + ' ';
    Listar(raiz->direita);
}

BstNo* RemoverValor(BstNo* raiz, int valor) {
    if (raiz == NULL) return raiz;

    if (valor < raiz->data) {
        raiz->esquerda = RemoverValor(raiz->esquerda, valor);
        return raiz;
    }
    if (valor > raiz->data) {
        raiz->direita = RemoverValor(raiz->direita, valor);
        return raiz;
    }
    
    if (raiz->esquerda == NULL) return raiz->direita;
    if (raiz->direita == NULL) return raiz->esquerda;

    raiz->data = MenorValor(raiz->direita);
    raiz->direita = RemoverValor(raiz->direita, raiz->data);

    return raiz;
}

int main() {
    BstNo* raiz = NULL;
    
    int opcao;
    std::string menu[6] = {
        "Listar árvore",
        "Inserir valor",
        "Remover valor",
        "Buscar valor",
        "Preencher árvore com valores predefinidos (poupa tempo)",
        "Sair"
    };
    int tamanhoMenu = sizeof(menu) / sizeof(menu[0]);
    while (true) {
        
        // Listar menu
        for (int i = 0; i < tamanhoMenu; ++i) {
            std::cout << std::to_string(i + 1) + ". " + menu[i] << std::endl;
        }
        std::cout << "Insira sua opção: " << std::flush;
        std::cin >> opcao;
        int valor;

        // Executar opção escolhida
        switch (opcao) {
            case 1: // Listar
                if (raiz == NULL) {
                    std::cout << "Não há uma árvore para ser listada." << std::flush;
                }
                else {
                    std::cout << "Listando árvore binária..." << std::endl;
                    Listar(raiz);
                    std::cout << std::endl;
                }
            break;

            case 2: // Inserir
                std::cout << "Insira o valor a ser inserido: " << std::flush;
                std::cin >> valor;

                
                std::cout << "Inserindo valor..." << std::endl;
                if (!Buscar(raiz, valor)) { raiz = Inserir(raiz, valor); }
                std::cout << "Valor inserido." << std::endl;
            break;

            case 3: // Remover
                std::cout << "Insira o valor a ser removido: " << std::flush;
                std::cin >> valor;
                if (!Buscar(raiz, valor)) {
                    std::cout << "Este valor não está na árvore. Insira um valor válido." << std::endl;
                    break;
                }
                std::cout << "Removendo valor..." << std::endl;
                RemoverValor(raiz, valor);
                std::cout << "Valor removido." << std::endl;

            break;

            case 4: // Buscar
                std::cout << "Insira o valor a ser procurado: " << std::flush;
                std::cin >> valor;
                std::cout << "Buscando valor..." << std::endl;

                if (Buscar(raiz, valor)) {
                    std::cout << "O valor " + std::to_string(valor) + " foi encontrado!" << std::flush;
                }
                else {
                    std::cout << "O valor " + std::to_string(valor) + " não foi encontrado." << std::flush;
                }
            break;

            case 5: // Preencher
                std::cout << "Inserindo valores..." << std::endl;
                if (!Buscar(raiz, 10)) { raiz = Inserir(raiz, 10); }
                if (!Buscar(raiz, 15)) { raiz = Inserir(raiz, 15); }
                if (!Buscar(raiz, 8))  { raiz = Inserir(raiz, 8);  }
                if (!Buscar(raiz, 20)) { raiz = Inserir(raiz, 20); }
                if (!Buscar(raiz, 12)) { raiz = Inserir(raiz, 12); }
                if (!Buscar(raiz, 25)) { raiz = Inserir(raiz, 25); }
                std::cout << "Valores inseridos." << std::endl;
            break;

            case 6: // Sair
                return 0;
            break;

            default:
                std::cout << "Insira uma opção válida.\n" << std::endl;
                continue;
            break;
        }

        std::cout << "\n" << std::endl;
    }
}