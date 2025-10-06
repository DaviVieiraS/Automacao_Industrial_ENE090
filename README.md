# Automação Industrial — ENE090

> Repositório de materiais, projetos e apresentações para a disciplina **Automação Industrial (ENE090)**
>
> Universidade Federal de Juiz de Fora (UFJF)

---

## 📌 Sumário

* [Sobre](#sobre)
* [Objetivo do Repositório](#objetivo-do-repositório)
* [Conteúdo da Disciplina](#conteúdo-da-disciplina)

  * [Introdução à IoT e IIoT](#introdução-à-iot-e-iiot)
  * [Evolução Histórica da IoT](#evolução-histórica-da-iot)
  * [Arquitetura e Componentes IoT](#arquitetura-e-componentes-iot)
  * [Tecnologias de Comunicação](#tecnologias-de-comunicação)
  * [Protocolos e Plataformas IoT](#protocolos-e-plataformas-iot)
  * [Aplicações Práticas no cotidiano e indústria](#aplicações-práticas-no-cotidiano-e-indústria)
  * [Desafios e Segurança](#desafios-e-segurança)
  * [Tendências Futuras](#tendências-futuras)
  * [Conclusão](#conclusão)
* [Recursos Práticos](#recursos-práticos)

  * [Checklist para projeto IIoT (MVP)](#checklist-para-projeto-iiot-mvp)
  * [KPIs recomendados](#kpis-recomendados)
* [Estrutura do Repositório](#estrutura-do-repositório)
* [Equipe](#equipe)
* [Como contribuir](#como-contribuir)
* [Referências e leituras recomendadas](#referências-e-leituras-recomendadas)

---

## 🔍 Sobre

Este repositório foi criado para a disciplina **Automação Industrial (ENE090)** com o objetivo de centralizar materiais didáticos, projetos práticos e apresentações. O foco principal do primeiro seminário é **Internet das Coisas (IoT)** aplicada ao contexto industrial (IIoT).

---

## 🎯 Objetivo do Repositório

* Organizar conteúdos teóricos e práticos da disciplina.
* Servir como material de apoio para seminários, trabalhos e projetos finais.
* Armazenar templates, checklists e exemplos de código/arquitetura para projetos IIoT.

---

# Conteúdo da Disciplina

## Introdução à IoT e IIoT

### O que é IoT

* Rede de objetos físicos (sensores, atuadores, dispositivos embarcados) conectados à internet.
* Permite coleta, transmissão, processamento e atuação sobre dados do mundo físico.
* Características: conectividade, sensoriamento, processamento local (edge), e integração com serviços em nuvem.

### O que é IIoT

* Aplicação da IoT em ambientes industriais: fábricas, usinas, logística, transportes.
* Integração com sistemas industriais (PLCs/CLPs, SCADA, MES, ERP).
* Requisitos típicos: alta disponibilidade, baixa latência, segurança reforçada, gestão de ciclo de vida.

### Valor e benefícios

* Monitoramento em tempo real, aumento da eficiência operacional.
* Manutenção preditiva e redução de paradas não planejadas.
* Otimização energética e rastreabilidade da produção.
* Novos modelos de negócio baseados em dados (SaaS de manutenção, analytics).

### Stakeholders comuns

* Engenharia de produção, engenharia elétrica/controle, equipes de manutenção, TI/OT, gerência, fornecedores, reguladores.

---

## Evolução Histórica da IoT

### Pré-IoT (antes de 2000)

* **RFID (1983+)** — identificação por radiofrequência, rastreamento de objetos.
* **SCADA** — sistemas de supervisão e aquisição de dados conectando sensores e atuadores.
* Primeiros experimentos com redes de sensores sem fio (WSN) em universidades e defesa.

### 2000–2010 (fundação)

* Adoção de redes sem fio e protocolos leves. Crescimento da pesquisa em WSN.
* Padrões como Zigbee surgem para automação de baixo consumo.
* Termo "Internet of Things" começa a ganhar popularidade.

### 2010–2020 (massificação)

* MQTT popularizado como protocolo leve de telemetria.
* LoRa/LoRaWAN e LPWANs mais amplamente adotados.
* NB‑IoT e LTE‑M como opções celulares para IoT.
* Surgimento de plataformas cloud (AWS IoT, Azure IoT, Google IoT).

### 2020–presente (integração com IA e 5G)

* Edge AI / TinyML: inferência local em MCUs.
* 5G começa a habilitar mMTC e URLLC para IIoT.
* Padrões de interoperabilidade (Thread, Matter) para smart home.
* Adoção de digital twins, blockchain e analytics em escala.

---

## Arquitetura e Componentes IoT

### Visão em camadas

1. **Camada de percepção (física):** sensores e atuadores, dispositivos embarcados (MCUs, SoCs).
2. **Camada de conexão:** tecnologias de enlace (Wi‑Fi, LoRa, NB‑IoT, Ethernet, 5G) e gateways.
3. **Camada de Edge/Fog:** processamento próximo à fonte (filtragem, compressão, inferência).
4. **Camada de nuvem/plataforma:** ingestão, armazenamento, processamento de larga escala, ML training.
5. **Camada de aplicação:** dashboards, APIs, integração com sistemas corporativos (MES, ERP).

### Componentes detalhados

* **Sensores**: tipos (temperatura, vibração, pressão, corrente, nível), precisão, consumo, calibração.
* **Atuadores**: válvulas, relés, inversores, contatores.
* **MCUs / SoCs**: ESP32, STM32, nRF52, RP Pico e variantes industriais com segurança integrada.
* **Gateways**: tradução e agregação de protocolos (ex.: Modbus → MQTT), segurança e cache.
* **Plataformas IoT**: device registry, rules engines, storage, dashboards, device management (OTA).
* **Middleware**: message brokers (MQTT, Kafka), stream processors.

### Fluxo de dados (exemplo)

1. Sensor captura sinal físico.
2. MCU faz ADC / pré-processamento (filtragem, agregação).
3. Envio para gateway via rádio/cabo.
4. Gateway valida, assina e encaminha para plataforma (MQTT/TLS).
5. Nuvem processa, armazena e executa modelos analíticos.
6. Ações: alertas, ordens de manutenção, ajustes na planta.

### Requisitos não‑funcionais

* Latência, through­put, disponibilidade (SLA), escalabilidade, tolerância a falhas, segurança ponta‑a‑ponta, consumo energético, custo por dispositivo.

---

## Tecnologias de Comunicação

### Critérios de seleção

* Alcance, consumo energético, latência, throughput, topologia, custo e ambiente (industrial vs. consumer).

### LPWAN (baixo consumo, longo alcance)

* **LoRa / LoRaWAN**: longa distância, baixo consumo, taxas baixas de dados; ideal para sensoriamento remoto.
* **NB‑IoT / LTE‑M**: soluções de operadora para cobertura ampla, boa penetração indoor; LTE‑M suporta mobilidade.

### Redes locais e de curta distância

* **BLE (Bluetooth Low Energy)**: beacons, wearables e conectividade com smartphones.
* **Zigbee / Thread / 6LoWPAN**: mesh para automação residencial/comercial.
* **Wi‑Fi (incl. Wi‑Fi 6/6E)**: alta taxa de dados; planejamento de espectro necessário em ambientes industriais.

### Redes industriais e fieldbus

* **Ethernet Industrial** (Profinet, EtherCAT): determinismo e baixa latência.
* **Fieldbus legados**: Modbus RTU/TCP, Profibus, CANopen.

### 5G e beyond

* Slicing, URLLC, mMTC: habilitam aplicações críticas com baixa latência e alta densidade de dispositivos.

### Topologias de rede

* Star, mesh, multi‑hop e híbridas; planejamento de RF, antenas, blindagem em plantas industriais.

---

## Protocolos e Plataformas IoT

### Protocolos de mensageria e transporte

* **MQTT**: pub/sub, QoS (0,1,2), leve e escalável para telemetria.
* **CoAP**: RESTful sobre UDP para dispositivos constrained.
* **AMQP**: mensageria avançada para integridade e roteamento empresarial.
* **HTTP/HTTPS**: simples, mas com overhead maior.

### Protocolos industriais e interoperabilidade

* **OPC UA**: modelagem de informação e segurança para interoperabilidade industrial.
* **Modbus**: muito usado em automação legada (RTU/TCP).

### Segurança de transporte

* **TLS / DTLS**, certificados X.509, autenticação mTLS.
* OAuth2 / JWT para APIs e autorização.

### Plataformas e ecossistema

* **Cloud**: AWS IoT Core, Azure IoT Hub, Google Cloud IoT Platform — device registry, ingestion, rules e ML.
* **Open source / self‑hosted**: ThingsBoard, Node‑RED, EMQX, Mosquitto, Eclipse Hono, The Things Stack.

### Device management

* Provisionamento seguro, inventário, OTA (firmware assinado), monitoramento de integridade.

### Data pipeline

* Brokers (MQTT) → stream processors (Kafka) → time-series DBs (InfluxDB, Timescale) → dashboards (Grafana) → ML pipelines.

---

## Aplicações Práticas no cotidiano e indústria

### Cotidiano (consumer)

* Smart home: iluminação, termostatos, assistentes, segurança.
* Wearables: monitoramento de saúde, fitness e segurança pessoal.
* Mobilidade: telemetria veicular, rastreamento e logística urbana.

### Indústria (IIoT)

* **Manutenção preditiva**: sensores de vibração, corrente e temperatura; análise espectral e modelos preditivos.
* **OEE (Overall Equipment Effectiveness)**: coleta automática de paradas, eficiência e qualidade.
* **Controle distribuído**: integração de sensores inteligentes e atuadores para automação remota.
* **Rastreabilidade e cadeia fria**: sensores ambientais em transporte e armazenamento.
* **Inspeção por visão computacional**: detecção automatizada de defeitos com ML.
* **Energia**: smart meters, monitoramento por máquina e gestão demand response.
* **Segurança ocupacional**: wearables para exposição, geofencing e alertas.

### Casos práticos / mini‑cenários

* *Fábrica*: sensores de vibração + gateway local executando FFT → envio de features por MQTT → modelo preditivo na nuvem que aciona ordem de manutenção 7 dias antes da falha prevista.
* *Logística fria*: sensores de temperatura com LoRaWAN → gateway publica eventos para dashboard e historiza em InfluxDB → alertas via webhook para times de operações.

---

## Desafios e Segurança

### Desafios técnicos

* Heterogeneidade de dispositivos e padrões.
* Escalabilidade para milhões de endpoints.
* Latência e determinismo para aplicações críticas.
* Consumo energético e manutenção de dispositivos remotos.

### Segurança — camadas e práticas

* **Dispositivo**: secure boot, armazenamento seguro de chaves (Secure Element / TPM), assinaturas de firmware.
* **Rede**: segmentação OT/IT, VPNs, firewall industrial, IDS/IPS.
* **Transporte**: TLS/DTLS, mTLS, certificados X.509.
* **Plataforma**: controle de acesso, logs auditáveis, monitoramento contínuo.
* **Supply chain**: verificação de componentes e proveniência do firmware.

### Privacidade e conformidade

* LGPD (Brasil) e GDPR (UE): cuidado com dados pessoais (wearables, localização).
* Minimização de dados, anonimização, políticas de retenção e consentimento.

### Boas práticas

* Inventariar dispositivos e firmwares.
* Gerenciar ciclo de vida: provisionamento → operação → OTA → descomissionamento.
* Testes de penetração e avaliações de vulnerabilidade periódicas.
* Planos de resposta a incidentes.

---

## Tendências Futuras

* **5G / 6G**: latências cada vez menores, suporte massivo de dispositivos e novas faixas de espectro (THz para 6G).
* **AIoT / TinyML**: inferência embarcada para decisões locais e redução de tráfego.
* **Digital Twins**: réplicas digitais de ativos e linhas para simulação e otimização.
* **Blockchain**: rastreabilidade e contratos inteligentes em supply chains.
* **Segurança pós‑quântica**: pesquisa para proteger comunicações IoT futuras.
* **Sustentabilidade e ESG**: IoT para auditoria ambiental e otimização energética.
* **Redes auto‑organizáveis**: capacidades de autoconfiguração e recuperação com IA distribuída.

---

## Conclusão

* IoT e IIoT são pilares centrais da Indústria 4.0 e representam uma transformação na forma como equipamentos, processos e pessoas interagem.
* O maior valor está na **integração** entre sensores, processamento e ações (fechamento de ciclo) e na capacidade de transformar dados em decisões confiáveis.
* Principais desafios: segurança, interoperabilidade e gestão de escala — todos superáveis com boas práticas de engenharia e governança.

---

## Recursos práticos

### Checklist para projeto IIoT (MVP)

1. Definir caso de uso e KPI (ex.: reduzir downtime em X%).
2. Selecionar sensores e hardware mínimo viável (MVP).
3. Escolher tecnologia de conectividade (LoRa/NB‑IoT/Wi‑Fi/5G).
4. Definir protocolo (MQTT/OPC UA/CoAP).
5. Implementar gateway com segurança e capacidade de edge.
6. Configurar ingestão em plataforma (cloud/self‑host) e dashboard mínimo.
7. Realizar piloto (2–4 semanas) e coletar métricas.
8. Ajustar, documentar e escalar gradualmente.
9. Estabelecer plano de manutenção e segurança (OTA assinada, monitoramento).

### KPIs recomendados

* Uptime do dispositivo (%);
* Latência média (ms);
* Taxa de perda de pacotes (%);
* MTBF / MTTR (tempo médio entre falhas / tempo médio de reparo);
* Economia gerada (R$);
* Acurácia/Recall de modelos preditivos;
* Número de eventos críticos detectados vs. ocorrências reais.

---

## Estrutura do Repositório

```
Automa-o-Industrial---ENE090/
├── README.md
├── seminarios/
│   └── 01-IoT/
│       ├── slides/
│       ├── notas-apresentador.md
│       └── exemplos-codigo/
├── projetos/
│   └── projeto-exemplo/
│       ├── hardware/
│       └── firmware/
└── materiais/
    ├── artigos/
    └── referencias/
```

> Subpastas sugeridas em `01-IoT/`: slides (PDF/PowerPoint), notebooks de demonstração, scripts de ingestão (ex.: MQTT → InfluxDB), diagramas de rede (.drawio / .svg) e instruções para replicação de experimentos.

---

## Equipe

**Professor:**

* Leonardo Honório

**Alunos:**

* Rafael Mimura
* Ana Luisa Basílio
* Davi Vieira
* Rafael Salzer

---

## Como contribuir

1. Fork este repositório.
2. Crie uma branch com seu tópico: `feature/nome-topico`.
3. Adicione materiais na pasta apropriada e escreva um `README` extra se necessário.
4. Submeta um Pull Request descrevendo as mudanças e justificativa.

> Antes de submeter PRs relacionados a código/firmware, execute os testes locais e inclua instruções de replicação no diretório.

---

## Referências e leituras recomendadas

* Kevin Ashton, "That ‘Internet of Things’ Thing" (artigo original). 1999.
* Whitepapers: AWS IoT, Azure IoT, Google Cloud IoT.
* Padrões: 3GPP (NB‑IoT, LTE‑M), LoRa Alliance, OPC Foundation (OPC UA).
* Livros: "Designing Connected Products" — Claire Rowland et al.; "Building the Internet of Things" — Maciej Kranz.
* Ferramentas: Grafana, InfluxDB, Node‑RED, Mosquitto, EMQX, ThingsBoard.

---

> **Universidade Federal de Juiz de Fora (UFJF)**
>
> *Disciplina: Automação Industrial — ENE090*

---

Se quiser, posso:

* Gerar automaticamente uma versão em `README.md` no formato do repositório (arquivo pronto para download).
* Converter este conteúdo em slides (PowerPoint ou formato Marp/Reveal.js) com notas do apresentador.
* Criar templates de pastas e arquivos iniciais (ex.: `notas-apresentador.md`, `slides/01-introducao.pptx`, `exemplos-codigo/mqtt-example.py`).

Diga qual dessas opções prefere que eu gere agora.
