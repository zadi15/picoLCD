`LCDinit()` - initializes the Display
`LCDclear()` - clears all lines on LCD
`LCDgoto(char hexString[])` - goes to the character at the hexadecimal DDRAM address specified (no 0x)
`LCDwriteMessage(char message[])` - writes the message to the LCD screen, takes a string max. 80 characters. Also tries to wrap the message automatically to the next line by detecting the screen size.
`LCDwriteRawMessage(char message[])` - writes the message to the display, but with no text wrapping/display detection.
`LCDsendRawInstruction(int RS_PIN, int RW_PIN, char binary[])` - sends binary data directly to the screen. Takes the state of the Instruction/Data pin, Read/Write pin and the binary itself.
`LCDwriteAscii(int characterCodeInDecimal)` - Writes 1 character based off the character code.
