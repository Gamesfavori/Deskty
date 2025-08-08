# **Linux Desktop Entry Creator (Deskty)**

**Deskty** is a command-line utility written in C++ that simplifies the process of creating .desktop files for Linux applications.

### **Features**

* **Easy Configuration**: Create .desktop files using a simple set of command-line flags.  
* **Local and Global Installation**: Easily install a .desktop file for your user only, or use sudo with the \--global flag to install it system-wide for all users.

### **Prerequisites**

To build and run this program, you will need:

* A C++ compiler (like g++).  
* The Boost library, specifically boost::program\_options. On most Debian-based systems (like Ubuntu), you can install it with:
```bash
sudo apt-get install libboost-program-options-dev
```
### **Building**

Navigate to the directory containing the source code and compile it using g++.
```bash
g++ main.cpp -o deskty -lboost_program_options
```
### **How to Use**

After compiling, you can use the deskty executable to create .desktop files.

#### **Available Options**

Options:  
  \-h \[ \--help \]                 Prints this text  
  \-n \[ \--name \] arg             Application name  
  \-i \[ \--icon \] arg             Path to application icon  
  \-p \[ \--path \] arg             Path to application folder  
  \-e \[ \--exec \] arg             Path to executable file  
  \-t \[ \--type \] arg             Application type (default: Application)  
  \-c \[ \--comment \] arg          Application description  
  \-g \[ \--global \]               Save .desktop file globally

#### **Examples**

**1\. Create a local .desktop file**  
This command creates a MyProgram.desktop file in your local applications directory (~/.local/share/applications/).
```bash
./deskty -n "MyProgram" -e "/home/user/bin/myprogram" -c "A simple program" -i "/home/user/images/icon.png"
```

**2\. Create a global .desktop file**  
To install for all users, use the \-g flag and run the command with sudo. This will create the file in /usr/share/applications/.
```bash
sudo ./deskty -n "MyProgram" -e "/usr/bin/myprogram" -c "A simple program" -i "/usr/share/icons/myprogram.png" -g
```
### **License**

This project is licensed under the MIT License. A copy of the license is available in the LICENSE.md file.
