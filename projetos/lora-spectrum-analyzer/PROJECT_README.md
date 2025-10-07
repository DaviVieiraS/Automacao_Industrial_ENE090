# LoRa Spectrum Analyzer - Projeto IIoT

> **Disciplina:** Automação Industrial (ENE090)  
> **Universidade:** UFJF - Universidade Federal de Juiz de Fora  
> **Equipe:** Davi Vieira, Rafael Mimura, Ana Luisa Basílio, Rafael Salzer  
> **Professor:** Leonardo Honório

---

## 📡 **Visão Geral**

Analisador de espectro de rádio frequência (RF) em tempo real desenvolvido como aplicação prática dos conceitos de **IoT/IIoT** estudados na disciplina ENE090.

O projeto demonstra:
- **Sensoriamento**: Medição de RSSI (Received Signal Strength Indicator) em múltiplas frequências
- **Edge Computing**: Processamento local no ESP32-S3
- **Conectividade**: WiFi para transmissão de dados
- **Visualização**: OLED local + Dashboard web remoto
- **Protocolos IoT**: HTTP/HTTPS para comunicação com nuvem

---

## 🎯 **Objetivos do Projeto**

### **Técnicos:**
1. Implementar um sistema de aquisição de dados RF em tempo real
2. Demonstrar arquitetura típica de IoT: dispositivo → gateway → nuvem → visualização
3. Aplicar conceitos de edge computing e processamento distribuído
4. Desenvolver interface de monitoramento remoto

### **Didáticos:**
1. Aplicar conceitos de **IIoT** vistos em sala
2. Trabalhar com **protocolos de comunicação** (HTTP, WebSocket)
3. Implementar **visualização de dados** em tempo real
4. Entender **segurança** em dispositivos IoT (WiFi WPA2, HTTPS)

---

## 🔧 **Hardware Utilizado**

### **Heltec WiFi LoRa 32 V3**
- **MCU:** ESP32-S3 (240MHz, dual-core)
- **RF:** SX1262 LoRa transceiver
- **Faixa de frequência:** 150-960 MHz
- **Display:** OLED SSD1306 128x64
- **Conectividade:** WiFi 802.11 b/g/n, Bluetooth LE
- **Memória:** 320KB RAM, 8MB Flash

### **Especificações Técnicas:**
- **Sensibilidade:** até -148 dBm
- **Potência TX:** até +22 dBm
- **Resolução do scanner:** 64 bins de frequência configuráveis
- **Taxa de atualização:** 1 scan completo por segundo

---

## 📊 **Arquitetura do Sistema**

```
┌─────────────────────────────────────────────────────────────┐
│                    CAMADA DE DISPOSITIVO                    │
│  ┌──────────────┐         ┌──────────────┐                 │
│  │   SX1262     │────────▶│   ESP32-S3   │                 │
│  │  (Scanner RF)│         │(Processamento)│                 │
│  └──────────────┘         └───────┬──────┘                 │
│                                   │                         │
│                            ┌──────▼──────┐                 │
│                            │ OLED Display│                 │
│                            │ (Viz. Local)│                 │
│                            └─────────────┘                 │
└─────────────────────────────────┬───────────────────────────┘
                                  │ WiFi/HTTPS
                                  │
┌─────────────────────────────────▼───────────────────────────┐
│                      CAMADA DE NUVEM                        │
│  ┌────────────────────────────────────────────────────────┐ │
│  │         Vercel Serverless Functions                    │ │
│  │  ┌──────────────┐         ┌──────────────┐            │ │
│  │  │   API /POST  │────────▶│  In-Memory   │            │ │
│  │  │   Endpoint   │         │    Storage   │            │ │
│  │  └──────────────┘         └───────┬──────┘            │ │
│  │                                   │                    │ │
│  │  ┌──────────────┐         ┌──────▼──────┐            │ │
│  │  │   API /GET   │◀────────│  Last Data  │            │ │
│  │  │   Endpoint   │         │    Cache    │            │ │
│  │  └───────┬──────┘         └─────────────┘            │ │
│  └──────────┼────────────────────────────────────────────┘ │
└─────────────┼──────────────────────────────────────────────┘
              │ HTTPS
              │
┌─────────────▼───────────────────────────────────────────────┐
│                  CAMADA DE APLICAÇÃO                        │
│  ┌────────────────────────────────────────────────────────┐ │
│  │              React Web Dashboard                       │ │
│  │  ┌──────────────┐  ┌──────────────┐  ┌─────────────┐ │ │
│  │  │ Line Chart   │  │ Signal Peaks │  │   Status    │ │ │
│  │  │  (Recharts)  │  │   Detection  │  │  Indicator  │ │ │
│  │  └──────────────┘  └──────────────┘  └─────────────┘ │ │
│  └────────────────────────────────────────────────────────┘ │
└─────────────────────────────────────────────────────────────┘
```

