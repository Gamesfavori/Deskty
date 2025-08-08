#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <string>
#include <unistd.h>

bool check_root(){
    uid_t uid = getuid();
    if(uid==0){
        return 1;
    }
    else{
        return 0;
    }
}


namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    try {
        po::options_description desc("Options");
        desc.add_options()
            ("help,h", "Prints this text")
            ("name,n", po::value<std::string>()->required(), "Application name")
            ("icon,i", po::value<std::string>()->default_value(""), "Path to application icon")
            ("path,p", po::value<std::string>()->default_value(""), "Path to application folder")
            ("exec,e", po::value<std::string>()->required(), "Path to executable file")
            ("type,t", po::value<std::string>()->default_value("Application"))
            ("comment,c", po::value<std::string>()->default_value(""), "Application description")
            ("global,g", po::bool_switch()->default_value(false), "Save .desktop file globally");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 1;
        }

        po::notify(vm);
        
        std::string name = vm["name"].as<std::string>();
        std::string comment = vm["comment"].as<std::string>();
        std::string icon_path = vm["icon"].as<std::string>();
        std::string path = vm["path"].as<std::string>();
        std::string exec = vm["exec"].as<std::string>();
        std::string type = vm["type"].as<std::string>();

        bool global = vm["global"].as<bool>();
        bool isRoot = check_root();


        std::ofstream desktop_file;

        std::string file_path;

        if(global and isRoot){
            file_path = "/usr/share/applications/" + name + ".desktop";
        }
        else if(global){
            std::cerr << "Looks like you forgot sudo before command :)" << std::endl;
            return 1;
        }
        else{
            std::string homedir = getenv("HOME");
            file_path = homedir + "/.local/share/applications/" + name + ".desktop";
        }

        std::cout << file_path;
        desktop_file.open(file_path);

        if(!desktop_file.is_open()){
            std::cerr << "Failed to create .desktop file" << std::endl;
            return 1;
        }

        desktop_file << "[Desktop Entry]" << std::endl;
        desktop_file << "Name=" << name << std::endl;
        desktop_file << "Comment=" << comment << std::endl;
        desktop_file << "Icon=" << icon_path << std::endl;
        desktop_file << "Path=" << path << std::endl;
        desktop_file << "Exec=" << exec << std::endl;
        desktop_file << "Type=" << type << std::endl;

        desktop_file.close();

    } catch(const po::error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}