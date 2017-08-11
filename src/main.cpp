#include "trie.h"
#include <vector>
#include <termios.h>

class BufferToggle
{
    private:
        struct termios t;

    public:

        /*
         * Disables buffered input
         */

        void off(void)
        {
            tcgetattr(0, &t); //get the current terminal I/O structure
            t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
            tcsetattr(0, TCSANOW, &t); //Apply the new settings
        }


        /*
         * Enables buffered input
         */

        void on(void)
        {
            tcgetattr(0, &t); //get the current terminal I/O structure
            t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
            tcsetattr(0, TCSANOW, &t); //Apply the new settings
        }
};

int main () 
{
	trie t("../words/words.txt");
	std::cout << "Loading..." << std::endl;
	t.initialize();
	std::cout << "Done" << std::endl;
	std::string input;
	BufferToggle bt;
	bt.off();

    termios oldt;
    tcgetattr(0, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &newt);

    std::cout << "Input: " << std::endl;
	for (;;) {

		char c;
		std::cin >> c;
	
		if (c == 127 && input.size() > 0) {
			input.pop_back();
		} else if (c != 127){
			input += c;
		}
		
		if (input.size() == 0) {
			std::cout << "Too Many Results, type more" << std::endl;
		}
		std::vector<std::string>* v = t.get_results(input);

		system("clear");
		std::cout << "Input: " << input << std::endl;
		if (v->size() > 0 && v->size() <= 40) {
			for(int i = 0; i < v->size(); i++) {
				std::cout << v->at(i) << std::endl;
			}
		} else if (v->size() == 0) {
			std::cout << "No results" << std::endl;
		} else if (v->size() > 40) {
			std::cout << "Too Many Results, type more" << std::endl;
		}
		
	}


	bt.on();


}