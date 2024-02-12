# The colemak-dh inspired keymap for Lily58 Split Keyboard

 ## compile the keymap
 
    qmk compile -kb lily58 -km schaeggi
 
 ## flash the firmware directly on the keyboard
 
    qmk flash -kb lily58 -km schaeggi -bl avrdude-split-left
    qmk flash -kb lily58 -km schaeggi -bl avrdude-split-right
    
Elite-C Bootloader:

    qmk flash -kb lily58 -km schaeggi -bl dfu-split-left
    qmk flash -kb lily58 -km schaeggi -bl dfu-split-right
    
    make lily58:schaeggi:flash

Helios RP2040 Controller:

    qmk flash -kb lily58 -km schaeggi -e CONVERT_TO=helios

Adafruit Kee Boar Controller:

    qmk flash -kb lily58 -km schaeggi -e CONVERT_TO=kb2040

# Things to test
- [ ] combo(s + t) -> backspace
- [ ] combo(t + r) -> strg + backspace
- [ ] combo(n + e) -> previous word
- [ ] combo(n + i) -> next word