# Automação Industrial - ENE090

Este repositório foi criado para a disciplina de **Automação Industrial (ENE090)**, com o objetivo de organizar materiais, projetos e apresentações desenvolvidos ao longo do curso.

## 📚 Sobre a Disciplina

A disciplina de Automação Industrial aborda conceitos fundamentais e aplicações práticas relacionadas à automação de processos industriais, incluindo:

- Sistemas de controle e supervisão
- Controladores Lógicos Programáveis (CLPs)
- Redes industriais e protocolos de comunicação
- Sensores e atuadores
- Interface Homem-Máquina (IHM)
- Internet das Coisas (IoT) aplicada à indústria

## 🎯 Seminários

### 1º Seminário: Internet das Coisas (IoT)

O primeiro seminário da disciplina aborda o tema **Internet das Coisas (IoT)** e suas aplicações no contexto da automação industrial.

#### Tópicos a serem apresentados:

- **Conceitos fundamentais de IoT**: Definição, arquitetura e componentes principais
- **IoT Industrial (IIoT)**: Diferenças entre IoT convencional e Industrial
- **Aplicações na Indústria 4.0**: Monitoramento remoto, manutenção preditiva, otimização de processos

#### Tecnologias IoT (Ordem Cronológica):

##### Anos 1980–1990: Pré-IoT (conectividade inicial)

- **RFID (Radio Frequency Identification)** – início dos experimentos comerciais para rastreamento de objetos (1983+)
  - Identificação por radiofrequência
  - Tags passivas e ativas
  - Precursor das tecnologias IoT modernas
  
- **SCADA e Automação Industrial** – sistemas de supervisão e aquisição de dados já conectando sensores e atuadores em redes locais
  - Monitoramento remoto de processos
  - Controle distribuído
  
- **Primeiros sensores sem fio** – infraestrutura experimental em universidades e exércitos

##### Anos 2000: Fundação da IoT

- **Redes sem fio de sensores (WSN)** – expansão acadêmica e militar
  - Monitoramento ambiental
  - Aplicações em defesa
  
- **Bluetooth Clássico (1999/2000)** – conectividade curta entre dispositivos
  - Alcance de até 10 metros
  - Pareamento ponto-a-ponto
  
- **NFC (Near Field Communication, 2002-2004)** – comunicação de campo próximo para IoT e pagamentos
  - Alcance ultra-curto (até 10 cm)
  - Comunicação por indução magnética
  - Aplicações em pagamentos mobile, controle de acesso e identificação
  - Baseado em RFID de alta frequência (13.56 MHz)
  
- **Zigbee (2003/2004)** – rede mesh de baixo consumo para automação e indústrias
  - Protocolo IEEE 802.15.4
  - Redes mesh auto-organizáveis
  - Alcance médio (10-100 metros)
  
- **6LoWPAN (2004)** – adaptação do protocolo IPv6 para redes de baixa potência
  - Conectividade IP para dispositivos embarcados
  - Base para Thread e outras tecnologias
  
- **Primeiros usos comerciais do termo "Internet das Coisas"** (Kevin Ashton, 1999 → popularização 2008+)

##### Anos 2010: Expansão e padronização

- **Bluetooth Low Energy (BLE, 2010)** – comunicação de baixo consumo em dispositivos móveis e vestíveis
  - Evolução do Bluetooth clássico
  - Consumo ultra-baixo de energia
  - Ideal para beacons e wearables
  
- **LoRa e LoRaWAN (2012–2015)** – redes LPWAN para IoT em áreas urbanas e rurais
  - Comunicação de longo alcance (até 15 km)
  - Baixíssimo consumo de energia
  - Ideal para sensores remotos
  
- **NB-IoT (2016)** – padrão 3GPP para IoT em redes celulares
  - Cobertura ampla e penetração em ambientes internos
  - Baixo custo e consumo de energia
  - Integração com redes LTE existentes
  
- **LTE-M (2016)** – outra solução 3GPP para IoT móvel e aplicações industriais
  - Mobilidade e roaming
  - Latência reduzida
  - Suporte a voz
  
