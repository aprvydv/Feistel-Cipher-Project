# Feistel Cipher in C

This project implements a toy Feistel cipher with S-box and P-box operations, input validation, and encryption/decryption logic in C.

## Features
- 8-round Feistel network
- S-box and P-box logic inspired by lightweight block ciphers
- Input validation and error handling
- Modular code with test support

## How to Compile

```bash
make
```

## Run

```bash
./feistel
```

## Example

```
Enter a 16-bit plaintext (0 - 65535): 12345
Enter an 8-bit key (0 - 255): 42
Encrypted: 56324
Decrypted: 12345
Decryption successful. Original and decrypted data match.
```

## License

MIT License
