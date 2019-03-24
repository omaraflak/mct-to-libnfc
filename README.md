# Dump converter - Mifare Classic Tool <-> LibNfc

This is a simple C++ script to convert dump files from Mifare Classic Tool Android app to LibNfc binary formats. Conversion can be done in both sided.

# Compile

```
g++ converter.cpp -o converter
```

# How To Use

### Mifare Classic Tool -> LibNfc

```
converter -bin -f mct_dump -o libnfc_dump
```

### LibNfc -> Mifare Classic Tool

```
converter -mct -f libnfc_dump -o mct_dump
```