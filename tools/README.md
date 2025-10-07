PC Bridge Tools
================

This folder contains scripts to forward ESP32 serial JSON to your web/API.

bridge_http.py
---------------
Reads JSON snapshots printed by the firmware over Serial and forwards them to your Vercel API:

- Edit the script and set:
  - SERIAL_PORT = 'COM5' (replace with your COM port)
  - API_ENDPOINT = 'https://automacao-industrial-ene-090-xwqc.vercel.app/api/spectrum'

Install and Run (Windows)
-------------------------

    pip install pyserial requests
    python tools\bridge_http.py

Keep PlatformIO Serial Monitor closed so the COM port is free. When data arrives, you will see lines like "POST 200 bytes= ..." and the site will show Connected.


