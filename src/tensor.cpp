#include <../headers/tensor.h>
#include <cmath>
#include <string.h>

void calculateSize(Tensor* tensor){

    tensor->size = 1;

    for(int i = 0; i < tensor->ndim; i++){
        tensor->size *= tensor->shape[i];
    }
}
void calculateStride(Tensor* tensor) {
    tensor->strides = (int*) malloc(tensor->ndim * sizeof(int));
    if (tensor->strides == NULL) {
        fprintf(stderr, "Could not allocate memory for strides\n");
        exit(1);
    }

    int stride = 1;
    for (int i = tensor->ndim - 1; i >= 0; i--) {
        tensor->strides[i] = stride;
        stride *= tensor->shape[i];
    }
}


Tensor* createTensor(float* data, int* shape, int ndim){

    Tensor* tensor = (Tensor*) malloc(sizeof(Tensor));
    if (tensor == NULL) {
        fprintf(stderr, "Could not allocate memory for Tensor\n");
        exit(1);
    }

    tensor->data = data;
    tensor->shape = (int*) malloc(ndim * sizeof(int));
    if (tensor->shape == NULL) {
        fprintf(stderr, "Could not allocate memory for shape\n");
        free(tensor);
        exit(1);
    }

    for (int i = 0; i < ndim; i++) {
        tensor->shape[i] = shape[i];
    }
    tensor->ndim = ndim;

    calculateSize(tensor);
    calculateStride(tensor);

    return tensor;
}

void freeTensor(Tensor* tensor){
    free(tensor->data);
    free(tensor->shape);
    free(tensor->strides);
    free(tensor);
}

float tensorGetItem(Tensor* tensor, int* indeces){
    int index = 0;
    for (int i = 0; i < tensor->ndim; i++) {
        index += indeces[i] * tensor->strides[i];
    }
    if(index < 0 || index >= tensor->size){
        fprintf(stderr, "Index out of bounds\n");
        return NAN;
    }
    // TODO: add logic to get item from gpu
    return tensor->data[index];
}

void tensorSetItem(Tensor* tensor, int* indeces, float value){
    int index = 0;
    for (int i = 0; i < tensor->ndim; i++) {
        index += indeces[i] * tensor->strides[i];
    }
    // TODO: add logic to set item in gpu
    tensor->data[index] = value;
}

Tensor* add(Tensor* tensor1, Tensor* tensor2){

    if(tensor1->ndim != tensor2->ndim){
        fprintf(stderr, "Tensors must have the same number of dimensions %d and %d for addition\n", tensor1->ndim, tensor2->ndim);
        return NULL;
    }
    if(strcmp(tensor1->device, tensor2->device) != 0){
        fprintf(stderr, "Tensors must be on the same device: %s and %s\n", tensor1->device, tensor2->device);
        return NULL;
    }
    
    int ndim = tensor1->ndim;
    int* shape = (int*) malloc(ndim * sizeof(int));
    if (shape == NULL){
        fprintf(stderr, "Could not allocate memory for shape\n");
        return NULL;
    }
    for (int i = 0; i < ndim; i++) {
        shape[i] = tensor1->shape[i];
    }

    float* resultData = (float*) malloc(tensor1->size * sizeof(float));
    if (resultData == NULL){
        fprintf(stderr, "Could not allocate memory for resultData\n");
        free(shape);
        return NULL;
    }
    //TODO: This code bellow can be separated to support additoin in cpu and gpu

    for (int i = 0; i < tensor1->size; i++) {
        resultData[i] = tensor1->data[i] + tensor2->data[i];
    }

    Tensor* result = createTensor(resultData, shape, ndim);
    free(shape);

    return result;
}