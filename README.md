# Module: Proximity
WiP module for connecting an Arduino with a proximity sensor to the MagicMirror ([https://github.com/MichMich/MagicMirror/](https://github.com/MichMich/MagicMirror/)).

## Usage
To use this module, add it to the modules array in the config/config.js file:

```
modules: [
	{
		module: 'MMM-proximity',
		position: 'top_right', // The status indicator position
	}
]
```

## Arduino and communication

The code for the Arduino is in the proximity.ino file. When a user is detected the information is sent via serial (USB connected to the MM host).

TODO: the library `serialport` which listens to the messages on serial, seems to crash the whole app, so this needs to be investigated.



## Licence

MIT
