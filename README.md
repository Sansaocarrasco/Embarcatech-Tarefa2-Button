# Tarefa 2 - Button com Temporizador

## 📌 Introdução
Este projeto implementa um sistema de temporização utilizando a função `add_alarm_in_ms()` do Pico SDK para o acionamento de LEDs a partir do clique em um botão (pushbutton).

## 🛠 Componentes Utilizados
A tarefa requer os seguintes componentes conectados à placa **BitDogLab**:

| Componente                  | Conexão à GPIO |
|-----------------------------|---------------|
| 1 Botão (Pushbutton)        | GPIO 5        |
| 3 LEDs (azul, vermelho e verde) | GPIOs 11, 12, 13 |
| 3 Resistores de 330 Ω       | Em série com os LEDs |

## 💻 Simulação no Wokwi
A configuração sugerida para a simulação no Wokwi pode ser acessada no repositório abaixo:

https://wokwi.com/projects/421724053827423233

## 📌 Requisitos da Atividade

1. Quando o usuário pressiona o botão (pushbutton), os três LEDs acendem simultaneamente (nível alto). Após um atraso de 3 segundos, um LED se apaga, seguido pelos outros dois, conforme mostrado no vídeo da prática.
2. O temporizador do alarme deve ser configurado para um atraso de 3 segundos (3.000 ms) entre os estados dos LEDs.
3. A mudança de estado dos LEDs deve ser implementada em funções de callback do temporizador, como na rotina `turn_off_callback()` abordada na aula síncrona.
4. O botão só pode alterar o estado dos LEDs quando o último LED for desligado. Durante a execução das rotinas de temporização, o botão não pode iniciar uma nova chamada da função callback.
5. Utilizando a Ferramenta Educacional BitDogLab, foi realizado um experimento com o código deste exercício utilizando o LED RGB nos GPIOs 11, 12 e 13 e o Botão A no GPIO 5.

## 🔘 Instruções de Uso

1. Clone este repositório:
   ```sh
   git clone https://github.com/Sansaocarrasco/Embarcatech-Tarefa2-Button.git
   ```
2. Abra o projeto no VS Code.
3. Conecte a placa Raspberry Pi Pico W ao computador no modo BOOTSEL (pressionando o botão BOOTSEL ao conectar via USB).
4. Compile e carregue o projeto para a placa.

## 🎥 Vídeo Demonstrativo

O vídeo associado a esta prática pode ser acessado no link a seguir:

(Adicionar o video)

*Fonte: autor*

## 📜 Licença

Este projeto está licenciado sob a Licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.
