# S-DES

Implementação do S-DES, uma versão simplificada do algoritmo DES usada para fins educacionais. Além disso, foram implementados também os modos de operação _Eletronic Codebook_ (ECB) e _Cipher Block Chaining_ (CBC), utilizando o próprio S-DES como algoritmo de criptografia para os blocos da mensagem.

## Aluno
- Pedro Avila Beneveli

## Compilação 

Para compilar, basta executar a linha de comando abaixo no terminal no diretório root do projeto:

```
make
```

Isso irá gerar o arquivo executável _sdes_, que executa uma interface no terminal para criptografar e descriptografar mensagens com o S-DES ou os Modos de Operação ECB e CBC.

## Como utilizar

É necessário apenas digitar no terminal, após realizar a compilação:

```
./sdes
```

Com isso, instruções com as operações possíveis e os dados necessários para realizá-las serão mostradas no terminal.