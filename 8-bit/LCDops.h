void LCDinit();
void LCDclear();
void E_INSTRUCTION();
void E_DATA();
void LCDgoto(char hexstring[]);
void LCDwriteMessage(char message[]);
void LCDwriteRawMessage(char message[]);
void LCDsendRawInstruction(int RS_PIN, int RW_PIN, char binary[]);
void LCDwriteAscii(int code);
