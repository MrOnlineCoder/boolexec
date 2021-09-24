#include <Lexer.hpp>
#include <Parser.hpp>
#include <Tuple.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::string input;

    const std::string REPL_PROMPT = "> ";

    std::cout << REPL_PROMPT;

    Lexer lexer;
    Parser parser;

    while (std::getline(std::cin, input)) {
        if (input == "/exit") {
            break;
        }

        if (input.length() == 0) {
            std::cout << "\n"
                      << REPL_PROMPT;

            continue;
        }

        lexer.clear();

        if (lexer.scan(input)) {
            if (lexer.getTokens().size() == 0) {
                std::cout << "\n"
                          << REPL_PROMPT;

                continue;
            }

            //lexer.dump();
            parser.clear();

            parser.parse(lexer.getTokens());

            auto root = parser.getRoot();

            //root->dump();

            auto context = parser.buildRuntimeContext();

            auto vars = context.getVariablesNames();

            if (vars.size() > 0) {
                std::string divider = "\n";

                for (auto var : vars) {
                    std::cout << var << " ";
                    divider += "--";
                }

                std::cout << "   F" << divider << "----\n";

                Tuple tuple(
                    vars.size(),
                    context.getK());

                bool wasFinal = false;

                std::size_t tuplesCount = 0;

                do {
                    for (std::size_t vi = 0; vi < vars.size(); vi++) {
                        context.updateVariable(vars[vi], tuple.getDigitAt(vi));
                    }

                    auto result = root->eval(context);

                    tuple.dump();

                    std::cout << " = " << result << "\n";

                    if (tuple.isFinal()) {
                        wasFinal = true;
                    } else {
                        tuple.increment();
                    }

                    tuplesCount++;
                } while (!wasFinal);

                std::cout << "Total " << tuplesCount << " tuples processed\n";
            } else {
                auto result = root->eval(context);

                std::cout << result << "\n";
            }

        } else {
            std::cout << "ERROR: invalid syntax";
        }

        std::cout << "\n"
                  << REPL_PROMPT;
    }

    return 0;
}