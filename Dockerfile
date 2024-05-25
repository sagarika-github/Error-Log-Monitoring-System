# Use Official GCC Compiler Image
FROM gcc:latest

# Copy The Current Directory Contents Into The Container
COPY . /usr/src/app

# Set This As The Working Directory
WORKDIR /usr/src/app

# Compile The C++ Program
RUN g++ -o code code.cpp

# Run The Executable
CMD ["./code"]