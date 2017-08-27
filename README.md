# BLE-Car-console
A Bluetooth low energy car console button pad (based on the Adafruit Bluefruit LE UART Friend)

This github is for the code I wrote for a project for a friend.
The project was to have an iPhone 6+ to replace the built in in-car navigation and entertainment system.
So we wanted to use one of the button panels that connected to the old system and make it have bluetooth capability, so it could connect to the iPhone. 

The hardware is as follows
* [Adafruit Bluefruit LE UART Friend](http://adafruit.com/products/2479)
* Arduino nano board
* Button panel out of a Nissan skyline V35 250GT, 350GT. The button panel is located under the factory pop-up screen. (If you google "nissan skyline 350 console" you'll find photos of it.
It has 11 buttons and a joystick (with a button). I didn't end up using the joystick as we couldn't finy any use for it.


I used the Adafruit library for the Bluetooth module [which is located here](https://github.com/adafruit/Adafruit_BluefruitLE_nRF51)
I also used a natrix keypad library made by Alexander Brevig.

As I said the button panel has 11 keys and one joystick. The keys I did are as follows.
Because the target device is apple there are a few apple specific keys I had to figure out, you could change them to suit android or some other OS as well.

Key | function | Keyboard command
--- | --- | --- |
1 | Keyboard enable | Eject key |
2 | Apple maps normal view | Command + 1 |
3 | Apple maps Satellite view | Command + 2 |
4 | Play/pause | Play/pause (media key) |
5 | Switch apps | Apple home button twice |
6 | Siri | Apple home button home for 500ms |
7 | Backlight increase | BRIGHTNESS+ (media key) |
8 | Backlight decrease | BRIGHTNESS- (media key) |
9 | Prev song | MEDIAPREVIOUS (media key) |
10 | Next song | MEDIANEXT (media key) |
11 | Apple Home button** | Home key (media key) |

** The home button can also be done via Command + H
