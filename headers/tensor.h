#ifndef TENSOR_H
#define TENSOR_H

#include <string>

extern "C" {
    

typedef struct{
    float* data;
    int* shape;
    int ndim;
    int* strides;
    int size;
    std::string name;
    char* device;
} Tensor;

void calculateStride(Tensor* tensor);
void calculateSize(Tensor* tensor);

Tensor* createTensor(float* data, int* shape, int ndim);

void freeTensor(Tensor* tensor);

float tensorGetItem(Tensor* tensor, int* index);
void tensorSetItem(Tensor* tensor, int* index, float value);

void printTensor(Tensor* tensor);

//TODO: ADD METHODS FOR A TENSOR LIKE RESHAPE, SPLIT, CONCAT
Tensor* add(Tensor* tensor1, Tensor* tensor2);
Tensor* subtract(Tensor* tensor1, Tensor* tensor2);
Tensor* elementwise_multiply(Tensor* tensor1, Tensor* tensor2);
Tensor* divide(Tensor* tensor1, Tensor* tensor2);
Tensor* matmul(Tensor* tensor1, Tensor* tensor2);

Tensor* transpose(Tensor* tensor);
Tensor* reshape(Tensor* tensor, int* shape, int ndim);
}
#endif