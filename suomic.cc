#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

struct KeywordMapping
{
    std::string suomi;
    std::string c;
};

std::vector<KeywordMapping> mappings = {
    // Reserved words.
    {"aloitus", "main"},
    {"palauta", "return"},
    {"sijoitusoperaattori", "="},
    {"tietue", "struct"},
    {"unioni", "union"},
    {"enumeraattori", "enum"},
    {"nuolioperaattori", "->"},

    // Conditional structures.
    {"jos", "if"},
    {"muuten", "else"},
    {"valitse", "switch"},
    {"tapaus", "case"},
    {"lopeta", "break"},
    {"vakio", "default"},

    // Arithmetic operators.
    {"lisaa_yksi", "++"},
    {"vahenna_yksi", "--"},
    {"yhteenlasku", "+"},
    {"vahennyslasku", "-"},
    {"kertolasku", "*"},
    {"jakolasku", "/"},
    {"jakojaannos", "%"},

    // Comparison operators.
    {"yhta_suuri_kuin", "=="},
    {"pienempi_kuin", "<"},
    {"suurempi_kuin", ">"},
    {"pienempi_tai_yhta_suuri_kuin", "<="},
    {"suurempi_tai_yhta_suuri_kuin", ">="},
    {"erisuuri_kuin", "!="},

    // Logical operators.
    {"ja", "&&"},
    {"tai", "||"},
    {"ei", "!"},
    {"joko_tai", "^"},

    // Data types.
    {"kokonaisluku", "int"},
    {"merkki", "char"},
    {"liukuluku", "double"},
    {"arvoton", "void"}
};

std::string translate_line(const std::string& line)
{
    std::string result = line;
    for (const auto& mapping : mappings)
    {
        size_t pos = 0;
        while ((pos = result.find(mapping.suomi, pos)) != std::string::npos)
        {
            result.replace(pos, mapping.suomi.length(), mapping.c);
            // Move past the replacement.
            pos += mapping.c.length();
        }
    }
    return result;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    const std::string input_filename = argv[1];
    const std::string output_filename = "out/suomic_translated.c";

    std::ifstream input_file(input_filename);
    if (!input_file)
    {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    std::ofstream output_file(output_filename);
    if (!output_file)
    {
        std::cerr << "Error creating output file" << std::endl;
        return 1;
    }

    output_file << "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <time.h>\n#include <math.h>\n\n";
    std::string line;
    while (std::getline(input_file, line))
    {
        output_file << translate_line(line) << std::endl;
    }

    input_file.close();
    output_file.close();

    // Compile the translated C code.
    if (system("gcc out/suomic_translated.c -o out/suomic_translated -lm") == 0)
    {
        std::cout << "Compilation successful. Running the program:" << std::endl;
        system("./out/suomic_translated");
    }
    else
    {
        std::cerr << "Compilation failed." << std::endl;
    }

    return 0;
}
