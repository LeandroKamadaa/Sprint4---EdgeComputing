# Projeto de Monitoramento de Temperatura e Umidade com MQTT - ESP32

Este projeto utiliza um **ESP32** para ler os valores de temperatura e umidade de um sensor **DHT22** quando a luminosidade atinge um certo valor. Os dados são enviados para um **broker MQTT público** a cada 5 segundos, formatados em JSON.

## Video

https://www.youtube.com/watch?v=z882cfO4xa4&ab_channel=Comic

## Integrantes

- Cilas Pinto Macedo - RM560745
- Ian Junji Maluvayshi Matsushita RM560588
- Pedro Arão Baquini - RM559580
- Leandro Kamada Pesce Dimov - RM560381
- Leonardo de Souza Pierangelli - RM560501

## Motivação

Este projeto no Wokwi simula o fluxo de coleta, processamento e envio de dados que será utilizado no projeto real.  
No sistema hospitalar real:

- Uma **câmera** será utilizada para capturar imagens de medicamentos.
- As imagens serão enviadas para a **nuvem**.
- Um **script Python** processará essas imagens, extraindo informações e gerando um **JSON estruturado**.
- O JSON será integrado ao **ERP** do hospital, automatizando o controle de medicamentos.

## Componentes Utilizados

- **ESP32 Dev Kit** (Placa principal)
- **DHT22** (Sensor de temperatura e umidade)
- **LDR** (Fotoresistor)
- **Broker MQTT público** (test.mosquitto.org)
- **ArduinoJson** (Para formatação de dados em JSON)

## Funcionalidades

- Conexão com a rede Wi-Fi sem senha (Rede: `Wokwi-GUEST`).
- Conexão com o broker MQTT público **test.mosquitto.org**.
- Leitura de temperatura e umidade do sensor **DHT22**.
- Leitura de luminosidade do **LDR** (Fotoresistor) no pino analógico **GPIO34**.
- Publicação dos dados em formato JSON no tópico MQTT `leonardo/1espb/dados`.
- Monitoramento contínuo com reconexão automática caso a conexão Wi-Fi ou MQTT caia.
- Atualização dos dados a cada 5 segundos.

## Montagem do Circuito

1. **DHT22**:
   - **VCC** -> **3.3V**
   - **GND** -> **GND**
   - **DATA** -> **GPIO15**

2. **LDR**:
   - Uma ponta do **LDR** vai para **3.3V**.
   - A outra ponta do **LDR** vai para um nó comum com:
     - Uma um fio indo para o **GND**.
     - Um fio indo para o **GPIO34**.

<img src="dashboard.png">

<img src="Diagrama.png">
