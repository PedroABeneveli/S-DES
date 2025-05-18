#include "globals.h"
#include "sdes.h"
#include "modes.h"
#include "utils.h"

int main() {

    int main_op;
    do {
        cout << "\n------------------------------------------------------------------------------------------------\n";
        cout << "\nDigite:\n";
        cout << "1 para realizar apenas a geracao de chaves subjacentes;\n";
        cout << "2 para realizar uma encriptacao ou decriptacao com o S-DES;\n";
        cout << "3 para realizar uma encriptacao ou decriptacao com o modo de operacao ECB;\n";
        cout << "4 para realizar uma encriptacao ou decriptacao com o modo de operacao CBC;\n";
        cout << "0 para terminar a execucao do programa.\n";

        int sub_op;
        string temp;
        bitset<10> key;
        cin >> main_op;

        if (main_op == 0) break;

        cout << "\nDigite a chave (10 bits):\n";
        cin >> temp;
        getchar();      // retira o ultimo \n do terminal que nao foi lido com o cin

        if ((int) temp.size() != 10) {
            cout << "\nChave com tamanho diferente de 10. Coloque todos os bits da chave juntos para que o programa leia a chave corretamente.\n";
            continue;
        }
        
        key = key_to_bits(temp);

        if (main_op == 1) {
            cout << "\nTodas chaves geradas:\n\n";
            subkey_generation(key, true);
        } else if (main_op == 2) {
            cout << "\nDigite 1 para realizar uma encriptacao, e 2 para realizar uma decriptacao.\n";
            cin >> sub_op;
            getchar();

            bitset<8> message;
            if (sub_op == 1) {
                cout << "\nDigite o texto em claro (8 bits):\n";
                cin >> temp;
                getchar();

                if ((int) temp.size() != 8) {
                    cout << "\nTexto com tamanho diferente de 8. Coloque todos os bits do texto em claro juntos para que o programa leia o texto em claro corretamente.\n";
                    continue;
                }

                message = text_to_bits(temp);
                message = sdes_encrypt(message, key, true);
                cout << "Texto cifrado:\n    " << show_data(message) << '\n';
            } else if (sub_op == 2) {
                cout << "\nDigite o texto cifrado (8 bits):\n";
                cin >> temp;
                getchar();

                if ((int) temp.size() != 8) {
                    cout << "\nTexto com tamanho diferente de 8. Coloque todos os bits do texto cifrado juntos para que o programa leia o texto cifrado corretamente.\n";
                    continue;
                }

                message = text_to_bits(temp);
                message = sdes_decrypt(message, key, true);
                cout << "Texto em claro:\n    " << show_data(message) << '\n';
            } else {
                cout << "\nOperacao invalida\n";
            }
        } else if (main_op == 3) {
            cout << "\nDigite 1 para realizar uma encriptacao, e 2 para realizar uma decriptacao.\n";
            cin >> sub_op;
            getchar();

            string message;
            if (sub_op == 1) {
                cout << "\nDigite o texto em claro (numero de bits multiplo de 8):\n";
                getline(cin, temp);

                // removendo espacos em branco
                for (int i = 0 ; i < (int) temp.size() ; i++) {
                    if (temp[i] == '0' || temp[i] == '1')
                        message.push_back(temp[i]);
                }

                if (((int) message.size()) % 8 != 0) {
                    cout << "\nTexto em claro com tamanho nao multiplo de 8. Para o correto funcionamento dos modos de operacao, o texto em claro deve ter uma quantidade de bits multipla de 8.\n";
                    continue;
                }

                message = eletronic_codebook_encrypt(message, key);
                cout << "\nTexto cifrado:\n    ";
                for (int i = 0 ; i < (int) message.size() ; i += 8) {
                    temp = message.substr(i, 8);
                    cout << temp << ' ';
                }
                cout << '\n';
            } else if (sub_op == 2) {
                cout << "\nDigite o texto cifrado (numero de bits multiplo de 8):\n";
                getline(cin, temp);

                // removendo espacos em branco
                for (int i = 0 ; i < (int) temp.size() ; i++) {
                    if (temp[i] == '0' || temp[i] == '1')
                        message.push_back(temp[i]);
                }

                if (((int) message.size()) % 8 != 0) {
                    cout << "\nTexto cifrado com tamanho nao multiplo de 8. Para o correto funcionamento dos modos de operacao, o texto cifrado deve ter uma quantidade de bits multipla de 8.\n";
                    continue;
                }

                message = eletronic_codebook_decrypt(message, key);
                cout << "\nTexto em claro:\n    ";
                for (int i = 0 ; i < (int) message.size() ; i += 8) {
                    temp = message.substr(i, 8);
                    cout << temp << ' ';
                }
                cout << '\n';
            } else {
                cout << "\nOperacao invalida\n";
            }
        } else if (main_op == 4) {
            bitset<8> iv;
            string message;

            cout << "\nDigite o vetor de inicializacao (8 bits):\n";
            cin >> temp;
            iv = text_to_bits(temp);
            getchar();

            if ((int) temp.size() != 8) {
                cout << "\nVetor de inicializacao com tamanho diferente de 8. Coloque todos os bits do vetor de inicializacao juntos para que o programa leia o vetor de inicializacao corretamente.\n";
                continue;
            }

            cout << "\nDigite 1 para realizar uma encriptacao, e 2 para realizar uma decriptacao.\n";
            cin >> sub_op;
            getchar();      // retira o ultimo \n do terminal que nao foi lido com o cin

            if (sub_op == 1) {
                cout << "\nDigite o texto em claro (tamanho multiplo de 8):\n";
                getline(cin, temp);

                // removendo espacos em branco
                for (int i = 0 ; i < (int) temp.size() ; i++) {
                    if (temp[i] == '0' || temp[i] == '1')
                        message.push_back(temp[i]);
                }

                if (((int) message.size()) % 8 != 0) {
                    cout << "\nTexto em claro com tamanho nao multiplo de 8. Para o correto funcionamento dos modos de operacao, o texto em claro deve ter uma quantidade de bits multipla de 8.\n";
                    continue;
                }

                message = cipher_block_chaining_encrypt(message, key, iv);
                cout << "\nTexto cifrado:\n    ";
                for (int i = 0 ; i < (int) message.size() ; i += 8) {
                    temp = message.substr(i, 8);
                    cout << temp << ' ';
                }
                cout << '\n';
            } else if (sub_op == 2) {
                cout << "\nDigite o texto cifrado (numero de bits multiplo de 8):\n";
                getline(cin, temp);

                // removendo espacos em branco
                for (int i = 0 ; i < (int) temp.size() ; i++) {
                    if (temp[i] == '0' || temp[i] == '1')
                        message.push_back(temp[i]);
                }

                if (((int) message.size()) % 8 != 0) {
                    cout << "\nTexto cifrado com tamanho nao multiplo de 8. Para o correto funcionamento dos modos de operacao, o texto cifrado deve ter uma quantidade de bits multipla de 8.\n";
                    continue;
                }

                message = cipher_block_chaining_decrypt(message, key, iv);
                cout << "\nTexto em claro:\n    ";
                for (int i = 0 ; i < (int) message.size() ; i += 8) {
                    temp = message.substr(i, 8);
                    cout << temp << ' ';
                }
                cout << '\n';
            } else {
                cout << "\nOperacao invalida\n";
            }
        } else if (main_op != 0) {
            cout << "\nOperacao invalida\n";
        }

        cout << "\nAperte Enter para continuar.";
        getline(cin, temp);    
    } while (main_op != 0);
}