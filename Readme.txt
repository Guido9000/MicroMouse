RUN esp ori
idf.py set-target esp32
idf.py build
idf.py -p COM9 flash monitor (Controlla la porta COM)