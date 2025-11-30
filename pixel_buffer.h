#ifndef PIXEL_BUFFER_H
#define PIXEL_BUFFER_H


template <typename T>
class PixelBuffer {
private:
    T* dataPointer;  
    int bufferSize;   

    PixelBuffer(const PixelBuffer&) = delete;
    PixelBuffer& operator=(const PixelBuffer&) = delete;

public:
    PixelBuffer() : dataPointer(nullptr), bufferSize(0) {}
    ~PixelBuffer() {
        clearMemory();
    }

    void resize(int newSize) {
        clearMemory();
        if (newSize > 0) {
            bufferSize = newSize;
            dataPointer = new T[newSize];
        }
    }

    void clearMemory() {
        if (dataPointer != nullptr) {
            delete[] dataPointer;
            dataPointer = nullptr;
        }
        bufferSize = 0;
    }

    T& operator[](int index) { 
        return dataPointer[index]; 
    }
    const T& operator[](int index) const { 
        return dataPointer[index]; 
    }

    T* begin() { 
        return dataPointer; 
    }
    T* end() { 
        return dataPointer + bufferSize; 
    }
    const T* begin() const { 
        return dataPointer; 
    }
    const T* end() const { 
        return dataPointer + bufferSize;
    }
    int getSize() const {
        return bufferSize; 
    }
};

#endif 