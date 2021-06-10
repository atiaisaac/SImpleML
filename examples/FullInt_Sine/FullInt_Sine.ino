#include <SimpleML.h>
// sine_model.h contains the array you exported from the previous step with xxd
#include "my_model.h"

/* Number of inputs and outputs needed. 
* this is useful when working with 
* IMU's since they typically have 3 or more
* axis and each will be counted as an input
* the model will then output the same number
* of inputs
*/

#define NUMBER_OF_INPUTS 1
#define NUMBER_OF_OUTPUTS 1

// in future projects you may need to tweek this value: it's a trial and error process
#define TENSOR_ARENA_SIZE 2*1024

SimpleML<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> nn;

void setup() {
    Serial.begin(115200);
    nn.begin(my_model);
}

void loop() {
    // pick up a random x and predict its sine
    float x = 3.14 * random(100) / 100;
    float y = sin(x);
    float input[1] = { x };

    /*predict takes a second argument which is an int type
    * 0 if model in full integer quantized
    * 1 if model is dynamic range quantized
    */
    float *predicted = nn.predict(input,0);

    Serial.print("sin(");
    Serial.print(x);
    Serial.print(") = ");
    Serial.print(y);
    Serial.print("\t predicted: ");
    Serial.println(*predicted);   
    delay(1000);
}
