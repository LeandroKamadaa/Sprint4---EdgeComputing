# Projeto de Monitoramento de Temperatura e Umidade com MQTT - ESP32

Este projeto utiliza um **ESP32** para ler os valores de temperatura e umidade de um sensor **DHT22**, além de monitorar a luminosidade com um **LDR** (Fotoresistor). Os dados são enviados para um **broker MQTT público** a cada 5 segundos, formatados em JSON. O código foi desenvolvido para facilitar a integração com sistemas IoT que requerem monitoramento remoto e automação.

## Componentes Utilizados

- **ESP32 Dev Kit** (Placa principal)
- **DHT22** (Sensor de temperatura e umidade)
- **LDR** (Fotoresistor)
- **Resistor de 10kΩ** (Para o divisor de tensão do LDR)
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
     - Uma ponta do **resistor de 10kΩ**.
     - Um fio indo para o **GPIO34**.
   - A outra ponta do **resistor de 10kΩ** vai para o **GND**.