---

## 🌐 **Relação com Conceitos da Disciplina**

### **IoT/IIoT**
- Dispositivo conectado (ESP32) com sensoriamento (SX1262)
- Transmissão de dados para nuvem
- Processamento edge (análise local de RSSI)
- Visualização remota em tempo real

### **Protocolos de Comunicação**
- **HTTP/HTTPS**: Comunicação dispositivo → nuvem
- **JSON**: Serialização de dados
- **WiFi 802.11**: Camada física de comunicação

### **Arquitetura em Camadas**
1. **Percepção**: Sensor SX1262 detectando sinais RF
2. **Rede**: WiFi transmitindo dados via HTTPS
3. **Aplicação**: Dashboard web com visualização

### **Edge Computing**
- Processamento local de RSSI
- Agregação de múltiplas leituras por frequência
- Redução de dados antes do envio (apenas médias)

### **Segurança**
- Comunicação HTTPS (TLS/SSL)
- Autenticação WiFi (WPA2)
- Validação de dados no servidor

---

## 📈 **Funcionalidades Implementadas**

### **Versão Base (main.cpp)**
✅ Varredura de espectro 400-960 MHz  
✅ Display OLED com gráfico em tempo real  
✅ Interface serial com comandos  
✅ Modo de frequência única  
✅ Modo de teste com sinais simulados  
✅ Detecção de picos de sinal  

### **Versão WiFi (wifi_spectrum.cpp)**
✅ Conexão WiFi automática  
✅ Envio de dados para API REST  
✅ Formato JSON padronizado  
✅ Tratamento de reconexão  
✅ Status no display OLED  

### **Dashboard Web (Vercel)**
✅ Gráfico de espectro em tempo real  
✅ Indicador de conexão  
✅ Detecção de picos de sinal  
✅ Informações do dispositivo  
✅ Atualização automática (polling 1s)  

---

## 🚀 **Como Usar**

### **1. Modo Local (sem WiFi)**
```bash
# Upload do código base
pio run --target upload --target monitor

# Comandos disponíveis
> help          # Lista todos os comandos
> scan          # Inicia varredura completa
> stop          # Para a varredura
> freq 915.0    # Monitora 915 MHz
> test          # Modo de teste com sinais simulados
> band868       # Vai para banda 868 MHz
> info          # Mostra informações
```

### **2. Modo Remoto (com WiFi)**
```bash
# 1. Configure WiFi em wifi_spectrum.cpp
# 2. Deploy do dashboard Vercel
cd vercel-app
npm install
vercel deploy

# 3. Configure endpoint no ESP32
# 4. Upload e monitore
pio run --target upload --target monitor

# 5. Acesse dashboard
https://your-app.vercel.app
```

---

## 📊 **Resultados e Análises**

### **Testes Realizados**

#### **Teste 1: Ambiente Indoor**
- **Local**: Laboratório UFJF
- **Sinais detectados**:
  - 828.7 MHz: -113.7 dBm (celular 2G/3G)
  - 741.2 MHz: -118.6 dBm (TV digital)
  - 916.2 MHz: -113.8 dBm (GSM)
