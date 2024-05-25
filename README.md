# Error Log Monitoring System

This is a robust solution for tracking and analyzing errors in real-time, ensuring smooth software operation. Leveraging C++ capabilities for efficient error detection, logging, and reporting, this system provides comprehensive insights into application health, facilitating timely debugging and resolution.

## Prerequisites

- g++ compiler installed

- Docker installed

## Running in Local Environment

1. Open Terminal.

2. Clone the repository:

   ```sh

   git clone https://github.com/sagarika-github/Error-Log-Monitoring-System.git

   ```

3. Navigate to the project directory:

   ```sh

   cd Error-Log-Monitoring-System

   ```

4. Compile the code:

   ```sh

   g++ -o code code.cpp

   ```

5. Run the compiled program:

   ```sh

   ./code

   ```

## Running in Docker Environment

1. Open Terminal.

2. Clone the repository:

   ```sh

   git clone https://github.com/sagarika-github/Error-Log-Monitoring-System.git

   ```

3. Navigate to the project directory:

   ```sh

   cd Error-Log-Monitoring-System

   ```

4. Build the Docker image:

   ```sh

   docker build -t error-log-monitoring-system .

   ```

5. Run the Docker container:

   ```sh

   docker run --name error-log-monitoring-system-container error-log-monitoring-system

   ```

## Notes

- Ensure `input.txt` is in the same directory as `code.cpp` before running the program.

- The program writes output to `output.txt` and logs errors to `error.txt` in the same directory.

Feel free to explore and modify the code to suit your needs. Contributions are welcome!
