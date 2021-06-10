#pragma once

#include <Arduino.h>
#include <math.h>
#include "tensorflow/lite/version.h"
#include "tensorflow/lite/micro/kernels/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"


template<size_t inputSize, size_t outputSize, size_t tensorArenaSize>
class SimpleML {
protected:
    int8_t x_quantized[inputSize];
    int8_t y_quantized[outputSize];
    bool failed;
    uint8_t tensorArena[tensorArenaSize];
    tflite::ErrorReporter *reporter;
    tflite::MicroInterpreter *interpreter;
    TfLiteTensor *input;
    TfLiteTensor *output;
    const tflite::Model *model;
public:
    SimpleML() {
    }

    bool begin(const unsigned char *modelData) {
        static tflite::MicroErrorReporter microReporter;
        static tflite::ops::micro::AllOpsResolver resolver;

        reporter = &microReporter;
        model = tflite::GetModel(modelData);

        // assert model version and runtime version match
        if (model->version() != TFLITE_SCHEMA_VERSION) {
            failed = true;
            reporter->Report(
                    "Model provided is schema version %d not equal "
                    "to supported version %d.",
                    model->version(), TFLITE_SCHEMA_VERSION);

            return false;
        }

        static tflite::MicroInterpreter interpreter(model, resolver, tensorArena, tensorArenaSize, reporter);

        if (interpreter.AllocateTensors() != kTfLiteOk) {
            failed = true;
            return false;
        }

        input = interpreter.input(0);
        output = interpreter.output(0);
        this->interpreter = &interpreter;

        return true;
    }


    /* The predict function returns an address to the output array
    and takes into account the type of model quantization. Enter;
    0 -> full integer quantization model
    1 -> dynamic range quantization model
    */

    float * predict (float user_input[], int quant_type) {
        static float y[outputSize];
        if (quant_type == 0) {
            // TF_LITE_MICRO_EXPECT_EQ(kTfLiteUInt8, input->type);
            for (size_t i = 0; i < inputSize; i++){
                x_quantized[i] = user_input[i] / input->params.scale + input->params.zero_point;
                input->data.int8[i] = x_quantized[i];
            }

            if (interpreter->Invoke() != kTfLiteOk) {
            error = INVOKE_ERROR;
            reporter->Report("Inference failed");
            }  

            for (size_t i = 0; i < outputSize; i++) {
                // y[i] = output->data.int8[i];
                y_quantized[i] = output->data.int8[i];
                y[i] = (y_quantized[i] - output->params.zero_point) * output->params.scale;
            }

            return y;

        } else if (quant_type == 1) {
                for (size_t i = 0; i < inputSize; i++){
                input->data.f[i] = user_input[i];
                }

            if (interpreter->Invoke() != kTfLiteOk) {
            error = INVOKE_ERROR;
            reporter->Report("Inference failed");
            }  

            for (size_t i = 0; i < outputSize; i++) {
                y[i] = output->data.f[i];
                }

            return y;
        }
    }
}