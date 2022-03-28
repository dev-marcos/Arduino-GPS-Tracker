# 🚘 Rastreador GPS para carro com Arduino
### Arduino + GPS + LoRa

**Terminar a descrição ainda**

## 1. Configuração de back-end

1. Se você ainda não a possui, [configure a conta da The Things Network](https://account.thethingsnetwork.org/register)
2. Crie um novo aplicativo no TTN [Applications Console](https://console.thethingsnetwork.org/applications)
3. Adicione um novo dispositivo ao seu novo aplicativo TTN e selecione **ABP Activation Method**
4. Insira **Application EUI**, **Device Address**, **Network Session Key** e **App Session Key** no arquivo `config.h` no projeto Arduino
5. No código fonte do projeto, descomente a linha configureLora() dentro da função setup(), carregue o codigo, espere o ardiono configurar o módulo Radioenge, comente a linha configureLora() e carregue o código novamente
6.TENHO QUE CONTINUAR O TUTORIAL


## 2. Fiação

Conecte os jumpers do GPS Shield com o TX no `pin3` e RX com o `pin4`.
Conecte o Shild do GPS no Arduino, o Shield do IOT Radioenge no GPS e o módulo Radioenge LoraWAn no Shield IOT.
Insira o Cartão de mória formatado em FAT ou FAT32.

## 3. Bibliotecas necessárias

- [TinyGPS++](https://github.com/mikalhart/TinyGPSPlus)
- [Time](https://github.com/PaulStoffregen/Time)


# Hardware

- **Arduino Uno**

<img src="https://uploads.filipeflop.com/2017/07/1AC01-9-1-min.jpeg" width="500" >

- **GPS Shield para Arduino**
  - Com Slot para cartão Micro SD

<img src="https://uploads.filipeflop.com/2017/07/1-157.jpg" width="500" >

- **Radioenge IOT-ARDUINO UNO**
	- O shield para Arduino Uno  permite conectar os módulos EndDevice LoRa Radioenge ao Arduino UnoTM e adicionar a comunicação sem fio de longo alcance LoRa ao seus projetos.*

<img src="https://www.radioenge.com.br/storage/2021/12/IOT_Arduino.jpg" alt="Radioenge IOT-ARDUINO UNO" width="500" >

- **Radioenge Módulo LoRaWAN**

<img src="https://www.radioenge.com.br/storage/2021/08/modulo-lorawan-radioenge.jpg " alt="Radioenge LoraWAN" width="500" >

## Referência

### Especificações do Arduino Uno
```
ATmega328P
  8-bit AVR 
  32KB ISP flash memory
  1024B EEPROM
  2KB SRAM
  1-UART, 2-SPI, 1-I2C
  Clack Max 20MHz
 
LORA
  Data Rate: 21900 bits/segundo
  Topologia de Rede: Estrela 
  Segurança: Criptografia AES (para a rede e para a aplicação)
  Protocolo de comunicação: Protocolo LoRaWAN (Opcionalmente LoRaMesh Radioenge)

  Banda de frequência: 915,2 – 927,8 MHz(upstream) e 923,3 – 927,5 MHz(downstream)
  Canais: 64+8 canais (8 downlink / 64 uplink)
  Modo de operação: Modo híbrido(Frequency Hopping e canais fixos)
  Largura dos canais: 125 kHz / 250KHz / 500KHz
  Potência de transmissão: 20 dBm 
  Sensibilidade de recepção: -137 dBm
  Nível máximo de recepção: 10 dBm
  Modulação: LoRa - Chirp Spread Spectrum (opcionalmente FSK / FHSS)
  ANATEL: - 02021-18-07215

GPS
  Módulo receptor GPS Ublox NEO-6M
  Comunicação serial (configurável por jumpers)
  Compatível com Arduino Uno e Mega
  Recepção de até 3 sistemas de satélite ao mesmo tempo: GPS, Galileo, GLONASS e BeiDou
  Conector U.FL para antena
  Nível de sinal: Compatível 3.3 e 5V
  Slot para cartão Micro SD
  Botão de reset Arduino
  Temperatura de Operação: -40 ~ +85°C
  Dimensões: 62 x 53 x 24,5m
  
```

### Mapa dos pinos Arduino UNO

![Arduino Pin map](https://components101.com/sites/default/files/component_pin/Arduino-Uno-Pin-Diagram.png)

## Melhoria adicional

Você pode contribuir para este projeto de qualquer forma. (Envie um problema, relatório de erro, bifurque e melhore ...)
Sugestões e comentários são muito apreciados.

## Créditos

- Agradecimentos a [Jim Lindblom](https://www.sparkfun.com/users/69916?_ga=2.7991733.605579908.1585914364-1666875447.1582645113) por seu [GPS Logger Shield Hookup Guide](https://learn.sparkfun.com/tutorials/gps-logger-shield-hookup-guide/example-sketch-sd-card-gps-logging), que veio como uma base e inspiração para este projeto.
