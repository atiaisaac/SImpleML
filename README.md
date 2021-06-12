# SimpleML

This arduino library is meant to ease the deployment of 
Tensorflow lite models for microcontrollers on other 
microntroller boards using the Arduino IDE.

It exposes methods for running inference for different
quantization models such is dynamic range and full integer 
quantizations.

Forked from https://github.com/eloquentarduino/EloquentTinyML.git 
whose fantastic work made it easy to compile and test this 
library on Raspberry Pi Pico.

# Compatibility

This library has been tested on the new Raspberry pi Pico 
board using the Arduino IDE running inference on both full 
integer quantization and dynamic range quantization models.
This is because at the time of writing, this was the only
board available to me.

You can test it as is on other machine learning capable 
boards or adapt it in your way to suit whatever microntroller 
you are using that is not part of the original supported boards.

Visit ```https://www.tensorflow.org/lite/guide```
for more detail and indepth knowledge on the differnt 
quantization techniques available and how to deploy them.

# Install

To use this library, clone the repo and add it to your arduino libraries folder.

```git clone https://github.com/atiaisaac/SimpleML.git```

and run any of the examples given. This library has been made very easy that
it can accept models with variable input and output sizes. All you have to do 
is specify the sizes when instantiating the class. It returns
the predictions as an array pointer.

# Credit

A big thank you to eloquentarduino, without whom I would not be able to bring this to you.

# Note

This library was originally compiled for ESP32 by the original author,
however it works right out the box on the rapberry pi pico as well 
and no special process is needed. Hopefully it works right out the 
box for the other boards.
