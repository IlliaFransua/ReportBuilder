# ReportBuilder

This project generates content for a practice report according to Ukrainian standards. Once the content is created, you
can easily copy it using:

- **Windows:** `Ctrl + A` (select all) and `Ctrl + C` (copy)
- **Mac:** `Command + A` and `Command + C`

Then, paste it into the required file with the title headings of your educational institution.

## Getting Started

### 1. Prerequisites

Ensure that you have the following installed on your system:

#### Git

- **Installation:** Follow the instructions on the [official Git website](https://git-scm.com/).

#### Python

- **Installation:** Download and install Python from the [official Python website](https://www.python.org/).
- **Windows 11 Users:** During installation, check **"Add python.exe to PATH"** to enable command-line usage.

### 2. Cloning the Repository

Open your terminal and run the following commands:

1. **Clone the repository:**
   ```bash
   git clone https://github.com/IlliaFransua/ReportBuilder.git
   ```
2. **Navigate to the project folder:**
   ```bash
   cd ReportBuilder
   ```

### 3. Creating a Virtual Environment

To ensure package dependencies do not interfere with other projects, create and activate a virtual environment.

#### 3.1 Create the Environment

- **On Linux/macOS:**
  ```bash
  python3 -m venv env
  ```
- **On Windows:**
  ```bash
  python -m venv env
  ```

#### 3.2 Activate the Virtual Environment

- **On Linux/macOS:**
  ```bash
  source env/bin/activate
  ```
- **On Windows:**
  ```bash
  env\Scripts\activate
  ```

> **Windows 11 Note:** If you encounter a security policy error, run the following command in an administrator
> PowerShell:
> ```powershell
> Set-ExecutionPolicy RemoteSigned
> ```
> Then, restart the terminal and try activating the environment again.

### 4. Installing Dependencies

With the virtual environment activated, install the required dependencies:

```bash
pip install -r requirements.txt
```

### 5. Running the Project

To execute the main script, run:

```bash
cd ReportBuilder
python practice.py
```

## Documentation

Currently, there is no official documentation available as the project is in the process of being translated to Java.
