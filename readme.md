<h1>Fresh Track</h1>

<p>O FreshTrack é um projeto que tem como foco a redução do desperdício de alimentos por meio da utilização de uma inteligência artificial (IA) que faz o gerenciamento de estoques de alimentos. Esta IA é alimentada por dados fornecidos por empresas e organizações, possibilitando um controle mais efetivo das quantidades adquiridas e prevenindo a aquisição excessiva de alimentos que acabam sendo descartados.</p>

<p>O código apresentado nesse repositório tem como objetivo monitorar e exibir as informações sobre temperatura, umidade e luminosidade do ambiente em um display LCD utilizando arduino. ALém do monitoramento o sistema conta com um buzzer, leds e mensagens verbais mostrando avarias no ambiente em que os alimentos estão sendo armazenados</p>

<h2>Componentes necessários</h2>

<ul>
    <li>Arduino Uno</li>
    <li>Protoboard</li>
    <li>Sensor de temperatura(DHT11)</li>
    <li>Sensor de umidade(DHT11)</li>
    <li>Sensor de luminosidade(LDR)</li>
    <li>Display LCD I2C</li>
    <li>LEDS (Verde, Amarelo, Vermelho)</li>
    <li>Cabos Jumper</li>
    <li>Buzzer</li>
</ul>

<h2>Conexão dos componentes</h2>

<ul>
    <li>PROTOBOARD</li>
    <li>Ligaremos a porta GND do Arduino Uno na entrada negativa da Protoboard</li>
    <li>Ligaremos a porta 5V do Arduino Uno na entrada positiva da Protoboard</li>
</ul>

<ul>
    <li>DISPLAY I2C</li>
    <li>Ligaremos a porta GND no polo negativo da protoboard</li>
    <li>Ligaremos a porta VCC no polo positivo da protoboard</li>
    <li>Ligaremos a porta SDA na entrada analógica A4 do arduino UNO</li>
    <li>Ligaremos a porta SCL na entrada analógica A5 do arduino UNO</li>
</ul>
<ul>
    <li>BUZZER</li>
    <li>Conectaremos o Buzzer na protoboard</li>
    <li>No polo positivo do Buzzer, ligar resistor de 1KΩ</li>
    <li>Do outro lado do resistor de 1K iremos ligar no arduino Uno, na porta digital 9</li>
    <li>O polo negátivo do Buzzer ligaremos no polo negátivo da protoboard</li>
</ul>

<ul>
    <li>LEDS</li>
    <li>Conectaremos um resitor de 1KΩ nas portas anodo dos leds</li>
    <li>O lado catódica dos leds serão ligados no polo negativo da protoboard</li>
    <li>Ligaremos o outro lado dos resistores no Arduino Uno através de cabos jumper</li>
    <li>Iremos conectar os leds nas respectivas portas digitais, Verde = porta 6, Amarelo = porta 7, Vermelho = porta 8</li>
</ul>

<ul>
    <li>DHT11</li>
    <li>Conectaremos o polo "Potência" no 5V da protoboard</li>
    <li>Conectaremos o polo "GND" no polo negativo da protoboard</li>
    <li>Ligaremos o pino "Vout" na porta análogica do Arduino Uno, porta A2</li>
</ul>

<ul>
    <li>SENSOR DE FORÇA / BALANÇA</li>
    <li>Conectaremos o polo "2" no 5V da protoboard</li>
    <li>Conectaremos o polo "1" a um resistor de 1KΩ</li>
    <li>De um lado do resistor iremos ligar no polo negativo da protoboard</li>
    <li>Do lado que não ligamos no polo negativo da protoboard, iremos conectar com um jumper na porta analógica A0 do arduino Uno</li>
</ul>
