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


# Features

## Combos

[s] + [t] ... left (KC_LEFT)
[r] + [t] ... left word
[r] + [s] ... backspace
[w] + [f] ... backspace word
[n] + [e] ... right (KC_RIGHT)
[n] + [i] ... left word
[e] + [i] ... delete
[u] + [z] ... delete word

[t] + [g] ... (
[m] + [n] ... )

## Tap dance

[L2]*5              ... Move to Layer 2
[L1] + [o]*2        ... Ö
[L1] + [a]*2        ... Ä
[L1] + [u]*2        ... Ü
[L2] + [Lshift]*2   ...Caps Lock
[L2] + [Esc]*2      ... Kill (Alt+F4)
[L1] + [J]*2        ... ]
[L1] + [B]*2        ... }



