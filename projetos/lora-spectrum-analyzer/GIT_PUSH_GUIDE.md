# Push LoRa Spectrum Analyzer to GitHub

Guide to push this project to: https://github.com/DaviVieiraS/Automacao_Industrial_ENE090

## 📋 **Quick Steps**

### **Step 1: Initialize Git (if not already done)**
```bash
cd C:\Users\Davi\Documents\PlatformIO\Projects\LoRa_aut
git init
```

### **Step 2: Add Remote Repository**
```bash
git remote add origin https://github.com/DaviVieiraS/Automacao_Industrial_ENE090.git
```

Or if remote already exists:
```bash
git remote set-url origin https://github.com/DaviVieiraS/Automacao_Industrial_ENE090.git
```

### **Step 3: Create Project Folder Structure**
```bash
# Create a dedicated folder for this project
mkdir -p projetos/LoRa_Spectrum_Analyzer
```

### **Step 4: Add All Files**
```bash
git add .
```

### **Step 5: Commit Changes**
```bash
git commit -m "Add LoRa Spectrum Analyzer project - Real-time RF spectrum analyzer for Heltec WiFi LoRa 32 V3"
```

### **Step 6: Pull Existing Content (if repository has content)**
```bash
git pull origin main --allow-unrelated-histories
```

### **Step 7: Push to GitHub**
```bash
git push -u origin main
```

---

## 🔧 **Alternative: Add as Project Subfolder**

If you want to add this as a project within the existing structure:

```bash
# 1. Clone the existing repository
cd C:\Users\Davi\Documents\PlatformIO\Projects
git clone https://github.com/DaviVieiraS/Automacao_Industrial_ENE090.git temp_repo

# 2. Copy your LoRa project into it
mkdir temp_repo\projetos\LoRa_Spectrum_Analyzer
xcopy LoRa_aut\* temp_repo\projetos\LoRa_Spectrum_Analyzer\ /E /I

# 3. Commit and push
cd temp_repo
git add projetos/LoRa_Spectrum_Analyzer
git commit -m "Add LoRa Spectrum Analyzer project for ENE090"
git push origin main

# 4. Clean up
cd ..
rmdir /s /q temp_repo
```

---

## 📝 **Recommended Commit Message**

```
Add LoRa Spectrum Analyzer - IIoT Practical Project

- Real-time RF spectrum analyzer (400-960 MHz)
- Heltec WiFi LoRa 32 V3 (ESP32-S3 + SX1262)
- OLED display visualization
- Serial command interface
- WiFi connectivity for remote monitoring
- Vercel web dashboard for real-time plotting

Part of ENE090 - Automação Industrial course
Practical application of IoT/IIoT concepts
```

---

## 🗂️ **Suggested Repository Structure**

```
Automacao_Industrial_ENE090/
├── README.md (existing)
├── seminarios/
│   └── 01-IoT/
├── projetos/
│   └── LoRa_Spectrum_Analyzer/          # Your new project
│       ├── README.md                     # Project-specific README
│       ├── platformio.ini
│       ├── src/
│       │   ├── main.cpp
│       │   └── wifi_spectrum.cpp
│       ├── include/
│       ├── lib/
│       ├── vercel-app/                   # Web dashboard
│       │   ├── pages/
│       │   ├── package.json
│       │   └── README.md
│       ├── REMOTE_PLOTTING_GUIDE.md
│       └── GIT_PUSH_GUIDE.md
└── materiais/
```

---

## 📄 **Create Project README**

Before pushing, create a project-specific README to explain this project within the course context.


