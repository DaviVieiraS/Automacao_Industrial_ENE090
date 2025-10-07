import json
import time
import sys

try:
    import serial  # pyserial
except Exception as e:
    print('Missing dependency: pyserial. Install with: pip install pyserial requests')
    raise

try:
    import requests
except Exception:
    print('Missing dependency: requests. Install with: pip install requests')
    raise


# ====== CONFIGURE THESE ======
# Set your Windows COM port here (e.g., 'COM5').
SERIAL_PORT = 'COM6'
BAUD = 115200

# Your deployed Vercel API endpoint for spectrum data:
API_ENDPOINT = 'https://automacao-industrial-ene-090-xwqc.vercel.app/api/spectrum'
# =============================


def main() -> int:
    print(f'Opening {SERIAL_PORT} at {BAUD} baud...')
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD, timeout=1)
    except Exception as e:
        print('Failed to open serial port:', e)
        print('Tips: Close PlatformIO Serial Monitor; verify COM port in Device Manager.')
        return 1

    print('Forwarding JSON lines to:', API_ENDPOINT)
    print('Press Ctrl+C to stop.')

    while True:
        try:
            raw = ser.readline()
            if not raw:
                continue
            line = raw.decode('utf-8', errors='ignore').strip()
            if not line or not line.startswith('{'):
                # Skip non-JSON debug lines
                continue

            try:
                payload = json.loads(line)
            except Exception:
                # Not valid JSON – skip
                continue

            try:
                r = requests.post(API_ENDPOINT, json=payload, timeout=10)
                print('POST', r.status_code, 'bytes=', len(line))
            except Exception as e:
                print('HTTP error:', e)

            time.sleep(0.02)
        except KeyboardInterrupt:
            print('\nExiting...')
            break

    return 0


if __name__ == '__main__':
    sys.exit(main())


