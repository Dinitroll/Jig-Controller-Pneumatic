# Pneumatic-JIG-controller
Arduino project of Ceragon networks. Based of Arduino Mega2650
This is original project for pneumatic jig station of Ceragon networks. So how it work...
We have 16 relays and 16 sensors for this relays. Sensors are works for "0". Sent command to COM for on or off relays. If you dont have "0" signal of sensor of relay yoy have wrong message and stop work.
Commands:"ABCDEFGHIJKLMN" for relays ON and "abcdefghijklmn" for relay OFF.
