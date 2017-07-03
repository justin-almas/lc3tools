#include <array>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include <iostream>

#include "tokens.h"

#include "printer.h"
#include "logger.h"

#include "state.h"

#include "instructions.h"
#include "instruction_decoder.h"

#include "simulator.h"

#include "../common/console_printer.h"

int main(int argc, char *argv[])
{
    utils::IPrinter * printer = new utils::ConsolePrinter();
    core::Simulator sim(true, *printer);

    if(argc < 2) {
        //printer->printf(utils::PRINT_TYPE_ERROR, "usage: %s file [file ...]", argv[0]);
    } else {
        for(int i = 1; i < argc; i += 1) {
            try {
                sim.loadObjectFile(argv[i]);
            } catch (std::runtime_error const & e) {std::cout << e.what();}
        }
    }

    delete printer;

    return 0;
}
