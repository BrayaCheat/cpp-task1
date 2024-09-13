# Use an official GCC (GNU Compiler Collection) image
FROM gcc:latest

# Set the working directory in the container
WORKDIR /usr/src/app

# Copy the current directory contents into the container at /usr/src/app
COPY . .

# Compile the C++ code (e.g., main.cpp)
RUN g++ -o output main.cpp

# Run the executable produced by the g++ compiler
CMD ["./output"]
