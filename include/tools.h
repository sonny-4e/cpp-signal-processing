#pragma once 
#include <fstream>
#include <iostream>


void generuj_wniosek(const std::string& tresc) {
    std::ofstream outfile;
    std::string output_file_path = "output/wnioski.txt";

    outfile.open(output_file_path);

    if (outfile.is_open()) {
        outfile << "==========================================" << std::endl;
        outfile << "      RAPORT I WNIOSKI Z LABORATORIUM     " << std::endl;
        outfile << "==========================================" << std::endl;
        outfile << tresc << std::endl;
        outfile.close();
        std::cout << "\n[INFO] Wnioski zostaly zapisane do pliku: " << output_file_path << std::endl;
    }
    else {
        std::cerr << "[BLAD] Nie udalo sie otworzyc pliku do zapisu!" << std::endl;
    }
}