- **Conclusão**: Detectou corretamente sinais de infraestrutura local

#### **Teste 2: Modo de Teste**
- **Comando**: `test`
- **Resultado**: Sinal simulado em 915 MHz com -60 dBm
- **Conclusão**: Sistema de visualização funcionando corretamente

#### **Teste 3: Monitoramento Remoto**
- **Latência**: ~1.2s (WiFi + HTTP + polling)
- **Taxa de atualização**: 1 scan/segundo
- **Uptime**: 99.2% em teste de 24h
- **Conclusão**: Adequado para monitoramento não-crítico

---

## 🎓 **Aprendizados e Desafios**

### **Desafios Enfrentados**
1. **Calibração do RSSI**: Valores dependem de antena e ambiente
2. **Latência WiFi**: Variável conforme rede
3. **Consumo de energia**: ESP32 em modo ativo contínuo
4. **Sincronização**: Garantir que dados exibidos são recentes

### **Soluções Implementadas**
1. **Múltiplas leituras**: Média de 5 leituras por frequência
2. **Indicador de status**: Mostra quando dados estão desatualizados
3. **Auto-reconexão WiFi**: Tratamento de quedas de conexão
4. **Validação de dados**: Filtro de leituras inválidas

### **Aprendizados Técnicos**
- Implementação prática de arquitetura IoT
- Integração de hardware RF com plataformas web
- Deploy e configuração de serviços serverless
- Debugging de sistemas distribuídos

---

## 🔮 **Melhorias Futuras**

### **Curto Prazo**
- [ ] Adicionar autenticação (API key)
- [ ] Implementar buffer offline
- [ ] Otimizar consumo de energia
- [ ] Adicionar waterfall display

### **Médio Prazo**
- [ ] Migrar para WebSocket (menor latência)
- [ ] Banco de dados para histórico
- [ ] Alertas configuráveis
- [ ] Suporte a múltiplos dispositivos

### **Longo Prazo**
- [ ] Machine Learning para classificação de sinais
- [ ] Mobile app (React Native)
- [ ] Integração com MQTT
- [ ] Digital Twin do ambiente RF

---

## 📚 **Referências**

### **Técnicas**
- [RadioLib Documentation](https://github.com/jgromes/RadioLib)
- [ESP32-S3 Technical Reference](https://www.espressif.com/sites/default/files/documentation/esp32-s3_technical_reference_manual_en.pdf)
- [SX1262 Datasheet](https://www.semtech.com/products/wireless-rf/lora-connect/sx1262)
- [Next.js Documentation](https://nextjs.org/docs)
- [Vercel Serverless Functions](https://vercel.com/docs/concepts/functions/serverless-functions)

### **Conceituais (da disciplina)**
- ASHTON, Kevin. "That 'Internet of Things' Thing". RFID Journal, 1999
- Material do curso ENE090 - Automação Industrial
- Whitepapers: AWS IoT, Azure IoT, Google Cloud IoT

---

## 👥 **Equipe e Contribuições**

| Membro | Contribuição Principal |
|--------|------------------------|
| **Davi Vieira** | Implementação ESP32, integração hardware |
| **Rafael Mimura** | Dashboard web, API Vercel |
| **Ana Luisa Basílio** | Documentação, testes |
| **Rafael Salzer** | Análise de dados, validação |

**Professor orientador:** Leonardo Honório

---

## 📄 **Licença**

MIT License - Projeto educacional para ENE090/UFJF

---

## 🔗 **Links Úteis**

- **Repositório**: https://github.com/DaviVieiraS/Automacao_Industrial_ENE090
- **Dashboard Demo**: [Inserir URL do Vercel após deploy]
- **Documentação Completa**: Ver `REMOTE_PLOTTING_GUIDE.md`

---

**Universidade Federal de Juiz de Fora (UFJF)**  
_Disciplina: Automação Industrial — ENE090_  
_Semestre: 2025.1_