- **MQTT (Message Queuing Telemetry Transport)** – popularização como protocolo de mensagens leve para IoT
  - Arquitetura publish-subscribe
  - Otimizado para conexões instáveis
  - Amplamente usado em IIoT
  
- **CoAP (Constrained Application Protocol)** – protocolo otimizado para dispositivos de baixo recurso
  - Similar ao HTTP, mas otimizado para IoT
  - Suporte a multicast
  - Integração com arquitetura REST
  
- **Smart Home (Google Nest, Amazon Alexa, Apple HomeKit, 2014–2016)** – consolidação de IoT no consumo doméstico
  - Assistentes virtuais
  - Automação residencial
  - Ecossistemas integrados

##### Anos 2020: Consolidação e integração com IA

- **5G (a partir de 2020)** – habilitando IoT massivo (mMTC) e comunicações críticas (URLLC)
  - Ultra-baixa latência (< 1ms)
  - Suporte a milhões de dispositivos por km²
  - Habilitador da Indústria 4.0
  
- **Thread (2020+)** – protocolo mesh IPv6 de baixo consumo, usado em automação residencial
  - Baseado em 6LoWPAN
  - Auto-configuração e auto-recuperação
  - Segurança nativa
  
- **Matter (2022)** – padrão unificado para casas inteligentes (Google, Apple, Amazon, Zigbee Alliance)
  - Interoperabilidade entre diferentes fabricantes
  - Baseado em Thread/Wi-Fi
  - Segurança integrada
  
- **Edge AI / TinyML** – aprendizado de máquina embarcado em microcontroladores para IoT inteligente
  - Processamento local de dados
  - Redução de latência
  - Privacidade preservada
  
- **Integração com Blockchain** – para rastreabilidade, segurança e contratos inteligentes em IoT
  - Registro imutável de dados
  - Descentralização
  - Smart contracts
  
- **IoT Industrial 4.0** – sensores inteligentes, gêmeos digitais e manutenção preditiva em larga escala
  - Digital twins
  - Análise preditiva
  - Otimização de processos

##### Futuro (2025+)

- **6G** – foco em ultra-confiabilidade, latência sub-ms e IoT massivo
  - Comunicação terahertz
  - Integração com IA nativa
  
- **Computação quântica aplicada ao IoT** (ainda em pesquisa)
  - Criptografia quântica
  - Otimização complexa
  
- **Redes auto-organizáveis de IoT com IA distribuída**
  - Autonomia completa
  - Aprendizado federado

#### Plataformas e Infraestrutura:

- **Cloud Computing**: AWS IoT, Azure IoT Hub, Google Cloud IoT
- **Edge Computing**: Processamento local e redução de latência
- **Gateways IoT**: Ponte entre dispositivos e nuvem
- **SCADA e HMI**: Integração com sistemas de supervisão

#### Desafios e Segurança:

- Proteção de dados e privacidade
- Segurança cibernética em ambientes industriais
- Autenticação e criptografia
- Gerenciamento de dispositivos em escala
- Padronização e interoperabilidade

#### Casos de Uso Práticos:

- Monitoramento de linhas de produção
- Manutenção preditiva de equipamentos
- Logística e rastreamento de ativos
- Controle de qualidade automatizado
- Otimização energética industrial

## 📁 Estrutura do Repositório

```
Automa-o-Industrial---ENE090/
├── README.md
├── seminarios/
│   └── 01-IoT/
├── projetos/
└── materiais/
```

## 👥 Equipe

### Professor:
- **Manuel Honório**

### Alunos:
- **Rafael Mimura**
- **Ana Luisa Basílio**
- **Davi Vieira**
- **Rafael Salzer**

## 📧 Contato

Para dúvidas ou sugestões relacionadas ao conteúdo deste repositório, entre em contato através dos canais oficiais da disciplina.

---

**Universidade Federal de Juiz de Fora (UFJF)**  
*Automação Industrial - ENE090*
