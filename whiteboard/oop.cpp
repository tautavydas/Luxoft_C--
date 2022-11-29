#include <cstring>
#include <iostream>

class Reader {
  public:
    virtual void read() = 0;
};

class Writer {
  public:
    virtual void write() = 0;
};


class FileCopier : public Reader, public Writer {
    void read() override {
        std::cout << "FileCopier::read()" << std::endl;
    }
    void write() override {
        std::cout << "FileCopier::write()" << std::endl;
    }
};

void read_file(Reader& copier) {
    copier.read();
}

void write_file(Writer& copier) {
    copier.write();
}

int main() {
    FileCopier file_copier;
    read_file(file_copier);
    write_file(file_copier);
  return 0;
}